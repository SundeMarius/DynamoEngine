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

#include "Dynamo/src/core/timestep.hpp"

#include <SDL2/SDL.h>

#include <string>

struct WindowSpecification
{
    std::string name = "Example application";
    int width = 1920;
    int height = 1080;
};

class Window
{
    using Point2d = SDL_FPoint;

public:
    Window(const WindowSpecification &specification) : spec(specification) {}
    ~Window();

    void Init();

    void SetBagroundColor(const SDL_Color &color);
    void SetFrameTime(const Timestep &dt) { frametime = dt; }

    int GetWidth() const { return spec.width; }
    int GetHeight() const { return spec.height; }
    int GetFPS() const { return frametime.GetFPS(); }

    Point2d GetCenter() const { return {float(spec.width) / 2.0f, float(spec.height) / 2.0f}; }

    SDL_Renderer *GetRenderer() { return renderer; }

private:
    WindowSpecification spec;
    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
    Timestep frametime;
};