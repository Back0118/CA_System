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
    // ���캯��
    RsaKeyGenerator(int keyLength = 2048, unsigned long publicExponent = RSA_F4);

    // ��������
    ~RsaKeyGenerator();

    // ����RSA��Կ��
    bool generateKeys();

    // ����Կд���ļ�
    bool writePublicKey(const std::string& publicKeyFile);

    // ��˽Կд���ļ�
    bool writePrivateKey(const std::string& privateKeyFile);
    std::string getPrivateKeyFilePath() const;  // �����Ļ�ȡ˽Կ·���ĺ���
private:
    RSA* rsa;         // RSA��Կ��
    BIGNUM* e;        // ��Կָ��
    int keyLength;    // ��Կ����
    unsigned long publicExponent;  // ��Կָ��
    std::string privateKeyFilePath;
    // ������Կ�Եĸ�������
    bool createKeyPair();
};


#endif // RSA_KEY_GENERATOR_H