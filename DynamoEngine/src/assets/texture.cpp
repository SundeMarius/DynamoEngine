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
#include "DynamoEngine/src/assets/texture.hpp"

#include <SDL2/SDL_image.h>

#include <stdexcept>

Texture::Texture(Window &window, SDL_Texture *texture) : window(&window)
{
    int *w = nullptr;
    int *h = nullptr;
    if (!texture)
        throw AssetInitializationError("SDL_Texture is NULL");
    mTexture = texture;
    SDL_QueryTexture(texture, NULL, NULL, w, h);
    width = *w;
    height = *h;
}

Texture::Texture(Window &window, Surface *surface) : window(&window), width(surface->GetWidth()), height(surface->GetHeight())
{
    mTexture = SDL_CreateTextureFromSurface(window.GetSDLRenderer(), surface->GetSDLSurface());
    if (!mTexture)
    {
        throw AssetInitializationError(SDL_GetError());
    }
}

void Texture::LoadFromFile(Window &window, const std::string &filePath)
{
    this->window = &window;
    Surface surface = IMG_Load(filePath.c_str());
    if (!surface.GetSDLSurface())
    {
        throw AssetInitializationError(SDL_GetError());
    }
    mTexture = SDL_CreateTextureFromSurface(window.GetSDLRenderer(), surface.GetSDLSurface());
    if (!mTexture)
    {
        throw AssetInitializationError(SDL_GetError());
    }
    width = surface.GetWidth();
    height = surface.GetHeight();
}

Texture::~Texture()
{
    SDL_DestroyTexture(mTexture);
}
