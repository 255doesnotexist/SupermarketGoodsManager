#ifndef COSMETICS_H
#define COSMETICS_H

#include <string>

#include "goods.h"

//定义化妆品类
class Cosmetics: public Goods {
private:
    std::string function; //化妆品功能
public:
    Cosmetics(std::string n, double p, int s, std::string m, std::string b, std::string f); //构造函数
    Cosmetics(std::string serialized_string); 
    void display();
    std::string getFunction();
    void setFunction(std::string f);
    std::wstring toString();
    std::string toSerializedString();
    void parse(const std::string &data);
    std::string getCategory(){return "Cosmetics";}
};

#endif
