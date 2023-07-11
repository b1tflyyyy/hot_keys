#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#define DEBUG_LOGS false

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <locale>
#include <algorithm>

class Parser final
{
public:
    Parser();
    ~Parser() = default;
    
    Parser(const Parser& other) = delete;
    Parser(const Parser&& other) = delete;

    void m_set_to_map();
    void m_parse_all_data();

    const std::map<int, std::wstring>& get_single_buttons();

private:
    std::wstring m_path;
    std::wifstream m_wfin;

private:
    std::map<int, std::wstring> m_single_button;
    std::vector<std::wstring> m_all_data;
    
    int m_parse_button_value(std::wstring& wstr);
    std::wstring m_parse_path(std::wstring& wstr);
    bool m_is_double_button(const std::wstring& wstr);
};

#endif // !PARSER_HPP

