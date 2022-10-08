// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of DynamoEngine Engine.
//
// DynamoEngine Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DynamoEngine Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DynamoEngine Engine.  If not, see <http://www.gnu.org/licenses/>.
#include "DynamoEngine/src/core/surface.hpp"

#include <stdexcept>

Surface::Surface(SDL_Surface *surface) : mSurface(surface)
{
    if (surface)
    {
        width = surface->w;
        height = surface->h;
    }
}

Surface::Surface(const SDL_Rect &frame, const SDL_Color &color) : width(frame.w), height(frame.h)
{
    mSurface = SDL_CreateRGBSurface(0, frame.w, frame.h, 32, 0, 0, 0, 0);
    if (SDL_FillRect(mSurface, NULL, SDL_MapRGBA(mSurface->format, color.r, color.g, color.b, color.a)) < 0)
    {
        throw std::runtime_error("Failed to create surface with given frame and color");
    }
}

Surface::~Surface()
{
    SDL_FreeSurface(mSurface);
}
