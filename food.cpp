#include "food.h"

#include <iostream>
#include <iomanip>

Food::Food(std::string n, double p, int s, std::string m, std::string b, std::string t): Goods(n, p, s, m, b), type(t) {} //构造函数

Food::Food(std::string serialized_string): Goods("uninitialized", -1, -1, "uninitialized", "uninitialized") {
    this->parse(serialized_string);
}

std::wstring Food::toString() { //重载虚函数
    std::ostringstream os;
    os << " - 商品类型: " << "食品" << std::endl;
    os << " - 商品名称: " << name << std::endl;
    os << " - 商品价格: " << std::fixed << std::setprecision(2) << price << std::endl;
    os << " - 商品库存量: " << stock << std::endl;
    os << " - 商品生产厂家: " << manufacturer << std::endl;
    os << " - 商品品牌: " << brand << std::endl;
    os << " - 食品类别: " << type << std::endl;

    std::string res = os.str();
    return Utils::toWstring(res);
}
void Food::display() { //重载虚函数
    std::cout << Utils::toString(this -> toString());
}
std::string Food::getType() {
    return type;   //获取食品类别
}
void Food::setType(std::string t) {
    type = t;   //设置食品类别
}
std::string Food::toSerializedString() {
    std::ostringstream os;
    os << "Food" << std::endl;
    os << Base64::encode(name) << std::endl;
    os << Base64::encode(price) << std::endl;
    os << Base64::encode(stock) << std::endl;
    os << Base64::encode(manufacturer) << std::endl;
    os << Base64::encode(brand) << std::endl;
    os << Base64::encode(type) << std::endl;
    return Base64::encode(os.str());
}
void Food::parse(const std::string &data) {
    std::string one_step_decoded_string = Base64::decode(data);
    std::istringstream is(one_step_decoded_string);
    std::string category;
    is >> category;
    assert(category == "Food");
    // 仅能解析食品品类
    std::string sname, sprice, sstock, smanufacturer, sbrand, stype;
    assert(is >> sname >> sprice >> sstock >> smanufacturer >> sbrand >> stype);
    // 若返回值非真则不合法
    name = Base64::decode(sname);
    price = Utils::toDouble(Base64::decode(sprice));
    stock = Utils::toInt(Base64::decode(sstock));
    manufacturer = Base64::decode(smanufacturer);
    brand = Base64::decode(sbrand);
    type = Base64::decode(stype);
}
