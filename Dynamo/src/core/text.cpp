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
#include "Dynamo/src/core/text.hpp"

Text::Text(Window &window, const std::string &text, TextSpecification specification) : text(text), spec(specification), textRenderer(window.GetRenderer())
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(spec.font->GetTTFFont(), text.c_str(), spec.color);
    textTexture = SDL_CreateTextureFromSurface(textRenderer, textSurface);
    SDL_FreeSurface(textSurface);
}

Text::~Text()
{
    SDL_DestroyTexture(textTexture);
}

void Text::SetText(const std::string &newText)
{
    text = newText;
    SDL_Surface *textSurface = TTF_RenderText_Solid(spec.font->GetTTFFont(), text.c_str(), spec.color);
    textTexture = SDL_CreateTextureFromSurface(textRenderer, textSurface);
    SDL_FreeSurface(textSurface);
}

void Text::Render()
{
    SDL_RenderCopyF(textRenderer, textTexture, NULL, &spec.box);
}