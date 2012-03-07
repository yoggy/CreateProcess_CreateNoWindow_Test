//
// see also...
//
//   CreateProcess (MSDN)
//   http://msdn.microsoft.com/ja-jp/library/cc429066.aspx
//   http://msdn.microsoft.com/en-us/library/ms682425.aspx
//
#include <SDKDDKVer.h>
#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
#ifdef _DEBUG
	char *target_cmd = "TestConsoleAppD.exe arg1 arg2 arg3";
#else
	char *target_cmd = "TestConsoleApp.exe arg1 arg2 arg3";
#endif

	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;
	memset(&startup_info, 0, sizeof(STARTUPINFO));
	startup_info.cb = sizeof(STARTUPINFO);
	memset(&process_info, 0, sizeof(PROCESS_INFORMATION));

	BOOL rv = ::CreateProcess(
		NULL,				// LPCTSTR lpApplicationName
		target_cmd,			// LPTSTR lpCommandLine
		NULL,				// LPSECURITY_ATTRIBUTES lpProcessAttributes
		NULL,				// LPSECURITY_ATTRIBUTES lpThreadAttributes
		FALSE,				// BOOL bInheritHandles
		CREATE_NO_WINDOW,	// DWORD dwCreationFlags
		NULL,				// LPVOID lpEnvironment
		NULL,				// LPCTSTR lpCurrentDirectory
		&startup_info,		// LPSTARTUPINFO lpStartupInfo
		&process_info		// LPPROCESS_INFORMATION lpProcessInformation
		);
	
	// http://msdn.microsoft.com/en-us/library/ms682425.aspx
	// If lpApplicationName is NULL, the first white space-delimited token of the command line
	// specifies the module name. If you are using a long file name that contains a space, 
	// use quoted strings to indicate where the file name ends and the arguments begin 
	// (see the explanation for the lpApplicationName parameter).

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
