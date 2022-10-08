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
#include "DynamoEngine/src/entities/sprite.hpp"

#include <stdexcept>

Sprite::Sprite(std::shared_ptr<Texture> texture, int width, int height, float orientation) : w(width), h(height), angle(orientation)
{
    if (!texture)
    {
        throw std::runtime_error("Cannot create sprite from emtpy texture");
    }
    mTexture = std::move(texture);
}