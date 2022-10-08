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

#include <string>
#include <fstream>

class Log
{
public:
    Log(const std::string &filePath, bool coloredOutput = true) : file(filePath), useColor(coloredOutput) {}

    void Debug(const std::string &message);
    void Trace(const std::string &message);
    void Success(const std::string &message);
    void Warning(const std::string &message);
    void Error(const std::string &message);
    void Fatal(const std::string &message);

private:
    std::ofstream file;
    bool useColor;

private:
    static std::string MessageWithTimeStamp(const std::string &message);
    void WriteToFile(const std::string &message, const std::string &color);
};
