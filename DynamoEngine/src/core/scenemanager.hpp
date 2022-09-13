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

#include "DynamoEngine/src/core/scene.hpp"
#include "DynamoEngine/src/core/window.hpp"

#include <memory>
#include <unordered_map>

class SceneManager
{
    using SceneId = int;

public:
    SceneManager() = default;
    ~SceneManager() = default;

    SceneId AddScene(std::unique_ptr<Scene> &scene);
    void RemoveScene(SceneId id);
    Scene *GetScene(SceneId id);
    void SwitchScene(SceneId id);

    void ProcessInput(SDL_Event *event);

    void Update(const Timestep &dt);
    void Render();

private:
    std::unordered_map<SceneId, std::unique_ptr<Scene>> scenes;
    Scene *currentScene = nullptr;
    SceneId sceneId = 0;
};