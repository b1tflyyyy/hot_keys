#pragma once
#ifndef IERROR_HPP
#define IERROR_HPP

#include <string>

class IError
{
public:
    virtual ~IError() = default;
    virtual explicit operator bool() const = 0;
    virtual const std::wstring what() const = 0;
};

#endif // !IERROR_HPP
