#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include<vector>

class Global {
public:
    // ���һ���û������ϣֵ
public:
    // ���һ���û������ϣֵ
    static void addUser(const std::string& userName, const std::string& sha256Hash);

    // ��ȡָ���û��� SHA256 ��ϣֵ
    static std::string getSHA256Hash(const std::string& userName);

    // ��ȡ�����û��Ĺ�ϣֵ
    static std::unordered_map<std::string, std::string> getAllUsers();

    // ��ʾ�����û�����Ϣ
    static void displayAllUsers();

    // ���ĳ���û��Ƿ��Ѵ���
    static bool userExists(const std::string& userName);

    // ��������û�������
    static void clearAllUsers();
    static void Global::removeUser(const std::string& userName);
    static std::vector <unsigned char> signature;
private:
    // ������̬��Ա����
    static std::unordered_map<std::string, std::string> userHashes;
};



