// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of DynamoEngine Engine.
//
// DynamoEngine Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DynamoEngine Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DynamoEngine Engine.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "DynamoEngine/src/assets/texture.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <memory>

class Sprite
{
public:
    Sprite() = default;
    Sprite(std::shared_ptr<Texture> texture, int width, int height, float orientation = 0.0f);

    void SetWidth(int width) { w = width; }
    void SetHeight(int height) { h = height; }
    int GetWidth() const { return w; }
    int GetHeight() const { return h; }

    void SetOrientation(float orientation) { angle = orientation; }
    void Rotate(float orientation) { angle += orientation; }

    float GetOrientation() const { return angle; }
    Texture *GetTexture() const { return mTexture.get(); }

private:
    std::shared_ptr<Texture> mTexture{};
    int w{};
    int h{};
    float angle{};
};