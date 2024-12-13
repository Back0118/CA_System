#pragma once
// AESFileDecryptor.h
#ifndef AES_FILE_DECRYPTOR_H
#define AES_FILE_DECRYPTOR_H

#include <string>

class AESFileDecryptor {
public:
    // ���캯����������Կ�ͳ�ʼ��������IV��
    AESFileDecryptor(const std::string& key, const std::string& iv);

    // �����ļ�����������ļ�·��������ļ�·���������� MD5 У��ֵ
    bool decryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& inputMD5);

private:
    // ���ַ���ת��Ϊ�ֽ�����
    void stringToBytes(const std::string& str, unsigned char* out);

    // ���� MD5 ��ϣֵ
    std::string calculateMD5(const std::string& input);

    // ���ܵ�������
    void decryptBlock(const unsigned char* in, unsigned char* out, const unsigned char* key, unsigned char* iv);

    // ���ڴ洢��Կ�� IV
    std::string key_;
    std::string iv_;
};



#endif // AES_FILE_DECRYPTOR_H


