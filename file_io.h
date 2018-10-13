#ifndef INVOKEPARSE_FILE_IO_H
#define INVOKEPARSE_FILE_IO_H

#include <string>
#include <vector>

/**
 *
 * @param basePath : 路径名
 * @param fileList ： 文件名列表
 * @return  正确返回0,错误返回-1.
 */
int readFileList(const std::string& basePath,std::vector<std::string>& fileList);


struct FilenameParserData
{
    std::string date;
    std::string hour;
    std::string app_name;
};


int filenameParser(const std::string& file, FilenameParserData& data);
#endif //INVOKEPARSE_FILE_IO_H
