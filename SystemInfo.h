#pragma once
#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <string>
#include <windows.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <iostream>

#pragma comment(lib, "wbemuuid.lib")
class SystemInfo
{
public:
    SystemInfo();
    ~SystemInfo();

    void GetDiskSerialNumber(DWORD* number);
    void GetMACAddress();
    std::wstring SystemInfo::ShowInfo();

private:
    std::string macAddress;
    DWORD diskSerialNumber;
};

#endif // SYSTEMINFO_H