# OpenMC2

[![Join the chat at https://gitter.im/LRFLEW/OpenMC2](https://badges.gitter.im/LRFLEW/OpenMC2.svg)](https://gitter.im/LRFLEW/OpenMC2?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

An Open Source Re-Implementation of Midnight Club 2

This project will rewrite the code of Midnight Club 2,
using the original binary in place of not-yet-implemented functions,
to allow for large-scale bug fixing and feature implementing.

This project is similar to the [OpenRCT2](https://github.com/OpenRCT2/OpenRCT2)
and [OpenTTD](https://www.openttd.org/en/) projects that came before it.

## Building

This project currently only supports building on
Visual Studio 2015 Update 2 or later.
Open up the OpenMC2.sln file, and run a "Rebuild".
The debugging currently expects Midnight Club 2 to be installed with Steam
with Steam installed to the default location.

## Running

To run the game, you need to first have Midnight Club 2 installed.
The easiest way to get the game to run is to place both `OpenMC2.exe`
and `OpenMC2.dll` in the same directory as `mc2.exe`. You can then
launch OpenMC2 from the directory, or use a shortcut to launch the game.

## Licence

The source code provided in this repository for
OpenMC2 is licenced under the [GNU General Public License version 3](https://www.gnu.org/licenses/gpl.html).
