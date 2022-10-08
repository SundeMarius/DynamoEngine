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
#include "DynamoEngine/src/log/log.hpp"
#include "color.hpp"

#include <ctime>
#include <iostream>

void Log::Debug(const std::string &message)
{
    WriteToFile(message, MAGENTA);
}
void Log::Trace(const std::string &message)
{
    WriteToFile(message, RESET);
}
void Log::Success(const std::string &message)
{
    WriteToFile(message, GREEN);
}
void Log::Warning(const std::string &message)
{
    WriteToFile(message, YELLOW);
}
void Log::Error(const std::string &message)
{
    WriteToFile(message, RED);
}
void Log::Fatal(const std::string &message)
{
    WriteToFile(message, BOLDRED);
}

std::string Log::MessageWithTimeStamp(const std::string &message)
{
    std::time_t now = std::time(nullptr);
    std::string time = std::ctime(&now);
    time.pop_back();
    return time + ": " + message;
}

void Log::WriteToFile(const std::string &message, const std::string &color)
{
    const std::string &msg = MessageWithTimeStamp(message);
    file << (useColor ? color + msg + RESET : msg) << std::endl;
}
