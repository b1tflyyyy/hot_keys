#include "parser.hpp"

Parser::Parser() :
    m_path(L"config.txt")
{ }

void Parser::m_parse_all_data()
{
    m_wfin.open(m_path, std::ios::in);
    m_wfin.imbue(std::locale(""));

    if (!m_wfin.is_open())
    {
        throw std::exception("ERROR WITH FILE, FILE WAS NOT FOUND!!!");
    }

    // expected reserve size
    m_all_data.reserve(10);

    std::wstring temp_data;
    while (std::getline(m_wfin, temp_data))
    {
        m_all_data.push_back(std::move(temp_data));
    }
    
    m_all_data.shrink_to_fit();

#if DEBUG_LOGS
    for (const auto& el : m_all_data)
    {
        std::wcout << el << '\n';
    }
#endif // !DEBUG_LOGS
}

// work correctly
bool Parser::m_is_double_button(const std::wstring& wstr)
{
    auto it = std::find(wstr.begin(), wstr.end(), ':');
    wchar_t value = *(it + 2);

    if (value != L'0' && value != L'1')
    {
        throw std::exception("ERROR: param double_buttons can be only 0 or 1!");
    }

    return value == L'1';
}

// work correctly
// think about pair of buttons
int Parser::m_parse_button_value(std::wstring& wstr)
{
    if (m_is_double_button(wstr))
    {
        return 0;
    }

    // single button logic
    // button_1 = 0x30; ptr on '=' and then read value '0x30'
    auto it = std::find(wstr.begin(), wstr.end(), L'=');
    
    std::wstring tmp;
    tmp.reserve(4);

    for (it += 2; *it != L';'; ++it)
    {
        tmp += *it;
    }

#if DEBUG_LOGS
    std::wcout << tmp << '\n';
#endif // !DEBUG_LOGS

    return std::stoi(tmp, nullptr, 16);
}

// TODO: optimise this 
std::wstring Parser::m_parse_path(std::wstring& wstr)
{
    std::wstring path;
    path.reserve(20);

    auto it = std::find(wstr.begin(), wstr.end(), L'>');
    for (++it; *it != L';'; ++it)
    {
        path += *it;
    }

#if DEBUG_LOGS
    std::wcout << path << '\n';
#endif // !DEBUG_LOGS

    return path;
}

void Parser::m_set_to_map()
{
    int val{};
    std::wstring path;

    for (int i{}; i < m_all_data.size(); ++i)
    {
        if (m_is_double_button(m_all_data[i]))
        {
            // TODO:
            continue;
        }

        val = m_parse_button_value(m_all_data[i]);
        path = m_parse_path(m_all_data[i]);

        m_single_button[val] = path;
    }
}

const std::map<int, std::wstring>& Parser::get_single_buttons()
{
    return m_single_button;
}