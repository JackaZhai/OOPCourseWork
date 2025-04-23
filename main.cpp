#include "common.h"
#include "fileio.h"
#include "utils.h"
#include "consumer.h"
#include "chef.h"
#include "server.h"
#include "cashier.h"
#include "admin.h"
#include "boss.h"
#include "auth.h"

// 主界面
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
       		serverSubsytemMenu();
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

int main() {
    // 加载数据
    loadSaleSummary(); // 加载小票概要信息
    loadSaleDetail(); // 加载小票详细信息
    loadGoods(); // 可提供菜品信息 
    loadTables(); // 加载餐桌信息
    loadUsers(); 
    mainmenu();
    return 0;
}

