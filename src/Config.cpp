/**********************************************************************
* OpenMC2 - An Open Source Re-Implementation of Midnight Club 2
* Copyright (C) 2016  LRFLEW
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#include "Config.hpp"

#define WIN32_LEAN_AND_MEAN
#include <comdef.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <windows.h>

#include "DllHooks/DllHooks.hpp"
#include "Settings.hpp"

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <exception>
#include <iostream>
#include <memory>
#include <string>

static boost::filesystem::path get_documents_path() {
    PWSTR rawPath;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, nullptr, &rawPath)))
        return boost::filesystem::path();
    boost::filesystem::path path(rawPath);
    CoTaskMemFree(rawPath);
    return path;
}

constexpr const char *default_paths[] = {
    ".",
    "C:\\Program Files\\Steam\\steamapps\\common\\Midnight Club 2",
    "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Midnight Club 2",
    "C:\\Program Files\\Rockstar Games\\Midnight Club II",
    "C:\\Program Files (x86)\\Rockstar Games\\Midnight Club II",
    "C:\\Program Files\\Midnight Club 2",
    "C:\\Program Files (x86)\\Midnight Club 2",
};

static boost::filesystem::path try_default_paths() {
    for (const char *path : default_paths) {
        boost::filesystem::path folder(path);
        if (boost::filesystem::is_directory(folder) &&
            boost::filesystem::is_regular_file(folder / config_assets_name))
            return folder;
    }
    return boost::filesystem::path();
}

constexpr LPCWSTR InfoBoxTitle = L"OpenMC2";
constexpr LPCWSTR InfoBoxMessage = L"\
OpenMC2 requires Midnight Club 2 to be installed to work.\n\
Please select the folder where Midnight Club 2 was installed.";
constexpr LPCWSTR BadDirMessage = L"\
Unable to find game assets.\n\
Please select the folder where Midnight Club 2 was installed.";

static boost::filesystem::path ask_game_path() {
    HRESULT res;
    int button;
    boost::filesystem::path path;

    if (SUCCEEDED(res = CoInitializeEx(nullptr,
        COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) {

        button = MessageBox(nullptr, InfoBoxMessage, InfoBoxTitle, MB_OKCANCEL);

        while (SUCCEEDED(res) && button == IDOK) {
            IFileDialog *dialog;
            if (SUCCEEDED(res = CoCreateInstance(CLSID_FileOpenDialog, nullptr,
                CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&dialog)))) {

                FILEOPENDIALOGOPTIONS opt;
                if (SUCCEEDED(res = dialog->GetOptions(&opt))) {
                    if (SUCCEEDED(res = dialog->SetOptions(opt | FOS_PICKFOLDERS | FOS_DONTADDTORECENT))) {

                        if (SUCCEEDED(res = dialog->Show(nullptr))) {
                            IShellItem *item;
                            if (SUCCEEDED(res = dialog->GetResult(&item))) {

                                LPWSTR pathstr;
                                if (SUCCEEDED(res = item->GetDisplayName(SIGDN_FILESYSPATH, &pathstr))) {
                                    path = pathstr;
                                    if (boost::filesystem::is_regular_file(path / config_assets_name)) button = 0;
                                    else path.clear(), button = MessageBox(nullptr, BadDirMessage, InfoBoxTitle, MB_OKCANCEL);
                                }
                                item->Release();
                            }
                        } else if (res == HRESULT_FROM_WIN32(ERROR_CANCELLED)) {
                            dialog->Release();
                            CoUninitialize();
                            std::exit(0);
                        }
                    }
                }
                dialog->Release();
            }
        }
        CoUninitialize();
    }

    if (FAILED(res)) throw _com_error(res);
    if (button != 0) std::exit(0);

    return path;
}

static boost::filesystem::path get_config_path() {
    return get_documents_path() / "OpenMC2" / "OpenMC2.config";
}

template<class T>
static void set_default(config_tree &tree, bool &modified, const config_tree::key_type &key, T value) {
    if (!tree.get_child_optional(key)) tree.put(key, value), modified = true;
}

static bool set_defaults(config_tree &tree) {
    bool modified = false;
    set_default(tree, modified, "gamepath", "");
    set_default(tree, modified, "window", false);
    set_default(tree, modified, "assets", "assets_p.dat");

    boost::optional<config_tree &> settings = tree.get_child_optional("settings");
    if (!settings) settings = tree.put_child("settings", { });
    modified |= glo_Settings.tree_set_defaults(settings.get());

    set_default(tree, modified, "net.main", "");
    set_default(tree, modified, "net.master", "");
    set_default(tree, modified, "net.natneg1", "");
    set_default(tree, modified, "net.natneg2", "");

    return modified;
}

// The default stream-translator adds redundant quotes
template <typename Source>
struct path_translator {
    typedef Source internal_type;
    typedef boost::filesystem::path external_type;
    inline boost::optional<external_type> get_value(const internal_type &v) const { return external_type(v); }
    inline boost::optional<internal_type> put_value(const external_type &v) const { return v.string<Source>(); }
};
constexpr path_translator<config_tree::data_type> config_tree_path_translator;

void load_config() {
    config_tree config;
    boost::filesystem::path path(get_config_path());
    if (boost::filesystem::is_regular_file(path))
        boost::property_tree::read_info(boost::filesystem::ifstream(path), config);
    bool modified = set_defaults(config);

    if (!boost::filesystem::is_directory(path.parent_path()))
        if (!boost::filesystem::create_directory(path.parent_path())) throw std::exception();
    if (modified) boost::property_tree::write_info(boost::filesystem::ofstream(path), config);

    glo_windowed_mode = config.get<bool>("window");
    config_assets_name = config.get<std::string>("assets");

    config_gamepath = config.get<boost::filesystem::path>("gamepath", config_tree_path_translator);
    if (config_gamepath.empty()) {
        config_gamepath = try_default_paths();
        if (config_gamepath.empty()) config_gamepath = ask_game_path();
        config.put("gamepath", config_gamepath, config_tree_path_translator);
        boost::property_tree::write_info(boost::filesystem::ofstream(path), config);
    }

    glo_Settings.tree_load_settings(config.get_child("settings"));

    net_config.main = config.get<std::string>("net.main");
    net_config.master = config.get<std::string>("net.master");
    net_config.natneg1 = config.get<std::string>("net.natneg1");
    net_config.natneg2 = config.get<std::string>("net.natneg2");

    if (!net_config.main.empty()) glo_6C4C74 = net_config.main.c_str(); // ms0
    if (!net_config.master.empty()) safe_strncpy(glo_6C4EA0, net_config.master.c_str(), sizeof(glo_6C4EA0)); // master
    if (!net_config.natneg1.empty()) glo_6738A0 = net_config.natneg1.c_str(); // natneg1
    if (!net_config.natneg2.empty()) glo_6738A4 = net_config.natneg2.c_str(); // natneg2

    // This should be set via the debug options, but that doesn't work correctly as-is.
    boost::filesystem::current_path(config_gamepath);
    AddDllHooks(config_gamepath);
}

void save_config() {
    config_tree config;

    config.put("gamepath", config_gamepath, config_tree_path_translator);
    config.put("window", glo_windowed_mode);
    config.put("assets", config_assets_name);

    glo_Settings.tree_set_settings(config.put_child("settings", { }));

    config.put("net.main", net_config.main);
    config.put("net.master", net_config.master);
    config.put("net.natneg1", net_config.natneg1);
    config.put("net.natneg2", net_config.natneg2);

    boost::filesystem::path path(get_config_path());
    boost::property_tree::write_info(boost::filesystem::ofstream(path), config);
}

boost::filesystem::path config_gamepath;
std::string config_assets_name;

net_config_t net_config;

MC2_DEF_GLOBAL(glo_windowed_mode, 0x00858370);

MC2_DEF_GLOBAL(glo_6738A0, 0x006738A0);
MC2_DEF_GLOBAL(glo_6738A4, 0x006738A4);
MC2_DEF_GLOBAL(glo_6C4C74, 0x006C4C74);
MC2_DEF_GLOBAL(glo_6C4EA0, 0x006C4EA0);
