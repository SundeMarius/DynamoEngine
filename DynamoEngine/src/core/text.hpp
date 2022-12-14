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

#include "DynamoEngine/src/core/window.hpp"
#include "DynamoEngine/src/assets/texture.hpp"
#include "DynamoEngine/src/assets/font.hpp"

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

#include <string>
#include <memory>

struct TextSpecification
{
    std::shared_ptr<Font> font = std::make_shared<Font>();
    SDL_Color color{};
    SDL_Rect box{};
    TextSpecification() = default;
    TextSpecification(Window &window, std::string fontFileName, SDL_Color color, SDL_Rect box) : color(color), box(box)
    {
        font->LoadFromFile(window, fontFileName);
    }
};

class Text
{
public:
    Text() = default;
    Text(Window &window, const std::string &text, const TextSpecification &specification);

    void Render();

private:
    std::string text{};
    TextSpecification spec{};
    std::unique_ptr<Texture> mTexture{};
};
