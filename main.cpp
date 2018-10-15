#include <iostream>
#include "pattern_parser.h"
#include "log_parser.h"
using namespace std;

int main()
{
    LogParser logParser("ejsQ5ufDFCmyHG6v","20180902-13:26:44.94");
    string s = logParser.serialize();

    return 0;
}