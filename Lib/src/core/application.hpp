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

#include "Lib/src/core/timestep.hpp"
#include "Lib/src/core/scene.hpp"
#include "Lib/src/log/log.hpp"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <string>

struct ApplicationCommandLineArguments
{
    int count = 0;
    char **argv = nullptr;
};

struct ApplicationSpecification
{
    std::string name = "Example application";

    int width = 1600;
    int height = 900;

    std::string fontFile = "assets/fonts/roboto/Roboto-Medium.ttf";
    TTF_Font *font = nullptr;

    bool displayFPS = true;
    ApplicationCommandLineArguments args{};

    std::string logFile = "./app.log";
};

class Application
{
public:
    Application(const ApplicationSpecification &specification) : spec(specification), appLog(spec.logFile) {}
    virtual ~Application();

    int Start();

    void Close();

    int GetFPS();

    void ToggleFPSCounter() { spec.displayFPS = !spec.displayFPS; }

protected:
    bool Init();

    virtual void OnEvent(SDL_Event *event) = 0;

    virtual void Update(const Timestep &dt) = 0;

    virtual void Display() = 0;

private:
    ApplicationSpecification spec{};
    Log appLog;

    bool running = true;
    bool init = false;

    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
    Timestep frameTime{};

    Scene scene;

private:
    bool InitializeFont();
    void DisplayFPS();
};
