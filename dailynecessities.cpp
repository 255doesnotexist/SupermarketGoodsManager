#include <iostream>
#include <iomanip>

#include "utils.h"
#include "dailynecessities.h"

DailyNecessities::DailyNecessities(std::string n, double p, int s, std::string m, std::string b, std::string ma): Goods(n, p, s, m, b), material(ma) {} //构造函数

DailyNecessities::DailyNecessities(std::string serialized_string): Goods("uninitialized", -1, -1, "uninitialized", "uninitialized") {
    this->parse(serialized_string);
}

std::wstring DailyNecessities::toString() { //重载虚函数
    std::ostringstream os;
    os << " - 商品类型: " << "日用品" << std::endl;
    os << " - 商品名称: " << name << std::endl;
    os << " - 商品价格: " << std::fixed << std::setprecision(2) << price << std::endl;
    os << " - 商品库存量: " << stock << std::endl;
    os << " - 商品生产厂家: " << manufacturer << std::endl;
    os << " - 商品品牌: " << brand << std::endl;
    os << " - 日用品材质: " << material << std::endl;
    
    std::string res=os.str();
    return Utils::toWstring(res);
}
void DailyNecessities::display() { //重载虚函数
    std::cout << Utils::toString(this -> toString());
}
std::string DailyNecessities::getMaterial() {
    return material;   //获取日用品材质
}
void DailyNecessities::setMaterial(std::string ma) {
    material = ma;   //设置日用品材质
}
std::string DailyNecessities::toSerializedString(){
    std::ostringstream os;
    os<<"DailyNecessities"<<std::endl;
    os<<Base64::encode(name)<<std::endl;
    os<<Base64::encode(price)<<std::endl;
    os<<Base64::encode(stock)<<std::endl;
    os<<Base64::encode(manufacturer)<<std::endl;
    os<<Base64::encode(brand)<<std::endl;
    os<<Base64::encode(material)<<std::endl;
    return Base64::encode(os.str());
}
void DailyNecessities::parse(const std::string &data){
    std::string one_step_decoded_string=Base64::decode(data);
    std::istringstream is(one_step_decoded_string);
    std::string category; is >> category;
    assert(category=="DailyNecessities");
    // 仅能解析饮料品类
    std::string sname,sprice,sstock,smanufacturer,sbrand,smaterial;
    assert(is>>sname>>sprice>>sstock>>smanufacturer>>sbrand>>smaterial);
    // 若返回值非真则不合法
    name=Base64::decode(sname);
    price=Utils::toDouble(Base64::decode(sprice));
    stock=Utils::toInt(Base64::decode(sstock));
    manufacturer=Base64::decode(smanufacturer);
    brand=Base64::decode(sbrand);
    material=Base64::decode(smaterial);
}
