#pragma once
#include <string>
#include <vector>
#include <openssl/rsa.h>
class RSASignerVerifier
{
public:
    // ����˽Կ
    RSA* LoadPrivateKey(const std::string& pemFilePath);

    // ���ع�Կ
    RSA* LoadPublicKey(const std::string& pemFilePath);

    // ʹ��˽Կ�Թ�ϣֵ����ǩ�������ܣ�
    std::vector<unsigned char> SignHashWithPrivateKey(RSA* privateKey, const std::string& hash);

    // ʹ�ù�Կ��֤ǩ��
    bool VerifySignatureWithPublicKey(RSA* publicKey, const std::string& hash, const std::vector<unsigned char>& signature);

    // ��ǩ�����浽�ļ�
    void SaveSignatureToFile(const std::string& filePath, const std::vector<unsigned char>& signature);

private:
    // ������������ʾ OpenSSL ����
    void ShowOpenSSLError();

    // ��ʾ������Ϣ
    void ShowError(const std::string& message);

    // ��ʾ��Ϣ��ʾ
    void ShowInfo(const std::string& message);
};

