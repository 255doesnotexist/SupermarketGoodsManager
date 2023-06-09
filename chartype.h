#ifndef CHARTYPE_H
#define CHARTYPE_H

#include <windows.h>

struct CharType {
    wchar_t WideChar;
    WORD Attribute;

    CharType(wchar_t WideChar = '\0', WORD Attribute = 0x0f): WideChar(WideChar), Attribute(Attribute) {}

    bool operator !=(const CharType& another) {
        return (WideChar != another.WideChar || Attribute != another.Attribute);
    }
};

#endif
