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
#include "Lib/src/core/sprite.hpp"

Sprite::Sprite(Window &window, Surface *surface, SDL_Rect spriteBox) : mRenderer(window.GetRenderer()), spriteBox(spriteBox)
{
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface->GetSDLSurface());
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(mTexture);
}

void Sprite::Rotate(float angle)
{
    if (!mTexture)
        return;
    SDL_RenderCopyEx(mRenderer, mTexture, NULL, &spriteBox, angle, NULL, SDL_FLIP_NONE);
}

void Sprite::Move(const SDL_Point &newPosition)
{
    spriteBox.x = newPosition.x;
    spriteBox.y = newPosition.y;
}

void Sprite::Render()
{
    if (!mTexture)
        return;
    SDL_RenderCopy(mRenderer, mTexture, NULL, &spriteBox);
}
