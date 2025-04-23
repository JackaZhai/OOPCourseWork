#include "consumer.h"
#include "utils.h"
#include "fileio.h"

// 消费者菜单
void consumerMenu() {
    int choice;
    while (true) {
        cout << "***************************************************" << endl;
        cout << "                 消费者功能菜单                    " << endl;
        cout << "***************************************************" << endl;
        cout << "*        1.预定餐位        2.点菜                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*        3.查看小票        4.退出                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "***************************************************" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            reserveTable(); //调用预定函数 
            break;
        case 2:
            takeOrder();//
            break;
        case 3:
            viewReceipt(); //输入桌号查看小票 
            break;
        case 4:
            return; // 返回主菜单
            break;
        default:
            cout << "无效的选择，请重新输入！" << endl;
            continue;
        }
        break;
    }
}

// 为顾客点菜
void takeOrder() {
    int tableNumber;
    cout << "请输入要加菜的桌号：" << endl;
    cin >> tableNumber;
    // 显示该桌已点的菜品
    showOrderedDishes(tableNumber);
    // 显示菜品信息
    displayDishes();
    ofstream orderFile("orders.txt", ios::app);
    if (!orderFile.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    cout << "请输入要点的菜品信息（输入格式：菜品名称 菜品数量，输入 \"完成\" 结束）" << endl;
    string dishName;
    int quantity;
    while (true) {
        cin >> dishName;
        if (dishName == "完成") {
            exit(0); 
            break;
        }
        cin >> quantity;
        bool found = false;
        double price = 0.0;
        for (int i = 0; i < goodsCount; i++) {
            if (goods[i].name == dishName) {
                found = true;
                price = goods[i].price;
                break;
            }
        }
        if (!found) {
            cout << "菜品不存在，请重新输入！" << endl;
            continue;
        }
        orderFile << tableNumber << " " << dishName << " " << quantity << " 0 " << price << endl;
        cout << "点菜成功！" << endl;
    }
    orderFile.close();
}

// 预定餐位
void reserveTable() {
    // 先输出所有的餐桌信息
    viewTables();
    int number;
    int customerNum;
    string username;
    while (true) {
        cout << "请输入要预订的餐位编号：" << endl;
        cin >> number;
        bool k = false;
        for (int i = 0; i < tableCount; i++) {
            if (tables[i].number == number && tables[i].use == 0) {
                k = true;
                tables[i].use = 1; 
                cout << "请输入预定名" << endl;
                cin >> username;
                // 记录预定用户的用户名
                tables[i].userName = username; 
                // 让用户输入顾客人数
                cout << "请输入该桌的顾客人数：" << endl;
                cin >> customerNum;
                tables[i].customerCount = customerNum; 
                // 记录预定时间
                time_t t = time(0);
                char tmp[32] = {0};
                strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H:%M:%S", localtime(&t)); 
                tables[i].reservationTime = tmp; //本地时间 
                saveTables();  //保存 
                break;
            }
        }
        if (!k) {
            cout << "没有可用的该编号餐位，请重新选择！" << endl;
        } else {
            break;
        }
    }
    cout << "输入\"返回\"以返回" << endl;
    string mm, mmm = "返回";
    cin >> mm;
    if (mm == mmm) {
        manageTables(); 
    }
}

// 查看小票
void viewReceipt() {
    int tableNumber;
    cout << "请输入要查看小票的桌号：" << endl;
    cin >> tableNumber;
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        bool foundTable = false;
        string line;
        cout << "       菜品名称    数量    单价    价格    状态" << endl;
        while (getline(orderFile, line)) {
            istringstream iss(line);
            int storedTableNumber; 
            string dishName;
            int quantity;
            int dishStatus;
            double dishPrice;
            iss >> storedTableNumber >> dishName >> quantity >> dishStatus >> dishPrice;
            if (storedTableNumber == tableNumber) {
                foundTable = true;
                double totalPrice = dishPrice * quantity;  // 计算该菜品的总价
                cout << setw(12) << dishName << setw(12) << quantity << setw(12) << dishPrice << setw(12) << totalPrice << setw(12) ;
                if(dishStatus==0) cout<< "已点菜"<< endl;
                else if(dishStatus==1) cout<< "已完成"<< endl;
                else if(dishStatus==3) cout<< "已上菜"<< endl;
            }
        }
        orderFile.close();
        if (!foundTable) {
            cout << "该桌号尚未点餐。" << endl;
        }
    } else {
        cout << "无法打开订单文件" << endl;
    }
    cout << "输入\"返回\"以返回" << endl;
    string back;
    cin >> back;
    if (back == "返回") {
        consumerMenu();
    } else {
        viewReceipt();
    }
}

// 管理餐位信息
void manageTables() {
    int choice;
    while (true) {
        cout << "***************************************************" << endl;
        cout << "                 请选择要进行的操作                " << endl;
        cout << "***************************************************" << endl;
        cout << "*        1.预订餐位        2.查看餐位信息         *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*        3.返回主菜单        4.退出               *" << endl;
        cout << "*                                                 *" << endl;
        cout << "***************************************************" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            reserveTable();
            break;
        case 2:
            viewTables();
            break;
        case 3:
            return; // 返回主菜单
            break;
        case 4:
            exit(0); 
            break;
        default:
            cout << "无效的选择，请重新输入！" << endl;
            continue;
        }
        system("pause"); 
        return; // 返回主菜单
    }
}
