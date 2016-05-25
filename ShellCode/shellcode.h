#pragma once
#include<windows.h>
DWORD __stdcall unicode_ror13_hash(const WCHAR *unicode_string);
DWORD __stdcall ror13_hash(const char *string);
PPEB __declspec(naked) get_peb(void);
HMODULE __stdcall find_kernel32(void);
HMODULE __stdcall find_module_by_hash(DWORD hash)