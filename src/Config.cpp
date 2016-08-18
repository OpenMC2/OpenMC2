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
#include <Shlobj.h>
#include <Shobjidl.h>
#include <Windows.h>

#include <BinkStub.hpp>
#include <MssStub.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <exception>
#include <iostream>
#include <memory>
#include <string>

typedef boost::property_tree::iptree config_tree;

static boost::filesystem::path get_documents_path() {
    PWSTR rawPath;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, nullptr, &rawPath)))
        return boost::filesystem::path();
    boost::filesystem::path path(rawPath);
    CoTaskMemFree(rawPath);
    return path;
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
                                    if (boost::filesystem::is_regular_file(path / "assets_p.dat")) button = 0;
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

inline boost::filesystem::path get_config_path() {
    return get_documents_path() / "OpenMC2" / "OpenMC2.config";
}

static config_tree get_defaults() {
    config_tree tree;
    tree.put("gamepath", "");
    tree.put("window", false);
    return tree;
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
    config_tree config = get_defaults();

    boost::filesystem::path path(get_config_path());
    if (boost::filesystem::is_regular_file(path))
        boost::property_tree::read_info(path.string(), config);

    if (!boost::filesystem::is_directory(path.parent_path()))
        if (!boost::filesystem::create_directory(path.parent_path())) throw new std::exception();
    boost::property_tree::write_info(path.string(), config);

    boost::filesystem::path gamepath = config.get<boost::filesystem::path>("gamepath", config_tree_path_translator);
    if (gamepath.empty()) {
        gamepath = ask_game_path();
        config.put("gamepath", gamepath, config_tree_path_translator);
        boost::property_tree::write_info(path.string(), config);
    }

    // This should be set via the debug options, but that doesn't work correctly as-is.
    boost::filesystem::current_path(gamepath);

    BinkStubInit(gamepath / "binkw32.dll");
    MssStubInit(gamepath / "mss32.dll");

    glo_windowed_mode = config.get<bool>("window");
}
