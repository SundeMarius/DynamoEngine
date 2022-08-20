// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of CannonLaunch.
//
// CannonLaunch is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CannonLaunch is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CannonLaunch.  If not, see <http://www.gnu.org/licenses/>.
#include "Lib/src/log/log.hpp"
#include "color.hpp"

#include <ctime>
#include <iostream>

void Log::Debug(const std::string &message)
{
    std::string msg = MessageWithTimeStamp(message);
    file << (color ? MAGENTA + msg + RESET : msg) << std::endl;
}
void Log::Trace(const std::string &message)
{
    std::string msg = MessageWithTimeStamp(message);
    file << msg << std::endl;
}
void Log::Success(const std::string &message)
{
    std::string msg = MessageWithTimeStamp(message);
    file << (color ? GREEN + msg + RESET : msg) << std::endl;
}
void Log::Warning(const std::string &message)
{
    std::string msg = MessageWithTimeStamp(message);
    file << (color ? YELLOW + msg + RESET : msg) << std::endl;
}
void Log::Error(const std::string &message)
{
    std::string msg = MessageWithTimeStamp(message);
    file << (color ? RED + msg + RESET : msg) << std::endl;
}
void Log::Fatal(const std::string &message)
{
    std::string msg = MessageWithTimeStamp(message);
    file << (color ? BOLDRED + msg + RESET : msg) << std::endl;
}

std::string Log::MessageWithTimeStamp(const std::string &message)
{
    std::time_t now = std::time(nullptr);
    std::string time = std::ctime(&now);
    time.pop_back();
    return time + ": " + message;
}