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
#include "DynamoEngine/src/core/text.hpp"
#include "DynamoEngine/src/exceptions/exceptions.hpp"

Text::Text(Window &window, const std::string &text, const TextSpecification &specification) : text(text), spec(specification)
{
    Surface textSurface = TTF_RenderText_Solid(spec.font->GetTTFFont(), text.c_str(), spec.color);
    mTexture = std::make_unique<Texture>(window, &textSurface);
}

void Text::Render()
{
    if (SDL_RenderCopy(mTexture->GetSDLRenderer(), mTexture->GetSDLTexture(), NULL, &spec.box) != 0)
        throw WarningException(SDL_GetError());
}