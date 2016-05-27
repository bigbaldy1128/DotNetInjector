@echo off
copy ..\ComForHook\bin\Release\ComForHook.dll
copy ..\DotNetDetour\bin\Release\DotNetDetour.dll
copy ..\x64\Release\Hook.dll
copy ..\x64\Release\shellcode.bin
copy ..\x64\Release\Inject.dll
copy ..\Target\bin\Release\Target.exe
copy ..\HookMain\bin\Release\HookMain.exe
copy ..\CustomMonitor\bin\Release\CustomMonitor.dll monitors\