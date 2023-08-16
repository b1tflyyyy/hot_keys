#pragma once
#ifndef TOKEN_ENTRY_HPP
#define TOKEN_ENTRY_HPP

#include <unordered_map>
#include <string>

class token_entry final
{
private:
    std::unordered_map<std::wstring, std::wstring> m_single_token;

public:
    explicit token_entry();
    explicit token_entry(const std::pair<std::wstring, std::wstring>& single_token);
    const std::wstring& get_value(const std::wstring& token_name);
};

#endif // !TOKEN_ENTRY_HPP
