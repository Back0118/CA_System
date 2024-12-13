#pragma once
#ifndef SHA256_H
#define SHA256_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
class SHA256 {
public:
    SHA256();

    // 输入数据
    void update(const uint8_t* data, size_t length);

    // 输出哈希值
    std::string final();

    // 计算文件的SHA-256哈希值
    bool computeFileHash(const std::string& filePath, std::string& hashOutput);

private:
    std::vector<uint8_t> m_data;
    uint32_t m_hash[8];

    // SHA-256常量
    static const uint32_t k[64];

    void reset();
    void processBlock();
    uint32_t rotateRight(uint32_t x, unsigned n);
    std::string toHex(const uint32_t* hash);
};

#endif // SHA256_H
