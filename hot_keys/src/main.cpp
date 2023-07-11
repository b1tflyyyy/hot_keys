#include <Windows.h>
#include <chrono>

#include "../parser/parser.hpp"

// TODO: create models single button && pair of button ?

VOID run_app(LPCWSTR app_path)
{
    STARTUPINFO startup_info{};
    PROCESS_INFORMATION process_information{};

    ZeroMemory(&startup_info, sizeof(startup_info));
    ZeroMemory(&process_information, sizeof(process_information));

    CreateProcessW(app_path,
                   NULL,
                   NULL,
                   FALSE,
                   NULL,
                   NULL,
                   NULL,
                   NULL,
                   &startup_info,
                   &process_information);

    CloseHandle(process_information.hProcess);
    CloseHandle(process_information.hThread);
}

int main()
{  
    using namespace std::chrono_literals;
    Parser parser;

    try
    {
        parser.m_parse_all_data();
        parser.m_set_to_map();

        for (;;)
        {
            for (const auto& [button_value, path] : parser.get_single_buttons())
            {
                if (GetAsyncKeyState(button_value) & 0x8000)
                {
                    run_app(path.c_str());
                }

                std::this_thread::sleep_for(50ms);
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }

    return 0;
}