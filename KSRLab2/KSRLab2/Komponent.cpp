#include "Komponent.h";
#include "GUID.h";
//jeden komponent (np Word) udost�pnia wiele interfejs�w (np. IChart, IExcelDocument, IEquotation)
HRESULT STDMETHODCALLTYPE Stos::QueryInterface(REFIID iid, void **ptr) {
	if(ptr == NULL) return E_POINTER;//nie ma gdzie zwr�ci� tablicy wska�nik�w (virtual method table) - tutaj b�dzie to po prostu lista metod naszej klasy
	*ptr = NULL;
	if(iid == IID_IUnknown) *ptr = this;//pyta o unknown, u nas jest tylko jeden wi�c zwr��my virtual method table stosu
	else if(iid == IID_IStos) *ptr = this;//pyta o stos, zwr��my virtual method table stosu
	if(*ptr != NULL) { AddRef(); return S_OK; };//dajemy mu dost�p do naszej klasy, wi�c zwi�kszamy licznik referencji
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
extern volatile ULONG usageCount;//statyczna informacja o liczbie �ywych obiekt�w

Stos::Stos() {
	InterlockedIncrement(&usageCount);
	m_ref = 0;
	// pozosta�a inicjalizacja
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