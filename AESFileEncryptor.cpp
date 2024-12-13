#include "pch.h"
#include "AESFileEncryptor.h"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#pragma warning(disable:4996)
void showMessageBox(const std::string& message, const std::string& title = "Message") {
    MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
}

// AESFileEncryptor 构造函数
AESFileEncryptor::AESFileEncryptor(const std::string& key, const std::string& iv) : key_(key), iv_(iv) {
    if (key_.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("AES key must be 16 bytes (128 bits).");
    }
    if (iv_.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("AES IV must be 16 bytes.");
    }
}

// 将字符串转换为字节数组
void AESFileEncryptor::stringToBytes(const std::string& str, unsigned char* out) {
    for (size_t i = 0; i < str.size(); ++i) {
        out[i] = static_cast<unsigned char>(str[i]);
    }
}

// 加密单块数据
void AESFileEncryptor::encryptBlock(const unsigned char* in, unsigned char* out, const unsigned char* key, const unsigned char* iv) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);  // 使用 128 位密钥

    // 使用 AES CBC 模式加密
    AES_cbc_encrypt(in, out, AES_BLOCK_SIZE, &aesKey, const_cast<unsigned char*>(iv), AES_ENCRYPT);
}

// 用 AES 加密文件并写入 MD5 值
bool AESFileEncryptor::encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& md5Hash) {
    std::ifstream inputFileStream(inputFile, std::ios::binary);
    if (!inputFileStream) {
        showMessageBox("无法打开输入文件: " + inputFile, "Error");
        return false;
    }

    // 获取当前工作目录
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);  // 获取当前工作目录
    std::string outputDir = std::string(buffer); // 获取当前目录路径
    std::string outputPath = outputDir + "\\" + outputFile; // 输出路径

    std::ofstream outputFileStream(outputPath, std::ios::binary);
    if (!outputFileStream) {
        showMessageBox("无法打开输出文件: " + outputPath, "Error");
        return false;
    }

    unsigned char key[AES_BLOCK_SIZE];
    unsigned char iv[AES_BLOCK_SIZE];

    // 将密钥和 IV 转换为字节数组
    stringToBytes(key_, key);
    stringToBytes(iv_, iv);

    unsigned char inBuffer[AES_BLOCK_SIZE];
    unsigned char outBuffer[AES_BLOCK_SIZE];

    std::stringstream encryptedDataStream;

    while (inputFileStream.read(reinterpret_cast<char*>(inBuffer), AES_BLOCK_SIZE)) {
        // 加密读取的每个 AES 块
        encryptBlock(inBuffer, outBuffer, key, iv);

        // 将加密后的数据写入内存流
        encryptedDataStream.write(reinterpret_cast<char*>(outBuffer), AES_BLOCK_SIZE);
    }

    // 处理文件最后剩余的部分，如果有的话
    size_t bytesRead = inputFileStream.gcount();
    if (bytesRead > 0) {
        // 填充最后一块数据
        std::memset(inBuffer, 0, AES_BLOCK_SIZE);
        std::memcpy(inBuffer, outBuffer, bytesRead);

        encryptBlock(inBuffer, outBuffer, key, iv);

        encryptedDataStream.write(reinterpret_cast<char*>(outBuffer), AES_BLOCK_SIZE);
    }

    // 获取加密数据的内容
    std::string encryptedData = encryptedDataStream.str();

    // 将 MD5 哈希值和加密数据写入文件
    outputFileStream.write(md5Hash.c_str(), md5Hash.size()); // 先写 MD5 值
    outputFileStream.write(reinterpret_cast<const char*>(encryptedData.c_str()), encryptedData.size()); // 写加密数据

    inputFileStream.close();
    outputFileStream.close();

    showMessageBox("文件已成功加密并保存为 " + outputPath, "Success");

    return true;
}