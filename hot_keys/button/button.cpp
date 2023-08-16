#include "button.hpp"

Button::Button(const bool is_double_button, 
               const std::int32_t first_button, 
               const std::int32_t second_button, 
               const std::wstring& app_path,
               const std::wstring& app_name) :
    m_is_double_button(is_double_button), 
    m_first_button(first_button), 
    m_second_button(second_button),
    m_app_path(app_path),
    m_app_name(app_name)
{ }

Button::Button(Button&& other) noexcept
{
    this->m_first_button = other.m_first_button;
    this->m_second_button = other.m_second_button;
    this->m_app_path = std::move(other.m_app_path);
    this->m_app_name = std::move(other.m_app_name);
    this->m_is_double_button = other.m_is_double_button;
}

const std::int32_t Button::get_first_button() const
{
    return m_first_button;
}

const std::int32_t Button::get_second_button() const
{
    return m_second_button;
}

//void Button::set_button(const std::int32_t first_value, const std::int32_t second_value)
//{
//    m_first_button = first_value;
//    m_second_button = second_value;
//}

const std::wstring& Button::get_app_path() const
{
    return m_app_path;
}

//void Button::set_app_path(const std::wstring& app_path)
//{
//    m_app_path = app_path;
//}

const std::wstring& Button::get_app_name() const
{
    return m_app_name;
}

//void Button::set_app_name(const std::wstring& app_name)
//{
//    m_app_name = app_name;
//}

const bool Button::is_double_button() const
{
    return m_is_double_button;
}

//void Button::set_is_single_button(const bool is_single_button)
//{
//    m_is_double_button = is_single_button;
//}

std::int32_t Button::get_closer_button()
{
    return m_closer_button;
}