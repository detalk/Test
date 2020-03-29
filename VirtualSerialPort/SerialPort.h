#pragma once
#include <Windows.h>
#include <string>

class SerialPort
{
public:
	SerialPort();
	~SerialPort();
	void SetDllPath(std::wstring & wstrPath);
	bool InitVSPD();
	BOOL CreatePairFn(char* port1, char* port2);
	BOOL DeletePairFn(char* port);
	BOOL SetStrictBaudrateFn(char* Port, bool bSetStrictBaudrate);
	bool WriteRegInfo(char* port1, char* port2);

	typedef BOOL(__stdcall*CreatePair)(char* Port1, char* Port2);
	typedef BOOL(__stdcall*DeletePair)(char* Port);
	typedef BOOL(__stdcall*SetStrictBaudrate)(char* Port, bool bSetStrictBaudrate);

private:
	HMODULE m_hLibrary;
	std::wstring m_wstrPath;
	bool m_bLoad;
	CreatePair m_lpCreatePair;
	DeletePair m_lpDeletePair;
	SetStrictBaudrate m_lpSetStrictBaudrate;
};

