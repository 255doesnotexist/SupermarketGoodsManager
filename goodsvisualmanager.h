#ifndef GOODSVISUALMANAGER_H
#define GOODSVISUALMANAGER_H

#include "virtualbuffer.h"
#include "goodslist.h"
#include "consolebuffer.h"
#include <conio.h>

class GoodsVisualManager {
    private:
        VirtualBuffer *vb = nullptr;
        GoodsList *gl = nullptr;
        GoodsList::Node *cur = nullptr;
        int index;
    public:
        GoodsVisualManager(GoodsList *gl) : gl(gl), cur(gl -> getHead()), index(1) {
            vb = new VirtualBuffer(20, 100);
            // SetConsoleMode(ConsoleBuffer.GetStdInputHandle(), ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
        }
        void Render() {
            if (cur == nullptr) {
                return;
            }

            vb -> Clear();

            for (SHORT i = 0; i < 100; ++i) { // 上下两条边栏
                vb->WriteChar((COORD) {
                    i, 0
                }, CharType('='));
                vb->WriteChar((COORD) {
                    i, 20 - 3
                }, CharType('-')); // 操作符的分割线
                vb->WriteChar((COORD) {
                    i, 20 - 1
                }, CharType('='));
            }

            std::ostringstream pagePromptStream;
            pagePromptStream << "第 " << this -> index << " 项， 共 " << this -> gl -> length() << " 项";
            vb -> WriteString((COORD) {
                43, 0
            }, Utils::toWstring(pagePromptStream.str()), 0x0f);


            vb -> WriteString((COORD) {
                0, 3
            }, cur->data->toString(), 0x0f);

            vb -> WriteString((COORD) {
                0, 20 - 2
            }, L"    [←] 前一个商品    [→] 后一个商品    [E] 修改本商品    [D] 删除本商品    [Q] 退出管理界面", 0x0f);
        }
        void ManagerMain() {
            if (cur == nullptr) {
                std::cout << "没有商品！" << std::endl;
                return;
            }

            unsigned char ch;
            fflush(stdin);

            cur = gl -> getHead();
            index = 1;
            while (ch != 'Q' && ch != 'q') {
                // 如有机会 此处应当重构 
                
                this -> Render();
                vb -> WriteToConsole();

                while (!kbhit()) {
                    Sleep(1);
                    fflush(stdin);
                }

                ch = getch();

                if (ch == 0xE0) { // 方向键
                    ch = getch();
                    if (ch == 0x4B) { // 左
                        if (cur -> prev != nullptr) {
                            cur = cur -> prev;
                            --index;
                        } else {
                            vb -> WriteString((COORD) {
                                4, 20 - 6
                            }, L"前面没有别的商品了! ", 0xcf);
                            vb -> WriteToConsole();
                            Sleep(500);
                        }
                    } else if (ch == 0x4D) { // 右
                        if (cur -> next != nullptr) {
                            cur = cur->next;
                            ++index;
                        } else {
                            vb -> WriteString((COORD) {
                                4, 20 - 6
                            }, L"后面没有别的商品了! ", 0xcf);
                            vb -> WriteToConsole();
                            Sleep(500);
                        }
                    }
                } else { // 别的字符
                    if (ch == 'd' || ch == 'D') {
                        vb -> WriteString((COORD) {
                            4, 20 - 6
                        }, L"确定要删除本商品吗? [Y/N]  ", 0xcf);
                        vb -> WriteToConsole();

                        char ch = getch();
                        while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N') {
                            ch = getch();
                        }

                        if (ch == 'n' || ch == 'N') {
                            continue; // 如果不删则回到循环开始时
                        }

                        GoodsList::Node *need_to_delete = cur;
                        if (cur -> next != nullptr) {
                            cur = cur -> next;
                            index = index;
                        } else {
                            cur = cur -> prev;
                            index = index - 1;
                        }
                        gl -> deleteGoods(need_to_delete);
                    } else if (ch == 'e' || ch == 'E') {
                        vb -> WriteString((COORD) {
                            4, 20 - 6
                        }, L"请用鼠标左键点击你需要更改的商品信息! ", 0xcf);
                        vb -> WriteToConsole();

                        /*typedef struct _INPUT_RECORD {
                          WORD  EventType;
                          union {
                          KEY_EVENT_RECORD          KeyEvent;
                          MOUSE_EVENT_RECORD        MouseEvent;
                          WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
                          MENU_EVENT_RECORD         MenuEvent;
                          FOCUS_EVENT_RECORD        FocusEvent;
                          } Event;
                          } INPUT_RECORD;*/

                        // 以上是 Windows 控制台的输入事件定义（来自MSDN）

                        // 第3行 商品类型
                        // 第4行 商品名称
                        // 第5行 商品价格
                        // 第6行 商品库存量
                        // 第7行 商品生产厂家
                        // 第8行 商品品牌
                        // 第9行 商品特化信息

                        SHORT click_line = -1;

                        while (true) { // TODO: fix bugs
                            // GetNumberOfConsoleInputEvents(控制台句柄, 返回数据指针)可以获得控制台事件个数 但这里用不到
                            // 轮询上个函数可以实现体验上无阻塞地读取事件，但没必要
                            INPUT_RECORD rec;
                            DWORD rec_cnt; // 后面那个值其实也用不到因为我打算一个一个处理事件
                            bool flg = ReadConsoleInput(ConsoleBuffer.GetStdInputHandle(), &rec, 1, &rec_cnt);
                            if (!flg) { // 处理错误
                                DWORD errcode = GetLastError();
                                std::cerr << errcode << std::endl;
                            }

                            if (rec.EventType == MOUSE_EVENT) { // 处理鼠标事件
                                COORD mousePos = rec.Event.MouseEvent.dwMousePosition;
                                bool isClicked = rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED;
                                bool isMoved = rec.Event.MouseEvent.dwEventFlags & MOUSE_MOVED;

                                if (mousePos.Y >= 4 && mousePos.Y <= 9) {
                                    if (isMoved) {
                                        ConsoleBuffer.GotoXY(1, mousePos.Y);
                                        // 给用户选择的视觉反馈XD
                                    }
                                    if (isClicked) {
                                        click_line = mousePos.Y;
                                        break;
                                    }
                                }
                            }

                            if (rec.EventType == KEY_EVENT) {
                                if (rec.Event.KeyEvent.wVirtualKeyCode == 'Q') {
                                    click_line = -1;
                                    break;
                                }
                            }


                            Sleep(1);
                        }

                        // 第3行 商品类型 不允许更改
                        // 第4行 商品名称
                        // 第5行 商品价格
                        // 第6行 商品库存量
                        // 第7行 商品生产厂家
                        // 第8行 商品品牌
                        // 第9行 商品特化信息

                        for (SHORT X = 0; X < 100; ++X) vb -> WriteChar((COORD) {
                            X, click_line
                        }, CharType(' ', 0xf0)); // 印一行很炫酷的白条！
                        vb -> WriteString((COORD) {
                            0, click_line
                        }, L" - 新内容: ", 0xf0); // 然后在白条上印字！
                        vb -> WriteToConsole();
                        ConsoleBuffer.GotoXY(13, click_line);
                        ConsoleBuffer.SetColor(0xf0);

                        FlushConsoleInputBuffer(ConsoleBuffer.GetStdInputHandle());
                        // 因为前面用了鼠标事件所以似乎也必须清一下事件缓冲区
                        std::string content;
                        std::cin >> content;
                        /*char ch = getch();
                        while (ch != '\n' && ch != '\r') { // 不手动读取似乎会遇到一些bug
                            if (ch != '\b')content += ch;

                            if (content.size() > 0 && ch == '\b') {
                                std::cout << "\b \b";
                                content = content.substr(0, content.size() - 1);
                            } else {
                                std::cout << ch;
                            }
                            ch = getch();
                        }*/
                        ConsoleBuffer.SetColor(0x0f);

                        std::string cur_category = cur -> data -> getCategory();

                        switch (click_line) { // 这里是一些硬编码 有机会应该重构
                            case 4: // 改商品名称
                                cur -> data -> setName(content);
                                break;
                            case 5: // 改商品价格
                                cur -> data -> setPrice(Utils::toDouble(content));
                                break;
                            case 6: // 改商品库存量
                                cur -> data -> setStock(Utils::toDouble(content));
                                break;
                            case 7: // 改商品生产厂家
                                cur -> data -> setManufacturer(content);
                                break;
                            case 8: // 改商品品牌
                                cur -> data -> setBrand(content);
                                break;
                            case 9: // 改商品特化信息
                                if (cur_category == "Beverage") {
                                    ((Beverage*)cur -> data) -> setFlavor(content);
                                } else if (cur_category == "Cosmetics") {
                                    ((Cosmetics*)cur -> data) -> setFunction(content);
                                } else if (cur_category == "DailyNecessities") {
                                    ((DailyNecessities*)cur -> data) -> setMaterial(content);
                                } else if (cur_category == "Food") {
                                    ((Food*)cur -> data) -> setType(content);
                                }
                                break;
                            default:
                                vb -> WriteString((COORD) {
                                    4, 20 - 6
                                }, L"无法更改选中项，换个别的吧~", 0xcf);
                                vb -> WriteToConsole();
                                Sleep(500);
                                break;
                        }
                    }
                }
            }
        }
};

#endif
