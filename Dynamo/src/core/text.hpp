// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Dynamo.
//
// Dynamo is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dynamo is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dynamo.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Dynamo/src/core/window.hpp"
#include "Dynamo/src/assets/font.hpp"

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

#include <string>
#include <memory>

struct TextSpecification
{
    SDL_Color color;
    Font *font;
    SDL_FRect box;
};

class Text
{
public:
    Text(Window &window, const std::string &text, TextSpecification specification);
    ~Text();

    void SetText(const std::string &newText);

    void Render();

private:
    std::string text;
    TextSpecification spec;

    SDL_Texture *textTexture = nullptr;
    SDL_Renderer *textRenderer = nullptr;
};
