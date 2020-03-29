#include "SerialPort.h"



SerialPort::SerialPort()
	:m_hLibrary(nullptr),
	m_wstrPath(L""),
	m_bLoad(false)
{
	
}


SerialPort::~SerialPort()
{
	if (m_bLoad)
	{
		FreeLibrary(m_hLibrary);
		m_hLibrary = nullptr;
		m_bLoad = false;
	}
}

void SerialPort::SetDllPath(std::wstring & wstrPath)
{
	m_wstrPath = wstrPath;
}

bool SerialPort::InitVSPD()
{
	if (m_bLoad)
	{
		return m_bLoad;
	}
	std::wstring strName = m_wstrPath + L"vspdctl.dll";
	m_hLibrary = LoadLibraryW(strName.c_str());
	if (!m_hLibrary)
	{
		m_bLoad = false;
		return m_bLoad;
	}
	m_lpCreatePair = (CreatePair)GetProcAddress(m_hLibrary, "CreatePair");
	m_lpDeletePair = (DeletePair)GetProcAddress(m_hLibrary, "DeletePair");
	m_lpSetStrictBaudrate = (SetStrictBaudrate)GetProcAddress(m_hLibrary, "SetStrictBaudrate");
	if (m_lpCreatePair == nullptr || m_lpDeletePair == nullptr || m_lpSetStrictBaudrate == nullptr)
	{
		FreeLibrary(m_hLibrary);
		m_hLibrary = nullptr;
		m_bLoad = false;
		return m_bLoad;
	}
	m_bLoad = true;
	return m_bLoad;
}

BOOL SerialPort::CreatePairFn(char * port1, char * port2)
{
	if (m_bLoad)
	{
		WriteRegInfo(port1, port2);
		return m_lpCreatePair(port1, port2);
	}
	return 0;
}

BOOL SerialPort::DeletePairFn(char * port)
{
	if (m_bLoad)
		return m_lpDeletePair(port);
	return 0;
}

BOOL SerialPort::SetStrictBaudrateFn(char * Port, bool bSetStrictBaudrate)
{
	if (m_bLoad)
		return m_lpSetStrictBaudrate(Port, bSetStrictBaudrate);
	return 0;
}

bool SerialPort::WriteRegInfo(char * port1, char * port2)
{
	int nRet = 0;
	HKEY hKey;
	char *pdata_set = "SYSTEM\\CurrentControlSet\\Services";
	LSTATUS status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, pdata_set, 0, KEY_SET_VALUE, &hKey);
	if (ERROR_SUCCESS == status)
	{
		std::string strKey = "VSBC7\\Ports\\";
		strKey += port1;
		strKey += port2;
		HKEY hTempKey;
		if (ERROR_SUCCESS == RegCreateKey(hKey, strKey.c_str(), &hTempKey))
		{
			BYTE name[4] = { 0xa0, 0x10, 0x00, 0x00 };
			DWORD dwValue = 0;
			DWORD dwSize = sizeof(DWORD);
			RegSetValueEx(hTempKey, "Port1", 0, REG_SZ, (const BYTE*)port1, (DWORD)strlen(port1));
			RegSetValueEx(hTempKey, "Port2", 0, REG_SZ, (const BYTE*)port2, (DWORD)strlen(port2));
			RegSetValueEx(hTempKey, "StrictBaudrate", 0, REG_DWORD, (const BYTE*)&dwValue, dwSize);
			RegSetValueEx(hTempKey, "Wiring", 0, REG_BINARY, name, 4);
			RegCloseKey(hTempKey);
		}
		else
		{
			RegCloseKey(hKey);
			return false;
		}
	}
	else
	{
		return false;
	}
	RegCloseKey(hKey);
	return true;
}
