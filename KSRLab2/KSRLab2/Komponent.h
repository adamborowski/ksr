#include<windows.h> // zawiera deklaracj� IUnknown


//IStos to tablica wska�nik�w na funkcje (przypadek, �e COM zwraca tablic� kt�ra si� deserializuje do interfejsu)
class IStos: public IUnknown {
	virtual HRESULT STDMETHODCALLTYPE Push(int val) = 0;
	virtual HRESULT STDMETHODCALLTYPE Pop(int *val) = 0;
};

class Stos: public IStos {
public:
	Stos();
	~Stos();
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ptr);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	virtual HRESULT STDMETHODCALLTYPE Push(int val);//zwi�ksza wielko�� stosu o warto��
	virtual HRESULT STDMETHODCALLTYPE Pop(int *val);//zmniejsza wielko�� stosu o jeden i zwraca wielko�� stosu
private:
	volatile ULONG m_ref; // licznik referencji
	volatile ULONG value; // wielko�� stosu
};