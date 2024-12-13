#include "pch.h"
#include "SystemInfo.h"
#include <sstream>
// ���캯������ʼ����Ա����
SystemInfo::SystemInfo() : macAddress(""), diskSerialNumber(0) {
    // ��ȡӲ�����к�
    GetDiskSerialNumber(&diskSerialNumber);
    // ��ȡ MAC ��ַ
    GetMACAddress();
}

// ��������
SystemInfo::~SystemInfo() {
    // ���� COM ��
    CoUninitialize();
}

// ��ȡӲ�����к�
void SystemInfo::GetDiskSerialNumber(DWORD* number) {
    char volumeNameBuffer[MAX_PATH + 1] = "";
    char fileSystemNameBuffer[MAX_PATH + 1] = "";
    DWORD maxComponentLength = 0;
    DWORD fileSystemFlags = 0;

    if (!GetVolumeInformationA("C:\\", volumeNameBuffer, MAX_PATH, number, &maxComponentLength, &fileSystemFlags, fileSystemNameBuffer, MAX_PATH)) {
        MessageBox(NULL, L"��ȡӲ�����к�ʧ�ܡ�", L"����", MB_ICONERROR);
    }
}

// ��ȡ MAC ��ַ
void SystemInfo::GetMACAddress() {
    HRESULT hres;

    // ��ʼ�� COM ��
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        /*MessageBox(NULL, L"Failed to initialize COM library.", L"����", MB_ICONERROR);*/
        return;
    }

    // ���� COM ��ȫ
    hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
    if (FAILED(hres)) {
      /*  MessageBox(NULL, L"Failed to initialize security.", L"����", MB_ICONERROR);*/
        CoUninitialize();
        return;
    }

    // ���� IWbemLocator ����
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
       /* MessageBox(NULL, L"Failed to create IWbemLocator object.", L"����", MB_ICONERROR);*/
        CoUninitialize();
        return;
    }

    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
    if (FAILED(hres)) {
       /* MessageBox(NULL, L"Failed to connect to WMI service.", L"����", MB_ICONERROR);*/
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // ���ô���İ�ȫ
    hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    if (FAILED(hres)) {
        /*MessageBox(NULL, L"Failed to set proxy blanket.", L"����", MB_ICONERROR);*/
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // ��ѯ������ IP ������������
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_NetworkAdapterConfiguration WHERE IPEnabled = True"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
    if (FAILED(hres)) {
       /* MessageBox(NULL, L"Failed to execute query.", L"����", MB_ICONERROR);*/
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
            macAddress = _bstr_t(vtProp.bstrVal);  // ��ȡ���� MAC ��ַ
            VariantClear(&vtProp);
        }
        pclsObj->Release();
    }
    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
}

// ��ʾӲ�����кź� MAC ��ַ
std::wstring SystemInfo::ShowInfo() {
    std::wostringstream result;
    // �� DWORD ���͵�Ӳ�����к�ת��Ϊ std::wstring
    result << std::to_wstring(diskSerialNumber) ;

    // �� macAddress ת��Ϊ std::wstring �����
    result << std::wstring(macAddress.begin(), macAddress.end());

    /*MessageBox(NULL, result.str().c_str(), L"ϵͳ��Ϣ", MB_OK | MB_ICONINFORMATION);*/
    return result.str().c_str();
}