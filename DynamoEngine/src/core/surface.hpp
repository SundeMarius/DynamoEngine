// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of DynamoEngine.
//
// DynamoEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DynamoEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DynamoEngine.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include <string>

#include <SDL2/SDL.h>

class Surface
{
public:
    Surface() = default;
    Surface(SDL_Surface *surface);
    Surface(const SDL_Rect &frame, const SDL_Color &color);
    ~Surface();

    SDL_Surface *GetSDLSurface() const { return mSurface; }

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

private:
    SDL_Surface *mSurface = nullptr;
    int width = 0;
    int height = 0;
};