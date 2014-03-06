
#include "Rejestr.h";
#include <new>;
#include "GUID.h";
#include "Fabryka.h";
HINSTANCE mojaDLLka;
BOOL WINAPI DllMain(HINSTANCE module_handle, DWORD reason_for_call, LPVOID reserved)
{
	mojaDLLka=module_handle;
	return TRUE;
}


volatile ULONG usageCount = 0;


//czy mo¿na Ciebie, dllko, usun¹æ z pamiêci?


HRESULT __stdcall DllCanUnloadNow() {
	return usageCount > 0 ? S_FALSE : S_OK;
}



//cls to guid naszej klasy, której obiekt chcemy wytworzyæ (np Word), iid to interfejs fabryki (jest wiele, np IClassFactory2), ptr to wskaŸnik na vtable obiektu (deserializuje siê na interfejs)


HRESULT __stdcall DllGetClassObject(REFCLSID cls, REFIID iid, void **ptr) {
	if(ptr == NULL) return E_INVALIDARG;
	*ptr = NULL;
	if(cls != CLSID_Stos) return CLASS_E_CLASSNOTAVAILABLE;//wytwarzamy tylko klasê Stos
	if(iid != IID_IClassFactory) return CLASS_E_CLASSNOTAVAILABLE;//dysponujemy tylko fabryk¹ która implementuje IClassFactory (a nie IClassFactory2)
	StosFactory *fact = new (std::nothrow) StosFactory();// tworzenie nowej fabryki
	if(fact == NULL) return E_OUTOFMEMORY;//memory full
	HRESULT rv = fact->QueryInterface(iid, ptr);//dostajemy interfejs fabryki typu IClassFactory (u nas zwraca po prostu sam¹ fabrykê)
	if(FAILED(rv)) { delete fact; *ptr = NULL; };//jeœli coœ nie tak, usuñ fabrykê
	return rv;
}
///////////////////////////////////////////////////////////////////////////////
//
//Registry.cpp
//
//Implementation for DllRegisterServer,DllUnregisterServer
//Contains code to write COM server data into the registry and 
//also removing the data that had been written into the registry 
//by this module.
//

#include    <windows.h>
#include    <objbase.h>

#include    "GUID.h"
#include <iostream>

#define     AddObjProgId    "adamborowskipl.ksr.1"


BOOL   HelperWriteKey(
	HKEY roothk,
	const char *lpSubKey,
	LPCTSTR val_name, 
	DWORD dwType,
	void *lpvData, 
	DWORD dwDataSize)
{
	//
	//Helper function for doing the registry write operations
	//
	//roothk:either of HKCR, HKLM, etc

	//lpSubKey: the key relative to 'roothk'

	//val_name:the key value name where the data will be written

	//dwType:the type of data that will be written ,REG_SZ,REG_BINARY, etc.

	//lpvData:a pointer to the data buffer

	//dwDataSize:the size of the data pointed to by lpvData
	//
	//
	//std::cout<<"CLSID: "<<lpSubKey<<"\n";

	HKEY hk;

	LSTATUS status;

	std::cout<<"[ proba zapisania rejestru: korzen = "<<roothk<<", adres = "<<lpSubKey<<", nazwa = "<<(val_name==0?"@":val_name)<<", wartosc = "<<lpvData<<" ]\n";

	status=RegCreateKey(roothk,lpSubKey,&hk);

	if (ERROR_SUCCESS !=status  ){ std::cout<<"[regCreate failed: "<<status<<"]\n"; return FALSE;}


	status=RegSetValueEx(hk,val_name,0,dwType,(CONST BYTE *)lpvData,dwDataSize);


	if (ERROR_SUCCESS != status){ std::cout<<"[regSetValueEx failed: "<<status<<"]\n"; return FALSE;}

	status = RegCloseKey(hk);

	if (ERROR_SUCCESS !=status) { std::cout<<"[regCloseKey failed: "<<status<<"]\n"; return FALSE;}
	return TRUE;

}



///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

