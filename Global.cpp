#include "pch.h"
#include "Global.h"
#include <Windows.h>  // 包含 Windows API 所需的头文件
#include <string>     // 用于处理字符串转换
// 初始化静态成员变量
std::unordered_map<std::string, std::string> Global::userHashes;
std::vector<unsigned char> Global::signature;

// 添加一个用户及其哈希值
void Global::addUser(const std::string& userName, const std::string& sha256Hash) {
    userHashes[userName] = sha256Hash;

    // 调试输出：使用 MessageBox 显示添加的用户和哈希值
    std::wstring message = L"Added user: " + std::wstring(userName.begin(), userName.end()) +
        L" with SHA256 Hash: " + std::wstring(sha256Hash.begin(), sha256Hash.end());
    MessageBoxW(NULL, message.c_str(), L"User Added", MB_OK | MB_ICONINFORMATION);
}

// 获取指定用户的 SHA256 哈希值
std::string Global::getSHA256Hash(const std::string& userName) {
    auto it = userHashes.find(userName);
    if (it != userHashes.end()) {
        return it->second;
    }
    return "";  // 如果没有找到，返回空字符串
}

// 获取所有用户的哈希值
std::unordered_map<std::string, std::string> Global::getAllUsers() {
    return userHashes;
}

// 显示所有用户的信息
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

// 检查某个用户是否已存在
bool Global::userExists(const std::string& userName) {
    return userHashes.find(userName) != userHashes.end();
}

// 清除所有用户的数据
void Global::clearAllUsers() {
    userHashes.clear();
    MessageBoxW(NULL, L"All users have been cleared.", L"Users Cleared", MB_OK | MB_ICONINFORMATION);
}

void Global::removeUser(const std::string& userName) {
    auto it = userHashes.find(userName);
    if (it != userHashes.end()) {
        userHashes.erase(it);  // 从 userHashes 中删除该用户
        // 弹窗显示删除成功
        std::wstring message = L"User " + std::wstring(userName.begin(), userName.end()) + L" has been removed.";
        MessageBoxW(NULL, message.c_str(), L"User Removed", MB_OK | MB_ICONINFORMATION);
    }
    else {
        // 用户不存在时，弹窗提示
        std::wstring message = L"User " + std::wstring(userName.begin(), userName.end()) + L" does not exist.";
        MessageBoxW(NULL, message.c_str(), L"User Not Found", MB_OK | MB_ICONERROR);
    }
}