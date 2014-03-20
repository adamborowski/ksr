#include<windows.h>
#include "oleauto.h"
#include "../Lab3_midl/stos.h"
int main() {
	HRESULT rc;
	OLECHAR filename[MAX_PATH];
	ITypeLib *tl;
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	// rejestracja
	mbstowcs(filename, "../Lab3_midl/stos.tlb", sizeof(filename));
	rc = LoadTypeLibEx(filename, REGKIND_REGISTER, &tl);
	if(rc == S_OK) tl->Release();
	// wyrejestrowanie
	rc = UnRegisterTypeLib(LIBID_KSRStack, 1, 0, LANG_NEUTRAL, SYS_WIN32);
	CoUninitialize();
	return 0;
};