#ifndef DAILYNECESSITIES_H
#define DAILYNECESSITIES_H

#include <iostream>
#include <string>

#include "goods.h"

//定义日用品类
class DailyNecessities: public Goods {
private:
    std::string material; //日用品材质
public:
    DailyNecessities(std::string n, double p, int s, std::string m, std::string b, std::string ma); //构造函数
    DailyNecessities(std::string serialized_string); 
    void display();
    std::string getMaterial();
    void setMaterial(std::string ma);
    std::wstring toString();
    std::string toSerializedString();
    void parse(const std::string &data);
    std::string getCategory(){return "DailyNecessities";}
};

#endif
