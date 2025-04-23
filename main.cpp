#include <iostream>
#include <iomanip>
#include <string>
#include<cstring>
#include <ctime> //提供了时间和日期的处理功能。
#include <sstream>//可以将一个字符串分解为多个子串，方便解析输入 iss>> 
#include <cstdlib> //提供了一些通用的实用函数 exit(0)函数，可用于程序的异常终止
#include <fstream> //文件处理 
#include <limits> //
#include <locale>//中文不乱码
using namespace std;
 
void mainmenu();//主界面 
void showUserSelection(); // 显示用户选择界面
void registerUser();// 注册用户
void login();// 登录函数
void riqi();// 显示日期
void loadUsers();// 加载用户数据
void loadTables();// 加载餐位数据 
void loadGoods();// 加载商品数据
void loadSaleSummary();// 加载小票概要信息
void loadSaleDetail();// 加载小票详细信息
void displayDishes();// 显示可提供菜品信息
void viewTables();// 查看所有的餐位信息
void reserveTable();// 预定餐位
void manageTables();// 管理餐位信息 /预定 查看 返回上一级 退出 
void saveGoods(); //保存商品信息到文件
void saveTables();// 保存餐位信息到文件tables.txt
void saveUsers();// 保存用户信息到文件users.txt
void showOrderedDishes(int n); //展示输入n时 其对应桌号的菜品 
void takeOrder();//点餐函数
void consumerMenu();// 消费者菜单
void viewReceipt();// 查看小票  小票信息存储在receipt.txt文件中 格式为：菜品名称 数量 价格
void chefMenu();// 厨师菜单
void chefViewReceipt();// 厨师查看小票 桌号 待做菜品名称 数量
int findGoodsIdByName(const string& dishName);//找到商品 ID辅助函数
void changeDishStatusByChef();// 厨师改变菜品状态 改变dishes【i】中的状态 
void chefViewStatistics();// 厨师查看统计 已完成
void serverSubsytemMenu();//服务员菜单
void addDishes();//加菜函数 
void dishOut(); ///出菜函数 更改状态为 2
void view_yichucai();//查看已出菜
void view_weichucai();//查看未出菜 
void printTableReceipt(); //服务员打印小票 输入桌号 输出 名称 价格 数量 
void cashierMenu();// 收银员菜单
void cashierSettlement();// 收银员结算收费  改变状态为3
void cashierStatistics();// 收银员统计
void cashierViewStatistics();// 收银员查看统计
void manageMenu();// 管理员菜单 
void addUserInformation(); //添加用户信息 用户名 密码 角色 
void changeUserInformation(); // 修改用户信息
void viewUserInformation();// 查看所有用户信息（老板和管理查看 
void addGoodsMenu();//添加菜品信息
void changeGoods();//修改菜品信息
void bossMenu();// 老板菜单
void shouru(); //查看总收入

void deleteGoods();//删除菜品信息
void lookall(); //已完成和未完成数量 和金额
void bossSearchByDanju();  //通过单据号查找对应点的菜品

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



#define MAX_GOODS 1000  // 假设最大商品数量为 1000
#define MAX_TABLES 100  // 假设最大餐位数量为 100
#define MAX_SALES 100  // 假设最大销售记录数量为 100
#define MAX_USERS 100  // 假设最大用户数量为 100
#define MAX_DISHES 1000 // 假设最大菜品数量为 1000

Goods goods[MAX_GOODS]; //goods结构体数组  用于存储能够提供的菜品 
int goodsCount = 0; //数量  
zuowei tables[MAX_TABLES]; 
int tableCount = 0;
SaleSummary saleSummary[MAX_SALES];
int saleSummaryCount = 0;
SaleDetail saleDetail[MAX_SALES];
int saleDetailCount = 0;
User id[MAX_USERS];
int userCount = 0;
Sale sale[MAX_SALES];
int saleCount = 0;
Dish dishes[MAX_DISHES]; // 名字 种类 价格 状态 数量  
int dishCount = 0;//
int pass = 0;

//主界面 
void mainmenu() {
    system("cls");  //清屏
    cout << "***************************************************" << endl;
    cout << "                 请选择要进行的操作                " << endl;
    cout << "***************************************************" << endl;
    cout << "*        1.消费者子系统     2.厨师子系统          *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*        3.服务员子系统     4.收银员子系统        *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*        5.管理员子系统     6.餐厅老板子系统      *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*        0.退出系统                               *" << endl;
    cout << "***************************************************" << endl;
    cout<<"请选择："<<endl;
    char select;
    cin>>select;
    switch(select){
        case '1':
            //login(1);  // 先登录，再进入消费者子系统
            consumerMenu();  
            break;
        case '2':
          //  login(2);  // 先登录，再进入厨师子系统
            chefMenu();  
            break;
        case '3':
        //	login(3);
       		serverSubsytemMenu();//服务员子系统 
        	break;
        case '4':
          //  login(4);  // 先登录，再进入收银员子系统
            cashierMenu();  
            break;
        case '5': 
          //  login(5);  // 先登录，再进入管理员子系统
            manageMenu();  
            break;
        case '6':
          //  login(6);  // 先登录，再进入餐厅老板子系统
            bossMenu();  
            break;
        case '0':
            exit(0);   //正常退出系统 
            break;
        default:
            cout<<"错误输入！！！"<<endl;  //错误输入 
            cout<<"请重新输入："<<endl;
            cin>>select;  //重新输入
            mainmenu(); 
    }
}

// 显示用户选择界面
void showUserSelection() {
    cout << "***************************************************" << endl;
    cout << "               餐厅管理系统用户选择界面            " << endl;
    cout << "***************************************************" << endl;
    cout << "*        1. 登录        2. 注册用户               *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*        3. 退出系统                              *" << endl;
    cout << "*                                                 *" << endl;
    cout << "***************************************************" << endl;
    cout << "请输入您的选择：";
}

