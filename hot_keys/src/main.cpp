#include <chrono>
#include <thread>

#include "../win_functions/win_functions.hpp"

#include "../parser/parser.hpp"
#include "../button/button.hpp"

int main()
{  
    using namespace std::chrono_literals;
    Parser parser;

    auto error = parser.separate_input_data();
    parser.parse_token_entries();
    parser.create_buttons();
    
    parser.show_buttons();
    parser.show_parsed();
    parser.show_tokens();


    for (;;)
    {
        for (const auto& el : parser.get_buttons())
        {
            std::this_thread::sleep_for(100ms);
            if (!el.is_double_button())
            {
                if (GetAsyncKeyState(el.get_first_button()) & 0x8000 && GetAsyncKeyState(Button::get_closer_button()) & 0x8000)
                {
                    kill_app(el.get_app_name().c_str());
                    std::this_thread::sleep_for(200ms);
                    continue;
                }
                else if (GetAsyncKeyState(el.get_first_button()) & 0x8000)
                {
                    run_app(el.get_app_path().c_str());
                    std::this_thread::sleep_for(200ms);
                    continue;
                }

                continue;
            }

            if (GetAsyncKeyState(el.get_first_button()) & 0x8000 &&
                GetAsyncKeyState(el.get_second_button()) & 0x8000 &&
                GetAsyncKeyState(Button::get_closer_button()) & 0x8000)
            {
                kill_app(el.get_app_name().c_str());
                std::this_thread::sleep_for(200ms);
                continue;
            }
            else if (GetAsyncKeyState(el.get_first_button()) & 0x8000 && GetAsyncKeyState(el.get_second_button()) & 0x8000)
            {
                run_app(el.get_app_path().c_str());
                std::this_thread::sleep_for(200ms);
                continue;
            }
        }

    }

    return 0;
}