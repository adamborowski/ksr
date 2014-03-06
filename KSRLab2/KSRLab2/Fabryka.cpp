#include "Fabryka.h";
#include "Komponent.h";
#include "GUID.h";
#include <new>
//jeden komponent (np Word) udost�pnia wiele interfejs�w (np. IChart, IExcelDocument, IEquotation)
HRESULT STDMETHODCALLTYPE StosFactory::QueryInterface(REFIID iid, void **ptr) {
	if(ptr == NULL) return E_POINTER;//nie ma gdzie zwr�ci� tablicy wska�nik�w (virtual method table) - tutaj b�dzie to po prostu lista metod naszej klasy
	*ptr = NULL;
	if(iid == IID_IUnknown) *ptr = this;//pyta o unknown, u nas jest tylko jeden wi�c zwr��my virtual method table fabryki stosu
	else if(iid == IID_IClassFactory) *ptr = this;//pyta o class factory, zwr��my virtual method table fabryki stosu
	if(*ptr != NULL) { AddRef(); return S_OK; };//dajemy mu dost�p do naszej klasy, wi�c zwi�kszamy licznik referencji
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
extern volatile ULONG usageCount;//statyczna informacja o liczbie �ywych obiekt�w
//#include <iostream>
StosFactory::StosFactory() {
	InterlockedIncrement(&usageCount);
	m_ref = 0;
	// pozosta�a inicjalizacja
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
 * IUnknown *outer - ignorowa� to (jaki� obiekt do agregacji...
 * REFIID iid - identyfikator interfejsu z klasy stosu (np. Word -> IChart) (my tutaj mamy jeden interfejs ale mo�e byc wi�cej)
 * void **ptr - wska�nik ta virtual table naszego interfejsu
 */

HRESULT STDMETHODCALLTYPE StosFactory::CreateInstance(IUnknown *outer, REFIID iid, void **ptr) {
	if(ptr == NULL) return E_POINTER; //nie ma gdzie zapisa�
	*ptr = NULL;
	if(iid != IID_IUnknown && iid != IID_IStos) return E_NOINTERFACE; // ��dany IID musi by� obs�ugiwany
	Stos *obj = new (std::nothrow) Stos();// chcemy dosta� NULL zamiast wyj�tku std::badalloc
	if(obj == NULL) return E_OUTOFMEMORY;// problem z pami�ci�
	HRESULT rv = obj->QueryInterface(iid, ptr);//zwracamy interfejs (grup� metod) danego obiektu (u nas obiekt->QueryInterface zwraca samego siebie)
	//trzeba pami�ta�, �e QueryInterface zwi�kszy� licznik referencji stosowi
	if(FAILED(rv)) { delete obj; *ptr = NULL; };//je�li problem z pobraniem interfejsu klasy, to usu� obiekt
	return rv;//zwracamy wynik pobrania interfejsu nowego obiektu stosu
};