// 注册用户
void registerUser() {
    string username, password, role;
    cout << "请输入用户名: ";
    cin >> username;
    cout << "请输入密码: ";
    cin >> password;
    cout << "请输入角色: ";
    cin >> role;

    // 检查用户名是否已存在
    bool exists = false;
    for (int i = 0; i < userCount; i++) {
        if (id[i].usname == username) {
            exists = true;
            cout << "该用户名已存在，请重新输入！" << endl;
            registerUser(); // 重复循环注册用户 
        }
    }
    // 添加新用户
    id[userCount] = {username, password, role}; // 储存到文件之中 
    userCount++;
    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        userFile << username << " " << password << " " << role << endl;
        userFile.close();
        cout << "用户注册成功！" << endl;
    } else {
        cout << "无法打开用户文件" << endl;
    }
    showUserSelection(); // 此处登录应当有所修改（还没有改 
}

// 登录函数 
void login(int a) {
    string username, password;
    int attempts = 3; // 限制登录尝试次数
    while (attempts > 0) {
        cout << "请输入用户名: ";
        cin >> username;
        cout << "请输入密码: ";
        cin >> password;
        bool found = false;
        for (int i = 0; i < userCount; i++) {
            if (id[i].usname == username && id[i].password == password) {
                pass = i;
                // 检查用户角色是否匹配
                if ((a == 1 && id[i].role == "consumer") || 
                    (a == 2 && id[i].role == "chef") || 
                    (a == 3 && id[i].role == "server") ||
                    (a == 4 && id[i].role == "cashier") || 
                    (a == 5 && id[i].role == "admin") || 
                    (a == 6 && id[i].role == "boss")) {
                    found = true;
                    break;
                } else {
                    cout << "你没有权限进入该子系统，请重新登录。" << endl;
                    break;
                }
            }
        }

        if (found) {
            break;
        } else {
            attempts--;
            cout << "用户名或密码错误，还有 " << attempts << " 次尝试机会！" << endl;
        }
    }

    if (attempts == 0) {
        cout << "登录失败，退出程序。" << endl;
        exit(0);
    }
}

//显示日期//cout <<年月日 小时分钟秒 
void riqi() {
    time_t t = time(0);
    char tmp[32];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    cout << tmp << endl;
}

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

//加载菜品数据 到goods数组中 
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

//加载小票详细信息
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

//显示菜品信息 （已经提前加载至goods数组中 （Good结构体为基础 
void displayDishes() {
    cout << "*************************全部菜品信息如下*************************" << endl;
    cout << "      菜品名称       菜品类别      菜品价格" << endl;
    for (int i = 0; i < goodsCount; i++) {
        cout <<setw(14)<< goods[i].name << setw(13) << goods[i].category << setw(13) << goods[i].price << endl;
    }
    cout << "*******************************************************************" << endl;
}

// 输出所有的餐桌信息 （已经提前加载到tables数组中 
void viewTables() {
    cout << "**************************************全部餐位信息如下**************************************" << endl;
    cout << "餐位编号    餐位位置    餐位状态    可容纳人数          预订时间        预订用户    顾客人数" << endl;
    for (int i = 0; i < tableCount; i++) {
        cout <<setw(3)<< tables[i].number << setw(16) << tables[i].seat << setw(11);
        if (tables[i].use == 0) {
            cout << "空闲";
        } else {
            cout << "已预订";
        }
        cout << setw(10) << tables[i].people << setw(26)<< tables[i].reservationTime << setw(11) << tables[i].userName << setw(10) << tables[i].customerCount << endl;
    }
    cout << "********************************************************************************************" << endl;
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
    cout << "输入“返回”以返回" << endl;
    string mm, mmm = "返回";
    cin >> mm;
    if (mm == mmm) {
        manageTables(); 
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
            mainmenu();
            break;
        case 4:
        	exit(0); 
            break;
        default:
            cout << "无效的选择，请重新输入！" << endl;
            continue;
        }
        system("pause"); 
        mainmenu();
    }
}
////////数据保存 
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

// 保存用户信息到文件（用户名 密码 职位 
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
            int storedTableNumber; //编号 
            string storedDishName; //名称 
            int storedQuantity; //数量  
            int storedDishStatus; //状态 
            double storedDishPrice; // 单价
            iss >> storedTableNumber >> storedDishName >> storedQuantity >> storedDishStatus >> storedDishPrice;
            if (storedTableNumber == tableNumber) {
                foundTable = true;
                cout << setw(8)<<storedDishName << "  " <<setw(6)<< storedQuantity << "  " <<setw(5)<< storedDishStatus << "  " <<setw(7) <<storedDishPrice << endl;
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

// 为顾客点菜以及顾客点菜均使用这个 
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
    cout << "请输入要点的菜品信息（输入格式：菜品名称 菜品数量，输入 “完成” 结束）" << endl;
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

//////////消费者 
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
        	mainmenu(); //返回了主菜单 
            break;
        default:
            cout << "无效的选择，请重新输入！" << endl;
            continue;
        }
        break;
    }
}


///3.消费者·查看小票，根据输入的桌号输出订单信息
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
    cout << "输入“返回”以返回" << endl;
    string back;
    cin >> back;
    if (back == "返回") {
        // 回消费者主菜单
        consumerMenu();
    } else {
        viewReceipt(); //继续循环输入并查看小票信息 
    }
}

//////////厨师
// 厨师菜单
void chefMenu() {
    while (true) {
        cout << "***************************************************" << endl;
        cout << "                欢迎进入厨师子系统                 " << endl;
        cout << "***************************************************" << endl;
        cout << "*        1.查看小票        2.做菜                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*        3.查看统计        0.退出到主菜单         *" << endl;
        cout << "*                                                 *" << endl;
        cout << "***************************************************" << endl;
        cout<<"请选择："<<endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            chefViewReceipt(); //查看小票 
            break;
        case 2:
            changeDishStatusByChef(); //做菜 改变菜品状态到1
            break;
        case 3:
            chefViewStatistics(); //查看总统计 已完成和未完成的菜品 
            break;
        case 0:
            mainmenu();
            break;
        default:
            cout<<"错误输入！！！"<<endl; 
            cout<<"请重新输入:"<<endl;
            continue;
        }
        break;
    }
} 

