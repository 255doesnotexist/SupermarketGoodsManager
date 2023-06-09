#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>

namespace Utils {
    int toInt(const std::string &input);
    double toDouble(const std::string &input);
    std::wstring toWstring(std::string input);
    std::string toString(std::wstring input);
    bool isChineseChar(wchar_t ch);
};

#endif
