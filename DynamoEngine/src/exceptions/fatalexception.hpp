#pragma once

#include <stdexcept>
#include <string>

class FatalException : public std::runtime_error
{
public:
    FatalException(const std::string &message) : std::runtime_error(message) {}
};