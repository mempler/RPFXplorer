#pragma once

class RPFReader;

class IRPF : public IUnknown
{
	STDMETHOD (GetRPFReader) (_Out_ RPFReader** ppOutReader) PURE;
};
