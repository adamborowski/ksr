#include<windows.h> // zawiera deklaracjê IUnknown


//IStos to tablica wskaŸników na funkcje (przypadek, ¿e COM zwraca tablicê która siê deserializuje do interfejsu)
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
	virtual HRESULT STDMETHODCALLTYPE Push(int val);//zwiêksza wielkoœæ stosu o wartoœæ
	virtual HRESULT STDMETHODCALLTYPE Pop(int *val);//zmniejsza wielkoœæ stosu o jeden i zwraca wielkoœæ stosu
private:
	volatile ULONG m_ref; // licznik referencji
	volatile ULONG value; // wielkoœæ stosu
};