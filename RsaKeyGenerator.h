#pragma once
#ifndef RSA_KEY_GENERATOR_H
#define RSA_KEY_GENERATOR_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <string>
class RsaKeyGenerator
{
public:
    // 构造函数
    RsaKeyGenerator(int keyLength = 2048, unsigned long publicExponent = RSA_F4);

    // 析构函数
    ~RsaKeyGenerator();

    // 生成RSA密钥对
    bool generateKeys();

    // 将公钥写入文件
    bool writePublicKey(const std::string& publicKeyFile);

    // 将私钥写入文件
    bool writePrivateKey(const std::string& privateKeyFile);
    std::string getPrivateKeyFilePath() const;  // 新增的获取私钥路径的函数
private:
    RSA* rsa;         // RSA密钥对
    BIGNUM* e;        // 公钥指数
    int keyLength;    // 密钥长度
    unsigned long publicExponent;  // 公钥指数
    std::string privateKeyFilePath;
    // 生成密钥对的辅助函数
    bool createKeyPair();
};


#endif // RSA_KEY_GENERATOR_H