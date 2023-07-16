#include "parser.hpp"

Parser::Parser() :
    m_path(std::move(L"config.txt"))
{ }

void Parser::parse_all_data()
{
    m_wfin.open(m_path, std::ios::in);
    m_wfin.imbue(std::locale(""));

    if (!m_wfin.is_open())
    {
        throw std::exception("ERROR WITH FILE, FILE WAS NOT FOUND!!!");
    }

    m_all_data.reserve(10);

    std::wstring temp_data{};
    while (std::getline(m_wfin, temp_data))
    {
        m_all_data.push_back(std::move(temp_data));
    }
    
    m_all_data.shrink_to_fit();

#if DEBUG_LOGS
    std::wcout << L"parse_all_data() --->\n";
    for (const auto& el : m_all_data)
    {
        std::wcout << el << '\n';
    }
    std::wcout << L"--------------------\n\n";
#endif // !DEBUG_LOGS
}

const std::vector<Button>& Parser::get_buttons() const
{
    return m_buttons;
}

bool Parser::m_is_single_button(const std::wstring_view wstr)
{
    auto it = std::find(wstr.begin(), wstr.end(), ':');
    wchar_t value = *(it + 2);

    if (value != L'0' && value != L'1')
    {
        throw std::exception("ERROR: param double_buttons can be only 0 or 1!");
    }

    return value == L'0';
}

std::pair<int, int> Parser::m_parse_button_value(const std::wstring& wstr)
{
    if (!m_is_single_button(wstr))
    {
        // TODO: redo this
        std::wstring first_button_value{};
        first_button_value.reserve(4);

        std::wstring second_button_value{};
        second_button_value.reserve(4);

        auto it_first_button = std::find(wstr.begin(), wstr.end(), L'1');
        for (it_first_button += 14; *it_first_button != L';'; ++it_first_button)
        {
            first_button_value += *it_first_button;
        }

        auto it_second_button = std::find(wstr.begin(), wstr.end(), L'2');
        for (it_second_button += 4; *it_second_button != L';'; ++it_second_button)
        {
            second_button_value += *it_second_button;
        }

#if DEBUG_LOGS
        std::wcout << "first value: " << first_button_value << " " << "second value: " << second_button_value << '\n';
#endif // DEBUG_LOGS

        return std::make_pair(std::stoi(first_button_value, nullptr, 16), std::stoi(second_button_value, nullptr, 16));
    }

    auto it = std::find(wstr.begin(), wstr.end(), L'=');
    
    std::wstring tmp{};
    tmp.reserve(4);

    for (it += 2; *it != L';'; ++it)
    {
        tmp += *it;
    }

#if DEBUG_LOGS
    std::wcout << L"m_parse_button_value(): " << tmp << '\n';
#endif // !DEBUG_LOGS

    return std::make_pair(std::stoi(tmp, nullptr, 16), 0);
}

void Parser::m_parse_path(std::wstring& wstr)
{
    wstr.erase(wstr.begin(), ++std::find(wstr.begin(), wstr.end(), L'>'));
    wstr.erase(wstr.find_last_of(L';'));

#if DEBUG_LOGS
    std::wcout << L"m_parse_path(): " << wstr << '\n';
#endif // !DEBUG_LOGS
}

void Parser::m_parse_app_name(std::wstring& wstr)
{
    wstr.erase(NULL, wstr.find_last_of(L"\\") + 1);

#if DEBUG_LOGS
    std::wcout << L"m_parse_app_name(): " << wstr << '\n';
#endif
}

void Parser::load_all_data_to_ram()
{
    std::pair<int, int> tmp_values{};
    std::wstring tmp_info{};
    bool is_single_button{};

    m_buttons.reserve(10);

    for (int i = 0; i < m_all_data.size(); ++i)
    {
        Button button{};
        tmp_info = m_all_data[i];

        is_single_button = m_is_single_button(tmp_info);
        button.set_is_single_button(is_single_button);

        tmp_values = m_parse_button_value(tmp_info);
        button.set_button(tmp_values.first, tmp_values.second);

        m_parse_path(tmp_info);
        button.set_app_path(tmp_info);

        m_parse_app_name(tmp_info);
        button.set_app_name(tmp_info);

        m_buttons.push_back(std::move(button));
    }
}
