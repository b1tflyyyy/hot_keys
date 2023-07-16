#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#define DEBUG_LOGS false

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <locale>
#include <algorithm>

#include "../button/button.hpp"

class Parser final
{
public:
    Parser();
    ~Parser() = default;
    
    Parser(const Parser& other) = delete;
    Parser(const Parser&& other) = delete;

    void parse_all_data();
    void load_all_data_to_ram();

    const std::vector<Button>& get_buttons() const;

private:
    std::wstring m_path;
    std::wifstream m_wfin;

private:
    std::vector<Button> m_buttons;
    std::vector<std::wstring> m_all_data;
    
    std::pair<int, int> m_parse_button_value(const std::wstring& wstr);
    void m_parse_app_name(std::wstring& wstr);
    void m_parse_path(std::wstring& wstr);
    bool m_is_single_button(const std::wstring_view wstr);
};

#endif // !PARSER_HPP

