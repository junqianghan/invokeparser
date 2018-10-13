#include "log_parser.h"
#include "file_io.h"
#include "pattern_parser.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::make_shared;

std::shared_ptr<ServiceNode> LogParser::parser()
{
    string dirPath = getDirPath();
    vector<string> fileList;
    readFileList(dirPath,fileList);
    for(auto f:fileList)
    {
        ifstream fs(f);
        string s;
        while(getline(fs,s))
        {
            if(s[0]=='T')
            {
                PatternParser patternParser(s);
                LogData logData = patternParser.match();

                if(logData.corr_id != corr_id_)
                    continue;

                FilenameParserData appData;
                filenameParser(f,appData);
                logData.app_name = appData.app_name;
                logData.date = appData.date;
                logDatas.push_back(logData);
            }
        }
    }

    for(auto& l:logDatas)
    {
        if(l.log_type == LogData::LogType::REQ_FINISH_MSG)
        {
            cout<<l.app_name<<endl;
            root = make_shared<ServiceNode>(l.app_name);
        }


        if(l.log_type == LogData::LogType::REQ_GENERATE_MSG)
        {
            requestIdToApp.insert({l.ri,l.app_name});
        }
    }

    for(auto& l:logDatas)
    {
        if(l.log_type == LogData::LogType::RES_MSG)
        {
            string res_ri = l.ri;
            if(requestIdToApp.find(res_ri) != requestIdToApp.end())
            {
                responseToRequest.insert({l.app_name,requestIdToApp[res_ri]});
            }
            else
            {
                cout<<"not found"<<endl;
            }
        }
    }

    for(auto& r:requestIdToApp)
    {
        cout<<r.first<<" "<<r.second<<endl;
    }


    cout<<"---------"<<endl;


    for(auto& r:responseToRequest)
    {
        cout<<r.first<<" "<<r.second<<endl;
    }

    cout<<"---------"<<endl;




    return make_shared<ServiceNode>();
}

std::string LogParser::getDirPath()
{
    string dirPath = datetime_;
    unsigned long pos = dirPath.find(':');
    dirPath[pos] = '/';
    dirPath = "../log/"+dirPath;
    return dirPath;
}