// 1.厨师查看小票
void chefViewReceipt() {
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        string line;
        cout << "       桌号    待做菜品名称    数量" << endl;
        while (getline(orderFile, line)) {
            istringstream iss(line);
            int tableNumber;
            string dishName;
            int quantity;
            int dishStatus;
            // 假设 orders.txt 中信息格式为 桌号 菜品名称 数量 菜品状态
            iss >> tableNumber >> dishName >> quantity >> dishStatus;
            if (dishStatus== 0) {
                cout << setw(10) << tableNumber << setw(14) << dishName << setw(10) << quantity << endl;
            }
        }
        orderFile.close();
    } else {
        cout << "无法打开订单文件" << endl;
    }
}


// 更新 orders.txt 中的菜品状态
void updateOrdersFile(const string& dishName, int newStatus) {
    ifstream orderFile("orders.txt");
    ofstream tempFile("temp_orders.txt");
    if (orderFile.is_open() && tempFile.is_open()) {
        string line;
        bool found = false;
        while (getline(orderFile, line)) {
            istringstream iss(line);
            int tableNumber;
            string storedDishName;
            int quantity;
            int dishStatus;
            double dishiPrice;
            iss >> tableNumber >> storedDishName >> quantity >> dishStatus>>dishiPrice;
            if (storedDishName == dishName) {
                dishStatus = newStatus;  // 将菜品状态更新为指定状态
                found = true;
            }
            tempFile << tableNumber << " " << storedDishName << " " << quantity << " " << dishStatus << dishiPrice<<endl;
        }
        orderFile.close();
        tempFile.close();
        if (found) {
            remove("orders.txt"); //删除文件 
            rename("temp_orders.txt", "orders.txt"); //重新命名文件名字 
            cout << "订单文件中的菜品状态已更新。" << endl;
        } else {
            remove("temp_orders.txt");
            cout << "未找到该菜品的订单信息，请确认输入是否正确。" << endl;
        }
    } else {
        cout << "无法打开订单文件或临时文件。" << endl;
    }
}



// 查找商品 ID 的辅助函数
int findGoodsIdByName(const string& dishName) {
    for (int i = 0; i < goodsCount; ++i) {
        if (goods[i].name == dishName) {
            return goods[i].id;
        }
    }
    return -1;
}

// 2.  做菜   厨师改变菜品状态
void changeDishStatusByChef() {
    bool found = false;
    bool done = false;
    while (!done) {
        // 打开订单文件和临时文件
        ifstream orderFile("orders.txt");
        ofstream tempFile("temp_orders.txt");
        try {
            // 检查文件是否成功打开
            if (!orderFile.is_open() ||!tempFile.is_open()) {
                throw ios_base::failure("无法打开文件");
            }
            string line;
            cout << "以下是待做的菜品：" << endl;
            while (getline(orderFile, line)) {
                istringstream iss(line);
                int tableNumber;
                string dishName;
                int quantity;
                int dishStatus;
                double dishPrice;
                iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice;
                if (dishStatus == 0 ) {
                    cout << "桌号：" << tableNumber << " 菜品：" << dishName << " 数量：" << quantity << " 单价：" << dishPrice << endl;
                    cout << "输入 'Y' 确认完成菜，其他键跳过：";
                    string choice;
                    cin >> choice;
                    // 验证用户输入
                    if (choice == "Y" || choice == "y") {
                        dishStatus = 1; //状态改为1 
                        found = true;
                    }
                }
                tempFile << tableNumber << " " << dishName << " " << quantity << " " << dishStatus << " " << dishPrice << endl;
            }
            orderFile.close();
            tempFile.close();
            if (found) {
                // 删除原文件并将临时文件重命名为原文件
                if (remove("orders.txt")!= 0) {
                    cerr << "删除原文件失败" << endl;
                }
                if (rename("temp_orders.txt", "orders.txt")!= 0) {
                    cerr << "重命名文件失败" << endl;
                }
                cout << "出菜信息已更新。" << endl;
            } else {
                // 删除临时文件
                if (remove("temp_orders.txt")!= 0) {
                    cerr << "删除临时文件失败" << endl;
                }
                cout << "没有出菜操作。" << endl;
            }
        } catch (const ios_base::failure& e) {
            cerr << "文件操作中发生错误: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "其他异常: " << e.what() << endl;
        }
        cout << "输入“返回”以返回，输入其他键继续出菜操作" << endl;
        string back;
        cin >> back;
        if (back == "返回") {
        	chefMenu(); //返回厨师界面 
            done = true;
        }
    }
}

//3.厨师查看统计
void chefViewStatistics() {
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        string line;
        cout << "当天已完成的菜品统计：" << endl;
        cout << "   菜品名称      数量     状态" << endl;
        while (getline(orderFile, line)) { //以行读取 
            istringstream iss(line);
            int tableNumber;
            string dishName;
            int quantity;
            int dishStatus;
            double dishPrice;//解析数据 
            iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice;
            if (dishStatus !=0) {
                cout <<setw(8)<< dishName << setw(12) << quantity << setw(12) ;
                if(dishStatus==0)cout<<"待制作"<<endl;
                else if(dishStatus==1)cout<<"已制作"<<endl;
                else if(dishStatus==3)cout<<"已结账"<<endl;
                
            }
        }
        orderFile.close();
    } else {
        cout << "无法打开订单文件" << endl;
    }

    cout << "输入“返回”以返回" << endl;
    string back;
    cin >> back;
    if (back == "返回") {
        chefMenu(); //返回厨师菜单 
    } else {
        chefViewStatistics();
    }
}

