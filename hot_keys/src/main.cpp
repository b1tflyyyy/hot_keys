#include <chrono>

#include "../win_functions/win_functions.hpp"

#include "../parser/parser.hpp"
#include "../button/button.hpp"

int main()
{  
    using namespace std::chrono_literals;
    Parser parser;

    try
    {
        parser.parse_all_data();
        parser.load_all_data_to_ram();

#if DEBUG_LOGS
        for (const auto& el : parser.get_buttons())
        {
            if (el.is_single_button())
            {
                std::wcout << L"single button: " << el.get_first_button() << L" app_path: " << el.get_app_path() << L" app_name: " << el.get_app_name() << L" closer_button: " << el.get_closer_button() << '\n';
                continue;
            }

            std::wcout << L"first button: " << el.get_first_button() << " second button: " << el.get_second_button() << L" app_path: " << el.get_app_path() << L" app_name: " << el.get_app_name() << L" closer_button: " << el.get_closer_button() << '\n';
        }
#endif

        for (;;)
        {
            for (const auto& el : parser.get_buttons())
            {
                std::this_thread::sleep_for(100ms);
                if (el.is_single_button())
                {
                    if (GetAsyncKeyState(el.get_first_button()) & 0x8000 && GetAsyncKeyState(Button::get_closer_button()) & 0x8000)
                    {
                        kill_app(el.get_app_name().c_str());
                        std::wcout << el.get_app_name() << '\n';
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
    }

    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
        std::cin.get();
    }

    return 0;
}