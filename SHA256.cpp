#include "pch.h"
#include "SHA256.h"
const uint32_t SHA256::k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0x49b40821, 0x4bdecfa9, 0x5e81e63e, 0x9b05688c, 0x1f83d9ab, 0x5b5a9e61, 0x8c9dfd9c, 0x8bbf61df,
    0xa62d62b4, 0xa919fbe5, 0xc2a0a1f2, 0x42260b6b, 0x9d3da78b, 0x43bd0607, 0xf5a247f4, 0x67ab53c1,
    0x55218bd3, 0xe73d3c23, 0x36d4df76, 0x36b6b925, 0x98b71e2a, 0x97f8c945, 0x66c07b4f, 0xcdaef179,
    0xe9e3ccbc, 0x63b283c1, 0x69498e1b, 0xa2809b87, 0x99f09d16, 0x986cf3ae, 0x3e5a1bb2, 0x8c9512d7,
    0x5623d50f, 0xe89b10d2, 0x1b3504e3, 0x92e72ef3, 0x072d0979, 0xc87b6376, 0xa5f1dfe1, 0x2345ac57
};

// 构造函数，初始化哈希值
SHA256::SHA256() {
    reset();
}

// 重置哈希值
void SHA256::reset() {
    m_hash[0] = 0x6a09e667;
    m_hash[1] = 0xbb67ae85;
    m_hash[2] = 0x3c6ef372;
    m_hash[3] = 0xa54ff53a;
    m_hash[4] = 0x510e527f;
    m_hash[5] = 0x9b05688c;
    m_hash[6] = 0x1f83d9ab;
    m_hash[7] = 0x5be0cd19;
}

// 更新数据
void SHA256::update(const uint8_t* data, size_t length) {
    m_data.insert(m_data.end(), data, data + length);
    while (m_data.size() >= 64) {
        processBlock();
    }
}

// 处理64字节块
void SHA256::processBlock() {
    uint32_t block[16];
    for (int i = 0; i < 16; ++i) {
        block[i] = (m_data[i * 4] << 24) |
            (m_data[i * 4 + 1] << 16) |
            (m_data[i * 4 + 2] << 8) |
            (m_data[i * 4 + 3]);
    }
    m_data.erase(m_data.begin(), m_data.begin() + 64);

    uint32_t w[64];
    for (int t = 0; t < 16; ++t) {
        w[t] = block[t];
    }

    for (int t = 16; t < 64; ++t) {
        w[t] = w[t - 16] + w[t - 7] +
            (rotateRight(w[t - 15], 7) ^ rotateRight(w[t - 15], 18) ^ (w[t - 15] >> 3)) +
            (rotateRight(w[t - 2], 17) ^ rotateRight(w[t - 2], 19) ^ (w[t - 2] >> 10));
    }

    uint32_t a = m_hash[0];
    uint32_t b = m_hash[1];
    uint32_t c = m_hash[2];
    uint32_t d = m_hash[3];
    uint32_t e = m_hash[4];
    uint32_t f = m_hash[5];
    uint32_t g = m_hash[6];
    uint32_t h = m_hash[7];

    for (int t = 0; t < 64; ++t) {
        uint32_t t1 = h + (rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25)) +
            (e & f) ^ (~e & g) + k[t] + w[t];
        uint32_t t2 = (rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22)) +
            (a & b) ^ (a & c) ^ (b & c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    m_hash[0] += a;
    m_hash[1] += b;
    m_hash[2] += c;
    m_hash[3] += d;
    m_hash[4] += e;
    m_hash[5] += f;
    m_hash[6] += g;
    m_hash[7] += h;
}

// 计算右旋
uint32_t SHA256::rotateRight(uint32_t x, unsigned n) {
    return (x >> n) | (x << (32 - n));
}

// 输出最终的哈希值
std::string SHA256::final() {
    size_t bitLength = m_data.size() * 8;

    // 添加1位和填充0
    m_data.push_back(0x80);
    while (m_data.size() % 64 != 56) {
        m_data.push_back(0x00);
    }

    // 添加长度
    for (int i = 7; i >= 0; --i) {
        m_data.push_back((bitLength >> (i * 8)) & 0xFF);
    }

    processBlock();
    return toHex(m_hash);
}

// 转换为十六进制字符串
std::string SHA256::toHex(const uint32_t* hash) {
    std::ostringstream result;
    for (int i = 0; i < 8; ++i) {
        result << std::setw(8) << std::setfill('0') << std::hex << hash[i];
    }
    return result.str();
}

// 计算文件的SHA-256哈希值
bool SHA256::computeFileHash(const std::string& filePath, std::string& hashOutput) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    char buffer[8192];
    while (file.read(buffer, sizeof(buffer))) {
        update(reinterpret_cast<uint8_t*>(buffer), file.gcount());
    }
    update(reinterpret_cast<uint8_t*>(buffer), file.gcount());  // 处理文件尾部
    hashOutput = final();
    return true;
}