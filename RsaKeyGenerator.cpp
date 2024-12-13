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

// �����������ͷ���Դ
RsaKeyGenerator::~RsaKeyGenerator() {
    if (rsa) RSA_free(rsa);
    if (e) BN_free(e);
}

// ����RSA��Կ��
bool RsaKeyGenerator::generateKeys() {
    return createKeyPair();
}

// ����RSA��Կ��
bool RsaKeyGenerator::createKeyPair() {
    // ���ù�Կָ��
    if (!BN_set_word(e, publicExponent)) {
        MessageBoxA(NULL, "���ù�Կָ��ʧ��!", "����", MB_OK | MB_ICONERROR);
        return false;
    }

    // ����RSA��Կ��
    if (RSA_generate_key_ex(rsa, keyLength, e, NULL) != 1) {
        MessageBoxA(NULL, "RSA��Կ����ʧ��!", "����", MB_OK | MB_ICONERROR);
        return false;
    }
    return true;
}

// ����Կд���ļ�
bool RsaKeyGenerator::writePublicKey(const std::string& publicKeyFile) {
    BIO* bio = BIO_new_file(publicKeyFile.c_str(), "w");
    if (!bio) {
        MessageBoxA(NULL, "�򿪹�Կ�ļ�ʧ��!", "����", MB_OK | MB_ICONERROR);
        return false;
    }

    if (PEM_write_bio_RSAPublicKey(bio, rsa) != 1) {
        MessageBoxA(NULL, "д�빫Կʧ��!", "����", MB_OK | MB_ICONERROR);
        BIO_free(bio);
        return false;
    }

    BIO_free(bio);
    return true;
}

std::string RsaKeyGenerator::getPrivateKeyFilePath() const {
    return privateKeyFilePath;  // ����˽Կ·��
}
// ��˽Կд���ļ�
bool RsaKeyGenerator::writePrivateKey(const std::string& privateKeyFile) {
    char currentDir[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDir);  // ��ȡ��ǰĿ¼���洢�� currentDir

    // ƴ�ӵ�ǰ����Ŀ¼��˽Կ�ļ���
    std::string fullPrivateKeyPath = std::string(currentDir) + "\\" + privateKeyFile;
    BIO* bio = BIO_new_file(privateKeyFile.c_str(), "w");
    if (!bio) {
        MessageBoxA(NULL, "��˽Կ�ļ�ʧ��!", "����", MB_OK | MB_ICONERROR);
        return false;
    }

    if (PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL) != 1) {
        MessageBoxA(NULL, "д��˽Կʧ��!", "����", MB_OK | MB_ICONERROR);
        BIO_free(bio);
        return false;
    }
    privateKeyFilePath = fullPrivateKeyPath;  // ����·��
    BIO_free(bio);
    return true;
}