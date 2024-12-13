#include "pch.h"
#include "Global.h"
#include <Windows.h>  // ���� Windows API �����ͷ�ļ�
#include <string>     // ���ڴ����ַ���ת��
// ��ʼ����̬��Ա����
std::unordered_map<std::string, std::string> Global::userHashes;
std::vector<unsigned char> Global::signature;

// ���һ���û������ϣֵ
void Global::addUser(const std::string& userName, const std::string& sha256Hash) {
    userHashes[userName] = sha256Hash;

    // ���������ʹ�� MessageBox ��ʾ��ӵ��û��͹�ϣֵ
    std::wstring message = L"Added user: " + std::wstring(userName.begin(), userName.end()) +
        L" with SHA256 Hash: " + std::wstring(sha256Hash.begin(), sha256Hash.end());
    MessageBoxW(NULL, message.c_str(), L"User Added", MB_OK | MB_ICONINFORMATION);
}

// ��ȡָ���û��� SHA256 ��ϣֵ
std::string Global::getSHA256Hash(const std::string& userName) {
    auto it = userHashes.find(userName);
    if (it != userHashes.end()) {
        return it->second;
    }
    return "";  // ���û���ҵ������ؿ��ַ���
}

// ��ȡ�����û��Ĺ�ϣֵ
std::unordered_map<std::string, std::string> Global::getAllUsers() {
    return userHashes;
}

// ��ʾ�����û�����Ϣ
void Global::displayAllUsers() {
    if (userHashes.empty()) {
        MessageBoxW(NULL, L"No users available.", L"Information", MB_OK | MB_ICONINFORMATION);
    }
    else {
        std::wstring message = L"Users and their SHA256 Hashes:\n";
        for (const auto& entry : userHashes) {
            message += L"User: " + std::wstring(entry.first.begin(), entry.first.end()) +
                L", SHA256 Hash: " + std::wstring(entry.second.begin(), entry.second.end()) + L"\n";
        }
        MessageBoxW(NULL, message.c_str(), L"All Users", MB_OK | MB_ICONINFORMATION);
    }
}

// ���ĳ���û��Ƿ��Ѵ���
bool Global::userExists(const std::string& userName) {
    return userHashes.find(userName) != userHashes.end();
}

// ��������û�������
void Global::clearAllUsers() {
    userHashes.clear();
    MessageBoxW(NULL, L"All users have been cleared.", L"Users Cleared", MB_OK | MB_ICONINFORMATION);
}

void Global::removeUser(const std::string& userName) {
    auto it = userHashes.find(userName);
    if (it != userHashes.end()) {
        userHashes.erase(it);  // �� userHashes ��ɾ�����û�
        // ������ʾɾ���ɹ�
        std::wstring message = L"User " + std::wstring(userName.begin(), userName.end()) + L" has been removed.";
        MessageBoxW(NULL, message.c_str(), L"User Removed", MB_OK | MB_ICONINFORMATION);
    }
    else {
        // �û�������ʱ��������ʾ
        std::wstring message = L"User " + std::wstring(userName.begin(), userName.end()) + L" does not exist.";
        MessageBoxW(NULL, message.c_str(), L"User Not Found", MB_OK | MB_ICONERROR);
    }
}