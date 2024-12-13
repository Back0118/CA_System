#include "pch.h"
#include "file.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <regex>// �����쳣����
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

    // ��ȡ�ļ�����
    bool readFilename(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            MessageBox(0,TEXT("Error opening file."), TEXT("Error"), MB_OK | MB_ICONERROR);
            return false;
        }

        // ����������Ҫƥ����ĸ��ֶε�������ʽ
        std::regex expectedPattern(R"(^\s*(name|phone|email|room)\s*:.*$)"); // ƥ�� "������"��"�ֻ��ţ�"��"���䣺"��"�༶��"
        std::string line;

        // ���ж�ȡ�ļ����ݲ�����ʽ
        while (std::getline(file, line)) {
            // �����ǰ�в�����Ԥ�ڵĸ�ʽ
            if (!std::regex_match(line, expectedPattern)) {
                MessageBox(0, TEXT(" opening file."), TEXT("WRONG"), MB_OK | MB_ICONERROR);
                file.close();
                return false;  // ������κ�һ�в�ƥ���ʽ������ false
            }
        }
        
        file.close();
        return true;  // �����ж�ƥ���ʽ������ true
    }

    bool readFilePubilcpath(const std::string& filePath) {
        std::ifstream file(filePath);

        // ����ļ��Ƿ�ɹ���
        if (!file.is_open()) {
            MessageBox(0, TEXT("Error opening file."), TEXT("Error"), MB_OK | MB_ICONERROR);
            return false;
        }

        // ��ȡ�ļ�����
        std::string line;
        bool hasBegin = false;
        bool hasEnd = false;

        // ���� "-----BEGIN" �� "-----END" ��ʶ��
        while (std::getline(file, line)) {
            // ȥ������β�Ŀհ��ַ�
            line.erase(0, line.find_first_not_of(" \t\n\r"));
            line.erase(line.find_last_not_of(" \t\n\r") + 1);

            // ����ļ������Ƿ���� PEM ��ʼ�ͽ������
            if (line.find("-----BEGIN") != std::string::npos) {
                hasBegin = true;
            }
            if (line.find("-----END") != std::string::npos) {
                hasEnd = true;
            }

            // ������߶����ڣ��Ҳ���ͬһ�У��Ϳ�����Ϊ�� PEM ��ʽ
            if (hasBegin && hasEnd) {
                break;
            }
        }

        file.close();

        // ����ļ����� BEGIN �� END ��ʶ������λ�ú�����Ϊ���� PEM �ļ�
        return hasBegin && hasEnd;
    }


    bool getNameFromFile(const std::string& filePath, std::string& outName) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            // ʹ�� MessageBox ��ʾ������Ϣ
            std::wstring wFilePath(filePath.begin(), filePath.end());
            std::wstring errorMessage = L"Error opening file: " + wFilePath;
            MessageBoxW(NULL, errorMessage.c_str(), L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        std::string firstLine;
        std::getline(file, firstLine);  // ��ȡ��һ��

        // ʹ��������ʽ��ȡ name: ���������
        std::regex nameRegex("^name:\\s*(.*)$", std::regex_constants::icase);
        std::smatch match;

        if (std::regex_match(firstLine, match, nameRegex) && match.size() > 1) {
            outName = match.str(1); // ��ȡ name ��Ĳ���
            return true;
        }

        // ���û���ҵ���Ч�� name, ʹ�� MessageBox ��ʾ����
        MessageBoxW(NULL, L"No valid name found in the first line.", L"File Error", MB_OK | MB_ICONERROR);
        return false;
    }

    // ��װ��ȡ���ϲ���д���ļ��ĺ���
    bool combineFilesToNewFile(const std::string& txtFilePath, const std::string& pemFilePath) {
        // ��ȡ txt �ļ�����
        std::ifstream txtFile(txtFilePath, std::ios::binary);
        if (!txtFile.is_open()) {
            // ʹ�� MessageBox ��ʾ������Ϣ
            std::wstring wTxtFilePath(txtFilePath.begin(), txtFilePath.end());
            std::wstring errorMessage = L"Error opening txt file: " + wTxtFilePath;
            MessageBoxW(NULL, errorMessage.c_str(), L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        std::ostringstream txtContentStream;
        txtContentStream << txtFile.rdbuf();
        std::string txtContent = txtContentStream.str();
        txtFile.close();

        // ��ȡ pem �ļ�����
        std::ifstream pemFile(pemFilePath, std::ios::binary);
        if (!pemFile.is_open()) {
            // ʹ�� MessageBox ��ʾ������Ϣ
            std::wstring wPemFilePath(pemFilePath.begin(), pemFilePath.end());
            std::wstring errorMessage = L"Error opening pem file: " + wPemFilePath;
            MessageBoxW(NULL, errorMessage.c_str(), L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        std::ostringstream pemContentStream;
        pemContentStream << pemFile.rdbuf();
        std::string pemContent = pemContentStream.str();
        pemFile.close();

        // �ϲ������ļ�������
        std::string combinedContent = txtContent + "\n" + pemContent;

        // �� txt �ļ���ȡ name ����������ļ���
        std::string outputFileName;
        if (!getNameFromFile(txtFilePath, outputFileName)) {
            // ������ļ���δ��ȡ�����֣���ʾ����
            MessageBoxW(NULL, L"Failed to extract name from txt file.", L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        // Ϊ����ļ���������·������������ļ�Ϊ .txt��
        std::string outputFilePath = outputFileName + ".txt";

        // ���ϲ��������д�뵽����ļ�
        std::ofstream outputFile(outputFilePath, std::ios::binary);
        if (!outputFile.is_open()) {
            // ʹ�� MessageBox ��ʾ������Ϣ
            std::wstring wOutputFilePath(outputFilePath.begin(), outputFilePath.end());
            std::wstring errorMessage = L"Error opening output file: " + wOutputFilePath;
            MessageBoxW(NULL, errorMessage.c_str(), L"File Error", MB_OK | MB_ICONERROR);
            return false;
        }

        outputFile.write(combinedContent.c_str(), combinedContent.size());
        outputFile.close();

        // ʹ�� MessageBox ��ʾ�ɹ���Ϣ
        std::wstring successMessage = L"Files successfully combined and written to: " + std::wstring(outputFilePath.begin(), outputFilePath.end());
        MessageBoxW(NULL, successMessage.c_str(), L"Success", MB_OK | MB_ICONINFORMATION);
        SHA256 sha256;
        // �����ļ��Ĺ�ϣֵ��ʹ�� SHA-256��
        std::string hashValue;
        if (sha256.computeFileHash(outputFilePath, hashValue)) {
            // ��ʾ��ϣֵ
            Global::addUser(outputFileName, hashValue);
            std::wstring hashMessage = L"SHA-256 Hash: " + std::wstring(hashValue.begin(), hashValue.end());
            MessageBoxW(NULL, hashMessage.c_str(), L"Hash Result", MB_OK | MB_ICONINFORMATION);

            // ����ϣֵ��������һ���ļ���
            std::string hashFileName = outputFileName + "_hash.txt";
            std::ofstream hashFile(hashFileName);
            if (hashFile.is_open()) {
                hashFile << hashValue;
                hashFile.close();

                // ��ʾ�����ϣ�ļ�
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


    // �����ı����ļ�
    void saveFile(const std::string& filePath, const std::string& text) {
        std::ofstream file(filePath, std::ios::binary);  // �Զ�����ģʽ���ļ�
        if (!file.is_open()) {
            throw std::ios_base::failure("Error opening file: " + filePath);  // �׳��쳣
        }

        file.write(text.c_str(), text.size());
        if (!file) {  // ���д���Ƿ�ɹ�
            throw std::ios_base::failure("Error writing to file: " + filePath);
        }
    }

    // ɾ���ļ�
    void deleteFile(const std::string& filePath) {
        if (std::remove(filePath.c_str()) != 0) {
            throw std::ios_base::failure("Error deleting file: " + filePath);  // �׳��쳣
        }
    }

}
