#include <iostream>
#include <iomanip>

#include "utils.h"
#include "cosmetics.h"

Cosmetics::Cosmetics(std::string n, double p, int s, std::string m, std::string b, std::string f): Goods(n, p, s, m, b), function(f) {} //构造函数

Cosmetics::Cosmetics(std::string serialized_string): Goods("uninitialized", -1, -1, "uninitialized", "uninitialized") {
    this->parse(serialized_string);
}

std::wstring Cosmetics::toString(){
    std::ostringstream os;
    os << " - 商品类型: " << "化妆品" << std::endl;
    os << " - 商品名称: " << name << std::endl;
    os << " - 商品价格: " << std::fixed << std::setprecision(2) << price << std::endl;
    os << " - 商品库存量: " << stock << std::endl;
    os << " - 商品生产厂家: " << manufacturer << std::endl;
    os << " - 商品品牌: " << brand << std::endl;
    os << " - 化妆品功能: " << function << std::endl;
    
    std::string res=os.str();
    return Utils::toWstring(res);
}
void Cosmetics::display() { //重载虚函数
    std::cout << Utils::toString(this -> toString());
}
std::string Cosmetics::getFunction() {
    return function;   //获取化妆品功能
}
void Cosmetics::setFunction(std::string f) {
    function = f;   //设置化妆品功能
}
std::string Cosmetics::toSerializedString(){
    std::ostringstream os;
    os<<"Cosmetics"<<std::endl;
    os<<Base64::encode(name)<<std::endl;
    os<<Base64::encode(price)<<std::endl;
    os<<Base64::encode(stock)<<std::endl;
    os<<Base64::encode(manufacturer)<<std::endl;
    os<<Base64::encode(brand)<<std::endl;
    os<<Base64::encode(function)<<std::endl;
    return Base64::encode(os.str());
}
void Cosmetics::parse(const std::string &data){
    std::string one_step_decoded_string=Base64::decode(data);
    std::istringstream is(one_step_decoded_string);
    std::string category; is >> category;
    assert(category=="Cosmetics");
    // 仅能解析化妆品品类
    std::string sname,sprice,sstock,smanufacturer,sbrand,sfunction;
    assert(is>>sname>>sprice>>sstock>>smanufacturer>>sbrand>>sfunction);
    // 若返回值非真则不合法
    name=Base64::decode(sname);
    price=Utils::toDouble(Base64::decode(sprice));
    stock=Utils::toInt(Base64::decode(sstock));
    manufacturer=Base64::decode(smanufacturer);
    brand=Base64::decode(sbrand);
    function=Base64::decode(sfunction);
}
