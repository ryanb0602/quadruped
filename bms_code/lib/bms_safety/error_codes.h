#include <map>

#ifndef ERROR_CODES_H
#define ERROR_CODES_H

std::map<int, const char*> __ERROR_CODES = {
    {1, "MCU TEMPERATURE OUT OF RANGE"},
    {2, "BATTERY TEMPERATURE OUT OF RANGE"},
    {3, "BOARD TEMPERATURE OUT OF RANGE"},
    {4, "FATAL SHUTDOWN"},
    {5, "LOAD CURRENT OUT OF RANGE"},
    {6, "CHARGE CURRENT OUT OF RANGE"}
};

#endif