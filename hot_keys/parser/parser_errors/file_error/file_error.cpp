#include "file_error.hpp"

file_error_info::file_error_info(const std::wstring& file_path, const std::wstring additional_error_info) :
    m_file_path(file_path), m_additional_error_info(additional_error_info)
{ }

file_error_info::operator bool() const
{
    return m_file_path != L"" && m_additional_error_info != L"";
}

const std::wstring file_error_info::what() const
{
    return m_additional_error_info + m_file_path;
}