/////////服务员
//服务员子系统菜单 
void serverSubsytemMenu(){
	system("cls");
	cout << "***************************************************" << endl;
    cout << "           欢迎进入系服务员子系统系统              " << endl;
    cout << "***************************************************" << endl;
    cout << "*               1.为顾客点菜                      *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               2.为顾客加菜                      *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               3.出菜                            *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               4.查看已出菜清单                  *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               5.查看未出菜清单                  *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               6.打印小票                        *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               7.查看餐桌信息                    *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               0.退出到主菜单                    *" << endl;
    cout << "***************************************************" << endl;
	int select;
	while(1){
		cin>>select;
		switch(select)
		{
			case 1:
				takeOrder(); //为顾客点菜 
				break;
			case 2:
				addDishes(); //加菜 
				break;
			case 3:
				dishOut(); //出菜 
				break;
			case 4:
				view_yichucai(); //查看已出菜 
				break;
			case 5:
				view_weichucai();//查看未出菜 
				break;
			case 6:
				printTableReceipt(); //服务员打印小票 
				break;
			case 7:
				viewTables(); 
				break; 
			case 0:
				 mainmenu();
				 break;
			default:
                cout << "输入的选项无效，请重新输入！" <<endl;
                continue;
		}
	}
	
}


///2.加菜函数
void addDishes() {
    int tableNumber;
    cout << "请输入要加菜的桌号：" << endl;
    cin >> tableNumber;
    // 显示该桌已点的菜品
    showOrderedDishes(tableNumber); //展示该桌已点菜品 
    // 显示菜品信息
    displayDishes();
    ofstream orderFile("orders.txt", ios::app);
    if (!orderFile.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    cout << "请输入要加的菜品信息（输入格式：菜品名称 菜品数量，输入 “完成” 结束）" << endl;
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
        cout << "加菜成功！" << endl;
    }
    orderFile.close();
}
//3.出菜函数 出菜后退出程序 
void dishOut() {
    // 打开订单文件和临时文件
    ifstream orderFile("orders.txt");
    ofstream tempFile("temp_orders.txt");
    string line;
    bool found = false;
    cout << "以下是待出菜的菜品：" << endl;
    // 逐行读取订单文件
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int tableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice; // 新增单价变量
        // 从行中解析桌号、菜品名称、数量、状态和单价
        iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice;
        // 若菜品状态为未准备或准备中
        if ( dishStatus == 1) {
            cout << "桌号：" << tableNumber << " 菜品：" << dishName << " 数量：" << quantity << " 单价：" << dishPrice << endl;
            cout << "输入 'Y' 确认出菜，其他键跳过：";
            string choice;
            cin >> choice;
            if (choice == "Y" || choice == "y") {
                dishStatus = 2;  // 将状态更新为已完成
                found = true;
            }
        }
        // 将更新后的信息写入临时文件 桌号 名称 数量 状态 单价
        tempFile << tableNumber << " " << dishName << " " << quantity << " " << dishStatus << " " << dishPrice << endl;
    }
    orderFile.close();
    tempFile.close();
    // 若有出菜操作，删除原订单文件并将临时文件重命名为订单文件
    if (found) {
        remove("orders.txt");//删除原来的文件 
        rename("temp_orders.txt", "orders.txt"); //命名新的文件 
        cout << "出菜信息已更新。" << endl;
    } else {
        remove("temp_orders.txt");
        cout << "没有出菜操作。" << endl;
    }
    exit(0);
}

//4.看已出菜清单
void view_yichucai() {
    ifstream orderFile("orders.txt");
    bool found = false;
    string line;
    cout << "已出菜清单：" << endl;
    cout << "桌号       菜品名称       数量         单价" << endl;
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int tableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice; // 新增变量用于存储单价
        iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice; // 读取单价信息
        if (dishStatus == 2||dishStatus == 3) {
            found = true;
            cout << tableNumber << setw(16) << dishName << setw(10) << quantity << setw(11) << dishPrice << endl;
        }
    }
    orderFile.close();
    if (!found) {
        cout << "没有已出菜的菜品。" << endl;
    }
    cout << "输入“返回”以返回服务员界面" << endl;
    string back;
    cin >> back;
    if (back == "返回") {
        serverSubsytemMenu(); //返回服务员界面 
    } else {
        view_yichucai();
    }
}

//5.查看未出菜清单
void view_weichucai() {
    ifstream orderFile("orders.txt");
    bool found = false;
    string line;
    cout << "未出菜清单：" << endl;
    cout << "桌号       菜品名称        数量       单价" << endl;
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int tableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice; // 新增变量用于存储单价
        iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice; // 解析 
        if (dishStatus == 0 || dishStatus == 1) {
            found = true;
            cout << tableNumber << setw(16) << dishName << setw(10) << quantity << setw(12) << dishPrice << endl;
        }
    }
    orderFile.close();
    if (!found) {
        cout << "没有未出菜的菜品。" << endl;
    }
    cout << "输入“返回”以返回服务员界面" << endl;
    string back;
    cin >> back;
    if (back == "返回") {
        serverSubsytemMenu(); //返回服务员界面 
    } else {
        view_weichucai();
    }
}

//6.服务员打印小票
void printTableReceipt() {
    int tableNumber;
    cout << "请输入要打印小票的桌号：" << endl;
    cin >> tableNumber;


    ifstream orderFile("orders.txt");
    if (!orderFile.is_open()) {
        cout << "无法打开订单文件" << endl;
        return;
    }


    bool found = false;
    cout << "--------------------------- 小票信息 ---------------------------" << endl;
    cout << "桌号：" << tableNumber << endl;
    cout << "     菜品名称       菜品价格       数量" << endl;
    string line;
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int orderTableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice;
        if (iss >> orderTableNumber >> dishName >> quantity >> dishStatus >> dishPrice) {
            if (orderTableNumber == tableNumber) {
                cout <<setw(13)<< dishName << setw(16) << dishPrice << setw(12) << quantity << endl;
                found = true;
            }
        }
    }
    orderFile.close();


    if (!found) {
        cout << "未找到该桌号的订单信息" << endl;
    }
    cout << "--------------------------- 结束 --------------------------------" << endl;
    exit(0); 
}


