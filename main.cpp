#include <bits/stdc++.h>
#include "allclasses.h"
#include <conio.h>

using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::cin;
using std::map;

#include "main.h"


//主函数
int main() {
    ConsoleBuffer.SetColor(0x0f);
    return ConsoleMain();
}

void PrintSelectionInformation(GoodsList &gl, char highlight) {
    ConsoleBuffer.SetConsoleSize(43, 24);
    ConsoleBuffer.ClearStdOutput();
    ConsoleBuffer.SetColor(0x0f);
    cout << "========== 超市商品管理系统 ==========" << endl;
    ConsoleBuffer.SetColor(highlight == 'l' ? 0xf0 : 0x0f);
    cout << " - [l] 显示所有商品信息" << endl;
    ConsoleBuffer.SetColor(highlight == 'b' ? 0xf0 : 0x0f);
    cout << " - [b] 购买商品" << endl;
    ConsoleBuffer.SetColor(0x0f);
    cout << "============== 商品管理 ==============" << endl;
    ConsoleBuffer.SetColor(highlight == 'M' ? 0xf0 : 0x0f);
    cout << " - [M] 进入商品管理列表" << endl;
    ConsoleBuffer.SetColor(highlight == 'a' ? 0xf0 : 0x0f);
    cout << " - [a] 添加新的商品" << endl;
    ConsoleBuffer.SetColor(highlight == 'q' ? 0xf0 : 0x0f);
    cout << " - [q] 以品名为依据精确查询商品" << endl;
    ConsoleBuffer.SetColor(highlight == 'm' ? 0xf0 : 0x0f);
    cout << " - [m] 以品名为依据修改商品信息" << endl;
    ConsoleBuffer.SetColor(highlight == 'd' ? 0xf0 : 0x0f);
    cout << " - [d] 以品名为依据删除商品" << endl;
    ConsoleBuffer.SetColor(0x0f);
    cout << "============== 其他功能 ==============" << endl;
    ConsoleBuffer.SetColor(highlight == 's' ? 0xf0 : 0x0f);
    cout << " - [s] 商品统计功能" << endl;
    ConsoleBuffer.SetColor(highlight == 'S' ? 0xf0 : 0x0f);
    cout << " - [S] 将商品信息存入磁盘" << endl;
    ConsoleBuffer.SetColor(highlight == 'L' ? 0xf0 : 0x0f);
    cout << " - [L] 从磁盘中加载商品信息" << endl;
    ConsoleBuffer.SetColor(highlight == 'x' ? 0xf0 : 0x0f);
    cout << " - [x] 退出本程序" << endl;
    ConsoleBuffer.SetColor(0x0f);
    cout << "------------ 库存情况概览 ------------" << endl;
    const int tiles = 38;
    map<string, int> typeMap = gl.getTypeMap(), tile_per_type, color_per_type;
    int sum = 0, cur = 0;
    for (auto it = typeMap.begin(); it != typeMap.end(); ++it) {
        sum += it -> second;
    }
    color_per_type["食品"] = 0x22; // 前景和后景色相同看起来就像是色块
    color_per_type["化妆品"] = 0x44;
    color_per_type["日用品"] = 0x66;
    color_per_type["饮料"] = 0x88;
    if (sum > 0) {
        for (auto it = typeMap.begin(); it != typeMap.end(); ++it) {
            tile_per_type[it -> first] = ceil((double)(it -> second) / sum * tiles);
            cur += tile_per_type[it -> first];
        }
        while (cur != tiles) {
            for (auto it = typeMap.begin(); it != typeMap.end(); ++it) {
                if (cur > tiles && tile_per_type[it -> first] > 0) --cur, --tile_per_type[it -> first];
                if (cur < tiles) ++cur, ++tile_per_type[it -> first];
            }
        }
        for (auto it = typeMap.begin(); it != typeMap.end(); ++it) {
            for (int k = 1; k <= tile_per_type[it->first]; ++k) {
                ConsoleBuffer.SetColor(color_per_type[it->first]);
                cout << "H" << flush;
            }
        }
        cout << endl;
        for (auto it = typeMap.begin(); it != typeMap.end(); ++it) {
            ConsoleBuffer.SetColor(color_per_type[it -> first] & 0x0F);
            // 与 0x0f 做 and 运算可以去掉前景色 小聪明
            cout << " ◆ " << flush;
            ConsoleBuffer.SetColor(0x0f);
            cout << it -> first << flush;
        }
        ConsoleBuffer.SetColor(0x0f);
    } else {
        cout << " ! 库存为空，添加些库存再来看看吧~";
    }

    cout << endl;
    cout << "======================================" << endl;
    cout << " * 请输入操作选项：[ ]\b\b" << flush;
    // 两个\b\b刚好使光标落在框内 免去gotoxy硬坐标
}

