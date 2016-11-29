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

#include "unk8600F8.hpp"

#include <string>
#include <boost/lexical_cast.hpp>

#include "..\Memory.hpp"

// Remove from Linked List?
void unk_8600F8::loc_611DC0() {
    unk_8600F8 **x;
    for (x = &glo_8600E8; *x != nullptr && *x != this; x = &(*x)->unk14);
    *x = this->unk14;
    this->unk14 = nullptr;
}

unk_612150 *unk_8600F8::sub_6124A0(const char *a) {
    if (this->entries == nullptr) {
        return nullptr;
    }

    int index = get_entry_index(a);
    
    for (hash_map_entry *entry = this->entries[index]; entry != nullptr; entry = entry->next) {
        if (std::strcmp(entry->name, a) == 0) return entry->value;
    }

    return nullptr;
}

// mc2: 0x00611E70
uint32_t unk_8600F8::get_entry_index(const char *a) {
    if (this->entries == nullptr) {
        this->entries = new hash_map_entry*[this->max_entries];
        std::memset(this->entries, 0, this->max_entries * 4);
    }

    uint32_t hash = 0;
    for (; *a != '\0'; ++a) {
        hash <<= 4;
        hash += *a;
        if (hash & 0xF0000000) {
            hash ^= (hash & 0xF0000000) | ((hash & 0xF0000000) >> 24);
        }
    }
    return hash % this->max_entries;
}

bool unk_8600F8::sub_612150(const char *a, unk_612150 *b) {
    int index = get_entry_index(a);

    for (hash_map_entry *entry = this->entries[index]; entry != nullptr; entry = entry->next) {
        if (std::strcmp(entry->name, a) == 0) return false;
    }

    if (this->unk02 != 0) {
        this->entries[index] = sub_611DF0(a, b, this->entries[index]);
        this->num_entries++;
        return true;
    }

    hash_map_entry *newEntry = new hash_map_entry(mc2_strdup(a), b, this->entries[index]);

    this->entries[index] = newEntry;
    this->num_entries++;

    if (this->num_entries <= this->max_entries) {
        return true;
    }
    
    if (glo_679778 == 0)
        return true;

    uint32_t esi_store = glo_8602C8;
    glo_8602C8 = 5;
    // Increase num entry size?
    sub_6125A0(this->max_entries * 4);

    glo_8602C8 = esi_store;

    return true;
}

bool unk_8600F8::sub_611FE0(indexed_map_entry *index_entry) {
    if (this->entries == nullptr)
        return false;

    hash_map_entry *entry = sub_611F60(0);

    if (entry == nullptr)
        return false;

    index_entry->index = 0;
    index_entry->name = entry->name;
    index_entry->value = entry->value;
    return true;
}

unk_8600F8::hash_map_entry *unk_8600F8::sub_611F60(int32_t entryIndex) {
    if (entryIndex < 0 || entryIndex >= this->num_entries)
        return nullptr;

    std::int32_t hashIndex = 0;
    hash_map_entry *entry = nullptr;
    while (entry == nullptr) {
        if (hashIndex >= this->max_entries)
            return nullptr;
        entry = this->entries[hashIndex++];
    }

    for (std::int32_t currentIndex = 0; currentIndex < entryIndex; ++currentIndex) {
        entry = entry->next;
        
        while (entry == nullptr) {
            if (hashIndex >= this->max_entries)
                return nullptr;
            entry = this->entries[hashIndex++];
        }
    }

    return entry;
}

bool unk_8600F8::sub_612020(indexed_map_entry *index_entry) {
    hash_map_entry *entry = sub_611F60(index_entry->index + 1);

    if (entry == nullptr)
        return false;

    index_entry->index++;
    index_entry->name = entry->name;
    index_entry->value = entry->value;
    return true;
}

bool sub_612E10(const char* key) {
    unk_612150 *result = glo_8600F8.sub_6124A0(key);
    return result != nullptr;
}

bool sub_612E30(const char *key, std::uint32_t index, int32_t * decimal_value) {
    unk_612150 *entry = glo_8600F8.sub_6124A0(key);

    if (entry == nullptr || index >= entry->count)
        return false;

    *decimal_value = boost::lexical_cast<int32_t>(entry->args[index]);
    return true;
}
