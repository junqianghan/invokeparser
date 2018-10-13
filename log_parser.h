#ifndef INVOKEPARSE_LOG_PARSER_H
#define INVOKEPARSE_LOG_PARSER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "def.h"
struct ServiceNode
{
    ServiceNode() = default;
    ServiceNode(std::string serviceName):name(serviceName),parent(nullptr){}

    std::string name;
    std::shared_ptr<ServiceNode> parent;
    std::vector<std::shared_ptr<ServiceNode>> childs;

};

class LogParser
{
  public:
    explicit LogParser(const std::string& corr_id, const std::string& datetime):corr_id_(corr_id),datetime_(datetime){}

    std::shared_ptr<ServiceNode> parser();

  private:

    std::string corr_id_;
    std::string datetime_;    //date:time

    std::shared_ptr<ServiceNode> root;  //根节点

    std::vector<LogData> logDatas;

    std::unordered_map<std::string,std::string> requestIdToApp;
    std::unordered_map<std::string,std::string> responseToRequest;
    std::string getDirPath();
};

#endif //INVOKEPARSE_LOG_PARSER_H