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

#include "Lib/src/core/window.hpp"
#include "Lib/src/assets/surface.hpp"

#include <SDL2/SDL.h>

class Sprite
{
public:
    Sprite(Window &window, Surface *surface, SDL_Rect spriteBox);
    virtual ~Sprite();

    void Rotate(float angle);

    void Move(const SDL_Point &newPosition);

    void Render();

private:
    SDL_Renderer *mRenderer;
    SDL_Texture *mTexture;

    Surface mSurface;

    SDL_Rect spriteBox;
};