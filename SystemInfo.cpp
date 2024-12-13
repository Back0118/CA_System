#include "pch.h"
#include "SystemInfo.h"
#include <sstream>
// 构造函数，初始化成员变量
SystemInfo::SystemInfo() : macAddress(""), diskSerialNumber(0) {
    // 获取硬盘序列号
    GetDiskSerialNumber(&diskSerialNumber);
    // 获取 MAC 地址
    GetMACAddress();
}

// 析构函数
SystemInfo::~SystemInfo() {
    // 清理 COM 库
    CoUninitialize();
}

// 获取硬盘序列号
void SystemInfo::GetDiskSerialNumber(DWORD* number) {
    char volumeNameBuffer[MAX_PATH + 1] = "";
    char fileSystemNameBuffer[MAX_PATH + 1] = "";
    DWORD maxComponentLength = 0;
    DWORD fileSystemFlags = 0;

    if (!GetVolumeInformationA("C:\\", volumeNameBuffer, MAX_PATH, number, &maxComponentLength, &fileSystemFlags, fileSystemNameBuffer, MAX_PATH)) {
        MessageBox(NULL, L"获取硬盘序列号失败。", L"错误", MB_ICONERROR);
    }
}

// 获取 MAC 地址
void SystemInfo::GetMACAddress() {
    HRESULT hres;

    // 初始化 COM 库
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        /*MessageBox(NULL, L"Failed to initialize COM library.", L"错误", MB_ICONERROR);*/
        return;
    }

    // 设置 COM 安全
    hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
    if (FAILED(hres)) {
      /*  MessageBox(NULL, L"Failed to initialize security.", L"错误", MB_ICONERROR);*/
        CoUninitialize();
        return;
    }

    // 创建 IWbemLocator 对象
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
       /* MessageBox(NULL, L"Failed to create IWbemLocator object.", L"错误", MB_ICONERROR);*/
        CoUninitialize();
        return;
    }

    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
    if (FAILED(hres)) {
       /* MessageBox(NULL, L"Failed to connect to WMI service.", L"错误", MB_ICONERROR);*/
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // 设置代理的安全
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    if (FAILED(hres)) {
        /*MessageBox(NULL, L"Failed to set proxy blanket.", L"错误", MB_ICONERROR);*/
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // 查询启用了 IP 的网络适配器
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_NetworkAdapterConfiguration WHERE IPEnabled = True"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
    if (FAILED(hres)) {
       /* MessageBox(NULL, L"Failed to execute query.", L"错误", MB_ICONERROR);*/
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    if (pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn) == S_OK) {
        VARIANT vtProp;
        hres = pclsObj->Get(L"MACAddress", 0, &vtProp, 0, 0);
        if (SUCCEEDED(hres)) {
            macAddress = _bstr_t(vtProp.bstrVal);  // 获取到的 MAC 地址
            VariantClear(&vtProp);
        }
        pclsObj->Release();
    }
    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
}

// 显示硬盘序列号和 MAC 地址
std::wstring SystemInfo::ShowInfo() {
    std::wostringstream result;
    // 将 DWORD 类型的硬盘序列号转换为 std::wstring
    result << std::to_wstring(diskSerialNumber) ;

    // 将 macAddress 转换为 std::wstring 并输出
    result << std::wstring(macAddress.begin(), macAddress.end());

    /*MessageBox(NULL, result.str().c_str(), L"系统信息", MB_OK | MB_ICONINFORMATION);*/
    return result.str().c_str();
}