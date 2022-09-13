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

#include "random.hpp"
#include <cstdint>

typedef std::uint64_t uint64;

class UUID
{
public:
    UUID() : UUID(Random::UInteger()) {}
    UUID(uint64 uuid) : m_uuid(uuid) {}

    operator uint64() const { return m_uuid; }

private:
    uint64 m_uuid;
};

// Make UUID hashable
template <>
struct std::hash<UUID>
{
    std::size_t operator()(const UUID &uuid) const
    {
        return hash<uint64>{}(uuid);
    }
};