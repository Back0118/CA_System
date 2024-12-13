#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
namespace F_ile
{
 // ��ȡ�ļ��������ļ�����
    bool readFilename(const std::string& filePath);
    bool readFilePubilcpath(const std::string& filePath);
    bool getNameFromFile(const std::string& filePath, std::string& outName);
    bool combineFilesToNewFile(const std::string& txtFilePath, const std::string& pemFilePath);
    // �����ı����ļ�
    void saveFile(const std::string& filePath, const std::string& text);

    // ɾ���ļ�
   void deleteFile(const std::string& filePath);


}
#endif // FILEMANAGER_H
