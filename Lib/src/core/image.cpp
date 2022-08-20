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
#include "image.hpp"

#include <SDL2/SDL_image.h>

Image::Image(const std::string &imagePath, SDL_Rect imageDescription, SDL_Renderer *renderer) : mRenderer(renderer)
{
    mTexture = IMG_LoadTexture(renderer, imagePath.c_str());
    mImageBox = imageDescription;
}

Image::~Image()
{
    SDL_DestroyTexture(mTexture);
}

void Image::Render()
{
    SDL_RenderCopy(mRenderer, mTexture, NULL, &mImageBox);
}
