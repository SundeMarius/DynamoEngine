// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of CannonLaunch.
//
// CannonLaunch is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CannonLaunch is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CannonLaunch.  If not, see <http://www.gnu.org/licenses/>.
#include "CannonLaunch.hpp"

#include "Lib/src/core/entrypoint.hpp"
#include "Lib/src/core/text.hpp"

Application *CreateApplication(ApplicationCommandLineArguments args)
{
    ApplicationSpecification spec = {
        .name = "Cannon Launch!",
        .RenderFPS = true,
        .args = args,
    };
    ResourceSpecification rspec = {
        .fontFile = "assets/fonts/open-sans/OpenSans-Regular.ttf",
        .backgroundTextureFile = "assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_1/game_background_1.png",
    };
    return new CannonLaunchGame(spec, rspec);
}

void CannonLaunchGame::OnEvent(SDL_Event *event)
{
}

void CannonLaunchGame::Update(const Timestep &dt)
{
}
