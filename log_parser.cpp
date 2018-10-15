#include "log_parser.h"
#include "file_io.h"
#include "pattern_parser.h"
#include "errorid.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <deque>
#include <regex>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::ifstream;
using std::shared_ptr;
using std::make_shared;
using std::deque;
using std::regex;
using std::smatch;
using std::regex_match;

LogParser::LogParser(const std::string &corr_id,std::function<std::string (std::string)> getDateTime):corr_id_(corr_id)
{
    datetime_ = getDateTime(corr_id_);
}


std::shared_ptr<ServiceNode> LogParser::parser()
{

    if(parsered)
    {
        return root;
    }
    else
    {
        parsered = true;
    }

    string dirPath = getDirPath();
    vector<string> fileList;
    readFileList(dirPath,fileList);

    string time_pre,time_last;
    int ret = getTimeFromDatetime(datetime_,time_pre,time_last,2);
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

                if(logData.time<time_pre)
                    continue;
                if(logData.time>time_last)
                    break;


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
            root = make_shared<ServiceNode>(l.app_name);
        }

        if(l.log_type == LogData::LogType::REQ_GENERATE_MSG)
        {
            requestIdToApp.insert({l.ri,l.app_name});
        }

    }

    unsigned resMsgNum = 0;     //node number of res msg.
    for(auto& l:logDatas)
    {
        if(l.log_type == LogData::LogType::RES_MSG)
        {
            ++resMsgNum;
            string res_ri = l.ri;
            if(requestIdToApp.find(res_ri) != requestIdToApp.end())
            {
                string requestName = requestIdToApp[res_ri];
                string responseName = l.app_name;
                responseToRequest.insert({responseName,requestName});
                requestToResponses[requestName].insert(responseName);
            }
            else
            {
                cerr<<"not found"<<endl;
                errorid = ERROR_LOG_PARSER_NO_APP_FROM_RI;
                root = nullptr;
                return root;
            }
        }
    }

    ret = getFreeNodes(resMsgNum);

    ret = getServiceNodeTree();

    if(ret)
    {
        errorid = ret;
        root = nullptr;
    }

    return root;
}

std::string LogParser::serialize() {

    if(!parsered)
    {
        parser();
        parsered = true;
    }

    if(!root)
    {
        return string();
    }

    string ret;

    deque<shared_ptr<ServiceNode>> nodeDeque;
    nodeDeque.push_back(root);

    while(nodeDeque.size())
    {
        shared_ptr<ServiceNode> node = nodeDeque.front();
        nodeDeque.pop_front();

        ret = ret + node->name + ":";
        if(node->childs.size() == 0)
        {
            ret += ";";
            continue;
        }
        for(auto i:node->childs)
        {
            nodeDeque.push_back(i);
            ret = ret + i->name + ",";
        }
        ret += ";";
    }
    return ret;
}


int LogParser::getServiceNodeTree()
{
    if(!root)
        return ERROR_LOG_PARSER_ROOT_NULL;
    deque<string> appDeque;
    deque<shared_ptr<ServiceNode>> nodeDeque;

    appDeque.push_back(root->name);
    nodeDeque.push_back(root);

    while(nodeDeque.size())
    {
        shared_ptr<ServiceNode> pNode = nodeDeque.front();
        nodeDeque.pop_front();
        string currAppName = pNode->name;
        for(auto response:requestToResponses[currAppName])
        {
            if(freeNodes.size() == 0)
            {
                return ERROR_LOG_PARSER_NO_FREENODE;
            }
            shared_ptr<ServiceNode> node = freeNodes.back();
            freeNodes.pop_back();
            node->name = response;
            node->parent = pNode;
            pNode->childs.push_back(node);
            nodeDeque.push_back(node);
        }
        if(requestToResponses.size() == 0)
        {
            break;
        }
    }

    return 0;
}

std::string LogParser::getDirPath()
{
    string dirPath(datetime_,0,11);
    unsigned long pos = dirPath.find('-');
    dirPath[pos] = '/';
    dirPath = "../log/"+dirPath;
    return dirPath;
}

int LogParser::getFreeNodes(unsigned int num) {
    for(unsigned i=0;i<num;++i)
    {
        freeNodes.push_back(make_shared<ServiceNode>());
    }
    return 0;
}

int LogParser::getTimeFromDatetime(std::string &datetime, std::string &pre, std::string &last, int interval)
{
    regex regex_datetime("(.*)-(.*)");
    smatch r;
    int hour,min;
    double sec;
    if(regex_match(datetime,r,regex_datetime))
    {
        sscanf(r.str(2).c_str(),"%d:%d:%lf",&hour,&min,&sec);
    }
    else
    {
        return ERROR_LOG_PARSER_DATETIME_FORMAT;
    }

    pre = to_string(hour)+":"+to_string(min)+":"+to_string(int(sec));
    last = to_string(hour)+":"+to_string(min+2)+":"+to_string(int(sec));
    return 0;
}