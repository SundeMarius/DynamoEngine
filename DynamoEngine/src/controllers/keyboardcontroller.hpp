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

#include <SDL2/SDL.h>

class KeyboardController
{
public:
    using Key = SDL_Scancode;
    bool IsKeyPressed(SDL_KeyboardEvent *keyEvent, Key key);
    bool IsKeyReleased(SDL_KeyboardEvent *keyEvent, Key key);
    bool IsKeyDown(SDL_KeyboardEvent *keyEvent, Key key);
    bool IsKeyUp(SDL_KeyboardEvent *keyEvent, Key key);
};