#pragma once
#ifndef PARSING_ERROR_HPP
#define PARSING_ERROR_HPP

#include "../error_interface/IError.hpp"

#include <string>

class parsing_error_info : public IError
{
private:
    const std::wstring m_expected_data;
    const std::wstring m_input_data;

    const std::size_t m_symbol_number;
    const wchar_t m_symbol;

    const std::size_t m_line_number;
    const std::wstring m_additional_error_info;

public:
    explicit parsing_error_info();
    ~parsing_error_info() override = default;

    explicit parsing_error_info(const std::wstring& expected_data,
                                const std::wstring& input_data,
                                const std::size_t symbol_number,
                                const wchar_t symbol,
                                std::size_t line_number,
                                const std::wstring& additional_error_info);

    explicit operator bool() const override;
    const std::wstring what() const override;
};

#endif // !PARSING_ERROR_HPP