///////////////收银员 
// 收银员菜单
void cashierMenu() {
    int choice;
    while (true) {
        cout << "***************************************************" << endl;
        cout << "                 收银员功能菜单                " << endl;
        cout << "***************************************************" << endl;
        cout << "*        1.结算收费        2.统计                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*        3.查看统计        4.退出                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "***************************************************" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            cashierSettlement(); //收银员结账 
            break;
        case 2:
            cashierViewStatistics(); //收银员统计 
            break;
        case 3:
            cashierViewStatistics();  //查看统计 
            break;
        case 4: 
            exit(0);
            break;
        default:
            cout << "无效的选择，请重新输入！" << endl;
            continue;
        }
        break;
    }
}

///1.收银员结算收费
void cashierSettlement() {
    int tableNumber;
    cout << "请输入桌号：" << endl;
    cin >> tableNumber;

    // 存储已完成菜品的信息
    int completedDishCount = 0;
    string completedDishNames[MAX_DISHES];
    int completedDishQuantities[MAX_DISHES];
    double mo = 0; // 总金额

    // 从 orders 中找出该桌号的已完成菜品
    ifstream orderFile("orders.txt");
    if (!orderFile.is_open()) {
        cout << "无法打开订单文件" << endl;
        return;
    }

    string line;
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int storedTableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice;
        // 假设 orders.txt 中信息格式为 桌号 菜品名称 数量 菜品状态 单价
        if (iss >> storedTableNumber >> dishName >> quantity >> dishStatus >> dishPrice) {
            if (storedTableNumber == tableNumber && dishStatus == 2) {
                completedDishNames[completedDishCount] = dishName;
                completedDishQuantities[completedDishCount] = quantity;
                mo += dishPrice * quantity;
                completedDishCount++;

                // 存储到 sale 结构体中
                sale[saleCount].salenumber[completedDishCount - 1] = completedDishCount;
                // 查找商品 ID
                sale[saleCount].goodsid[completedDishCount - 1] = findGoodsIdByName(dishName);
                // 使用 strncpy 复制字符串到 char 数组
                strncpy(sale[saleCount].salename[completedDishCount - 1], dishName.c_str(), sizeof(sale[saleCount].salename[completedDishCount - 1]) - 1);
                sale[saleCount].salename[completedDishCount - 1][sizeof(sale[saleCount].salename[completedDishCount - 1]) - 1] = '\0';
                sale[saleCount].saledanjia[completedDishCount - 1] = dishPrice;
            }
        }
    }
    orderFile.close();

    // 储存销售单据号
    sale[saleCount].danju = saleCount + 1; // 单据号自增
    sale[saleCount].allmoney = mo;
    sale[saleCount].salenumberCount = completedDishCount;

    // 打印小票
    system("cls");
    cout << " " << endl;
    cout << "     欢迎光临666餐厅！" << endl;
    system("color 70"); //更改底色 
    cout << "..................................." << endl;
    cout << "      单据号：" << saleSummaryCount << endl;
    cout << "      日期：";
    riqi();
    cout << "..................................." << endl;
    cout << "  名称           数 量        单价       总金额" << endl;
    cout << " " << endl;
    for (int i = 0; i < completedDishCount; ++i) {
        cout << setw(10) << completedDishNames[i];
        cout << setw(8) << completedDishQuantities[i];
        cout << setw(16) << fixed << setprecision(2) << sale[saleCount].saledanjia[i];
        cout << setw(10) << fixed << setprecision(2) << sale[saleCount].saledanjia[i] * completedDishQuantities[i] << endl;
    }
    cout << setw(36) << fixed << setprecision(2) << mo;
    cout << endl;
    cout << "..................................." << endl;
    cout << "      谢谢惠顾！欢迎下次光临！" << endl;

    // 保存销售明细到文件
    ofstream saleFile("sales_detail.txt", ios::app); // 小票明细文件
    ofstream summaryFile("sales_summary.txt", ios::app); // 小票概要文件
    if (saleFile.is_open() && summaryFile.is_open()) {
        // 保存小票概要信息
        summaryFile << saleSummaryCount << " " << mo << endl;

        // 保存小票明细信息
        for (int i = 0; i < completedDishCount; ++i) {
            saleFile << saleSummaryCount << " " << sale[saleCount].salename[i] << " " << sale[saleCount].saledanjia[i] << " " << completedDishQuantities[i] << endl;
        }
        saleFile.close();
        summaryFile.close();
    } else {
        cout << "无法打开文件" << endl;
    }

    // 更新订单状态
    ifstream orderFile2("orders.txt");
    ofstream tempFile("temp_orders.txt");
    if (orderFile2.is_open() && tempFile.is_open()) {
        while (getline(orderFile2, line)) {
            istringstream iss(line);
            int storedTableNumber;
            string dishName;
            int quantity;
            int dishStatus;
            double dishPrice;
            if (iss >> storedTableNumber >> dishName >> quantity >> dishStatus >> dishPrice) {
                if (storedTableNumber == tableNumber) {
                    dishStatus = 3; // 将该桌号的订单状态改为 3（已结账）
                }
                tempFile << storedTableNumber << " " << dishName << " " << quantity << " " << dishStatus << " " << dishPrice << endl;
            }
        }
        orderFile2.close();
        tempFile.close();
        remove("orders.txt");
        rename("temp_orders.txt", "orders.txt");
    }

    // 将对应餐桌状态置为 0 并将时间置为 "NULL" 以及将用户名改为 "NULL"
    bool foundTable = false;
    for (int i = 0; i < tableCount; ++i) {
        if (tables[i].number == tableNumber) {
            tables[i].use = 0; // 将餐桌状态置为 0（空闲）
            tables[i].reservationTime = "无"; // 将时间置为 "NULL"
            tables[i].userName = "无"; // 将用户名置为 "NULL"
            foundTable = true;
            break;
        }
    }
    saveTables();
    if (!foundTable) {
        cout << "未找到该桌号对应的餐桌信息。" << endl;
    }

    // 打印结算信息
    cout << "结算信息：" << endl;
    cout << "已做菜品种类数量：" << completedDishCount << endl;
    cout << "已做菜品金额：" << mo << endl;

    // 打印 orders 中状态为 1 的菜品信息
    ifstream orderFile3("orders.txt");
    if (orderFile3.is_open()) {
        cout << "订单中状态为 0 or 1 的菜品信息：" << endl;
        cout << "桌号    菜品名称    数量    状态" << endl;
        while (getline(orderFile3, line)) {
            istringstream iss(line);
            int storedTableNumber;
            string dishName;
            int quantity;
            int dishStatus;
            double dishPrice;
            if (iss >> storedTableNumber >> dishName >> quantity >> dishStatus >> dishPrice) {
                if (dishStatus == 1 || dishStatus == 0) {
                    cout << storedTableNumber << setw(12) << dishName << setw(8) << quantity << setw(8) ;
					if(dishStatus==0)cout<<"未制作" << endl;
					if(dishStatus==1)cout<<"未上菜" << endl;
                }
            }
        }
        orderFile3.close();
    } else {
        cout << "无法打开订单文件" << endl;
    }

    cout << "输入数字“1”以返回" << endl;
    string nm, mmmm = "1";
    while (true) {
        cin >> nm;
        if (nm == mmmm) {
            cashierMenu();
            break;
        } else {
            cout << "请重新输入" << endl;
        }
    }
    saleCount++;

    // 保存餐桌信息
    saveTables();
}

