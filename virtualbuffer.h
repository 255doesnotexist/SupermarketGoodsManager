#ifndef VIRTUALBUFFER_H
#define VIRTUALBUFFER_H

#include "chartype.h"
#include <string>

// 虚拟缓冲“画布”

class VirtualBuffer {
    private:
        int lines, columns;
        CharType **buffer, **last_buffer;
    public:
        VirtualBuffer(int lines, int columns): lines(lines), columns(columns) {
            buffer = new CharType*[lines];
            last_buffer = new CharType*[lines];
            for (int i = 0; i < lines; ++i) {
                buffer[i] = new CharType[columns + 1];
                last_buffer[i] = new CharType[columns + 1];
                buffer[i][columns] = last_buffer[i][columns] = '\0';
            }
        }
        virtual ~VirtualBuffer() {
            for (int i = 0; i < lines; ++i) {
                delete[] buffer[i];
                delete[] last_buffer[i];
            }
            delete[] buffer;
            delete[] last_buffer;
        }
        void Clear() {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    buffer[i][j] = CharType(' ', 0x0f);
                    // last_buffer[i][j] = CharType('\0', 0x0f); // 强制全屏更新
                }
            }
        }
        void WriteChar(COORD pos, CharType ch);
        void WriteString(COORD pos, const std::wstring &str, WORD attribute);
        void InitializeConsole();
        void WriteToConsole();
};

#endif
