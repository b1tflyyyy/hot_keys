#include "token_entry.hpp"

token_entry::token_entry() :
    m_single_token { std::make_pair<std::wstring, std::wstring>(L"", L"") }
{}

token_entry::token_entry(const std::pair<std::wstring, std::wstring>& single_token) :
    m_single_token{ single_token }
{ }

const std::wstring& token_entry::get_value(const std::wstring& token_name)
{
    return m_single_token[token_name];
}
