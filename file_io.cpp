#include "file_io.h"
#include <dirent.h>
#include <cstring>
#include <iostream>
#include <regex>
using std::string;
using std::vector;
using std::cerr;
using std::cout;
using std::endl;
using std::regex;
using std::smatch;
using std::regex_match;

int readFileList(const string& basePath, vector<std::string>& fileList){
    DIR *dir;
    struct dirent *ptr;

    dir = opendir(basePath.c_str());
    if(dir == NULL)
    {
        cerr<<"Open dir error..."<<endl;
        return -1;
    }

    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".") == 0|| strcmp(ptr->d_name,"..") == 0)
        {
            continue;
        }
        else if(ptr->d_type == 8 || ptr->d_type == 10){
            fileList.push_back(basePath+"/"+string(ptr->d_name));
        }
        else if(ptr->d_type == 4)
        {
            string subPath = basePath+"/"+string(ptr->d_name);
            readFileList(subPath,fileList);
        }
    }
    closedir(dir);
    return 0;
}

int filenameParser(const std::string& file, FilenameParserData& data)
{
    regex nameRegex("^(.*)/log/([0-9]+)/([0-9]+)/(.*)/(.*).log$");
    smatch r;
    if(regex_match(file,r,nameRegex))
    {
        data.date = r.str(2);
        data.hour = r.str(3);
        data.app_name = r.str(4);
        return 0;
    }
    else
    {
        cerr<<"no match"<<endl;
        return -1;
    }
}