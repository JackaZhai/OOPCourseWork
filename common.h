#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <locale>

using namespace std;

// 常量定义
#define MAX_GOODS 1000
#define MAX_TABLES 100
#define MAX_SALES 100
#define MAX_USERS 100
#define MAX_DISHES 1000

// 菜品结构体
struct Goods {
    int id;
    string name;
    string category;
    double price;
};

// 餐位结构体
struct zuowei {
    int number;
    string seat;
    int use;
    int people;
    string reservationTime;
    string userName;
    int customerCount;
};

// 用户结构体
struct User {
    string usname;
    string password;
    string role;
};

// 销售记录结构体
struct SaleSummary {
    int danju;
    double allmoney;
};

// 加载小票详细数据
struct SaleDetail {
    int danju;
    string dishName;
    double dishPrice;
    int quantity;
};

// 销售记录结构体
struct Sale {
    int salenumber[100];
    int goodsid[100];
    char salename[100][50];
    double saledanjia[100];
    double allmoney;
    int danju;
    int salenumberCount;
    int goodsidCount;
    int salenameCount;
    int saledanjiaCount;
};

// 点餐结构体
struct Dish {
    string dishName;
    string dishCategory;
    double dishPrice;
    int dishStatus; // 0: 未准备, 1: 准备中, 2: 已完成
    int quantity;
};

// 全局变量声明
extern Goods goods[MAX_GOODS];
extern int goodsCount;
extern zuowei tables[MAX_TABLES];
extern int tableCount;
extern SaleSummary saleSummary[MAX_SALES];
extern int saleSummaryCount;
extern SaleDetail saleDetail[MAX_SALES];
extern int saleDetailCount;
extern User id[MAX_USERS];
extern int userCount;
extern Sale sale[MAX_SALES];
extern int saleCount;
extern Dish dishes[MAX_DISHES];
extern int dishCount;
extern int pass;

#endif // COMMON_H
