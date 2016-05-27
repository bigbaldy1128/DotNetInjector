#include<windows.h>
#include <stdio.h>
#include "inject.h"

BOOL EnableDebugPrivilege(BOOL bEnable)
{
	BOOL fOK = FALSE;
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{ 
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		fOK = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	return fOK;
}

bool Inject(DWORD pid)
{
	LPTHREAD_START_ROUTINE start_routine = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
	EnableDebugPrivilege(TRUE);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess)
	{
		auto dll_name_length = strlen("hook.dll") + 1;
		LPVOID Param = VirtualAllocEx(hProcess, 0, dll_name_length, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (WriteProcessMemory(hProcess, Param, "hook.dll", dll_name_length, NULL))
		{
			HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, start_routine, Param, 0, NULL);
			if (hThread)
			{
				WaitForSingleObject(hThread, INFINITE);
				//一段shellcode,功能是调用Hook.dll中的Hook方法
				FILE* in_file = fopen("shellcode.bin", "r");
				char shell_code[1024];
				auto shell_code_length=fread(shell_code, 1, 1024, in_file);
				fclose(in_file);
				auto hook_method_routine= (LPTHREAD_START_ROUTINE)VirtualAllocEx(hProcess, 0, shell_code_length, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				if (WriteProcessMemory(hProcess, hook_method_routine, shell_code, shell_code_length, NULL))
				{
					HANDLE hThread2 = CreateRemoteThread(hProcess, NULL, NULL, hook_method_routine, NULL, 0, NULL);
					if (hThread2) //success
					{
						WaitForSingleObject(hThread2, INFINITE);
						return true;
					}
				}
			}
		}
	}
	return false;
}