#include "pch.h"
#include "file.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <regex>// 引入异常处理
#include <sstream>
#include <filesystem>  
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <bitset>
#include "SHA256.h"
#include"Global.h"
namespace F_ile 
{

    // 读取文件内容
    bool readFilename(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            MessageBox(0,TEXT("Error opening file."), TEXT("Error"), MB_OK | MB_ICONERROR);
            return false;
        }

        // 定义我们需要匹配的四个字段的正则表达式
        std::regex expectedPattern(R"(^\s*(name|phone|email|room)\s*:.*$)"); // 匹配 "姓名："、"手机号："、"邮箱："、"班级："
        std::string line;

        // 逐行读取文件内容并检查格式
        while (std::getline(file, line)) {
            // 如果当前行不符合预期的格式
            if (!std::regex_match(line, expectedPattern)) {
                MessageBox(0, TEXT(" opening file."), TEXT("WRONG"), MB_OK | MB_ICONERROR);
                file.close();
                return false;  // 如果有任何一行不匹配格式，返回 false
            }
        }
        
        file.close();
        return true;  // 所有行都匹配格式，返回 true
    }

    bool readFilePubilcpath(const std::string& filePath) {
        std::ifstream file(filePath);

        // 检查文件是否成功打开
        if (!file.is_open()) {
            MessageBox(0, TEXT("Error opening file."), TEXT("Error"), MB_OK | MB_ICONERROR);
            return false;
        }

        // 读取文件内容
        std::string line;
        bool hasBegin = false;
        bool hasEnd = false;

        // 查找 "-----BEGIN" 和 "-----END" 标识符
        while (std::getline(file, line)) {
            // 去除行首尾的空白字符
            line.erase(0, line.find_first_not_of(" \t\n\r"));
            line.erase(line.find_last_not_of(" \t\n\r") + 1);

            // 检查文件内容是否包含 PEM 开始和结束标记
            if (line.find("-----BEGIN") != std::string::npos) {
                hasBegin = true;
            }
            if (line.find("-----END") != std::string::npos) {
                hasEnd = true;
            }

            // 如果两者都存在，且不是同一行，就可以认为是 PEM 格式
            if (hasBegin && hasEnd) {
                break;
            }
        }

        file.close();

        // 如果文件包含 BEGIN 和 END 标识符，且位置合理，认为它是 PEM 文件
        return hasBegin && hasEnd;
    }


    bool getNameFromFile(const std::string& filePath, std::string& outName) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            // 使用 MessageBox 显示错误信息
            std::wstring wFilePath(filePath.begin(), filePath.end());
            std::wstring errorMessage = L"Error opening file: " + wFilePath;
            MessageBoxW(NULL, errorMessage.c_str(), L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        std::string firstLine;
        std::getline(file, firstLine);  // 读取第一行

        // 使用正则表达式提取 name: 后面的内容
        std::regex nameRegex("^name:\\s*(.*)$", std::regex_constants::icase);
        std::smatch match;

        if (std::regex_match(firstLine, match, nameRegex) && match.size() > 1) {
            outName = match.str(1); // 提取 name 后的部分
            return true;
        }

        // 如果没有找到有效的 name, 使用 MessageBox 显示错误
        MessageBoxW(NULL, L"No valid name found in the first line.", L"File Error", MB_OK | MB_ICONERROR);
        return false;
    }

    // 封装读取、合并和写入文件的函数
    bool combineFilesToNewFile(const std::string& txtFilePath, const std::string& pemFilePath) {
        // 读取 txt 文件内容
        std::ifstream txtFile(txtFilePath, std::ios::binary);
        if (!txtFile.is_open()) {
            // 使用 MessageBox 显示错误信息
            std::wstring wTxtFilePath(txtFilePath.begin(), txtFilePath.end());
            std::wstring errorMessage = L"Error opening txt file: " + wTxtFilePath;
            MessageBoxW(NULL, errorMessage.c_str(), L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        std::ostringstream txtContentStream;
        txtContentStream << txtFile.rdbuf();
        std::string txtContent = txtContentStream.str();
        txtFile.close();

        // 读取 pem 文件内容
        std::ifstream pemFile(pemFilePath, std::ios::binary);
        if (!pemFile.is_open()) {
            // 使用 MessageBox 显示错误信息
            std::wstring wPemFilePath(pemFilePath.begin(), pemFilePath.end());
            std::wstring errorMessage = L"Error opening pem file: " + wPemFilePath;
            MessageBoxW(NULL, errorMessage.c_str(), L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        std::ostringstream pemContentStream;
        pemContentStream << pemFile.rdbuf();
        std::string pemContent = pemContentStream.str();
        pemFile.close();

        // 合并两个文件的内容
        std::string combinedContent = txtContent + "\n" + pemContent;

        // 从 txt 文件获取 name 并创建输出文件名
        std::string outputFileName;
        if (!getNameFromFile(txtFilePath, outputFileName)) {
            // 如果从文件中未提取到名字，显示错误
            MessageBoxW(NULL, L"Failed to extract name from txt file.", L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        // 为输出文件创建完整路径（假设输出文件为 .txt）
        std::string outputFilePath = outputFileName + ".txt";

        // 将合并后的内容写入到输出文件
        std::ofstream outputFile(outputFilePath, std::ios::binary);
        if (!outputFile.is_open()) {
            // 使用 MessageBox 显示错误信息
            std::wstring wOutputFilePath(outputFilePath.begin(), outputFilePath.end());
            std::wstring errorMessage = L"Error opening output file: " + wOutputFilePath;
            MessageBoxW(NULL, errorMessage.c_str(), L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        outputFile.write(combinedContent.c_str(), combinedContent.size());
        outputFile.close();

        // 使用 MessageBox 显示成功信息
        std::wstring successMessage = L"Files successfully combined and written to: " + std::wstring(outputFilePath.begin(), outputFilePath.end());
        MessageBoxW(NULL, successMessage.c_str(), L"Success", MB_OK | MB_ICONINFORMATION);
        SHA256 sha256;
        // 计算文件的哈希值（使用 SHA-256）
        std::string hashValue;
        if (sha256.computeFileHash(outputFilePath, hashValue)) {
            // 显示哈希值
            Global::addUser(outputFileName, hashValue);
            std::wstring hashMessage = L"SHA-256 Hash: " + std::wstring(hashValue.begin(), hashValue.end());
            MessageBoxW(NULL, hashMessage.c_str(), L"Hash Result", MB_OK | MB_ICONINFORMATION);

            // 将哈希值保存在另一个文件中
            std::string hashFileName = outputFileName + "_hash.txt";
            std::ofstream hashFile(hashFileName);
            if (hashFile.is_open()) {
                hashFile << hashValue;
                hashFile.close();

                // 提示保存哈希文件
                std::wstring hashFileMessage = L"Hash saved to: " + std::wstring(hashFileName.begin(), hashFileName.end());
                MessageBoxW(NULL, hashFileMessage.c_str(), L"Success", MB_OK | MB_ICONINFORMATION);
            }
            else {
                MessageBoxW(NULL, L"Error saving hash to file.", L"File Error", MB_OK | MB_ICONERROR);
            }
        }
        else {
            MessageBoxW(NULL, L"Failed to compute hash for the output file.", L"Error", MB_OK | MB_ICONERROR);
            return false;
        }

        return true;
    }


    // 保存文本到文件
    void saveFile(const std::string& filePath, const std::string& text) {
        std::ofstream file(filePath, std::ios::binary);  // 以二进制模式打开文件
        if (!file.is_open()) {
            throw std::ios_base::failure("Error opening file: " + filePath);  // 抛出异常
        }

        file.write(text.c_str(), text.size());
        if (!file) {  // 检查写入是否成功
            throw std::ios_base::failure("Error writing to file: " + filePath);
        }
    }

    // 删除文件
    void deleteFile(const std::string& filePath) {
        if (std::remove(filePath.c_str()) != 0) {
            throw std::ios_base::failure("Error deleting file: " + filePath);  // 抛出异常
        }
    }

}
