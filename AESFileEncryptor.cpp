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

// AESFileEncryptor ���캯��
AESFileEncryptor::AESFileEncryptor(const std::string& key, const std::string& iv) : key_(key), iv_(iv) {
    if (key_.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("AES key must be 16 bytes (128 bits).");
    }
    if (iv_.size() != AES_BLOCK_SIZE) {
        throw std::invalid_argument("AES IV must be 16 bytes.");
    }
}

// ���ַ���ת��Ϊ�ֽ�����
void AESFileEncryptor::stringToBytes(const std::string& str, unsigned char* out) {
    for (size_t i = 0; i < str.size(); ++i) {
        out[i] = static_cast<unsigned char>(str[i]);
    }
}

// ���ܵ�������
void AESFileEncryptor::encryptBlock(const unsigned char* in, unsigned char* out, const unsigned char* key, const unsigned char* iv) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);  // ʹ�� 128 λ��Կ

    // ʹ�� AES CBC ģʽ����
    AES_cbc_encrypt(in, out, AES_BLOCK_SIZE, &aesKey, const_cast<unsigned char*>(iv), AES_ENCRYPT);
}

// �� AES �����ļ���д�� MD5 ֵ
bool AESFileEncryptor::encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& md5Hash) {
    std::ifstream inputFileStream(inputFile, std::ios::binary);
    if (!inputFileStream) {
        showMessageBox("�޷��������ļ�: " + inputFile, "Error");
        return false;
    }

    // ��ȡ��ǰ����Ŀ¼
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);  // ��ȡ��ǰ����Ŀ¼
    std::string outputDir = std::string(buffer); // ��ȡ��ǰĿ¼·��
    std::string outputPath = outputDir + "\\" + outputFile; // ���·��

    std::ofstream outputFileStream(outputPath, std::ios::binary);
    if (!outputFileStream) {
        showMessageBox("�޷�������ļ�: " + outputPath, "Error");
        return false;
    }

    unsigned char key[AES_BLOCK_SIZE];
    unsigned char iv[AES_BLOCK_SIZE];

    // ����Կ�� IV ת��Ϊ�ֽ�����
    stringToBytes(key_, key);
    stringToBytes(iv_, iv);

    unsigned char inBuffer[AES_BLOCK_SIZE];
    unsigned char outBuffer[AES_BLOCK_SIZE];

    std::stringstream encryptedDataStream;

    while (inputFileStream.read(reinterpret_cast<char*>(inBuffer), AES_BLOCK_SIZE)) {
        // ���ܶ�ȡ��ÿ�� AES ��
        encryptBlock(inBuffer, outBuffer, key, iv);

        // �����ܺ������д���ڴ���
        encryptedDataStream.write(reinterpret_cast<char*>(outBuffer), AES_BLOCK_SIZE);
    }

    // �����ļ����ʣ��Ĳ��֣�����еĻ�
    size_t bytesRead = inputFileStream.gcount();
    if (bytesRead > 0) {
        // ������һ������
        std::memset(inBuffer, 0, AES_BLOCK_SIZE);
        std::memcpy(inBuffer, outBuffer, bytesRead);

        encryptBlock(inBuffer, outBuffer, key, iv);

        encryptedDataStream.write(reinterpret_cast<char*>(outBuffer), AES_BLOCK_SIZE);
    }

    // ��ȡ�������ݵ�����
    std::string encryptedData = encryptedDataStream.str();

    // �� MD5 ��ϣֵ�ͼ�������д���ļ�
    outputFileStream.write(md5Hash.c_str(), md5Hash.size()); // ��д MD5 ֵ
    outputFileStream.write(reinterpret_cast<const char*>(encryptedData.c_str()), encryptedData.size()); // д��������

    inputFileStream.close();
    outputFileStream.close();

    showMessageBox("�ļ��ѳɹ����ܲ�����Ϊ " + outputPath, "Success");

    return true;
}