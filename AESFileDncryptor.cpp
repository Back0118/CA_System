#include "pch.h"
#include "AESFileDncryptor.h"
#include <openssl/aes.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <Windows.h>  // ���� MessageBoxA
#pragma warning(disable:4996)

// ��ʾ��Ϣ��
void showMessageBoxD(const std::string& message, const std::string& title) {
    MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
}

// ���캯������ʼ����Կ�� IV
AESFileDecryptor::AESFileDecryptor(const std::string& key, const std::string& iv) : key_(key), iv_(iv) {
    if (key_.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("AES key must be 16 bytes (128 bits).");
    }
    if (iv_.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("AES IV must be 16 bytes.");
    }
}

// ���ַ���ת��Ϊ�ֽ�����
void AESFileDecryptor::stringToBytes(const std::string& str, unsigned char* out) {
    for (size_t i = 0; i < str.size(); ++i) {
        out[i] = static_cast<unsigned char>(str[i]);
    }
}

// ���ܵ�������
void AESFileDecryptor::decryptBlock(const unsigned char* in, unsigned char* out, const unsigned char* key, unsigned char* iv) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);  // ʹ�� 128 λ��Կ

    // ʹ�� AES CBC ģʽ����
    AES_cbc_encrypt(in, out, AES_BLOCK_SIZE, &aesKey, iv, AES_DECRYPT);
}

// �����ļ�
bool AESFileDecryptor::decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& expectedMD5) {
    std::ifstream inputFileStream(inputFile, std::ios::binary);
    if (!inputFileStream) {
        showMessageBoxD("�޷��������ļ�: " + inputFile, "Error");
        return false;
    }

    // ��ȡ��ǰ����Ŀ¼
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);  // ��ȡ��ǰ����Ŀ¼
    std::string outputDir = std::string(buffer); // ��ȡ��ǰĿ¼·��
    std::string outputPath = outputDir + "\\" + outputFile; // ���·����ȷ���ļ������ڵ�ǰĿ¼��

    std::ofstream outputFileStream(outputPath, std::ios::binary);
    if (!outputFileStream) {
        showMessageBoxD("�޷�������ļ�: " + outputPath, "Error");
        return false;
    }

    unsigned char key[AES_BLOCK_SIZE];
    unsigned char iv[AES_BLOCK_SIZE];

    // ����Կ�� IV ת��Ϊ�ֽ�����
    stringToBytes(key_, key);
    stringToBytes(iv_, iv);

    // ��ȡ�����ļ��е�ǰ 32 �ֽڣ��� MD5 ֵ��32 ���ַ���16 �ֽڣ�
    char md5Hash[32];
    inputFileStream.read(md5Hash, 32);

    // �� MD5 ֵת��Ϊ�ַ���
    std::string storedMD5(md5Hash, 32);

    // ���ṩ�� MD5 ���бȽ�
    if (storedMD5 != expectedMD5) {
        showMessageBoxD("MD5 У��ʧ�ܣ��ļ������ѱ��۸Ļ��𻵡�", "Error");
        inputFileStream.close();
        return false;
    }

    // ���� MD5 ֵ����ʼ�����ļ���ʣ������
    inputFileStream.seekg(32, std::ios::beg);

    // ��ȡ�����ļ�����
    unsigned char inBuffer[AES_BLOCK_SIZE];
    unsigned char outBuffer[AES_BLOCK_SIZE];

    std::stringstream decryptedDataStream;

    while (inputFileStream.read(reinterpret_cast<char*>(inBuffer), AES_BLOCK_SIZE)) {
        // ���ܶ�ȡ��ÿ�� AES ��
        decryptBlock(inBuffer, outBuffer, key, iv);

        // �����ܺ������д���ڴ���
        decryptedDataStream.write(reinterpret_cast<char*>(outBuffer), AES_BLOCK_SIZE);

        // ���� IV Ϊ��ǰ�ļ��ܿ飨CBC ģʽ��Ҫ��
        std::memcpy(iv, inBuffer, AES_BLOCK_SIZE);
    }

    // ��ȡ�������ݵ�����
    std::string decryptedData = decryptedDataStream.str();

    // �����ܺ������д���ļ�
    outputFileStream.write(decryptedData.c_str(), decryptedData.size());

    inputFileStream.close();
    outputFileStream.close();

    showMessageBoxD("�ļ��ѳɹ����ܲ�����Ϊ " + outputPath, "Success");

    return true;
}