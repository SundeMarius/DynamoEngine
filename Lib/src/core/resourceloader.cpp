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
#include "Lib/src/core/resourceloader.hpp"

#include <SDL2/SDL_image.h>

void ResourceLoader::Init(SDL_Renderer *renderer, Log &log)
{
    // Initialize texture settings
    IMG_Init(IMG_INIT_PNG);

    // Load  global font
    if (TTF_Init() < 0)
    {
        log.Fatal("SDL_ttf failed to initialize");
    }
    log.Debug("Loading font file " + spec.fontFile);
    InitializeFont();
    log.Trace("Font initialized");

    // Load background
    if (!spec.backgroundTextureFile.empty())
    {
        log.Trace("Loading background texture from " + spec.backgroundTextureFile);
        LoadBackgroundTexture(renderer);
        log.Trace("Background texture initialized");
    }
}

void ResourceLoader::InitializeFont()
{
    font = std::make_shared<Font>(spec.fontFile);
}
void ResourceLoader::LoadBackgroundTexture(SDL_Renderer *renderer)
{
    backgroundTexture = std::make_shared<Texture>(spec.backgroundTextureFile, nullptr, renderer);
}