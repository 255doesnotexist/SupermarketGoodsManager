#include "goods.h"

Goods::Goods(std::string n, double p, int s, std::string m, std::string b): name(n), price(p), stock(s), manufacturer(m), brand(b) {} //构造函数

void Goods::display() {} //虚函数，用于在派生类中重载
std::string Goods::getName() {
    return name;   //获取商品名称
}
double Goods::getPrice() {
    return price;   //获取商品价格
}
int Goods::getStock() {
    return stock;   //获取商品库存量
}
std::string Goods::getManufacturer() {
    return manufacturer;   //获取商品生产厂家
}
std::string Goods::getBrand() {
    return brand;   //获取商品品牌
}
void Goods::setPrice(double p) {
    price = p;   //设置商品价格
}
void Goods::setStock(int s) {
    stock = s;   //设置商品库存量
}
void Goods::setManufacturer(std::string m) {
    manufacturer = m;   //设置商品生产厂家
}
void Goods::setName(std::string n) {
    name = n;   //设置商品生产厂家
}
void Goods::setBrand(std::string b) {
    brand = b;   //设置商品品牌
}
