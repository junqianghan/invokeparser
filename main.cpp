#include <iostream>
#include "file_io.h"
#include "pattern_parser.h"
#include <vector>
#include <string>
#include <regex>
#include "log_parser.h"
using namespace std;

int main()
{
//    vector<string> fileList;
//    int ret = readFileList(string("../log"),fileList);
//    if(ret != 0)
//    {
//        return ret;
//    }
//    for(auto i:fileList)
//    {
//        cout<<i<<endl;
//    }

//    string s("T13:26:44.94 Client_Request finish 22ms 0 corr_id_=ejsQ5ufDFCmyHG6v&ri=OgXI76Q5z9++&node_id=NSflDxKmr2AR");
//    regex regex1("^T(.*)corr_id_=(.*)&ri=(.*)&node_id=(.*)");
//
//    smatch r1;
//    cout<<boolalpha<<regex_match(s,r1,regex1)<<endl;
//    cout<<r1.str(1)<<endl;
//    cout<<r1.str(2)<<endl;
//    cout<<r1.str(3)<<endl;

//    string s("T13:26:44.94 Client_Request finish 22ms 0 corr_id_=ejsQ5ufDFCmyHG6v&ri=OgXI76Q5z9++&node_id=NSflDxKmr2AR");
//    string s2("T13:26:45.14 URL API_1 of Application A 237ms 0 corr_id_=ejsQ5ufDFCmyHG6v&node_id=NSflDxKmr2AR");
//    string s3("T13:26:44.94 URL API_2 of Application B 20ms 0 corr_id_=ejsQ5ufDFCmyHG6v&node_id=ehqX1s11N9vA&ri=OgXI76Q5z9++");
//
//    PatternParser pp(s3);
//    LogData &logData = pp.match();
//    cout<<logData<<endl;

//    pattern_match(s,logData);
//    cout<<logData<<endl;
//    pattern_match(s2,logData);
//    cout<<logData<<endl;
//    pattern_match(s3,logData);
//    cout<<logData<<endl;
    LogParser logParser("ejsQ5ufDFCmyHG6v","20180902:14");
//    logParser.parser();
    string s = logParser.serialize();
//    string app;
//    filenameParser("./log/20180902/14/A/1.log",app);
//    cout<<app<<endl;

    return 0;
}