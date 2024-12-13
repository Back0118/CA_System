#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include<vector>

class Global {
public:
    // 添加一个用户及其哈希值
public:
    // 添加一个用户及其哈希值
    static void addUser(const std::string& userName, const std::string& sha256Hash);

    // 获取指定用户的 SHA256 哈希值
    static std::string getSHA256Hash(const std::string& userName);

    // 获取所有用户的哈希值
    static std::unordered_map<std::string, std::string> getAllUsers();

    // 显示所有用户的信息
    static void displayAllUsers();

    // 检查某个用户是否已存在
    static bool userExists(const std::string& userName);

    // 清除所有用户的数据
    static void clearAllUsers();
    static void Global::removeUser(const std::string& userName);
    static std::vector <unsigned char> signature;
private:
    // 声明静态成员变量
    static std::unordered_map<std::string, std::string> userHashes;
};



