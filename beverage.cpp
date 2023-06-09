#include <iostream>
#include <sstream>
#include <iomanip>

#include "beverage.h"

Beverage::Beverage(std::string n, double p, int s, std::string m, std::string b, std::string f): Goods(n, p, s, m, b), flavor(f) {}

Beverage::Beverage(std::string serialized_string): Goods("uninitialized", -1, -1, "uninitialized", "uninitialized") {
    this->parse(serialized_string);
}

std::wstring Beverage::toString(){
    std::ostringstream os;
    os << " - 商品类型: " << "饮料" << std::endl;
    os << " - 商品名称: " << name << std::endl;
    os << " - 商品价格: " << std::fixed << std::setprecision(2) << price << std::endl;
    os << " - 商品库存量: " << stock << std::endl;
    os << " - 商品生产厂家: " << manufacturer << std::endl;
    os << " - 商品品牌: " << brand << std::endl;
    os << " - 饮料口味: " << flavor << std::endl;
    
    std::string res=os.str();
    return Utils::toWstring(res);
}
void Beverage::display() { //重载虚函数
    std::cout << Utils::toString(this -> toString());
}
std::string Beverage::getFlavor() {
    return flavor;   //获取饮料口味
}
void Beverage::setFlavor(std::string f) {
    flavor = f;   //设置饮料口味
}
std::string Beverage::toSerializedString() {
    std::ostringstream os;
    os << "Beverage" << std::endl;
    os << Base64::encode(name) << std::endl;
    os << Base64::encode(price) << std::endl;
    os << Base64::encode(stock) << std::endl;
    os << Base64::encode(manufacturer) << std::endl;
    os << Base64::encode(brand) << std::endl;
    os << Base64::encode(flavor) << std::endl;
    return Base64::encode(os.str());
}
void Beverage::parse(const std::string &data) {
    std::string one_step_decoded_string=Base64::decode(data);
    std::istringstream is(one_step_decoded_string);
    std::string category; is >> category;
    assert(category == "Beverage");
    // 仅能解析饮料品类
    std::string sname, sprice, sstock, smanufacturer, sbrand, sflavor;
    assert(is >> sname >> sprice >> sstock >> smanufacturer >> sbrand >> sflavor);
    // 若返回值非真则不合法
    name = Base64::decode(sname);
    price = Utils::toDouble(Base64::decode(sprice));
    stock = Utils::toInt(Base64::decode(sstock));
    manufacturer = Base64::decode(smanufacturer);
    brand = Base64::decode(sbrand);
    flavor = Base64::decode(sflavor);
}
