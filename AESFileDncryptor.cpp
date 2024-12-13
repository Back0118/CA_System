#include "pch.h"
#include "AESFileDncryptor.h"
#include <openssl/aes.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <Windows.h>  // 用于 MessageBoxA
#pragma warning(disable:4996)

// 显示消息框
void showMessageBoxD(const std::string& message, const std::string& title) {
    MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
}

// 构造函数，初始化密钥和 IV
AESFileDecryptor::AESFileDecryptor(const std::string& key, const std::string& iv) : key_(key), iv_(iv) {
    if (key_.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("AES key must be 16 bytes (128 bits).");
    }
    if (iv_.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("AES IV must be 16 bytes.");
    }
}

// 将字符串转换为字节数组
void AESFileDecryptor::stringToBytes(const std::string& str, unsigned char* out) {
    for (size_t i = 0; i < str.size(); ++i) {
        out[i] = static_cast<unsigned char>(str[i]);
    }
}

// 解密单块数据
void AESFileDecryptor::decryptBlock(const unsigned char* in, unsigned char* out, const unsigned char* key, unsigned char* iv) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);  // 使用 128 位密钥

    // 使用 AES CBC 模式解密
    AES_cbc_encrypt(in, out, AES_BLOCK_SIZE, &aesKey, iv, AES_DECRYPT);
}

// 解密文件
bool AESFileDecryptor::decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& expectedMD5) {
    std::ifstream inputFileStream(inputFile, std::ios::binary);
    if (!inputFileStream) {
        showMessageBoxD("无法打开输入文件: " + inputFile, "Error");
        return false;
    }

    // 获取当前工作目录
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);  // 获取当前工作目录
    std::string outputDir = std::string(buffer); // 获取当前目录路径
    std::string outputPath = outputDir + "\\" + outputFile; // 输出路径，确保文件保存在当前目录下

    std::ofstream outputFileStream(outputPath, std::ios::binary);
    if (!outputFileStream) {
        showMessageBoxD("无法打开输出文件: " + outputPath, "Error");
        return false;
    }

    unsigned char key[AES_BLOCK_SIZE];
    unsigned char iv[AES_BLOCK_SIZE];

    // 将密钥和 IV 转换为字节数组
    stringToBytes(key_, key);
    stringToBytes(iv_, iv);

    // 读取加密文件中的前 32 字节，即 MD5 值（32 个字符，16 字节）
    char md5Hash[32];
    inputFileStream.read(md5Hash, 32);

    // 将 MD5 值转换为字符串
    std::string storedMD5(md5Hash, 32);

    // 与提供的 MD5 进行比较
    if (storedMD5 != expectedMD5) {
        showMessageBoxD("MD5 校验失败！文件可能已被篡改或损坏。", "Error");
        inputFileStream.close();
        return false;
    }

    // 跳过 MD5 值，开始解密文件的剩余内容
    inputFileStream.seekg(32, std::ios::beg);

    // 读取加密文件数据
    unsigned char inBuffer[AES_BLOCK_SIZE];
    unsigned char outBuffer[AES_BLOCK_SIZE];

    std::stringstream decryptedDataStream;

    while (inputFileStream.read(reinterpret_cast<char*>(inBuffer), AES_BLOCK_SIZE)) {
        // 解密读取的每个 AES 块
        decryptBlock(inBuffer, outBuffer, key, iv);

        // 将解密后的数据写入内存流
        decryptedDataStream.write(reinterpret_cast<char*>(outBuffer), AES_BLOCK_SIZE);

        // 更新 IV 为当前的加密块（CBC 模式的要求）
        std::memcpy(iv, inBuffer, AES_BLOCK_SIZE);
    }

    // 获取解密数据的内容
    std::string decryptedData = decryptedDataStream.str();

    // 将解密后的数据写入文件
    outputFileStream.write(decryptedData.c_str(), decryptedData.size());

    inputFileStream.close();
    outputFileStream.close();

    showMessageBoxD("文件已成功解密并保存为 " + outputPath, "Success");

    return true;
}