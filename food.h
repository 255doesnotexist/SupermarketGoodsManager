#ifndef FOOD_H
#define FOOD_H

#include "goods.h"

//定义食品类
class Food: public Goods {
    private:
        std::string type; //食品类别
    public:
        Food(std::string n, double p, int s, std::string m, std::string b, std::string t); //构造函数
        Food(std::string serialized_string);
        void display();
        std::string getType();
        void setType(std::string t);
        std::wstring toString();
        std::string toSerializedString();
        void parse(const std::string &data);
        std::string getCategory(){return "Food";}
};

#endif
