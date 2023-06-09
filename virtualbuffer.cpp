#include "consolebuffer.h"
#include "virtualbuffer.h"

#include <cassert>

void VirtualBuffer::InitializeConsole() {
    ConsoleBuffer.SetConsoleSize(this -> columns + 3, this -> lines + 3);
    ConsoleBuffer.OnFront = this; // 接管当前控制台缓冲区 设定为此虚拟缓冲区

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            last_buffer[i][j] = CharType('\0');
        } // 标记所有字符为待更新
    }
}

void VirtualBuffer::WriteToConsole() {
    if (ConsoleBuffer.OnFront != this) { // 如果在前台展示的并非此缓冲区，则重新初始化控制台 
        ConsoleBuffer.ClearStdOutput();
        this -> InitializeConsole();
    }

    ConsoleBuffer.HideConsoleCursor(); // 防止更新缓冲区时光标一直闪 先隐藏等会儿再恢复 
    
    const bool ALWAYS_UPDATE = false;
    for (int i = 0; i < lines; ++i) {
        bool chain_update = false; // 链式更新是被设计用于更新需要两格宽的中文字符的 
        for (int j = 0; j < columns; ++j) {
            if (last_buffer[i][j] != buffer[i][j] || chain_update || ALWAYS_UPDATE) {
                ConsoleBuffer.GotoXY(j, i);
                
                ConsoleBuffer.WriteChar(buffer[i][j]);
                last_buffer[i][j] = buffer[i][j];
                
                if(last_buffer[i][j] != buffer[i][j]){
                    chain_update = true;
                }else{
                    chain_update = false;
                }
            }
        } // 双缓冲，若字符与原本缓冲区中不同则更新
    }
    
    ConsoleBuffer.GotoXY(columns, lines);
    // 刷新完后光标统一放置在末尾 
    ConsoleBuffer.ShowConsoleCursor(); // 重新恢复光标显示 
}

// 往缓冲区写入字符，assert 确保写入合法 

void VirtualBuffer::WriteChar(COORD pos, CharType ch) {
    assert(pos.X >= 0);
    assert(pos.X < columns);
    assert(pos.Y >= 0);
    assert(pos.Y < lines);
    
    buffer[pos.Y][pos.X] = ch;
}

void VirtualBuffer::WriteString(COORD pos, const std::wstring &str, WORD attribute) {
    int j = pos.X;
    size_t it = 0;
    for (int i = pos.Y; it < str.size(); ++it, ++j, i += j / columns, j %= columns) {
        assert(j >= 0);
        assert(j < columns);
        assert(i >= 0);
        assert(i < lines);
        
        if(str[it] == '\n'){
            j = columns - 1; // 光标移至行末，continue后将自动换行
            continue;
        }
        
        buffer[i][j] = CharType(str[it], attribute);
        
        // 虽然unsigned char必然在0x00~0xff之间 但是我还是要查 而且不喜欢看到warning 遂关之 
        #pragma GCC diagnostic ignored "-Wtype-limits"
        unsigned char *pCh = (unsigned char*)&str[it];
        if((((*pCh >= 0) && (*pCh <= 0xff)) && (*(pCh + 1) >= 0x4e && *(pCh + 1) <= 0x9f))){
            ++j; buffer[i][j] = CharType('\0', attribute);// 中文字符标记空一格留给控制台渲染空间 
        }
        
    }
}
