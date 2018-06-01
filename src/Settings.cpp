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

#include "Settings.hpp"

#include <sstream>

#include <boost/property_tree/ptree.hpp>

#include "UnkObjects/unk613330.hpp"
#include "UnkObjects/unk616420.hpp"
#include "Game.hpp"

//mc2: 0x0053B990
Settings::Settings() {
    set_defaults();
    this->requires_saving = false;
    this->unk71 = false;
}

//mc2: 0x0053B930
void Settings::set_defaults() {
    this->unk00 = 0;
    set_audio_driver("Miles Fast 2D Positional Audio");
    set_screen_width(640);
    set_screen_height(480);
    set_screen_depth(32);
    set_draw_distance(500);
    set_environment_mapping(1);
    set_reflections(1);
    set_shadows(1);
    set_fullscreen_effects(1);
    this->language_id = 0;
}

template <typename Ch, typename Traits, typename Alloc, typename A, typename B>
struct pair_translator {
    typedef std::basic_string<Ch, Traits, Alloc> internal_type;
    typedef std::pair<A, B> external_type;
    typedef boost::property_tree::customize_stream<Ch, Traits, A> customizeA;
    typedef boost::property_tree::customize_stream<Ch, Traits, B> customizeB;

    inline boost::optional<external_type> get_value(const internal_type &v) const {
        std::basic_istringstream<Ch, Traits, Alloc> stream(v);
        external_type value;
        customizeA::extract(stream, value.first);
        customizeB::extract(stream, value.second);
        if (stream.fail() || stream.bad() || stream.get() != Traits::eof()) return { };
        return value;
    }
    inline boost::optional<internal_type> put_value(const external_type &v) const {
        std::basic_ostringstream<Ch, Traits, Alloc> stream;
        customizeA::insert(stream, v.first);
        stream << " ";
        customizeB::insert(stream, v.second);
        if (stream) return stream.str();
        else return { };
    }
};
template <typename Source, typename A, typename B>
struct get_pair_translator {
    typedef pair_translator<typename Source::value_type,
        typename Source::traits_type, typename Source::allocator_type, A, B> type;
};
constexpr get_pair_translator<config_tree::data_type, std::int32_t, std::int32_t>::type config_tree_input_translator;

template<class T>
static void tree_set_default(config_tree &tree, bool &modified, const config_tree::key_type &key, T value) {
    if (!tree.get_child_optional(key)) tree.put(key, value), modified = true;
}
template<class T, class Tr>
static void tree_set_default(config_tree &tree, bool &modified, const config_tree::key_type &key, T value, Tr tr) {
    if (!tree.get_child_optional(key)) tree.put(key, value, tr), modified = true;
}

bool Settings::tree_set_defaults(config_tree &tree) {
    bool modified = false;
    tree_set_default(tree, modified, "audio_driver", "Miles Fast 2D Positional Audio");
    tree_set_default(tree, modified, "screen_width", 640);
    tree_set_default(tree, modified, "screen_height", 480);
    tree_set_default(tree, modified, "screen_depth", 32);
    tree_set_default(tree, modified, "draw_distance", 500);
    tree_set_default(tree, modified, "environment_mapping", true);
    tree_set_default(tree, modified, "reflections", true);
    tree_set_default(tree, modified, "shadows", true);
    tree_set_default(tree, modified, "fullscreen_effects", true);
    tree_set_default(tree, modified, "input_device", input_t{ 1, -1 }, config_tree_input_translator);
    tree_set_default(tree, modified, "language", "en");
    return modified;
}

void Settings::tree_load_settings(config_tree &tree) {
    set_audio_driver(tree.get<std::string>("audio_driver").c_str());
    set_screen_width(tree.get<int>("screen_width"));
    set_screen_height(tree.get<int>("screen_height"));
    set_screen_depth(tree.get<int>("screen_depth"));
    set_draw_distance(tree.get<int>("draw_distance"));
    set_environment_mapping(tree.get<bool>("environment_mapping"));
    set_reflections(tree.get<bool>("reflections"));
    set_shadows(tree.get<bool>("shadows"));
    set_fullscreen_effects(tree.get<bool>("fullscreen_effects"));
    set_input_device(tree.get<input_t>("input_device", config_tree_input_translator));
    set_language_id(get_language_id(tree.get<std::string>("language").c_str()));
}

