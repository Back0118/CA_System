#include "pch.h"
#include "RsaKeyGenerator.h"
#include <iostream>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#pragma warning(disable:4996)
RsaKeyGenerator::RsaKeyGenerator(int keyLength, unsigned long publicExponent)
    : rsa(nullptr), e(nullptr), keyLength(keyLength), publicExponent(publicExponent) {
    rsa = RSA_new();
    e = BN_new();
}

// 析构函数，释放资源
RsaKeyGenerator::~RsaKeyGenerator() {
    if (rsa) RSA_free(rsa);
    if (e) BN_free(e);
}

// 生成RSA密钥对
bool RsaKeyGenerator::generateKeys() {
    return createKeyPair();
}

// 创建RSA密钥对
bool RsaKeyGenerator::createKeyPair() {
    // 设置公钥指数
    if (!BN_set_word(e, publicExponent)) {
        MessageBoxA(NULL, "设置公钥指数失败!", "错误", MB_OK | MB_ICONERROR);
        return false;
    }

    // 生成RSA密钥对
    if (RSA_generate_key_ex(rsa, keyLength, e, NULL) != 1) {
        MessageBoxA(NULL, "RSA密钥生成失败!", "错误", MB_OK | MB_ICONERROR);
        return false;
    }
    return true;
}

// 将公钥写入文件
bool RsaKeyGenerator::writePublicKey(const std::string& publicKeyFile) {
    BIO* bio = BIO_new_file(publicKeyFile.c_str(), "w");
    if (!bio) {
        MessageBoxA(NULL, "打开公钥文件失败!", "错误", MB_OK | MB_ICONERROR);
        return false;
    }

    if (PEM_write_bio_RSAPublicKey(bio, rsa) != 1) {
        MessageBoxA(NULL, "写入公钥失败!", "错误", MB_OK | MB_ICONERROR);
        BIO_free(bio);
        return false;
    }

    BIO_free(bio);
    return true;
}

std::string RsaKeyGenerator::getPrivateKeyFilePath() const {
    return privateKeyFilePath;  // 返回私钥路径
}
// 将私钥写入文件
bool RsaKeyGenerator::writePrivateKey(const std::string& privateKeyFile) {
    char currentDir[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDir);  // 获取当前目录，存储到 currentDir

    // 拼接当前工作目录和私钥文件名
    std::string fullPrivateKeyPath = std::string(currentDir) + "\\" + privateKeyFile;
    BIO* bio = BIO_new_file(privateKeyFile.c_str(), "w");
    if (!bio) {
        MessageBoxA(NULL, "打开私钥文件失败!", "错误", MB_OK | MB_ICONERROR);
        return false;
    }

    if (PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL) != 1) {
        MessageBoxA(NULL, "写入私钥失败!", "错误", MB_OK | MB_ICONERROR);
        BIO_free(bio);
        return false;
    }
    privateKeyFilePath = fullPrivateKeyPath;  // 保存路径
    BIO_free(bio);
    return true;
}