////2.收银员统计（未使用 
void cashierStatistics() {
    int completedDishCount[MAX_DISHES] = {0}; // 存储每种已完成菜品的数量
    double completedDishAmount[MAX_DISHES] = {0}; // 存储每种已完成菜品的总金额
    int pendingDishCount[MAX_DISHES] = {0}; // 存储每种待做菜品的数量
    double pendingDishAmount[MAX_DISHES] = {0}; // 存储每种待做菜品的总金额
    // 打开订单文件
    ifstream orderFile("orders.txt");
    if (!orderFile.is_open()) {
        cout << "无法打开订单文件" << endl;
        return;
    }

    string line;
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int tableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice;
        // 假设 order.txt 中信息格式为 桌号 菜品名称 数量 菜品状态 菜品价格
        if (iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice) {
            bool found = false;
            for (int i = 0; i < dishCount; i++) {
                if (dishes[i].dishName == dishName) {
                    found = true;
                    if (dishStatus == 2) {
                        completedDishCount[i] += quantity;
                        completedDishAmount[i] += dishPrice * quantity;
                    } else if (dishStatus == 0 || dishStatus == 1) {
                        pendingDishCount[i] += quantity;
                        pendingDishAmount[i] += dishPrice * quantity;
                    }
                    break;
                }
            }
            if (!found) {
                // 可添加更完善的错误处理逻辑，这里暂时仅输出提示信息
                cerr << "菜品 " << dishName << " 未在 dishes 数组中找到" << endl;
            }
        } else {
            // 处理解析错误，可添加更完善的错误处理逻辑
            cerr << "解析订单文件行出错：" << line << endl;
        }
    }
    orderFile.close();


    cout << "当天统计信息：" << endl;


    // 输出已完成菜品数量
    cout << "已做菜品数量：" << endl;
    for (int i = 0; i < dishCount; i++) {
        if (completedDishCount[i] > 0) {
            cout << dishes[i].dishName << ": " << completedDishCount[i] << endl;
        }
    }


    // 输出已完成菜品金额
    cout << "已做菜品金额：" << endl;
    for (int i = 0; i < dishCount; i++) {
        if (completedDishAmount[i] > 0) {
            cout << dishes[i].dishName << ": " << fixed << setprecision(2) << completedDishAmount[i] << endl;
        }
    }


    // 输出待做菜品数量
    cout << "待做菜品数量：" << endl;
    for (int i = 0; i < dishCount; i++) {
        if (pendingDishCount[i] > 0) {
            cout << dishes[i].dishName << ": " << pendingDishCount[i] << endl;
        }
    }


    // 输出待做菜品金额
    cout << "待做菜品金额：" << endl;
    for (int i = 0; i < dishCount; i++) {
        if (pendingDishAmount[i] > 0) {
            cout << dishes[i].dishName << ": " << fixed << setprecision(2) << pendingDishAmount[i] << endl;
        }
    }


    // 改进返回逻辑
    cout << "输入数字“1”以返回" << endl;
    string input;
    while (true) {
        cin >> input;
        if (input == "1") {
            cashierMenu();
            break;
        } else {
            cout << "请重新输入" << endl;
        }
    }
}

//3.收银查看统计
void cashierViewStatistics() {
    int completedDishCount[MAX_GOODS] = {0};


    // 打开订单文件
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        string line;
        while (getline(orderFile, line)) {
            istringstream iss(line);
            int tableNumber;
            string dishName;
            int quantity;
            int dishStatus;
            double dishPrice;
            // 假设 order.txt 中信息格式为 桌号 菜品名称 数量 菜品状态 菜品价格
            if (iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice) {
                if (dishStatus == 3) {
                    bool found = false;
                    for (int i = 0; i < goodsCount; i++) {
                        if (goods[i].name == dishName) {
                            completedDishCount[i] += quantity;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        // 可添加更完善的错误处理逻辑，这里暂时仅输出提示信息
                        cerr << "菜品 " << dishName << " 未在 goods 数组中找到" << endl;
                    }
                }
            } else {
                // 处理解析错误，可添加更完善的错误处理逻辑
                cerr << "解析订单文件行出错：" << line << endl;
            }
        }
        orderFile.close();
    } else {
        cout << "无法打开订单文件" << endl;
        return;
    }


    cout << "当天已完成菜品统计（财务角度）：" << endl;
    cout << "    菜品名称           数量         总金额" << endl;
    for (int i = 0; i < goodsCount; i++) {
        if (completedDishCount[i] > 0) {
            double totalAmount = goods[i].price * completedDishCount[i];
            cout << setw(8) << goods[i].name << setw(12) << completedDishCount[i] << setw(12) << fixed << setprecision(2) << totalAmount << endl;
        }
    }


    cout << "输入数字“1”以返回" << endl;
    string nm, mmmm = "1";
    while (true) {
        cin >> nm;
        if (nm == mmmm) {
            cashierMenu();
            break;
        } else {
            cout << "请重新输入" << endl;
        }
    }
}



