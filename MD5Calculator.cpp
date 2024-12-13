#include "pch.h"
#include "MD5Calculator.h"
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#pragma warning(disable:4996)

MD5Calculator::MD5Calculator() {
    // �����Ҫ���������������ʼ����������
}

// ���� MD5 ��ϣ
std::string MD5Calculator::computeMD5(const std::string& input) {
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5_CTX md5Context;

    // ��ʼ�� MD5 ������
    MD5_Init(&md5Context);

    // ���� MD5 ���㣬������������
    MD5_Update(&md5Context, input.c_str(), input.length());

    // ��ȡ���� MD5 ���
    MD5_Final(result, &md5Context);

    // ���ֽ�����ת��Ϊʮ�������ַ���
    return byteArrayToHexString(result, MD5_DIGEST_LENGTH);
}

// ���ֽ�����ת��Ϊʮ�������ַ���
std::string MD5Calculator::byteArrayToHexString(const unsigned char* byteArray, size_t length) {
    std::stringstream ss;
    for (size_t i = 0; i < length; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)byteArray[i];
    }
    return ss.str();
}
std::wstring MD5Calculator::md5stringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}
