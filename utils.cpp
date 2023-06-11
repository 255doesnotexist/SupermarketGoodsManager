#include "utils.h"

#include <sstream>
#include <string>
#include <codecvt>
#include <cstdint>
#include <locale>
#include <windows.h>

int Utils::toInt(const std::string &input) {
    std::istringstream is(input);
    int ret;
    is >> ret;
    return ret;
}

double Utils::toDouble(const std::string &input) {
    std::istringstream is(input);
    double ret;
    is >> ret;
    return ret;
}

#include <comdef.h>
std::string Utils::toString(std::wstring wstr) {
    std::string result;
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    if ( len <= 0 )return result;
    char* buffer = new char[len + 1];
    if (buffer == NULL )return result;
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    result.append(buffer);
    delete[] buffer;
    return result;
}
std::wstring Utils::toWstring(std::string str) {
    std::wstring result;
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    if ( len < 0 )return result;
    wchar_t* buffer = new wchar_t[len + 1];
    if ( buffer == NULL )return result;
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';
    result.append(buffer);
    delete[] buffer;
    return result;
}

bool Utils::isChineseChar(wchar_t ch) {
#pragma GCC diagnostic ignored "-Wtype-limits"
    unsigned char *pCh = (unsigned char*)&ch;
    return (((*pCh >= 0) && (*pCh <= 0xff)) && (*(pCh + 1) >= 0x4e && *(pCh + 1) <= 0x9f));
}

std::string Utils::toString(int input){
    std::ostringstream os; 
    os << input;
    return os.str();
}