void Settings::tree_set_settings(config_tree &tree) {
    tree.put<std::string>("audio_driver", this->audio_driver);
    tree.put<int>("screen_width", this->screen_width);
    tree.put<int>("screen_height", this->screen_height);
    tree.put<int>("screen_depth", this->screen_depth);
    tree.put<int>("draw_distance", this->draw_distance);
    tree.put<bool>("environment_mapping", this->environment_mapping);
    tree.put<bool>("reflections", this->reflections);
    tree.put<bool>("shadows", this->shadows);
    tree.put<bool>("fullscreen_effects", this->fullscreen_effects);
    tree.put<input_t>("input_device", this->input_device, config_tree_input_translator);
    tree.put<std::string>("language", get_language_string(this->language_id));
}

//mc2: 0x0053B6A0
bool Settings::load_settings() {
    FileHandler::FuncTable *fileFuncs = glo_679810;

    glo_679810 = &glo_679884;

    FileHandler* file = glo_860220->vir_1C("userdata\\options.cfg", "", 0, 1);
    if (file == nullptr) {
        file = glo_860220->vir_1C("userdata\\default.cfg", "", 0, 1);
    }

    glo_679810 = fileFuncs;
    if (file == nullptr) {
        return false;
    }

    unk_616420 option("options", file);
    char buffer[256];
    if (option.sub_6154D0("AudioDriver:", 1)) {
        if (option.sub_47C920(buffer, 0xFF) >= 0) {
            buffer[255] = '\0';
            set_audio_driver(buffer);
        }
    }

    if (option.sub_6154D0("ScreenWidth:", 1)) {
        set_screen_width(option.read_integer());
    }

    if (option.sub_6154D0("ScreenHeight:", 1)) {
        set_screen_height(option.read_integer());
    }

    if (option.sub_6154D0("ScreenDepth:", 1)) {
        set_screen_depth(option.read_integer());
    }

    if (option.sub_6154D0("DrawDistance:", 1)) {
        set_draw_distance(option.read_integer());
    }

    if (option.sub_6154D0("EnvironmentMapping:", 1)) {
        set_environment_mapping(option.read_integer());
    }

    if (option.sub_6154D0("Reflections:", 1)) {
        set_reflections(option.read_integer());
    }

    if (option.sub_6154D0("Shadows:", 1)) {
        set_shadows(option.read_integer());
    }

    if (option.sub_6154D0("FullScreenEffects:", 1)) {
        set_fullscreen_effects(option.read_integer());
    }

    if (option.sub_6154D0("Language:", 1)) {
        if (option.sub_47C920(buffer, 0xFF) >= 0) {
            buffer[255] = '\0';
            int languageId = get_language_id(buffer);
            if (languageId != -1) {
                set_language_id(languageId);
            }
        }
    }

    if (option.sub_6154D0("InputDevice:", 1)) {
        int32_t device_1 = option.read_integer();
        int32_t device_2 = option.read_integer();
        set_input_device(device_1, device_2);
    }

    set_require_saving(false);

    file->sub_617FB0();
    return true;
}

//mc2: 0x0053B370
bool Settings::save_settings_force() {
    FileHandler::FuncTable *fileFuncs = glo_679810;
    glo_679810 = &glo_679884;
    FileHandler* file = glo_860220->vir_20("userdata\\options.cfg", "", 0);
    glo_679810 = fileFuncs;

    if (file == nullptr) {
        return false;
    }

    unk_616420 option("options", file);

    sub_615740(&option, "Audio Driver: %s\n", this->get_audio_driver());
    sub_615740(&option, "ScreenWidth: %d\n", this->get_screen_width());
    sub_615740(&option, "ScreenHeight: %d\n", this->get_screen_height());
    sub_615740(&option, "ScreenDepth: %d\n", this->get_screen_depth());
    sub_615740(&option, "DrawDistance: %d\n", this->get_draw_distance());
    sub_615740(&option, "EnvironmentMapping: %d\n", this->get_environment_mapping());
    sub_615740(&option, "Reflections: %d\n", this->get_reflections());
    sub_615740(&option, "Shadows: %d\n", this->get_shadows());
    sub_615740(&option, "FullscreenEffects: %d\n", this->get_fullscreen_effects());
    const char *language = get_language_string(this->language_id);
    if (language != nullptr) {
        sub_615740(&option, "Language: %s\n", language);
    }
    sub_615740(&option, "InputDevice: %d %d\n", this->get_input_device_1(), this->get_input_device_2());

    set_require_saving(false);
    
    file->sub_617FB0();
    return true;
}

MC2_DEF_GLOBAL(glo_Settings, 0x006C3250);

AUTO_HOOK_MEMBER_X86(0x0053B510, &Settings::save_settings);
