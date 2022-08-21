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

#include <string>

#include <SDL2/SDL.h>

class Texture
{
public:
    Texture(const std::string &texturePath, SDL_Rect *textureBox, SDL_Renderer *renderer);
    ~Texture();

    void Rotate(float angle);

    void Move(SDL_Point newPosition);

    void Render();

private:
    SDL_Rect *mTextureBox = nullptr;
    SDL_Texture *mTexture = nullptr;
    SDL_Renderer *mRenderer = nullptr;
};

class TextureInitializationError : public std::exception
{
public:
    TextureInitializationError(const std::string &errorMessage)
    {
        msg = errorMessage;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }

private:
    std::string msg;
};