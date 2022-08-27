// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of BallisticPotatoes.
//
// BallisticPotatoes is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// BallisticPotatoes is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BallisticPotatoes.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Dynamo/src/core/sprite.hpp"
#include "Dynamo/src/core/scene.hpp"
#include "Dynamo/src/assets/assetloader.hpp"
#include "Dynamo/src/assets/font.hpp"
#include "Dynamo/src/core/text.hpp"
#include "Dynamo/src/assets/surface.hpp"

#include "BallisticPotatoes/src/entities/cannon.hpp"

#include <map>

enum class GameResource
{
    Background1,
    Background2,
    Background3,
    Background4,
    CannonPlayer,
    Ground,
    FpsFont
};

class GameScreen : public Scene
{
public:
    GameScreen(Window &window, Log &log) : window(window), log(log), textureLoader(log), fontLoader(log) {}

    bool Init() override;
    void Activate() override;
    bool Completed() override { return false; }
    void Update(const Timestep &dt) override;
    void Render() override;

private:
    void AddText(GameResource type, float textPosX, float textPosY, float textWidth, float textHeight, SDL_Color color);
    void AddImage(GameResource type, float texturePosX, float texturePosY, float textureSizeX, float textureSizeY);
    void AddSprite(GameResource type, float texturePosX, float texturePosY, float textureSizeX, float textureSizeY);

private:
    Cannon player{};

private:
    Window &window;
    Log &log;

    AssetLoader<Surface> textureLoader;
    AssetLoader<Font> fontLoader;
    std::map<GameResource, int> assetIds{};

    std::map<GameResource, std::unique_ptr<Sprite>> images{};
    std::map<GameResource, std::unique_ptr<Sprite>> sprites{};
    std::map<GameResource, std::unique_ptr<Text>> texts{};

    float currentSeconds = 0.f;
};