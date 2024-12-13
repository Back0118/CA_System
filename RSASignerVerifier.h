#pragma once
#include <string>
#include <vector>
#include <openssl/rsa.h>
class RSASignerVerifier
{
public:
    // 加载私钥
    RSA* LoadPrivateKey(const std::string& pemFilePath);

    // 加载公钥
    RSA* LoadPublicKey(const std::string& pemFilePath);

    // 使用私钥对哈希值进行签名（加密）
    std::vector<unsigned char> SignHashWithPrivateKey(RSA* privateKey, const std::string& hash);

    // 使用公钥验证签名
    bool VerifySignatureWithPublicKey(RSA* publicKey, const std::string& hash, const std::vector<unsigned char>& signature);

    // 将签名保存到文件
    void SaveSignatureToFile(const std::string& filePath, const std::vector<unsigned char>& signature);

private:
    // 错误处理函数：显示 OpenSSL 错误
    void ShowOpenSSLError();

    // 显示错误信息
    void ShowError(const std::string& message);

    // 显示信息提示
    void ShowInfo(const std::string& message);
};

