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

#include "DynamoEngine/src/entities/compositegameobject.hpp"

int CompositeGameObject::AddObject(std::unique_ptr<GameObject> object)
{
    objects.try_emplace(objectId, std::move(object));
    return objectId++;
}

void CompositeGameObject::RemoveObject(int objectId)
{
    objects.erase(objectId);
}

GameObject *CompositeGameObject::GetObject(int objectId)
{
    return objects.at(objectId).get();
}

std::unique_ptr<GameObject> CompositeGameObject::ReleaseObject(int objectId)
{
    GameObject *object = objects.at(objectId).release();
    RemoveObject(objectId);
    return std::unique_ptr<GameObject>(object);
}

void CompositeGameObject::SetPosition(const glm::vec2 &position)
{
    for (auto &[key, object] : objects)
    {
        object->AddPosition(position - pos);
    }
    pos = position;
}
void CompositeGameObject::AddPosition(const glm::vec2 &displacement)
{
    pos += displacement;
    for (auto &[key, object] : objects)
    {
        object->AddPosition(displacement);
    }
}
void CompositeGameObject::SetVelocity(const glm::vec2 &velocity)
{
    vel = velocity;
    for (auto &[key, object] : objects)
    {
        object->SetVelocity(velocity);
    }
}
void CompositeGameObject::AddVelocity(const glm::vec2 &velocity)
{
    vel += velocity;
    for (auto &[key, object] : objects)
    {
        object->AddVelocity(velocity);
    }
}

void CompositeGameObject::Rotate(float angle)
{
    for (auto &[key, object] : objects)
    {
        object->Rotate(angle);
    }
}

void CompositeGameObject::Update(const Timestep &dt)
{
    for (auto &[key, object] : objects)
    {
        object->Update(dt);
    }
    pos += vel * dt.GetSeconds();
}

void CompositeGameObject::Render()
{
    for (auto &[key, object] : objects)
    {
        const auto &sprite = object->GetSprite();
        const auto &position = object->GetPosition();
        const SDL_Rect box = {int(position.x), int(position.y), sprite->GetWidth(), sprite->GetHeight()};
        SDL_RenderCopyEx(sprite->GetTexture()->GetSDLRenderer(), sprite->GetTexture()->GetSDLTexture(), NULL, &box, glm::degrees(sprite->GetOrientation()), NULL, SDL_FLIP_NONE);
    }
}