#include<windows.h>
#include<stdio.h>
#include<objbase.h>
#include "hook.h"
#import "../ComForHook/bin/Release/ComForHook.tlb"
//BOOL APIENTRY DllMain( HMODULE hModule,
//					   DWORD  dwReason,
//					   LPVOID lpReserved
//					  )
//{
//	Hook(); //ºÇºÇ£¬ÕâÑù»áËÀËø
//	return TRUE;
//}

EXTERN_C __declspec(dllexport) VOID Hook()
{
	CoInitialize(NULL);
	ComForHook::IHookPtr hook(__uuidof(ComForHook::Hook));
	hook->Apply();
	CoUninitialize();
}