#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <locale>
#include <algorithm>
#include <memory>

#include "../button/button.hpp"

#include "token_entry/token_entry.hpp"
#include "token_storage/token_storage.hpp"

#include "parser_errors/file_error/file_error.hpp"
#include "parser_errors/parsing_error/parsing_error.hpp"

class Parser final
{
public:
    Parser();
    ~Parser() = default;
    
    Parser(const Parser& other) = delete;
    Parser(const Parser&& other) = delete;

    const std::vector<Button>& get_buttons() const;
    
    std::unique_ptr<IError> separate_input_data(); // separate data from txt file by ';'
    __inline void remove_bad_symbols(std::wstring& data); // remove '\n' && ' '

    std::unique_ptr<IError> parse_token_entry(const std::wstring& data, const token_index token_index);
    void create_buttons();

    void parse_token_entries();
    const bool is_double_button(const std::wstring& data);

    std::unique_ptr<IError> parse_single_button(std::size_t& current_index);
    std::unique_ptr<IError> parse_double_button(std::size_t& current_index);

    void create_single_button(std::size_t& current_index);
    void create_double_button(std::size_t& current_index);

    // TEST funcs
    void show_parsed();
    void show_tokens();
    void show_buttons();

private:
    const std::wstring m_path;
    std::wifstream m_wfin;

    std::vector<Button> m_buttons;
    
    std::vector<std::wstring> m_separated_data;
    std::vector<token_entry> m_token_entries;
};

#endif // !PARSER_HPP

