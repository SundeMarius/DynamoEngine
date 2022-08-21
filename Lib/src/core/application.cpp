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
// along with Projects. If not, see <http://www.gnu.org/licenses/>.

#include "Lib/src/core/application.hpp"
#include "Lib/src/core/text.hpp"

#include <SDL2/SDL_image.h>

#include <iostream>

Application::Application(ApplicationSpecification spec, ResourceSpecification rSpec) : spec(spec), appLog(spec.logFile)
{
    resources = std::make_unique<ResourceLoader>(rSpec);
}

Application::~Application()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    if (init)
        appLog.Trace("Application has shut down successfully");
    else
        appLog.Fatal("Application could not start due to errors in initialization.");
}

bool Application::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        appLog.Fatal("SDL failed to initialize");
        return false;
    }

    window = SDL_CreateWindow(
        spec.name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        spec.width,
        spec.height,
        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
    if (!window)
    {
        appLog.Fatal("Window failed to initialize");
        return false;
    }
    appLog.Trace("Window system initialized");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        appLog.Fatal("Renderer failed to initialize");
        return false;
    }
    appLog.Trace("Renderer initialized");

    // Load application font and textures
    resources->Init(renderer, appLog);
    font = resources->GetFont();
    backgroundTexture = resources->GetBackgroundTexture();

    return true;
}

int Application::Start()
{
    appLog.Trace("Starting application '" + spec.name + "'");
    if (!(init = Init()))
    {
        std::cerr << "Fatal error occured -- see log file " << spec.logFile << std::endl;
        return -1;
    }
    appLog.Success("Application initialized successfully");

    appLog.Debug("Starting main application loop");
    SDL_Event event;
    while (running)
    {
        uint64_t startTimeMilliSec = SDL_GetTicks64();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                appLog.Debug("Event registered: EXIT");
                Close();
            }
            OnEvent(&event);
        }
        // update timeStep is set to frame time in seconds
        Timestep dt = frameTime * 1.e-1;
        Update(dt.GetSeconds());
        SDL_RenderClear(renderer);
        Render();
        SDL_RenderPresent(renderer);
        // FPS
        frameTime = SDL_GetTicks64() - startTimeMilliSec;
    }
    appLog.Debug("Main application loop finished");

    return 0;
}

void Application::Close()
{
    appLog.Debug("Closing application");
    running = false;
}

void Application::Render()
{

    backgroundTexture->Render();
    scene.Render();
    if (spec.RenderFPS)
        RenderFPS();
}

int Application::GetFPS()
{
    int fps = frameTime.GetFPS();
    if (fps < 5)
    {
        appLog.Warning("Performance issues (" + std::to_string(fps) + " FPS)");
    }
    return fps;
}
void Application::RenderFPS()
{
    Text text("FPS: " + std::to_string(GetFPS()), {spec.width - 75, spec.height - 25, 75, 25});
    text.Render(font->GetTTFFont(), renderer);
}
