// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Dynamo Engine.
//
// Dynamo Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dynamo Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dynamo Engine.  If not, see <http://www.gnu.org/licenses/>.
#include "Dynamo/src/core/sprite.hpp"

#include <stdexcept>

Sprite::Sprite(Window &window, SDL_FRect spriteBox, Surface *surface) : mRenderer(window.GetRenderer()), spriteBox(spriteBox)
{
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface->GetSDLSurface());
    if (!mTexture)
        throw std::invalid_argument(SDL_GetError());
}

Sprite::Sprite(Window &window, SDL_FRect spriteBox, SDL_Color color) : mRenderer(window.GetRenderer()), spriteBox(spriteBox)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0, spriteBox.w, spriteBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (!mTexture)
        throw std::invalid_argument(SDL_GetError());
    SDL_FreeSurface(surface);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(mTexture);
}

void Sprite::SetPosition(const glm::vec2 &newPosition)
{
    spriteBox.x = newPosition.x;
    spriteBox.y = newPosition.y;
}

void Sprite::Rotate(float angle)
{
    orientationAngle = angle;
}

void Sprite::Render()
{
    if (!mTexture)
        return;
    if (glm::abs(orientationAngle) < 1e-3)
        SDL_RenderCopyF(mRenderer, mTexture, NULL, &spriteBox);
    else
        SDL_RenderCopyExF(mRenderer, mTexture, NULL, &spriteBox, orientationAngle, NULL, SDL_FLIP_NONE);
}
