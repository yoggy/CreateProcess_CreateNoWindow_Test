#include <SDKDDKVer.h>
#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
#ifdef _DEBUG
	const char *target_cmd = "TestConsoleAppD.exe";
#else
	const char *target_cmd = "TestConsoleApp.exe";
#endif

	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;
	memset(&startup_info, 0, sizeof(STARTUPINFO));
	startup_info.cb = sizeof(STARTUPINFO);
	memset(&process_info, 0, sizeof(PROCESS_INFORMATION));

	BOOL rv = ::CreateProcess(
		target_cmd,			// LPCTSTR lpApplicationName
		NULL,				// LPTSTR lpCommandLine
		NULL,				// LPSECURITY_ATTRIBUTES lpProcessAttributes
		NULL,				// LPSECURITY_ATTRIBUTES lpThreadAttributes
		FALSE,				// BOOL bInheritHandles
		CREATE_NO_WINDOW,	// DWORD dwCreationFlags
		NULL,				// LPVOID lpEnvironment
		NULL,				// LPCTSTR lpCurrentDirectory
		&startup_info,		// LPSTARTUPINFO lpStartupInfo
		&process_info		// LPPROCESS_INFORMATION lpProcessInformation
		);

	if (rv == FALSE) {
		::MessageBox(NULL, "CreateProcess() failed...", "error", MB_OK);
		return 0;
	}
	::CloseHandle(process_info.hThread);
	
	::WaitForSingleObject(process_info.hProcess, INFINITE);
	::CloseHandle(process_info.hProcess);

	::MessageBox(NULL, "CreateProcess() finish", "error", MB_OK);

	return 0;
}
