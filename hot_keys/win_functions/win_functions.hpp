#pragma once
#ifndef WIN_FUNCTIONS_HPP
#define WIN_FUNCTIONS_HPP

#include <Windows.h>
#include <process.h>
#include <TlHelp32.h>
#include <winbase.h>
#include <string.h>

VOID run_app(const LPCWSTR& app_path);
VOID kill_app(const LPCWSTR& app_name);

#endif // !WIN_FUNCTIONS_HPP
