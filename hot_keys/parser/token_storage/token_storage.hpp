#pragma once
#ifndef TOKEN_STORAGE_HPP
#define TOKEN_STORAGE_HPP

#include <string>

enum token_index : std::size_t
{
    is_double_button = 0,
    first_button = 1,
    second_button = 2,
    path = 3
};

class token_storage final
{
private:
    const static std::wstring m_is_double_button;
    const static std::wstring m_first_button;
    const static std::wstring m_second_button;
    const static std::wstring m_path;

public:
    constexpr static std::size_t size = 4;
    const static std::wstring token[size];
};

#endif // !TOKEN_STORAGE_HPP
