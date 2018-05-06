//Copyright ©2018, multics, Inc.All rights reserved.

#include <Windows.h>

BOOL WINAPI DllMain(__in HINSTANCE hInstDLL, 
				    __in DWORD fdwReason, 
					__in LPVOID lpReserved) {
	UNREFERENCED_PARAMETER(hInstDLL);
	UNREFERENCED_PARAMETER(lpReserved);

	//Perform actions based on the reason for calling
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		//Initialize once for each new process
		//Return FALSE to fail DLL Load
		break;
	case DLL_THREAD_ATTACH:
		//Do thread-specific initialization
		break;
	case DLL_THREAD_DETACH:
		//Do thread-specific cleanup
		break;
	case DLL_PROCESS_DETACH:
		//Perform any necessary cleanup
		break;
	default:
		//Should not have come here
		return FALSE;
	}

	return TRUE; //Successful DLL_PROCESS_ATTACH
}

__declspec(dllexport) int Dummy() { return 0; };