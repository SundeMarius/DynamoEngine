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
#pragma once

#include "DynamoEngine/src/core/text.hpp"
#include "DynamoEngine/src/core/window.hpp"
#include "DynamoEngine/src/core/timestep.hpp"
#include "DynamoEngine/src/log/log.hpp"

#include <string>
#include <vector>
#include <memory>

#define JSON_DIAGNOSTICS 1
#include "DynamoEngine/vendor/json.hpp"

using json = nlohmann::json;

struct ApplicationCommandLineArguments
{
    int argc{};
    char **argv = nullptr;
};
// dd
struct ApplicationSpecification
{
    json config;
    WindowSpecification windowSpecification;
    ApplicationCommandLineArguments args;
};

class Application
{
public:
    Application(const ApplicationSpecification &applicationSpec);
    virtual ~Application();

    int Start();

    void TurnFPSCounterOff() { showDebugInfo = false; }

    void TurnFPSCounterOn() { showDebugInfo = true; }

protected:
    bool Init();

    void Close();

    virtual void Render() = 0;

    virtual void OnEvent(SDL_Event *event) = 0;

    virtual void Update(const Timestep &dt) = 0;

protected:
    Window window;
    ApplicationSpecification appSpec;
    Log appLog;
    bool showDebugInfo = false;

private:
    bool running = true;
};
