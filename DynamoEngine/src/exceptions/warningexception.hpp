#pragma once

#include <stdexcept>
#include <string>

class WarningException : public std::runtime_error
{
public:
    WarningException(const std::string &message) : std::runtime_error(message) {}
};