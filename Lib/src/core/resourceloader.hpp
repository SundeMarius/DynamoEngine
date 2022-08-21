// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of CannonLaunch.
//
// CannonLaunch is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CannonLaunch is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CannonLaunch.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Lib/src/core/texture.hpp"
#include "Lib/src/core/font.hpp"
#include "Lib/src/log/log.hpp"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <memory>
#include <unordered_map>

struct ResourceSpecification
{
    std::string fontFile;
    std::string backgroundTextureFile;
};

using Resources = std::unordered_map<std::string, std::unique_ptr<ResourceSpecification>>;

class ResourceLoader
{
public:
    ResourceLoader(ResourceSpecification &specification) : spec(specification) {}
    virtual ~ResourceLoader() = default;

    virtual bool Init(SDL_Renderer *renderer, Log &log);

    std::shared_ptr<Font> UseFont() { return font; }
    std::shared_ptr<Texture> UseBackgroundTexture() { return backgroundTexture; }

private:
    void InitializeFont();
    void LoadBackgroundTexture(SDL_Renderer *renderer);

private:
    ResourceSpecification spec;

    std::shared_ptr<Font> font;
    std::shared_ptr<Texture> backgroundTexture;
};