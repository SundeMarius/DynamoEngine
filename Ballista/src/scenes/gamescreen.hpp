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
#include "Ballista/src/utilities/eventtrigger.hpp"
#include "Ballista/src/utilities/physics.hpp"

#include <map>
#include <vector>

enum class GameResource
{
    Background,
    Ground,
};

struct GameSceneAssetConfig
{
    std::string backgroundPath;
    std::string grassPath;
    BallistaAssetConfig playerConfig;
};

class GameScreen : public Scene
{
public:
    GameScreen(const GameSceneAssetConfig &config, Window &window, EventTrigger &eventTrigger)
        : config(config), window(window), eventTrigger(eventTrigger),
          textureLoader(window), fontLoader(window) {}

    bool Init() override;
    void Activate() override;
    void Finish() override {}
    void Update(const Timestep &dt) override;
    void ProcessInput(SDL_Event *event) override;
    void Render() override;

private:
    void AddText(GameResource type, const std::string &text, TextSpecification textSpec);
    void AddBackground(GameResource type, SDL_Point position, int width, int height);

private:
    std::unique_ptr<Ballista> player{};
    std::vector<std::unique_ptr<Arrow>> arrows{};
    glm::vec2 gravity{0.f, physics::constants::accelerationDueToGravity};
    int groundLevel{0};

    bool ArrowHasLanded(Arrow &arrow) const;
    void ApplyGravity(GameObject &object, const Timestep &dt) const;

private:
    GameSceneAssetConfig config{};
    Window &window;
    EventTrigger &eventTrigger;

    AssetLoader<Texture> textureLoader;
    AssetLoader<Font> fontLoader;
    std::map<GameResource, int> assetIds{};

    std::map<GameResource, Image> backgrounds{};
    std::map<GameResource, Text> texts{};

    float currentSeconds = 0.f;
};