int ConsoleMain() {
    GoodsList list;
    list.readFromFile();

    char operations[] = "-lbMaqmdsSLx";
    int index = 1;

    while (true) {
        PrintSelectionInformation(list, operations[index]);

        char now_ch = ' ';
        char ch = now_ch;
        bool lazy_clear = 0;

        while (true) { // 都是些保证光标在框内且为有效字符的判断
            if (!lazy_clear) PrintSelectionInformation(list, operations[index]);
            else lazy_clear = 0;
            if ((unsigned char)now_ch == 0xE0) { // 处理方向键
                now_ch = getch();
                if ((unsigned char)now_ch == 0x48) { // 方向上 方向下
                    if ((size_t)index - 1 >= 1) --index;
                    else lazy_clear = 1;
                } else if ((unsigned char)now_ch == 0x50) {
                    if ((size_t)index + 1 <= strlen(operations) - 1) ++index;
                    else lazy_clear = 1;
                }
                now_ch = operations[index];
                continue;
            }
            if (now_ch == '\n' || now_ch == '\r') {
                ch = operations[index];
                break;
            } else if (now_ch == '\b') {
                ch = ' ';
                cout << ch << "\b";
                fflush(stdin);
            }
            cout << ch << "\b";
            fflush(stdin);
            now_ch = getch();
            if (isalpha(now_ch)) {
                for (size_t k = 0, ls = strlen(operations); k < ls; ++k) {
                    if (now_ch == operations[k]) {
                        index = k;
                        break;
                    }
                }
                ch = now_ch;
            }
        }



        ConsoleBuffer.ClearStdOutput();
        cout << "======================================" << endl;

        switch (ch) {
            case 'l': {
                list.displayAllGoods();
                cout << " - 全部商品信息显示完毕，按下回车键返回主菜单。" << endl;
                while (getch() != '\r');
                break;
            }
            case 'b': {
                string stringType[5] = {"", "Food", "Cosmetics", "DailyNecessities", "Beverage"};
                cout << " + 请选择要购买的商品类型：" << endl;
                cout << " - [1] 食品" << endl;
                cout << " - [2] 化妆品" << endl;
                cout << " - [3] 日用品" << endl;
                cout << " - [4] 饮料" << endl;
                cout << " : ";
                int type;
                cin >> type;
                cout << " * 请输入商品名称：" << endl;
                string name;
                cin >> name;

                GoodsList::Node* item = list.searchGoodsByName(name);
                while (item != nullptr && item -> data -> getCategory() != stringType[type]) {
                    list.searchGoodsByName(name, item -> next); // 如果搜到的商品与输入类型不匹配，则从该处链表节点开始继续向后查找
                }

                if (item != nullptr) {
                    item -> data -> display();
                } else {
                    cout << " ! 由于未查询到库存商品信息，即将退出购买流程。" << endl;
                    fflush(stdin);
                    cout << " - 购买流程结束，按下回车键返回主菜单。" << endl;
                    while (getch() != '\r');
                    break;
                }

                int order_cnt, stock = item -> data -> getStock();
                cout << " * 请输入想购买的商品数量：" << endl;
                cin >> order_cnt;

                if (order_cnt <= stock && order_cnt > 0) {
                    item -> data -> setStock(stock - order_cnt);
                    cout << " - 购买成功，现存该商品信息如下：" << endl;
                    item -> data -> display();
                } else {
                    cout << " ! 购买数量大于库存数量或不合法！" << endl;
                }

                fflush(stdin);
                cout << " - 购买流程结束，按下回车键返回主菜单。" << endl;
                while (getch() != '\r');

                break;
            }
            case 'a': {
                cout << " * 请输入商品名称：" << endl;
                string name;
                cin >> name;
                cout << " * 请输入商品价格：" << endl;
                double price;
                cin >> price;
                cout << " * 请输入商品库存量：" << endl;
                int stock;
                cin >> stock;
                cout << " * 请输入商品生产厂家：" << endl;
                string manufacturer;
                cin >> manufacturer;
                cout << " * 请输入商品品牌：" << endl;
                string brand;
                cin >> brand;
                cout << "======================================" << endl;
                cout << " + 请选择商品类型：" << endl;
                cout << " - [1] 食品" << endl;
                cout << " - [2] 化妆品" << endl;
                cout << " - [3] 日用品" << endl;
                cout << " - [4] 饮料" << endl;
                cout << " : ";
                int type;
                cin >> type;
                switch (type) {
                    case 1: {
                        cout << "* 请输入食品类型：" << endl;
                        string t;
                        cin >> t;
                        list.insertGoodsAtEnd(new Food(name, price, stock, manufacturer, brand, t));
                        break;
                    }
                    case 2: {
                        cout << "* 请输入化妆品功能：" << endl;
                        string f;
                        cin >> f;
                        list.insertGoodsAtEnd(new Cosmetics(name, price, stock, manufacturer, brand, f));
                        break;
                    }
                    case 3: {
                        cout << "* 请输入日用品材质：" << endl;
                        string m;
                        cin >> m;
                        list.insertGoodsAtEnd(new DailyNecessities(name, price, stock, manufacturer, brand, m));
                        break;
                    }
                    case 4: {
                        cout << "* 请输入饮料口味：" << endl;
                        string f;
                        cin >> f;
                        list.insertGoodsAtEnd(new Beverage(name, price, stock, manufacturer, brand, f));
                        break;
                    }
                    default: {
                        cout << "! 输入有误！" << endl;
                        break;
                    }
                }

                cout << " - 录入流程结束，按下回车键返回主菜单。" << endl;
                while (getch() != '\r');
                break;
            }
            case 'd': {
                string stringType[5] = {"", "Food", "Cosmetics", "DailyNecessities", "Beverage"};
                cout << " + 请选择商品类型：" << endl;
                cout << " - [1] 食品" << endl;
                cout << " - [2] 化妆品" << endl;
                cout << " - [3] 日用品" << endl;
                cout << " - [4] 饮料" << endl;
                cout << " : ";
                int type;
                cin >> type;

                cout << "请输入商品名称：" << endl;
                string name;
                cin >> name;
                list.searchAndDeleteGoods(name, stringType[type]);

                cout << " - 删除商品流程结束，按下回车键返回主菜单。" << endl;
                while (getch() != '\r');
                break;
            }

            case 'm': {
                cout << "请输入商品名称：" << endl;
                string name;
                cin >> name;
                list.modifyGoods(name);

                cout << " - 修改商品流程结束，按下回车键返回主菜单。" << endl;
                while (getch() != '\r');
                break;
            }
            case 'q': {
                string stringType[5] = {"", "Food", "Cosmetics", "DailyNecessities", "Beverage"};
                cout << " + 请选择查找方式：" << endl;
                cout << " - [1] 以品名为依据" << endl;
                cout << " - [2] 以制造商为依据" << endl;
                cout << " - [3] 以商品类型为依据" << endl;
                cout << " : ";
                int type;
                cin >> type;

                GoodsList::Node* item = nullptr;

                switch (type) {
                    case 1: {
                        cout << "请输入商品名称：" << endl;
                        string name;
                        cin >> name;
                        item = list.searchGoodsByName(name);

                        if (item != nullptr) {
                            item -> data -> display();
                        } else {
                            cout << " ! 管理系统中没有商品 \"" << name << "\" 的信息！" << endl;
                        }
                        break;
                    }
                    case 2:{
                        cout << "请输入商品制造商名：" << endl;
                        string name;
                        cin >> name;
                        item = list.searchGoodsByManufacturer(name);
                        
                        if (item != nullptr) {
                            item -> data -> display();
                        } else {
                            cout << " ! 管理系统中没有商品制造商是 \"" << name << "\" 的商品信息！" << endl;
                        }
                        break;
                    }
                    case 3:{
                        cout << " + 请选择商品类型：" << endl;
                        cout << " - [1] 食品" << endl;
                        cout << " - [2] 化妆品" << endl;
                        cout << " - [3] 日用品" << endl;
                        cout << " - [4] 饮料" << endl;
                        cout << " : ";
                        int type;
                        cin >> type;
                        item = list.searchGoodsByCategory(stringType[type]);
                        
                        if (item != nullptr) {
                            item -> data -> display();
                        } else {
                            cout << " ! 管理系统中没有商品类型是 \"" << stringType[type] << "\" 的商品信息！" << endl;
                        }
                        break;
                    }
                    default:
                        cout << " ! 选择有误，即将退出本过程。" << endl;
                        break;
                }

                cout << " - 精确查询商品流程结束，按下回车键返回主菜单。" << endl;
                while (getch() != '\r');
                break;
            }
            case 's': {
                cout << "- 请选择统计功能：" << endl;
                cout << "- [1] 按商品品牌统计" << endl;
                cout << "- [2] 按商品类型统计" << endl;
                char choice = getch();
                while (!isdigit(choice)) choice = getch();

                cout << "======================================" << endl;
                switch (choice) {
                    case '1': {
                        map<string, int> brandMap = list.getBrandMap();

                        double stock_sum = 0.0;

                        for (auto it = brandMap.begin(); it != brandMap.end(); ++it) {
                            cout << " - 品牌：" << it -> first << "（入库商品数：" << it -> second << "）" << endl;
                            stock_sum += it -> second;
                        }

                        cout << " + 总商品库存量：" << stock_sum << endl;

                        break;
                    }
                    case '2': {
                        map<string, int> typeMap = list.getTypeMap();

                        double stock_sum = 0.0;

                        for (auto it = typeMap.begin(); it != typeMap.end(); ++it) {
                            cout << " - 类型：" << it -> first << "（入库商品数：" << it -> second << "）" << endl;
                            stock_sum += it -> second;
                        }

                        cout << " + 总商品库存量：" << stock_sum << endl;

                        break;
                    }
                    default: {
                        cout << "输入有误！" << endl;
                        break;
                    }
                }
                cout << " - 统计结束，按下回车键回到主菜单。" << endl;
                fflush(stdin);
                while (getch() != '\r');
                break;
            }
            case 'S': {
                list.saveToFile();
                cout << " - 存盘成功，按下回车键回到主菜单。" << endl;
                fflush(stdin);
                while (getch() != '\r');
                break;
            }
            case 'L': {
                list.readFromFile();
                cout << " - 读取数据成功，按下回车键回到主菜单。" << endl;
                fflush(stdin);
                while (getch() != '\r');
                break;
            }
            case 'x': {
                list.saveToFile();
                cout << " - 自动存盘成功，感谢您使用本系统。再见。" << endl;
                exit(0);
            }
            case 'M': {
                if (list.length() <= 0) {
                    cout << " ! 商品列表空空如也，添加几个商品再来吧~" << endl;
                    fflush(stdin);
                    while (getch() != '\r');
                }
                GoodsVisualManager gvm(&list);
                gvm.ManagerMain();
                break;
            }
            default: {
                cout << "! 不支持此操作！按下回车键回到主菜单。" << endl;
                fflush(stdin);
                while (getch() != '\r');
                break;
            }
        }
    }
}
