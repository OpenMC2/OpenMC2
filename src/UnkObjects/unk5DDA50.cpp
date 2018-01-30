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

#include "unk5DDA50.hpp"

#include <cassert>
#include <cmath>

constexpr float pi_256 = 0.01227184664f; // Pi / 256

unk_5DDA50::unk_5DDA50() {
    // sine is computed slightly differently,
    // which causes an error of approx. +-2.3e-7.
    // It should be close enough, though.
    for (int i = 0; i < glo_857880.size(); ++i) {
        glo_857880[i] = std::sin(i * pi_256);
    }
}

std::array<float, 641> &glo_857880 = MC2_GLOBAL<std::array<float, 641>>(0x00857880);

static unk_5DDA50 var_858284; // calls constructor on launch
