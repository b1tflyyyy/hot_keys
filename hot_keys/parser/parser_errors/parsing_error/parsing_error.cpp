#include "parsing_error.hpp"

parsing_error_info::parsing_error_info() :
    m_expected_data(L""), 
    m_input_data(L""),
    m_symbol_number(0),
    m_symbol(L' '),
    m_line_number(0),
    m_additional_error_info(L"")
{ }

parsing_error_info::parsing_error_info(const std::wstring& expected_data,
                                                const std::wstring& input_data,
                                                const std::size_t symbol_number,
                                                const wchar_t symbol,
                                                std::size_t line_number,
                                                const std::wstring& additional_error_info) :
    m_expected_data(expected_data), 
    m_input_data(input_data),
    m_symbol_number(symbol_number),
    m_symbol(symbol),
    m_line_number(line_number),
    m_additional_error_info(additional_error_info)
{ }

parsing_error_info::operator bool() const
{
    return m_expected_data != L"" &&
           m_input_data != L"" &&
           m_symbol_number != 0 &&
           m_symbol != L' ',
           m_line_number != 0 &&
           m_additional_error_info != L"";
}

const std::wstring parsing_error_info::what() const
{
    return L"expected data: " + m_expected_data + L"\n" +
           L"input data: " + m_input_data + L"\n" +
           L"error symbol number: " + std::to_wstring(m_symbol_number) + L"\n" +
           L"error symbol: " + m_symbol + L"\n" +
           L"error in " + std::to_wstring(m_line_number) + L" line" + L"\n" +
           L"additional information: " + m_additional_error_info + L"\n";
}