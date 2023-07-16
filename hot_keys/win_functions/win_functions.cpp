#include "win_functions.hpp"

VOID run_app(const LPCWSTR& app_path)
{
    STARTUPINFO startup_info{};
    PROCESS_INFORMATION process_information{};

    ZeroMemory(&startup_info, sizeof(startup_info));
    ZeroMemory(&process_information, sizeof(process_information));

    CreateProcessW(app_path,
                   nullptr,
                   nullptr,
                   nullptr,
                   FALSE,
                   NULL,
                   nullptr,
                   nullptr,
                   &startup_info,
                   &process_information);

    CloseHandle(process_information.hProcess);
    CloseHandle(process_information.hThread);
}

VOID kill_app(const LPCWSTR& app_name)
{
    HANDLE h_snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    
    PROCESSENTRY32 p_entry{};
    p_entry.dwSize = sizeof(p_entry);

    BOOL h_result = Process32First(h_snap_shot, &p_entry);

    while (h_result)
    {
        if (wcscmp(p_entry.szExeFile, app_name) == NULL)
        {
            HANDLE h_process = OpenProcess(PROCESS_TERMINATE, FALSE, static_cast<DWORD>(p_entry.th32ProcessID));

            if (h_process != nullptr)
            {
                TerminateProcess(h_process, 9);
                CloseHandle(h_process);
            }
        }

        h_result = Process32Next(h_snap_shot, &p_entry);
    }

    CloseHandle(h_snap_shot);
}