/////////////////系统管理员 
// 管理员 
void manageMenu() {
	system("cls");
    while (true) {
        cout << "***************************************************" << endl;
        cout << "              欢迎进入系统管理员系统               " << endl;
        cout << "***************************************************" << endl;
        cout << "*              1.添加用户信息                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              2.修改用户信息                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              3.查看用户信息                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              4.添加菜品信息                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              5.删除菜品信息                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              6.更改菜品信息                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              7.查看菜品信息                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              0.退出到主菜单                     *" << endl;
        cout << "***************************************************" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            addUserInformation();
            break;
        case 2:
            changeUserInformation();
            break;
        case 3:
            viewUserInformation();
            break;
        case 4:
        	addGoodsMenu();
        	break;
        case 5:
        	deleteGoods();
        	break;
        case 6:
        	changeGoods();
        	break;
        case 7:
        	displayDishes();
        	break;
        case 0:
            mainmenu();
            break;
        default:
            cout << "无效的选择，请重新输入！" << endl;
            continue;
        }
        system("pause");
        manageMenu();
    }
}

// 1.添加用户信息
void addUserInformation() {
    string username, password, role;
    cout << "请输入要添加的用户信息(输入 Q 时退出；若输入多个，请分两行输入 Q 退出)" << endl;
    cout << "输入格式：用户名 密码 角色" << endl;
    while (true) {
        cin >> username;
        if (username == "Q") {
            cout << "****添加成功，正在退出****" << endl;
            saveUsers();
            break;
        }
        cin >> password >> role;
        id[userCount++] = {username, password, role};
    }
}


//2. 修改用户信息
void changeUserInformation() {
    string targetUsername;
    cout << "请输入要修改的用户的用户名：" << endl;
    cin >> targetUsername;
    bool found = false;
    for (int i = 0; i < userCount; i++) {
        if (id[i].usname == targetUsername) {
            found = true;
            cout << "已找到该用户，请输入新的用户信息（输入格式：用户名 密码 角色）：" << endl;
            string newUsername, newPassword, newRole;
            cin >> newUsername >> newPassword >> newRole;
            id[i].usname = newUsername;
            id[i].password = newPassword;
            id[i].role = newRole;
            saveUsers();   //保存到文件中 (调用函数 
            cout << "用户信息修改成功！" << endl;
            break;
        }
    }
    if (!found) {
        cout << "未查找到要修改的用户，请确认是否输入有误！" << endl;
        manageMenu();//返回到系统管理员界面 
    }
}

//3.查看所有的用户信息（老板和 管理员未分开！！ 
void viewUserInformation() {
    cout << "*************************全部用户信息如下*************************" << endl;
    cout << "           用户名        密码        角色" << endl;
    for (int i = 0; i < userCount; i++) {
        cout <<setw(18)<< id[i].usname << setw(12) << id[i].password << setw(12) << id[i].role << endl;
    }
    cout << "*******************************************************************" << endl;
    system("pause");//界面暂停 
    exit(0); 
}

//4.// 添加商品菜单
void addGoodsMenu() {
    string name, category;
    double price;
    char choice;
    do {
        // 自动生成 id，将其设置为 goodsCount
        int id = goodsCount;
        cout << "请输入商品的名称：";
        cin >> name;
        cout << "请输入商品的类别：";
        cin >> category;
        cout << "请输入商品的价格：";
        cin >> price;

        // 将商品信息添加到 goods 数组中
        if (goodsCount < MAX_GOODS) {
            goods[goodsCount].id = id+1;
            goods[goodsCount].name = name;
            goods[goodsCount].category = category;
            goods[goodsCount].price = price;
            goodsCount++;

            // 保存商品信息到文件
            saveGoods();
        } else {
            cout << "商品数量已达到上限，无法添加新商品！" << endl;
        }

        cout << "是否继续添加商品？(Y/N) ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
}


//6.修改菜品信息函数
void changeGoods() {
    if (goodsCount == 0) {
        cout << "当前没有菜品可供修改。" << endl;
        return;
    }
    string name;
    cout << "请输入要修改的菜品名称：" << endl;
    cin >> name;
    bool found = false;
    for (int i = 0; i < goodsCount; ++i) {
        if (goods[i].name == name) {
            found = true;
            // 输出原有的菜品信息
            cout << "原有的菜品信息如下：" << endl;
            cout << "菜品名称：" << goods[i].name << endl;
            cout << "菜品类别：" << goods[i].category << endl;
            cout << "菜品价格：" << goods[i].price << endl;
            string newName, newCategory;
            double newPrice;
            cout << "请输入新的菜品名称：" << endl;
            cin >> newName;
            cout << "请输入新的菜品类别：" << endl;
            cin >> newCategory;
            cout << "请输入新的菜品价格：" << endl;
            cin >> newPrice;
            goods[i].name = newName;
            goods[i].category = newCategory;
            goods[i].price = newPrice;
            cout << "菜品 " << name << " 已修改成功！" << endl;
            break;
        }
    }
    if (!found) {
        cout << "未找到名为 " << name << " 的菜品。" << endl;
        return;
    }
    // 保存更新后的菜品信息到文件
    saveGoods();
} 



/////////////老板
// 老板菜单
void bossMenu() {
	system("cls");
    while (true) {
        cout << "***************************************************" << endl;
        cout << "              欢迎进入餐厅老板子系统               " << endl;
        cout << "***************************************************" << endl;
        cout << "*              1.查看今日总收入如何               *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              2.查看菜品销售情况                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              3.查看今日完成与未完成             *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              4.查看座位使用情况                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              5.查看员工信息                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              6.查看菜单                         *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              7.输入单据号查找销售               *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              8.删除某个菜品                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              0.退出到主菜单                     *" << endl;
        cout << "***************************************************" << endl;
        cout<<"请选择："<<endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
        	shouru(); //查看今日总收入如何 （遍历了我小票概要总收入 
         	break;
        case 2:
        	cashierViewStatistics();//这里使用了和收银一样的函数 (有点问题 
        	break;
        case 3:
        	lookall();    //
            break;
        case 4:
        	viewTables();    //查看座位使用情况
            break;
        case 5:
        	viewUserInformation();    
            break;
        case 6:
			displayDishes(); 
			break; 
		case 7:
			bossSearchByDanju(); 
			break; 
		case 8:
			deleteGoods();
			break; 
        case 0:
            mainmenu();    
            break;    
        default:
            cout<<"错误输入！！！"<<endl; 
            cout<<"请重新输入:"<<endl;
            continue;
        }
        break;
    }
}

