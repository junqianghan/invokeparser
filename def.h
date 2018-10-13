#ifndef INVOKEPARSE_DEF_H
#define INVOKEPARSE_DEF_H
#include <string>
#include <iostream>

struct LogData{
    enum class LogType
    {
        REQ_GENERATE_MSG = 0,
        REQ_FINISH_MSG = 1,
        RES_MSG = 2,
        NONE = 3
    };

    LogType log_type;
    std::string app_name;
    std::string corr_id;
    std::string ri;
    std::string node_id;
    std::string time;
    std::string date;
};

inline std::ostream& operator<<(std::ostream& os,const LogData::LogType logType)
{
    switch(logType)
    {
      case LogData::LogType::REQ_GENERATE_MSG:
        os<<"REQ_GENERATE_MSG";
        break;
      case LogData::LogType::REQ_FINISH_MSG:
        os<<"REQ_FINISH_MSG";
        break;
      case LogData::LogType::RES_MSG:
        os<<"RES_MSG";
        break;
      case LogData::LogType::NONE:
        os<<"NONE";
        break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os,const LogData& logData)
{
    os<<"log_type : "<<logData.log_type<<std::endl;
    os<<"date     : "<<logData.date<<std::endl;
    os<<"time     : "<<logData.time<<std::endl;
    os<<"app_name : "<<logData.app_name<<std::endl;
    os<<"coor_id  : "<<logData.corr_id<<std::endl;
    os<<"ri       : "<<logData.ri<<std::endl;
    os<<"node_id  : "<<logData.node_id<<std::endl;
    return os;
}

#endif //INVOKEPARSE_DEF_H
