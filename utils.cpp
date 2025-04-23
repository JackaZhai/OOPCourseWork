#include "utils.h"

// 显示日期
void riqi() {
    time_t t = time(0);
    char tmp[32];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    cout << tmp << endl;
}

// 显示菜品信息
void displayDishes() {
    cout << "*************************全部菜品信息如下*************************" << endl;
    cout << "      菜品名称       菜品类别      菜品价格" << endl;
    for (int i = 0; i < goodsCount; i++) {
        cout << setw(14) << goods[i].name << setw(13) << goods[i].category << setw(13) << goods[i].price << endl;
    }
    cout << "*******************************************************************" << endl;
}

// 输出所有的餐桌信息
void viewTables() {
    cout << "**************************************全部餐位信息如下**************************************" << endl;
    cout << "餐位编号    餐位位置    餐位状态    可容纳人数          预订时间        预订用户    顾客人数" << endl;
    for (int i = 0; i < tableCount; i++) {
        cout << setw(3) << tables[i].number << setw(16) << tables[i].seat << setw(11);
        if (tables[i].use == 0) {
            cout << "空闲";
        } else {
            cout << "已预订";
        }
        cout << setw(10) << tables[i].people << setw(26) << tables[i].reservationTime << setw(11) << tables[i].userName << setw(10) << tables[i].customerCount << endl;
    }
    cout << "********************************************************************************************" << endl;
}

// 显示指定桌号已点的菜品信息
void showOrderedDishes(int tableNumber) {
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        bool foundTable = false;
        string line;
        cout << "已点菜品如下：" << endl;
        cout << "菜品名称     数量    状态    单价" << endl;
        while (getline(orderFile, line)) {
            istringstream iss(line);
            int storedTableNumber;
            string storedDishName;
            int storedQuantity;
            int storedDishStatus;
            double storedDishPrice;
            iss >> storedTableNumber >> storedDishName >> storedQuantity >> storedDishStatus >> storedDishPrice;
            if (storedTableNumber == tableNumber) {
                foundTable = true;
                cout << setw(8) << storedDishName << "  " << setw(6) << storedQuantity << "  " << setw(5) << storedDishStatus << "  " << setw(7) << storedDishPrice << endl;
            }
        }
        orderFile.close();
        if (!foundTable) {
            cout << "该桌号尚未点餐。" << endl;
        }
    } else {
        cout << "无法打开文件" << endl;
    }
}

// 查找商品ID的辅助函数
int findGoodsIdByName(const string& dishName) {
    for (int i = 0; i < goodsCount; ++i) {
        if (goods[i].name == dishName) {
            return goods[i].id;
        }
    }
    return -1;
}