//1.看今日收入如何
void shouru() {
    double totalIncome = 0;

    // 打开销售概要文件
    ifstream salesSummaryFile("sales_summary.txt");
    if (salesSummaryFile.is_open()) {
        string line;

        // 逐行读取文件
        while (getline(salesSummaryFile, line)) {
            istringstream iss(line);
            int danju;  // 单据号
            double allmoney;  // 该单据的总金额

            // 从当前行解析单据号和总金额
            if (iss >> danju >> allmoney) {
                // 将该单据的总金额累加到总收入
                totalIncome += allmoney;
            } else {
                // 解析失败时输出错误信息
                cerr << "解析销售概要文件行出错：" << line << endl;
            }
        }
        salesSummaryFile.close();
    } else {
        cout << "无法打开销售概要文件" << endl;
        return;
    }

    // 输出今日总收入，保留两位小数
    cout << "今日总收入：" << fixed << setprecision(2) << totalIncome << endl;
}


//3.查看今日完成与未完成
void lookall() {
    int completedDishCount = 0;
    double completedDishAmount = 0;
    int pendingDishCount = 0;
    double pendingDishAmount = 0;
    string pendingDishNames[MAX_DISHES];
    int pendingDishQuantities[MAX_DISHES];
    int pendingDishIndex = 0;


    ifstream ordersFile("orders.txt");
    if (ordersFile.is_open()) {
        string line;
        while (getline(ordersFile, line)) {
            istringstream iss(line);
            int tableNumber;
            string dishName;
            int quantity;
            int dishStatus;
            double dishPrice;
            // 假设 orders.txt 中信息格式为 桌号 菜品名称 数量 菜品状态 菜品价格
            iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice;


            if (dishStatus == 2 || dishStatus == 3) {
                completedDishCount += quantity;
                completedDishAmount += dishPrice * quantity;
            } else {
                pendingDishCount += quantity;
                pendingDishAmount += dishPrice * quantity;
                pendingDishNames[pendingDishIndex] = dishName;
                pendingDishQuantities[pendingDishIndex] = quantity;
                pendingDishIndex++;
            }
        }
        ordersFile.close();
    } else {
        cout << "无法打开订单文件" << endl;
        return;
    }


    cout << "已完成菜品数量：" << completedDishCount << " 已完成菜品金额：" << fixed << setprecision(2) << completedDishAmount << endl;
    cout << "未完成菜品数量：" << pendingDishCount << " 未完成菜品金额：" << fixed << setprecision(2) << pendingDishAmount << endl;


    // 输出未完成菜品的名称和数量
    if (pendingDishIndex > 0) {
        cout << "未完成菜品信息：" << endl;
        cout << "菜品名称    数量" << endl;
        for (int i = 0; i < pendingDishIndex; ++i) {
            cout << setw(12) << pendingDishNames[i] << setw(12) << pendingDishQuantities[i] << endl;
        }
    }
}

// 7.老板根据单据号查找小票详细信息
void bossSearchByDanju() {
    int inputDanju;
    cout << "请输入单据号: ";
    cin >> inputDanju;


    ifstream detailFile("sales_detail.txt");
    if (!detailFile.is_open()) {
        cout << "无法打开销售详细文件。" << endl;
        return;
    }


    string line;
    bool found = false;
    while (getline(detailFile, line)) {
        istringstream iss(line);
        SaleDetail detail;
        if (iss >> detail.danju >> detail.dishName >> detail.dishPrice >> detail.quantity) {
            if (detail.danju == inputDanju) {
                found = true;
                cout << "菜品名称: " << detail.dishName << " 数量: " << detail.quantity << " 单价: " << fixed << setprecision(2) << detail.dishPrice << endl;
            }
        } else {
            cout << "解析销售详细信息行出错。" << endl;
        }
    }
    detailFile.close();


    if (!found) {
        cout << "未找到该单据号对应的销售信息。" << endl;
    }

    cout << "输入数字“1”以返回" << endl;
    string input;
    while (true) {
        cin >> input;
        if (input == "1") {
            bossMenu();
            break;
        } else {
            cout << "请重新输入" << endl;
        }
    }
} 

//8. 删除菜品函数
void deleteGoods() {
    if (goodsCount == 0) {
        cout << "当前没有菜品可供删除。" << endl;
        return;
    }
    string nameToDelete;
    cout << "请输入要删除的菜品名称：" << endl;
    cin >> nameToDelete;
    bool found = false;
    for (int i = 0; i < goodsCount; ++i) {
        if (goods[i].name == nameToDelete) {
            found = true;
            for (int j = i; j < goodsCount - 1; ++j) {
                goods[j] = goods[j + 1];
            }
            goodsCount--;
            cout << "菜品 " << nameToDelete << " 已删除成功！" << endl;
            break;
        }
    }
    if (!found) {
        cout << "未找到名为 " << nameToDelete << " 的菜品。" << endl;
    }
    // 调整菜品的 id
    for (int i = 0; i < goodsCount; ++i) {
        goods[i].id = i + 1;
    }
    saveGoods();
}

int main() {
    // 加载数据
   
    loadSaleSummary(); // 加载小票概要信息
    loadSaleDetail();// 加载小票详细信息
    loadGoods(); //可提供菜品信息 
    loadTables();//加载餐桌信息 
    
    loadUsers(); 
    mainmenu();
    return 0;
}

