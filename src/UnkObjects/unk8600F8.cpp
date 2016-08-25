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

// Remove from Linked List?
void unk_8600F8::loc_611DC0() {
    unk_8600F8 **x;
    for (x = &glo_8600E8; *x != nullptr && *x != this; x = &(*x)->unk14);
    *x = this->unk14;
    this->unk14 = nullptr;
}

unk_612150 *unk_8600F8::sub_6124A0(const char *a) {
    if (this->entries == NULL) {
        return nullptr;
    }

    int index = get_entry_index(a);
    
    if (this->entries[index] == nullptr) {
        return nullptr;
    }

    hash_map_entry *entry = this->entries[index];
    
    while (entry != nullptr) {
        char *entryName = entry->name;

        const char* a_p = a;
        while (*a_p == *entryName) {

            if (*entryName == '\0') {
                return entry->value;
            }
            entryName++;
            a_p++;
        }
        entry = entry->next;
    }
    return nullptr;
}

// mc2: 0x00611E70
uint32_t unk_8600F8::get_entry_index(const char *a) {
    if (this->entries == nullptr) {
        this->entries = (hash_map_entry**)MC2_MALLOC(this->max_entries * 4);
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

    if (this->entries[index] != NULL) {
        hash_map_entry *inital_entry = this->entries[index];
        hash_map_entry *entry = inital_entry;

        while (entry != nullptr) {
            char *entryName = entry->name;

            const char *a_p = a;
            while (*a_p == *entryName) {
                if (*entryName == '\0') {
                    return false;
                }
                entryName++;
                a_p++;
            }
            entry = entry->next;
        }
    }

    if (this->unk02 != 0) {
        this->entries[index] = sub_611DF0(a, b, this->entries[index]);
        this->num_entries++;
        return true;
    }

    hash_map_entry *newEntry = (hash_map_entry*)MC2_MALLOC(sizeof(hash_map_entry));
    if (newEntry != nullptr) {
        newEntry->name = MC2_STRDUP(a);
        newEntry->value = b;
        newEntry->next = this->entries[index];
    }

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

bool unk_8600F8::sub_611FE0(uint32_t *eax) {
    if (this->entries == nullptr)
        return false;

    hash_map_entry *entry = sub_611F60(0);

    if (entry == nullptr)
        return false;

    eax[0] = 0;
    eax[1] = (uint32_t)entry->name;
    eax[2] = (uint32_t)entry->value;
    return true;
}

hash_map_entry *unk_8600F8::sub_611F60(int32_t entryIndex) {
    if (entryIndex == -1)
        return nullptr;

    int hashEntryIndex = -1;
    int numFoundEntries = -1;
    int edx = 0;
    int esi = 0;
    bool entryFound = false;
    hash_map_entry *entry = nullptr;

    hash_map_entry *lastFound = nullptr;

    do {
        if (hashEntryIndex >= (int)this->max_entries)
            return nullptr;
        if (entryFound) {
            entryFound = false;

            entry = entry->next;

            if (entry == nullptr) {
                continue;
            }

            if (entry == lastFound) {
                continue;
            }

            entryFound = true;
            numFoundEntries++;
            continue;
        }

        if (hashEntryIndex >= (int)(this->max_entries - 1))
            return nullptr;

        entry = this->entries[++hashEntryIndex];

        if (entry == nullptr)
            continue;

        entryFound = true;
        lastFound = entry;
        numFoundEntries++;
    } while (entryIndex != numFoundEntries);

    return entry;
}

bool unk_8600F8::sub_612020(uint32_t *eax) {
    hash_map_entry *entry = sub_611F60(eax[0] + 1);

    if (entry == nullptr)
        return false;

    eax[0]++;
    eax[1] = (uint32_t)entry->name;
    eax[2] = (uint32_t)entry->value;
    return true;
}

bool sub_612E10(const char* key) {
    unk_612150 *result = glo_8600F8.sub_6124A0(key);
    return result != nullptr;
}

bool sub_612E30(const char *key, std::uint32_t index, int32_t * decimal_value) {
    unk_612150 *entry = glo_8600F8.sub_6124A0(key);

    if (entry == nullptr)
        return false;

    if (index >= entry->count)
        return false;

    *decimal_value = sub_61A5DC(entry->args[index]);
    return true;
}
