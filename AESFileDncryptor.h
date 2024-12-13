#pragma once
// AESFileDecryptor.h
#ifndef AES_FILE_DECRYPTOR_H
#define AES_FILE_DECRYPTOR_H

#include <string>

class AESFileDecryptor {
public:
    // 构造函数，传入密钥和初始化向量（IV）
    AESFileDecryptor(const std::string& key, const std::string& iv);

    // 解密文件，传入加密文件路径、输出文件路径和期望的 MD5 校验值
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& inputMD5);

private:
    // 将字符串转换为字节数组
    void stringToBytes(const std::string& str, unsigned char* out);

    // 计算 MD5 哈希值
    std::string calculateMD5(const std::string& input);

    // 解密单块数据
    void decryptBlock(const unsigned char* in, unsigned char* out, const unsigned char* key, unsigned char* iv);

    // 用于存储密钥和 IV
    std::string key_;
    std::string iv_;
};



#endif // AES_FILE_DECRYPTOR_H


