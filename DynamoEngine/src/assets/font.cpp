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
#include "DynamoEngine/src/assets/font.hpp"

Font::~Font()
{
    TTF_CloseFont(font);
}

void Font::LoadFromFile(Window &window, const std::string &filePath)
{
    (void)window;
    font = TTF_OpenFont(filePath.c_str(), size);
    if (!font)
    {
        throw AssetInitializationError(SDL_GetError());
    }
}

void Font::Resize(int newSize)
{
    size = newSize;
    TTF_SetFontSize(font, size);
}
