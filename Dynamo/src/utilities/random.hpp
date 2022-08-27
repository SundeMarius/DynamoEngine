// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Dynamo
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

#include <random>

typedef std::int64_t int64;
typedef std::uint64_t uint64;

class Random
{
public:
    static int64 Integer(int64 min = INT64_MIN, int64 max = INT64_MAX);
    static uint64 UInteger(uint64 min = 0, uint64 max = UINT64_MAX);
    static double Real(double min = 0.0f, double max = 1.0f);

private:
    static inline std::random_device rd{};
    static inline std::mt19937_64 engine{rd()};
    static inline std::uniform_int_distribution<uint64> int_dist{};
    static inline std::uniform_real_distribution<double> real_dist{};
};
