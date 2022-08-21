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
#include "Lib/src/core/texture.hpp"

#include <SDL2/SDL_image.h>

// TODO: exceptions
Texture::Texture(const std::string &texturePath, SDL_Rect *textureBox, SDL_Renderer *renderer)
{
    mRenderer = renderer;
    mTextureBox = textureBox;
    mTexture = IMG_LoadTexture(mRenderer, texturePath.c_str());
    if (!mTexture)
        throw TextureInitializationError(SDL_GetError());
}

Texture::~Texture()
{
    SDL_DestroyTexture(mTexture);
}

void Texture::Rotate(float angle)
{
    SDL_RenderCopyEx(mRenderer, mTexture, NULL, mTextureBox, angle, NULL, SDL_FLIP_NONE);
}

void Texture::Move(SDL_Point newPosition)
{
    mTextureBox->x = newPosition.x;
    mTextureBox->y = newPosition.y;
}

void Texture::Render()
{
    if (!mTexture)
        return;
    SDL_RenderCopy(mRenderer, mTexture, NULL, mTextureBox);
}
