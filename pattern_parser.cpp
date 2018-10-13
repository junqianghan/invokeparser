#include "pattern_parser.h"
#include <regex>
using std::string;
using std::smatch;
using std::regex;
using std::regex_match;
using std::cout;
using std::endl;
using std::boolalpha;

static const string req_generate_pattern("^T(.*) C(.*)corr_id_=(.*)&ri=(.*)&node_id=(.*)\r");
static const string req_finish_pattern("^T(.*) U(.*)corr_id_=(.*)&node_id=(.*)\r");
static const string res_pattern("^T(.*) U(.*)corr_id_=(.*)&node_id=(.*)&ri=(.*)\r");

LogData& PatternParser::match() {
    smatch r;
    regex regex_generate(req_generate_pattern);
    regex regex_finish(req_finish_pattern);
    regex regex_res(res_pattern);

    if(regex_match(src_,r,regex_generate))
    {
        regex_to_logData_generate(r,logData);
    }
    else if(regex_match(src_,r,regex_res))
    {
        regex_to_logData_res(r,logData);
    }
    else if(regex_match(src_,r,regex_finish))
    {
        regex_to_logData_finish(r,logData);
    }
    else
    {
        logData.log_type = LogData::LogType::NONE;
    }
    return logData;
}

void PatternParser::regex_to_logData_generate(const std::smatch &r, LogData &logData) {
    logData.log_type = LogData::LogType::REQ_GENERATE_MSG;
    logData.time = r.str(1);
    logData.corr_id = r.str(3);
    logData.ri = r.str(4);
    logData.node_id = r.str(5);
}

void PatternParser::regex_to_logData_finish(const std::smatch &r, LogData &logData) {
    logData.log_type = LogData::LogType::REQ_FINISH_MSG;
    logData.time = r.str(1);
    logData.corr_id = r.str(3);
    logData.node_id = r.str(4);
}

void PatternParser::regex_to_logData_res(const std::smatch &r, LogData &logData) {
    logData.log_type = LogData::LogType::RES_MSG;
    logData.time = r.str(1);
    logData.corr_id = r.str(3);
    logData.node_id = r.str(4);
    logData.ri = r.str(5);
}