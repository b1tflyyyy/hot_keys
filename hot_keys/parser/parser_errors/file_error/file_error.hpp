#pragma once
#ifndef FILE_ERROR_HPP
#define FILE_ERROR_HPP

#include "../error_interface/IError.hpp"

#include <string>

class file_error_info : public IError
{
private:
    const std::wstring m_file_path;
    const std::wstring m_additional_error_info;

public:
    explicit file_error_info() = default;
    ~file_error_info() override = default;

    explicit file_error_info(const std::wstring& file_path, const std::wstring additional_error_info);

    explicit operator bool() const override;
    const std::wstring what() const override;
};

#endif // !FILE_ERROR_HPP
