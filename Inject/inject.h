#pragma once
#include<Windows.h>
#define DLLExport EXTERN_C __declspec(dllexport)

DLLExport bool Inject(DWORD pid);