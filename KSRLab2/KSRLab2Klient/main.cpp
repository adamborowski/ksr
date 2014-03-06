#include <Windows.h>
#include <iostream>
#include "../KSRLab2/Komponent.h"
#include "../KSRLab2/GUID.h"
int main(){

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);


	IStos *s;
	HRESULT rv;



	CLSID CLSID_Stos_FROM_PROGID;
	CLSIDFromProgID(L"adamborowskipl.ksr.1", &CLSID_Stos_FROM_PROGID);



	rv = CoCreateInstance(CLSID_Stos_FROM_PROGID, NULL, CLSCTX_INPROC_SERVER, IID_IStos, (void **)&s);
	//rv = CoCreateInstance(CLSID_Stos, NULL, CLSCTX_INPROC_SERVER, IID_IStos, (void **)&s);

	s->Push(5);

	int ret;
	s->Pop(&ret);

	std::cout<<"wynik: "<<ret;




	CoUninitialize();	return 0;
}