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
#pragma once

#include "DynamoEngine/src/core/surface.hpp"
#include "DynamoEngine/src/assets/asset.hpp"

#include <SDL2/SDL.h>

class Texture : public Asset
{
public:
    Texture() = default;
    Texture(Window &window, Surface *surface);
    ~Texture();

    void LoadFromFile(Window &window, const std::string &filePath) override;

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    SDL_Texture *GetSDLTexture() const { return mTexture; }
    SDL_Renderer *GetSDLRenderer() const { return window->GetSDLRenderer(); }

private:
    Window *window;
    SDL_Texture *mTexture;
    int width;
    int height;
};