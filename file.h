#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
namespace F_ile
{
 // 读取文件，返回文件内容
    bool readFilename(const std::string& filePath);
    bool readFilePubilcpath(const std::string& filePath);
    bool getNameFromFile(const std::string& filePath, std::string& outName);
    bool combineFilesToNewFile(const std::string& txtFilePath, const std::string& pemFilePath);
    // 保存文本到文件
    void saveFile(const std::string& filePath, const std::string& text);

    // 删除文件
   void deleteFile(const std::string& filePath);


}
#endif // FILEMANAGER_H
