#include "Komponent.h";
#include "GUID.h";
//jeden komponent (np Word) udostêpnia wiele interfejsów (np. IChart, IExcelDocument, IEquotation)
HRESULT STDMETHODCALLTYPE Stos::QueryInterface(REFIID iid, void **ptr) {
	if(ptr == NULL) return E_POINTER;//nie ma gdzie zwróciæ tablicy wskaŸników (virtual method table) - tutaj bêdzie to po prostu lista metod naszej klasy
	*ptr = NULL;
	if(iid == IID_IUnknown) *ptr = this;//pyta o unknown, u nas jest tylko jeden wiêc zwróæmy virtual method table stosu
	else if(iid == IID_IStos) *ptr = this;//pyta o stos, zwróæmy virtual method table stosu
	if(*ptr != NULL) { AddRef(); return S_OK; };//dajemy mu dostêp do naszej klasy, wiêc zwiêkszamy licznik referencji
	return E_NOINTERFACE;
};

//implementacja liczenia referencji
ULONG STDMETHODCALLTYPE Stos::AddRef() {
	InterlockedIncrement(&m_ref);
	return m_ref;
};
ULONG STDMETHODCALLTYPE Stos::Release() {
	ULONG rv = InterlockedDecrement(&m_ref);
	if(rv == 0) delete this;
	return rv;
};
extern volatile ULONG usageCount;//statyczna informacja o liczbie ¿ywych obiektów

Stos::Stos() {
	InterlockedIncrement(&usageCount);
	m_ref = 0;
	// pozosta³a inicjalizacja
};
Stos::~Stos() {
	InterlockedDecrement(&usageCount);
};


HRESULT STDMETHODCALLTYPE Stos::Push(int val){
	value += val;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Stos::Pop(int *val){
	value -= 1;
	*val = value;
	return S_OK;
}