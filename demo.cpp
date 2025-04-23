#include <iostream>
#include <iomanip>
#include <string>
#include<cstring>
#include <ctime> //提供了时间和日期的处理功能。
using namespace std; 
#include <sstream>//可以将一个字符串分解为多个子串，方便解析输入 iss>> 
#include <cstdlib> //提供了一些通用的实用函数 exit(0)函数，可用于程序的异常终止
#include <fstream> //文件处理 
#include <limits> //
#include <locale>//中文不乱码


struct Goods;
struct zuowei;
struct User;
struct SaleSummary;
struct SaleDetail;

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
    string reservationTime; //预定时间 
    string userName; //新增用户名 
    int customerCount; // 新增顾客人数成员变量
};

// 用户结构体
struct User {
    string usname;
    string password;
    string role;
};

// 销售记录结构体
struct SaleSummary {
    int danju; // 单据号 
    double allmoney; // 总金额 
};

// 加载小票详细数据
struct SaleDetail {
    int danju; //单据号 
    string dishName; //商品名称 
    double dishPrice; //单价 
    int quantity;//数量 
};

// 销售记录结构体
struct Sale {
    int salenumber[100]; // 假设最多 100 个销售记录
    int goodsid[100];
    char salename[100][50]; // 假设名称长度不超过 50
    double saledanjia[100];
    double allmoney; //总金额 
    int danju; //单据号 
    int salenumberCount; // 用于记录实际的销售数量
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

class DataRead {
public:
    // 单例模式
    static DataRead& getInstance() {
        static DataRead instance;
        return instance;
    }

    // 加载用户数据
    bool loadUsers(User* users, int& userCount, int maxUsers) {
        std::ifstream userFile("users.txt");
        if (!userFile.is_open()) {
            std::cout << "无法打开用户文件" << std::endl;
            return false;
        }
        
        userCount = 0;
        User user;
        while (userFile >> user.usname >> user.password >> user.role) {
            if (userCount < maxUsers) {
                users[userCount] = user;
                userCount++;
            } else {
                std::cout << "用户数据存储已满，无法继续添加。" << std::endl;
                break;
            }
        }
        userFile.close();
        return true;
    }

    // 加载餐位数据
    bool loadTables(zuowei* tables, int& tableCount, int maxTables) {
        std::ifstream tableFile("tables.txt");
        if (!tableFile.is_open()) {
            std::cout << "无法打开餐位文件" << std::endl;
            return false;
        }
        
        tableCount = 0;
        zuowei table;
        while (tableFile >> table.number >> table.seat >> table.use >> table.people 
            >> table.reservationTime >> table.userName >> table.customerCount) {
            if (tableCount < maxTables) {
                tables[tableCount] = table;
                tableCount++;
            } else {
                std::cout << "餐位数据存储已满，无法继续添加。" << std::endl;
                break;
            }
        }
        tableFile.close();
        return true;
    }

    // 加载商品数据
    bool loadGoods(Goods* goods, int& goodsCount, int maxGoods) {
        std::ifstream goodsFile("goods.txt");
        if (!goodsFile.is_open()) {
            std::cout << "无法打开商品文件" << std::endl;
            return false;
        }
        
        goodsCount = 0;
        Goods good;
        while (goodsFile >> good.id >> good.name >> good.category >> good.price) {
            if (goodsCount < maxGoods) {
                goods[goodsCount] = good;
                goodsCount++;
            } else {
                std::cout << "商品数据存储已满，无法继续添加。" << std::endl;
                break;
            }
        }
        goodsFile.close();
        return true;
    }

    // 加载销售概要信息
    bool loadSaleSummary(SaleSummary* saleSummary, int& saleSummaryCount, int maxSales) {
        std::ifstream summaryFile("sales_summary.txt");
        if (!summaryFile.is_open()) {
            std::cout << "无法打开销售概要文件。" << std::endl;
            return false;
        }
        
        saleSummaryCount = 0;
        std::string line;
        while (std::getline(summaryFile, line)) {
            std::istringstream iss(line);
            SaleSummary record;
            if (iss >> record.danju >> record.allmoney) {
                if (saleSummaryCount < maxSales) {
                    saleSummary[saleSummaryCount] = record;
                    saleSummaryCount++;
                } else {
                    std::cout << "销售概要数据存储已满，无法继续添加。" << std::endl;
                    break;
                }
            } else {
                std::cout << "读取销售概要数据时发生错误。" << std::endl;
                break;
            }
        }
        summaryFile.close();
        return true;
    }

    // 加载销售详细信息
    bool loadSaleDetail(SaleDetail* saleDetail, int& saleDetailCount, int maxSales) {
        std::ifstream detailFile("sales_detail.txt");
        if (!detailFile.is_open()) {
            std::cout << "无法打开销售详细文件。" << std::endl;
            return false;
        }
        
        saleDetailCount = 0;
        std::string line;
        while (std::getline(detailFile, line)) {
            std::istringstream iss(line);
            SaleDetail record;
            if (iss >> record.danju >> record.dishName >> record.dishPrice >> record.quantity) {
                if (saleDetailCount < maxSales) {
                    saleDetail[saleDetailCount] = record;
                    saleDetailCount++;
                } else {
                    std::cout << "销售详细数据存储已满，无法继续添加。" << std::endl;
                    break;
                }
            } else {
                std::cout << "读取销售详细数据时发生错误。" << std::endl;
                break;
            }
        }
        detailFile.close();
        return true;
    }

