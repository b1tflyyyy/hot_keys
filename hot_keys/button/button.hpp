#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <cstdint>

class Button final
{
public:
    Button() = default;
    explicit Button(const bool is_double_button,
                    const std::int32_t first_button,
                    const std::int32_t second_button,
                    const std::wstring& app_path,
                    const std::wstring& app_name);

    ~Button() = default;

    Button(const Button& other) = default;
    Button(Button&& other) noexcept;

    // void set_button(const std::int32_t first_value, const std::int32_t second_value = 0);

    const std::int32_t get_first_button() const;
    const std::int32_t get_second_button() const;

    const std::wstring& get_app_path() const;
    // void set_app_path(const std::wstring& app_path);

    const std::wstring& get_app_name() const;
    // void set_app_name(const std::wstring& app_name);

    const bool is_double_button() const;
    // void set_is_single_button(const bool is_single_button);

    static std::int32_t get_closer_button();

private:
    std::int32_t m_first_button;
    std::int32_t m_second_button;
    std::wstring m_app_path;
    std::wstring m_app_name;
    bool m_is_double_button;
    constexpr static std::int32_t m_closer_button = 0x2E; // delete button
};

#endif // !BUTTON_HPP
