#pragma once
#ifndef MD5CALCULATOR_H
#define MD5CALCULATOR_H

#include <string>
class MD5Calculator
{
public:
    // 构造函数
    MD5Calculator();

    // 计算给定字符串的 MD5 哈希
    std::string computeMD5(const std::string& input);
    std::wstring md5stringToWString(const std::string& str);
private:
    // 使用 OpenSSL 函数处理 MD5 哈希
    std::string byteArrayToHexString(const unsigned char* byteArray, size_t length);
};

#endif // MD5CALCULATOR_H