    // 读取订单文件
    std::vector<std::string> readOrderFile() {
        std::vector<std::string> lines;
        std::ifstream orderFile("orders.txt");
        if (!orderFile.is_open()) {
            std::cout << "无法打开订单文件" << std::endl;
            return lines;
        }
        
        std::string line;
        while (std::getline(orderFile, line)) {
            lines.push_back(line);
        }
        orderFile.close();
        return lines;
    }

private:
    // 私有构造函数，防止外部创建实例
    DataRead() {}
    // 删除拷贝构造函数和赋值运算符
    DataRead(const DataRead&) = delete;
    DataRead& operator=(const DataRead&) = delete;
};

class DataWrite {
public:
    // 单例模式
    static DataWrite& getInstance() {
        static DataWrite instance;
        return instance;
    }

    // 保存用户信息
    bool saveUsers(const User* users, int userCount) {
        std::ofstream userFile("users.txt");
        if (!userFile.is_open()) {
            std::cout << "无法打开用户文件" << std::endl;
            return false;
        }
        
        for (int i = 0; i < userCount; i++) {
            userFile << users[i].usname << " " << users[i].password << " " << users[i].role << std::endl;
        }
        userFile.close();
        return true;
    }

    // 保存餐位信息
    bool saveTables(const zuowei* tables, int tableCount) {
        std::ofstream tableFile("tables.txt");
        if (!tableFile.is_open()) {
            std::cout << "无法打开餐位文件" << std::endl;
            return false;
        }
        
        for (int i = 0; i < tableCount; i++) {
            tableFile << tables[i].number << " " 
                    << tables[i].seat << " " 
                    << tables[i].use << " " 
                    << tables[i].people << " " 
                    << tables[i].reservationTime << " " 
                    << tables[i].userName << " " 
                    << tables[i].customerCount << std::endl;
        }
        tableFile.close();
        return true;
    }

    // 保存商品信息
    bool saveGoods(const Goods* goods, int goodsCount) {
        std::ofstream goodsFile("goods.txt");
        if (!goodsFile.is_open()) {
            std::cout << "无法打开商品文件" << std::endl;
            return false;
        }
        
        for (int i = 0; i < goodsCount; i++) {
            goodsFile << goods[i].id << " " 
                     << goods[i].name << " " 
                     << goods[i].category << " " 
                     << goods[i].price << std::endl;
        }
        goodsFile.close();
        return true;
    }

    // 保存销售概要信息
    bool saveSaleSummary(int danju, double totalAmount) {
        std::ofstream summaryFile("sales_summary.txt", std::ios::app);
        if (!summaryFile.is_open()) {
            std::cout << "无法打开销售概要文件" << std::endl;
            return false;
        }
        
        summaryFile << danju << " " << totalAmount << std::endl;
        summaryFile.close();
        return true;
    }

    // 保存销售详细信息
    bool saveSaleDetail(int danju, const std::string& dishName, double price, int quantity) {
        std::ofstream detailFile("sales_detail.txt", std::ios::app);
        if (!detailFile.is_open()) {
            std::cout << "无法打开销售详细文件" << std::endl;
            return false;
        }
        
        detailFile << danju << " " << dishName << " " << price << " " << quantity << std::endl;
        detailFile.close();
        return true;
    }

    // 保存订单信息
    bool saveOrder(int tableNumber, const std::string& dishName, int quantity, int status, double price) {
        std::ofstream orderFile("orders.txt", std::ios::app);
        if (!orderFile.is_open()) {
            std::cout << "无法打开订单文件" << std::endl;
            return false;
        }
        
        orderFile << tableNumber << " " << dishName << " " << quantity << " " << status << " " << price << std::endl;
        orderFile.close();
        return true;
    }

    // 更新订单文件
    bool updateOrderFile(const std::vector<std::string>& lines) {
        std::ofstream orderFile("orders.txt");
        if (!orderFile.is_open()) {
            std::cout << "无法打开订单文件" << std::endl;
            return false;
        }
        
        for (const auto& line : lines) {
            orderFile << line << std::endl;
        }
        orderFile.close();
        return true;
    }

private:
    // 私有构造函数，防止外部创建实例
    DataWrite() {}
    // 删除拷贝构造函数和赋值运算符
    DataWrite(const DataWrite&) = delete;
    DataWrite& operator=(const DataWrite&) = delete;
};

// // 读取数据示例
// void loadData() {
//     DataRead& dataReader = DataRead::getInstance();
    
//     // 加载用户数据
//     dataReader.loadUsers(id, userCount, MAX_USERS);
    
//     // 加载餐位数据
//     dataReader.loadTables(tables, tableCount, MAX_TABLES);
    
//     // 加载商品数据
//     dataReader.loadGoods(goods, goodsCount, MAX_GOODS);
    
//     // 加载销售概要和详细信息
//     dataReader.loadSaleSummary(saleSummary, saleSummaryCount, MAX_SALES);
//     dataReader.loadSaleDetail(saleDetail, saleDetailCount, MAX_SALES);
// }

// // 保存数据示例
// void saveData() {
//     DataWrite& dataWriter = DataWrite::getInstance();
    
//     // 保存用户数据
//     dataWriter.saveUsers(id, userCount);
    
//     // 保存餐位数据
//     dataWriter.saveTables(tables, tableCount);
    
//     // 保存商品数据
//     dataWriter.saveGoods(goods, goodsCount);
    
//     // 添加销售记录
//     dataWriter.saveSaleSummary(danjuNumber, totalAmount);
//     dataWriter.saveSaleDetail(danjuNumber, "宫保鸡丁", 28.0, 2);
// }

// 11111