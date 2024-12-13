#include "pch.h"
#include "MD5Calculator.h"
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#pragma warning(disable:4996)

MD5Calculator::MD5Calculator() {
    // 如果需要，您可以在这里初始化其他内容
}

// 计算 MD5 哈希
std::string MD5Calculator::computeMD5(const std::string& input) {
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5_CTX md5Context;

    // 初始化 MD5 上下文
    MD5_Init(&md5Context);

    // 更新 MD5 计算，传入输入数据
    MD5_Update(&md5Context, input.c_str(), input.length());

    // 获取最终 MD5 结果
    MD5_Final(result, &md5Context);

    // 将字节数组转换为十六进制字符串
    return byteArrayToHexString(result, MD5_DIGEST_LENGTH);
}

// 将字节数组转换为十六进制字符串
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
