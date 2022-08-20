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
#include "Lib/src/core/scene.hpp"

#include <SDL2/SDL_image.h>

bool Scene::Init(const std::string &backgroundImagePath)
{
    IMG_Init(IMG_INIT_PNG);
    LoadBackgroundImage(backgroundImagePath);
}

bool LoadPNGBackground(const std::string &filename)
{
    SDL_Surface *imageSurface = IMG_Load(filename.c_str());
}

void Scene::Display()
{
    background.Render();
    for (const auto &[uuid, object] : objects)
    {
        object->Display();
    }
}
