#pragma once
#ifndef MD5CALCULATOR_H
#define MD5CALCULATOR_H

#include <string>
class MD5Calculator
{
public:
    // ���캯��
    MD5Calculator();

    // ��������ַ����� MD5 ��ϣ
    std::string computeMD5(const std::string& input);
    std::wstring md5stringToWString(const std::string& str);
private:
    // ʹ�� OpenSSL �������� MD5 ��ϣ
    std::string byteArrayToHexString(const unsigned char* byteArray, size_t length);
};

#endif // MD5CALCULATOR_H