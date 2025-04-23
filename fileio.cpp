#include "fileio.h"

// 加载用户数据
void loadUsers() {
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        User user;
        while (userFile >> user.usname >> user.password >> user.role) {
            id[userCount] = user;
            userCount++;
        }
        userFile.close();
    } else {
        cout << "无法打开用户文件" << endl;
    }
}

// 加载餐位数据到tables数组
void loadTables() {
    ifstream tableFile("tables.txt");
    if (tableFile.is_open()) {
        zuowei table;
        while (tableFile >> table.number >> table.seat >> table.use >> table.people>>table.reservationTime>>table.userName>>table.customerCount) {
            tables[tableCount] = table;
            tableCount++;
        }
        tableFile.close();
    } else {
        cout << "无法打开餐位文件" << endl;
    }
}

// 加载菜品数据到goods数组
void loadGoods() {
    ifstream goodsFile("goods.txt");
    if (goodsFile.is_open()) {
        Goods good;
        while (goodsFile >> good.id>>good.name >> good.category >> good.price) {
            goods[goodsCount] = good;
            goodsCount++;
        }
        goodsFile.close();
    } else {
        cout << "无法打开商品文件" << endl;
    }
}

// 加载小票概要信息
void loadSaleSummary() {
    ifstream summaryFile("sales_summary.txt");
    if (summaryFile.is_open()) {
        string line;
        while (getline(summaryFile, line)) {
            istringstream iss(line);
            SaleSummary record;
            if (iss >> record.danju >> record.allmoney) {
                if (saleSummaryCount < MAX_SALES) {
                    saleSummary[saleSummaryCount] = record;
                    saleSummaryCount++;
                } else {
                    cout << "销售概要数据存储已满，无法继续添加。" << endl;
                    break;
                }
            } else {
                cout << "读取销售概要数据时发生错误。" << endl;
                break;
            }
        }
        summaryFile.close();
    } else {
        cout << "无法打开销售概要文件。" << endl;
    }
}

// 加载小票详细信息
void loadSaleDetail() {
    ifstream detailFile("sales_detail.txt");
    if (detailFile.is_open()) {
        string line;
        while (getline(detailFile, line)) {
            istringstream iss(line);
            SaleDetail record;
            if (iss >> record.danju >> record.dishName >> record.dishPrice >> record.quantity) {
                if (saleDetailCount < MAX_SALES) {
                    saleDetail[saleDetailCount] = record;
                    saleDetailCount++;
                } else {
                    cout << "小票详细数据存储已满，无法继续添加。" << endl;
                    break;
                }
            } else {
                cout << "读取小票详细数据时发生错误。" << endl;
                break;
            }
        }
        detailFile.close();
    } else {
        cout << "无法打开小票详细文件。" << endl;
    }
}

// 保存商品信息到文件
void saveGoods() {
    ofstream goodsFile("goods.txt");
    if (goodsFile.is_open()) {
        for (int i = 0; i < goodsCount; i++) {
            goodsFile << goods[i].id << " " << goods[i].name << " " << goods[i].category << " " << goods[i].price << endl;
        }
        goodsFile.close();
    } else {
        cout << "无法打开商品文件" << endl;
    }
}

// 保存餐位信息到文件
void saveTables() {
    ofstream myfile("tables.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < tableCount; i++) { 
            myfile << tables[i].number << " " << tables[i].seat << " " << tables[i].use << " " << tables[i].people << " " << tables[i].reservationTime << " " << tables[i].userName << " " << tables[i].customerCount << endl;
        }
        myfile.close();
    } else {
        cout << "无法打开文件" << endl;
    }
}

// 保存用户信息到文件
void saveUsers() {
    ofstream userFile("users.txt");
    if (userFile.is_open()) {
        for (int i = 0; i < userCount; i++) {
            userFile << id[i].usname << " " << id[i].password << " " << id[i].role << endl;
        }
        userFile.close();
    } else {
        cout << "无法打开用户文件" << endl;
    }
}
