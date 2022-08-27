// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Dynamo.
//
// Dynamo is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dynamo is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dynamo.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

class Timestep
{
public:
    Timestep(float ms = 0.0f) : t(ms) {}

    float GetSeconds() const { return t / 1000.f; }
    int GetFPS() const { return t < 0.1f ? 0 : 1000 / t; }

    operator float() const { return t; }

private:
    float t = 0.0f;
};