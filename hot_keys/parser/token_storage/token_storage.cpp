#include "token_storage.hpp"

const std::wstring token_storage::m_is_double_button(L"double_buttons:");
const std::wstring token_storage::m_first_button(L"button_1=");
const std::wstring token_storage::m_second_button(L"button_2=");
const std::wstring token_storage::m_path(L"path->");

const std::wstring token_storage::token[token_storage::size] =
{
    token_storage::m_is_double_button,
    token_storage::m_first_button,
    token_storage::m_second_button,
    token_storage::m_path
};