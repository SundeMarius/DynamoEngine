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
#pragma once

#include "Dynamo/src/core/window.hpp"
#include "Dynamo/src/assets/surface.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Sprite
{
public:
    Sprite() = default;
    // Create rectangle sprite
    Sprite(Window &window, SDL_FRect spriteBox, SDL_Color color);
    // Create rectangle from texture
    Sprite(Window &window, SDL_FRect spriteBox, Surface *surface);
    ~Sprite();

    SDL_Renderer *GetRenderer() { return mRenderer; }
    SDL_Texture *GetTexture() { return mTexture; }
    SDL_FRect *GetSpriteBox() { return &spriteBox; }

    void SetPosition(const glm::vec2 &newPosition);
    float GetRotation() const { return orientationAngle; }

    void Rotate(float angle);

    void Render();

private:
    SDL_Renderer *mRenderer = nullptr;
    SDL_Texture *mTexture = nullptr;
    SDL_FRect spriteBox{};
    float orientationAngle{0.f};
};