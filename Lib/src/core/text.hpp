// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Lib.
//
// Lib is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Lib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Lib.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Lib/src/core/texture.hpp"

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

#include <string>
#include <memory>

class Text
{
public:
    Text(const std::string &text, SDL_Rect textBox, SDL_Color color) : text(text), color(color), textBox(textBox) {}
    Text(const std::string &text, SDL_Rect textBox) : Text(text, textBox, {255, 255, 255, 0}) {}
    ~Text();

    void Render(TTF_Font *font, SDL_Renderer *renderer);

private:
    std::string text;
    SDL_Color color;
    SDL_Rect textBox;
    SDL_Texture *textTexture;
};
