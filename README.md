# OpenMC2

[![Join the chat at https://gitter.im/LRFLEW/OpenMC2](https://badges.gitter.im/LRFLEW/OpenMC2.svg)](https://gitter.im/LRFLEW/OpenMC2?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

An Open Source Re-Implementation of Midnight Club 2

This project is a bottom-up rewrite of Midnight Club 2,
using the original binary in place of not-yet-implemented functions,
to allow for large-scale bug fixing and feature implementing.

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

### Linux and macOS

Native support for Linux and macOS is planned for the future, but because of how
the project is developed, a native binary will not be possible for a while.
In the mean time, **using Wine is supported** on Linux and macOS, and is the
recommended way of using OpenMC2 on those platforms.

## Licence

The source code provided in this repository for
OpenMC2 is licenced under the [GNU General Public License version 3](https://www.gnu.org/licenses/gpl.html).

## Other Open-Game Projects

Below is a list of similar projects that I know of and their respective base games:

 * [OpenRCT2](https://github.com/OpenRCT2/OpenRCT2) - RollerCoaster Tycoon 2
 * [OpenTTD](https://www.openttd.org/) - Transport Tycoon Deluxe
 * [OpenRW](https://github.com/rwengine/openrw) - Grand Theft Auto III
 * [OpenMW](https://openmw.org/) - The Elder Scrolls III: Morrowind
 * [openage](https://github.com/SFTtech/openage) - Age of Empires II
 * [OpenRA](https://github.com/OpenRA/OpenRA) - Command & Conquer: Red Alert
 * [OpenXcom](http://openxcom.org) - UFO: Enemy Unknown (aka, X-COM: UFO Defense)
 * [Freeciv](http://www.freeciv.org) - Civilization II

There is also the [Wikipedia page for open source games](https://en.wikipedia.org/wiki/List_of_open-source_video_games).