HRESULT  __stdcall DllRegisterServer(void)
{
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	//
	//As per COM guidelines, every self installable COM inprocess component
	//should export the function DllRegisterServer for printing the 
	//specified information to the registry
	//
	//

	WCHAR *lpwszClsid;
	char szBuff[MAX_PATH]="";
	char szClsid[MAX_PATH]="", szInproc[MAX_PATH]="",szProgId[MAX_PATH];
	char szDescriptionVal[256]="";

	StringFromCLSID(CLSID_Stos,&lpwszClsid);

	wsprintf(szClsid,"%S",lpwszClsid);
	wsprintf(szInproc,"%s\\%s\\%s","WOW6432Node\\CLSID",szClsid,"InprocServer32");
	wsprintf(szProgId,"%s\\%s\\%s","WOW6432Node\\CLSID",szClsid,"ProgId");


	//
	//write the default value 
	//
	wsprintf(szBuff,"%s","KSR TAKIE LABKI");
	wsprintf(szDescriptionVal,"%s\\%s","WOW6432Node\\CLSID",szClsid);

	HelperWriteKey (
		HKEY_CLASSES_ROOT,
		szDescriptionVal,
		NULL,//write to the "default" value
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
		);


	//
	//write the "InprocServer32" key data
	//
	GetModuleFileName(
		mojaDLLka,
		szBuff,
		sizeof(szBuff));
	std::cout<<"[adres dll komponentu: "<<szBuff<<"  ]";
	HelperWriteKey (
		HKEY_CLASSES_ROOT,
		szInproc,
		NULL,//write to the "default" value
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
		);

	//
	//write the "ProgId" key data under HKCR\clsid\{---}\ProgId
	//
	lstrcpy(szBuff,AddObjProgId);
	HelperWriteKey (
		HKEY_CLASSES_ROOT,
		szProgId,
		NULL,
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
		);


	//
	//write the "ProgId" data under HKCR\CodeGuru.FastAddition
	//
	wsprintf(szBuff,"%s","Fast Addition Algorithm");
	HelperWriteKey (
		HKEY_CLASSES_ROOT,
		AddObjProgId,
		NULL,
		REG_SZ,
		(void*)szBuff,
		lstrlen(szBuff)
		);


	wsprintf(szProgId,"%s\\%s",AddObjProgId,"CLSID");
	HelperWriteKey (
		HKEY_CLASSES_ROOT,
		szProgId,
		NULL,
		REG_SZ,
		(void*)szClsid,
		lstrlen(szClsid)
		);

	return 1;

}


///////////////////////////////////////////////////////////////////////////////

HRESULT  __stdcall DllUnregisterServer(void)
{
	//
	//As per COM guidelines, every self removable COM inprocess component
	//should export the function DllUnregisterServer for erasing all the 
	//information that was printed into the registry
	//
	//

	char szKeyName[256]="",szClsid[256]="";
	WCHAR *lpwszClsid;



	//
	//delete the ProgId entry
	//
	wsprintf(szKeyName,"%s\\%s",AddObjProgId,"CLSID");
	RegDeleteKey(HKEY_CLASSES_ROOT,szKeyName);
	RegDeleteKey(HKEY_CLASSES_ROOT,AddObjProgId);


	//
	//delete the CLSID entry for this COM object
	//
	StringFromCLSID(
		CLSID_Stos,
		&lpwszClsid);
	wsprintf(szClsid,"%S",lpwszClsid);
	wsprintf(szKeyName,"%s\\%s\\%s","CLSID",szClsid,"InprocServer32");
	RegDeleteKey(HKEY_CLASSES_ROOT,szKeyName);

	wsprintf(szKeyName,"%s\\%s\\%s","CLSID",szClsid,"ProgId");
	RegDeleteKey(HKEY_CLASSES_ROOT,szKeyName);

	wsprintf(szKeyName,"%s\\%s","CLSID",szClsid);
	RegDeleteKey(HKEY_CLASSES_ROOT,szKeyName);

	return 1;

}



