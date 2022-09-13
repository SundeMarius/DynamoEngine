// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of DynamoEngine Engine.
//
// DynamoEngine Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DynamoEngine Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DynamoEngine Engine.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "DynamoEngine/src/core/window.hpp"

#include <string>

class Asset
{
public:
    Asset() = default;
    virtual ~Asset() = default;

    virtual void LoadFromFile(Window &window, const std::string &filePath) = 0;
};

class AssetInitializationError : public std::exception
{
public:
    AssetInitializationError(const std::string &errorMessage)
    {
        msg = errorMessage;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }

private:
    std::string msg;
};