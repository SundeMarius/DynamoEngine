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
#include "Lib/src/core/scenemanager.hpp"
#include "Lib/src/core/timestep.hpp"

int SceneManager::AddScene(std::unique_ptr<Scene> &scene)
{
    auto inserted = scenes.emplace(sceneId, std::move(scene));
    inserted.first->second->Init();
    return sceneId++;
}
void SceneManager::RemoveScene(int id)
{
    auto sceneIterator = scenes.find(id);
    if (sceneIterator == scenes.end())
        return;
    if (sceneIterator->second.get() == currentScene)
        currentScene = nullptr;
    // Remove the scene
    scenes.erase(sceneIterator);
}
void SceneManager::SwitchScene(int id)
{
    auto sceneIterator = scenes.find(id);
    if (sceneIterator == scenes.end())
        return;
    if (currentScene)
        currentScene->Deactivate();
    currentScene = sceneIterator->second.get();
    currentScene->Activate();
}

void SceneManager::Update(const Timestep &dt)
{
    if (currentScene)
        currentScene->Update(dt);
}
void SceneManager::Render()
{
    if (currentScene)
        currentScene->Render();
}
