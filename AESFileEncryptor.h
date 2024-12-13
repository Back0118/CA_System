#pragma once
#ifndef AESFILEENCRYPTOR_H
#define AESFILEENCRYPTOR_H
#include <string>

class AESFileEncryptor {
public:
    AESFileEncryptor(const std::string& key, const std::string& iv);
    bool encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& md5Hash);

private:
    void stringToBytes(const std::string& str, unsigned char* out);
    void encryptBlock(const unsigned char* in, unsigned char* out, const unsigned char* key, const unsigned char* iv);

    std::string key_;
    std::string iv_;
};

#endif // AESFILEENCRYPTOR_H

