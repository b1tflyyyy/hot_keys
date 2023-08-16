#include "parser.hpp"

Parser::Parser() :
    m_path(std::move(L"config.txt"))
{ }

const std::vector<Button>& Parser::get_buttons() const
{
    return m_buttons;
}

std::unique_ptr<IError> Parser::separate_input_data()
{
    std::locale::global(std::locale(""));

    m_wfin.open(m_path, std::ios::in);
    m_wfin.imbue(std::locale(""));

    if (!m_wfin.is_open())
    {
        return std::make_unique<file_error_info>(file_error_info(m_path, L"ERROR opening the file "));
    }

    m_separated_data.reserve(10);

    std::wstring temp_data{};
    while (std::getline(m_wfin, temp_data, L';'))
    {
        remove_bad_symbols(temp_data); // remove bad symbols also remove ' ' in path, think about it
        m_separated_data.push_back(std::move(temp_data));
    }
    
    m_wfin.close();
    return std::make_unique<file_error_info>(file_error_info());
}

__inline void Parser::remove_bad_symbols(std::wstring& data)
{
    data.erase(std::remove_if(data.begin(), data.end(), [](char symbol) -> bool 
    {
        return symbol == L' ' || symbol == L'\n';
    }), data.end());
}

std::unique_ptr<IError> Parser::parse_token_entry(const std::wstring& data, const token_index token_index)
{
    std::wstring expected_data = token_storage::token[token_index];

    std::size_t i{};
    for (; i < expected_data.size(); ++i)
    {
        if (data[i] != expected_data[i])
        {
            // error with line number, here it is 0
            return std::make_unique<parsing_error_info>(parsing_error_info(expected_data, data, i, data[i], 0, L"parsing error!"));
        }
    }

    m_token_entries.push_back(token_entry({ expected_data, std::wstring(data.begin() + i, data.end()) }));
    return std::make_unique<parsing_error_info>(parsing_error_info());
}

void Parser::create_buttons()
{
    for (std::size_t i{}; i < m_token_entries.size();)
    {
        if (m_token_entries[i].get_value(token_storage::token[token_index::is_double_button]) == L"1")
        {
            create_double_button(i);
            continue;
        }

        create_single_button(i);
    }
}

void Parser::parse_token_entries()
{
    for (std::size_t i{}; i < m_separated_data.size();)
    {
        if (is_double_button(m_separated_data[i]))
        {
            parse_double_button(i);
            continue;
        }

        parse_single_button(i);
    }
}

const bool Parser::is_double_button(const std::wstring& data)
{
    std::wstring double_button_value(data.begin() + token_storage::token[token_index::is_double_button].size(), data.end());
    return std::stoi(double_button_value);
}

std::unique_ptr<IError> Parser::parse_single_button(std::size_t& current_index)
{
    auto error = parse_token_entry(m_separated_data[current_index++], token_index::is_double_button);
    error = parse_token_entry(m_separated_data[current_index++], token_index::first_button);
    error = parse_token_entry(m_separated_data[current_index++], token_index::path);

    return error;
}

std::unique_ptr<IError> Parser::parse_double_button(std::size_t& current_index)
{
    auto error = parse_token_entry(m_separated_data[current_index++], token_index::is_double_button);
    error = parse_token_entry(m_separated_data[current_index++], token_index::first_button);
    error = parse_token_entry(m_separated_data[current_index++], token_index::second_button);
    error = parse_token_entry(m_separated_data[current_index++], token_index::path);

    return error;
}

void Parser::create_single_button(std::size_t& current_index)
{
    bool is_double_button_value = std::stoi(m_token_entries[current_index++].get_value(token_storage::token[token_index::is_double_button]));
    std::int32_t first_button_value = std::stoi(m_token_entries[current_index++].get_value(token_storage::token[token_index::first_button]), nullptr, 16);
    std::wstring app_path_value = m_token_entries[current_index++].get_value(token_storage::token[token_index::path]);

    // app_name is blank here
    m_buttons.emplace_back(is_double_button_value, first_button_value, 0, app_path_value, L"");
}

void Parser::create_double_button(std::size_t& current_index)
{
    bool is_double_button_value = std::stoi(m_token_entries[current_index++].get_value(token_storage::token[token_index::is_double_button]));
    std::int32_t first_button_value = std::stoi(m_token_entries[current_index++].get_value(token_storage::token[token_index::first_button]), nullptr, 16);
    std::int32_t second_button_value = std::stoi(m_token_entries[current_index++].get_value(token_storage::token[token_index::second_button]), nullptr, 16);
    std::wstring app_path_value = m_token_entries[current_index++].get_value(token_storage::token[token_index::path]);

    // app_name is blank here
    m_buttons.emplace_back(is_double_button_value, first_button_value, second_button_value, app_path_value, L"");
}

/* ======================================== TEST PART ======================================== */
void Parser::show_parsed()
{
    std::wcout << "======================================== parsed input data ========================================\n";
    for (std::size_t i{}; i < m_separated_data.size(); ++i)
    {
        std::wcout << m_separated_data[i];
        std::wcout << std::endl;
    }
    std::wcout << std::endl;
    std::wcout << std::endl;
}

void Parser::show_tokens()
{
    std::wcout << "======================================== token entries ========================================\n";

    for (std::size_t i{}; i < m_token_entries.size();)
    {
        if (m_token_entries[i].get_value(token_storage::token[token_index::is_double_button]) == L"1")
        {
            std::wcout << m_token_entries[i++].get_value(token_storage::token[token_index::is_double_button]) << '\n';
            std::wcout << m_token_entries[i++].get_value(token_storage::token[token_index::first_button]) << '\n';
            std::wcout << m_token_entries[i++].get_value(token_storage::token[token_index::second_button]) << '\n';
            std::wcout << m_token_entries[i++].get_value(token_storage::token[token_index::path]) << '\n';

            continue;
        }

        std::wcout << m_token_entries[i++].get_value(token_storage::token[token_index::is_double_button]) << '\n';
        std::wcout << m_token_entries[i++].get_value(token_storage::token[token_index::first_button]) << '\n';
        std::wcout << m_token_entries[i++].get_value(token_storage::token[token_index::path]) << '\n';
    }
}

void Parser::show_buttons()
{
    std::wcout << "======================================== BUTTONS ========================================\n";

    for (const auto& el : m_buttons)
    {
        std::wcout << L"first button: " << el.get_first_button() << " second button: " << el.get_second_button() << L" app_path: " << el.get_app_path() << L" app_name: " << el.get_app_name() << L" closer_button: " << el.get_closer_button() << '\n';
    }
}
