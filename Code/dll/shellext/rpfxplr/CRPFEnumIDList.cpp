#include "pch.h"

#include <IRPF.h>

class CRPFEnumIDList :
    public CComObjectRootEx<CComMultiThreadModelNoCS>,
    public IEnumIDList
{
private:
	IRPF* m_pRPF = NULL;

public:
	HRESULT Initialize(IRPF* pRPF)
	{
		m_pRPF = pRPF;
		return S_OK;
	}

	//
	// IEnumIDList
	//
	STDMETHODIMP Next(_In_ ULONG celt, _Out_ PITEMID_CHILD* rgelt, _Out_ ULONG* pceltFetched) override
	{
		if (!pceltFetched || !rgelt)
			return E_POINTER;

		return E_NOTIMPL;
	}

	STDMETHODIMP Skip(_In_ ULONG celt) override
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP Reset(void) override
	{
		return E_NOTIMPL;
	}

	STDMETHODIMP Clone(_Out_opt_ IEnumIDList** ppenum) override
	{
		if (!ppenum)
			return E_POINTER;

		ppenum = NULL;

		return E_NOTIMPL;
	}

public:
	DECLARE_NOT_AGGREGATABLE(CRPFEnumIDList)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CRPFEnumIDList)
		COM_INTERFACE_ENTRY_IID(IID_IEnumIDList, IEnumIDList)
	END_COM_MAP()
};

HRESULT CreateRPFEnumIDL(IRPF* pRPF, REFIID riid, LPVOID* ppvOut)
{
	HRESULT hr;
	CComObject<CRPFEnumIDList>* pList;

	hr = CComObject<CRPFEnumIDList>::CreateInstance(&pList);
	if (FAILED(hr))
		return hr;

	pList->AddRef();

	hr = pList->Initialize(pRPF);
	if (SUCCEEDED(hr))
		hr = pList->QueryInterface(riid, reinterpret_cast<void**>(ppvOut));

	pList->Release();

	return E_NOTIMPL;
}
