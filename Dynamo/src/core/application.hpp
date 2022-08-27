// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Projects.
//
// Projects is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Projects is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Projects.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Dynamo/src/core/window.hpp"
#include "Dynamo/src/core/timestep.hpp"
#include "Dynamo/src/log/log.hpp"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <memory>

struct ApplicationCommandLineArguments
{
    int count = 0;
    char **argv = nullptr;
};
// dd
struct ApplicationSpecification
{
    std::string logFile = "./app.log";
    bool ShowFPSCounter = true;
    ApplicationCommandLineArguments args{};
};

class Application
{
public:
    Application(const WindowSpecification &windowSpec, const ApplicationSpecification &applicationSpec);
    virtual ~Application();

    int Start();

protected:
    bool Init();

    void Close();

    virtual void Render() = 0;

    virtual void OnEvent(SDL_Event *event) = 0;

    virtual void Update(const Timestep &dt) = 0;

    int GetFPS();

    void ToggleFPSCounter() { appSpec.ShowFPSCounter = !appSpec.ShowFPSCounter; }

protected:
    Window window;
    Timestep frameTime;
    ApplicationSpecification appSpec;
    WindowSpecification winSpec;
    Log appLog;

private:
    bool running = true;
};
