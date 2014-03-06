#include "Fabryka.h";
#include "Komponent.h";
#include "GUID.h";
#include <new>
//jeden komponent (np Word) udostêpnia wiele interfejsów (np. IChart, IExcelDocument, IEquotation)
HRESULT STDMETHODCALLTYPE StosFactory::QueryInterface(REFIID iid, void **ptr) {
	if(ptr == NULL) return E_POINTER;//nie ma gdzie zwróciæ tablicy wskaŸników (virtual method table) - tutaj bêdzie to po prostu lista metod naszej klasy
	*ptr = NULL;
	if(iid == IID_IUnknown) *ptr = this;//pyta o unknown, u nas jest tylko jeden wiêc zwróæmy virtual method table fabryki stosu
	else if(iid == IID_IClassFactory) *ptr = this;//pyta o class factory, zwróæmy virtual method table fabryki stosu
	if(*ptr != NULL) { AddRef(); return S_OK; };//dajemy mu dostêp do naszej klasy, wiêc zwiêkszamy licznik referencji
	return E_NOINTERFACE;
};

//implementacja liczenia referencji
ULONG STDMETHODCALLTYPE StosFactory::AddRef() {
	InterlockedIncrement(&m_ref);
	return m_ref;
};
ULONG STDMETHODCALLTYPE StosFactory::Release() {
	ULONG rv = InterlockedDecrement(&m_ref);
	if(rv == 0) delete this;
	return rv;
};
extern volatile ULONG usageCount;//statyczna informacja o liczbie ¿ywych obiektów
//#include <iostream>
StosFactory::StosFactory() {
	InterlockedIncrement(&usageCount);
	m_ref = 0;
	// pozosta³a inicjalizacja
	//std::cout<<"stos factory";
};
StosFactory::~StosFactory() {
	InterlockedDecrement(&usageCount);
};

// implementacja fabryki
HRESULT STDMETHODCALLTYPE StosFactory::LockServer(BOOL lock) {
	if(lock) InterlockedIncrement(&usageCount); 
	else InterlockedDecrement(&usageCount);
	return S_OK;
};

/*
 * IUnknown *outer - ignorowaæ to (jakiœ obiekt do agregacji...
 * REFIID iid - identyfikator interfejsu z klasy stosu (np. Word -> IChart) (my tutaj mamy jeden interfejs ale mo¿e byc wiêcej)
 * void **ptr - wskaŸnik ta virtual table naszego interfejsu
 */

HRESULT STDMETHODCALLTYPE StosFactory::CreateInstance(IUnknown *outer, REFIID iid, void **ptr) {
	if(ptr == NULL) return E_POINTER; //nie ma gdzie zapisaæ
	*ptr = NULL;
	if(iid != IID_IUnknown && iid != IID_IStos) return E_NOINTERFACE; // ¿¹dany IID musi byæ obs³ugiwany
	Stos *obj = new (std::nothrow) Stos();// chcemy dostaæ NULL zamiast wyj¹tku std::badalloc
	if(obj == NULL) return E_OUTOFMEMORY;// problem z pamiêci¹
	HRESULT rv = obj->QueryInterface(iid, ptr);//zwracamy interfejs (grupê metod) danego obiektu (u nas obiekt->QueryInterface zwraca samego siebie)
	//trzeba pamiêtaæ, ¿e QueryInterface zwiêkszy³ licznik referencji stosowi
	if(FAILED(rv)) { delete obj; *ptr = NULL; };//jeœli problem z pobraniem interfejsu klasy, to usuñ obiekt
	return rv;//zwracamy wynik pobrania interfejsu nowego obiektu stosu
};
