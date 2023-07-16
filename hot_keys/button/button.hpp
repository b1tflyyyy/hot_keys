#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

class Button final
{
public:
    Button() = default;
    
    inline ~Button() noexcept = default;

    constexpr Button(const Button& other) = default;
    Button(Button&& other) noexcept;

    void set_button(const int first_value, const int second_value);

    const int get_first_button() const;    
    const int get_second_button() const;

    const std::wstring& get_app_path() const;
    void set_app_path(const std::wstring& app_path);

    const std::wstring& get_app_name() const;
    void set_app_name(const std::wstring& app_name);

    const bool is_single_button() const;
    void set_is_single_button(const bool is_single_button);

    static int get_closer_button();

private:
    int m_first_button;
    int m_second_button;
    std::wstring m_app_path;
    std::wstring m_app_name;
    bool m_is_single_button;
    constexpr static int m_closer_button = 0x2E; // delete button
};

#endif // !BUTTON_HPP
