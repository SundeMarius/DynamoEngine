// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Ballista.
//
// Ballista is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Ballista is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Ballista.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "DynamoEngine/src/core/scene.hpp"
#include "DynamoEngine/src/assets/assetloader.hpp"
#include "DynamoEngine/src/assets/font.hpp"
#include "DynamoEngine/src/core/text.hpp"
#include "DynamoEngine/src/core/image.hpp"
#include "DynamoEngine/src/assets/texture.hpp"
#include "DynamoEngine/src/entities/sprite.hpp"

#include "Ballista/src/entities/ballista.hpp"

#include <map>

enum class GameResource
{
    Background,
    Ground,
};

class GameScreen : public Scene
{
public:
    GameScreen(Window &window, Log &log) : window(window), log(log), textureLoader(window), fontLoader(window) {}

    bool Init() override;
    void Activate() override;
    bool Completed() override { return false; }
    void Update(const Timestep &dt) override;
    void ProcessInput(SDL_Event *event) override;
    void Render() override;

private:
    void AddText(GameResource type, SDL_Point position, int width, int height, SDL_Color color);
    void AddSprite(GameResource type, int width, int height);
    void AddBackground(GameResource type, SDL_Point position, int width, int height);

private:
    std::unique_ptr<Ballista> player;
    int groundLevel{};
    float playerScale{};
    glm::vec2 gravity{};

private:
    Window &window;
    Log &log;

    AssetLoader<Texture> textureLoader;
    AssetLoader<Font> fontLoader;
    std::map<GameResource, int> assetIds{};

    std::map<GameResource, Sprite> sprites{};
    std::map<GameResource, Image> backgrounds{};
    std::map<GameResource, Text> texts{};

    float currentSeconds = 0.f;
};