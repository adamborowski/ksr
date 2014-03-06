#include <Windows.h>

class StosFactory: public IClassFactory {
public:
	StosFactory();
	~StosFactory();
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID id, void **rv);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	// interfejs IClassFactory
	virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL v);
	virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *outer, REFIID id, void **rv);
private:
	ULONG m_ref; // licznik referencji
};