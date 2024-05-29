//	Get Directory
//	Get FF7Remake Window
//	Get FF7Remale PID via Window
//	OpenProcess
//	Allocate Memory into process
//	Write Dll to allocated memory
//	Call LoadLibrary 
//	Cleanup

#include <Windows.h>
#include <cstdio>
#include <string>


/// HELPERS
struct CProcess
{
	HWND window;
	DWORD procID;
	HANDLE hProc;
};


std::string GetCurrentPath();
int ExitWithErrorMsg(const char* eMSG, DWORD eCODE);
bool GetProcessByWindow(const char* lpTitle, CProcess* outProcess);
bool Inject(HANDLE hProc, const char* lpModulePath);


///	ENTRYPOINT
int main()
{
	//	Resolve Process
	CProcess proc;
	if (!GetProcessByWindow("FINAL FANTASY VII REMAKE", &proc))
		ExitWithErrorMsg("failed to resolve process info.", GetLastError());
	printf("[+] found window handle: %d\n[+] found process ID: %d\n[+] obtained handle to process: %d\n", 
		proc.window, proc.procID, proc.hProc);

	//	set window focus
	SetForegroundWindow(proc.window);
	SetActiveWindow(proc.window);
	printf("[+] set target as active window\n");

	//	inject 
	if (!Inject(proc.hProc, (GetCurrentPath() + "\\" + "FF7Internal.dll").c_str()))
	{
		CloseHandle(proc.hProc);
		return ExitWithErrorMsg("Inject", GetLastError());
	}
	
	//	cleanup
	printf("[+] sucessfully injected module into the process.\n");
	CloseHandle(proc.hProc);

	return EXIT_SUCCESS;
}


/// ---------------------------------------------------------------------------------


std::string GetCurrentPath()
{
	std::string result;

	char buffer[MAX_PATH];
	if (GetCurrentDirectoryA(MAX_PATH, buffer) > 0)
		result = std::string(buffer);

	return result;
}

int ExitWithErrorMsg(const char* eMSG, DWORD lastError = 0)
{
	//	format 'GetLastError'
	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
	std::string errorMsg(messageBuffer, size);
	LocalFree(messageBuffer);

	//	print message box error
	char buf[512];	//	512kb of storage
	sprintf_s(buf, "Final Fantasy VII Remake Injector encountered an error and will now exit.\n\nMSG: %s\nSRC: %s", errorMsg.c_str(), eMSG);
	MessageBoxA(nullptr, buf, "Final Fantasy VII Injector Fatal Error", MB_ICONWARNING);
	
	//	cleanup
	free(buf);
	return EXIT_FAILURE;
}

bool GetProcessByWindow(const char* lpTitle, CProcess* outProcess)
{
	//	 get game window
	HWND wndw = FindWindowA(0, lpTitle);
	if (!wndw)
		false;

	//	get process id
	DWORD procID;
	if (!GetWindowThreadProcessId(wndw, &procID))
		false;

	//	open handle to process
	HANDLE hProc;
	hProc = OpenProcess(PROCESS_ALL_ACCESS, false, procID);
	if (hProc == INVALID_HANDLE_VALUE)
		return false;

	//	store result
	outProcess->procID = procID;
	outProcess->window = wndw;
	outProcess->hProc = hProc;

	return true;
}

bool Inject(HANDLE hProc, const char* lpModulePath)
{
	//	allocate memory to process 
	void* cave = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!cave)
		return false;

	//	write dll to memory
	SIZE_T bytesWritten;
	SIZE_T lpSize = strlen(lpModulePath) + 1;
	if (!WriteProcessMemory(hProc, cave, lpModulePath, lpSize, &bytesWritten) || bytesWritten != lpSize)
	{
		VirtualFreeEx(hProc, cave, 0, MEM_RELEASE);
		return false;
	}

	//	execute DLLMain in module
	HANDLE hThread = CreateRemoteThread(hProc, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA), cave, 0, 0);
	if (hThread == INVALID_HANDLE_VALUE)
	{
		VirtualFreeEx(hProc, cave, 0, MEM_RELEASE);
		return false;
	}

	//	cleanup
	if (hThread)
		CloseHandle(hThread);

	return true;
}