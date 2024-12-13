#include "pch.h"
#include "RSASignerVerifier.h"
#include <windows.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include<openssl/rsa.h>
#include <vector>
#include <cstdio>
#include "openssl/applink.c"
#pragma warning(disable:4996)
RSA* RSASignerVerifier::LoadPrivateKey(const std::string& pemFilePath) {
    FILE* privateKeyFile = fopen(pemFilePath.c_str(), "r");
    if (!privateKeyFile) {
        ShowError("Error opening private key file.");
        return nullptr;
    }

    RSA* rsaPrivateKey = PEM_read_RSAPrivateKey(privateKeyFile, nullptr, nullptr, nullptr);
    fclose(privateKeyFile);

    if (!rsaPrivateKey) {
        ShowOpenSSLError();
    }

    return rsaPrivateKey;
}

RSA* RSASignerVerifier::LoadPublicKey(const std::string& pemFilePath) {
    FILE* publicKeyFile = fopen(pemFilePath.c_str(), "r");
    if (!publicKeyFile) {
        ShowError("Error opening public key file.");
        return nullptr;
    }

    RSA* rsaPublicKey = PEM_read_RSAPublicKey(publicKeyFile, nullptr, nullptr, nullptr);
    fclose(publicKeyFile);

    if (!rsaPublicKey) {
        ShowOpenSSLError();
    }

    return rsaPublicKey;
}

std::vector<unsigned char> RSASignerVerifier::SignHashWithPrivateKey(RSA* privateKey, const std::string& hash) {
    std::vector<unsigned char> signature(RSA_size(privateKey));  // ǩ����С
    unsigned int signatureLen = 0;

    if (RSA_sign(NID_sha256, reinterpret_cast<const unsigned char*>(hash.c_str()), hash.length(),
        signature.data(), &signatureLen, privateKey) != 1) {
        ShowOpenSSLError();
    }

    signature.resize(signatureLen);  // ����ǩ���Ĵ�С
    return signature;
}

bool RSASignerVerifier::VerifySignatureWithPublicKey(RSA* publicKey, const std::string& hash, const std::vector<unsigned char>& signature) {
    int result = RSA_verify(NID_sha256, reinterpret_cast<const unsigned char*>(hash.c_str()), hash.length(),
        signature.data(), signature.size(), publicKey);

    if (result != 1) {
        ShowOpenSSLError();
        return false;  // ��֤ʧ��
    }

    return true;  // ��֤�ɹ�
}

void RSASignerVerifier::SaveSignatureToFile(const std::string& fileName, const std::vector<unsigned char>& signature) {
    char currentDir[MAX_PATH];
    if (GetCurrentDirectoryA(MAX_PATH, currentDir) == 0) {
        ShowError("Error getting current directory.");
        return;
    }

    // �����������ļ�·��
    std::string filePath = std::string(currentDir) + "\\" + fileName;

    // ���ļ�������ǩ��
    FILE* sigFile = fopen(filePath.c_str(), "wb");
    if (!sigFile) {
        ShowError("Error opening file to save signature.");
        return;
    }

    fwrite(signature.data(), 1, signature.size(), sigFile);
    fclose(sigFile);

    // ��ʾ����ɹ���Ϣ
    std::string successMessage = "Signature saved to: " + filePath;
    ShowInfo(successMessage);
}

void RSASignerVerifier::ShowOpenSSLError() {
    char* errMsg = (char*)malloc(120);
    ERR_error_string_n(ERR_get_error(), errMsg, 120);
    std::string errorMsg = "OpenSSL Error: " + std::string(errMsg);
    free(errMsg);
    ShowError(errorMsg);
}

void RSASignerVerifier::ShowError(const std::string& message) {
    MessageBoxA(0, message.c_str(), "Error", MB_OK | MB_ICONERROR);
}

void RSASignerVerifier::ShowInfo(const std::string& message) {
    MessageBoxA(0, message.c_str(), "Info", MB_OK | MB_ICONINFORMATION);
}


