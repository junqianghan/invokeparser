#ifndef INVOKEPARSE_PATTERN_MATCH_H
#define INVOKEPARSE_PATTERN_MATCH_H

#include <string>
#include "def.h"
#include <regex>
/**
 * 分析给出src的类型,模式匹配,提取出数据放到logData中.
 */
class PatternParser
{
  public:
    PatternParser(std::string& src):src_(src){}
    LogData& match();

  private:
    std::string src_;

    LogData logData;

    void regex_to_logData_generate(const std::smatch& r, LogData& logData);
    void regex_to_logData_finish(const std::smatch& r, LogData& logData);
    void regex_to_logData_res(const std::smatch& r, LogData& logData);
};

#endif //INVOKEPARSE_PATTERN_MATCH_H
