#ifndef INVOKEPARSE_LOG_PARSER_H
#define INVOKEPARSE_LOG_PARSER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
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
    explicit LogParser(const std::string& corr_id, std::function<std::string (std::string)> getDateTime);

    std::shared_ptr<ServiceNode> parser();

    std::string serialize();

    int getErrorId()
    {
        return errorid;
    }

  private:

    std::string corr_id_;
    std::string datetime_;    //date-hour:min:sec

    int errorid;
    bool parsered = false;

    std::shared_ptr<ServiceNode> root;  //root node
    std::vector<std::shared_ptr<ServiceNode>> freeNodes;    // node vector valid.

    std::vector<LogData> logDatas;

    std::unordered_map<std::string,std::string> requestIdToApp;     //hashmap, from requestid to appname which generate this requestid
    std::unordered_map<std::string,std::string> responseToRequest;  //hashmap, from appname which response to appname which request
    std::unordered_map<std::string,std::unordered_set<std::string>> requestToResponses;    //hashmap, from appname which request to appname list which response.
  private:

    std::string getDirPath();

    int getFreeNodes(unsigned int num);

    int getServiceNodeTree();

    bool isTimeValid(std::string& time);
};

#endif //INVOKEPARSE_LOG_PARSER_H