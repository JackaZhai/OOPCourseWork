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

// ������
void mainmenu() {
    system("cls");  //����
    cout << "***************************************************" << endl;
    cout << "                 ��ѡ��Ҫ���еĲ���                " << endl;
    cout << "***************************************************" << endl;
    cout << "*        1.��������ϵͳ     2.��ʦ��ϵͳ          *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*        3.����Ա��ϵͳ     4.����Ա��ϵͳ        *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*        5.����Ա��ϵͳ     6.�����ϰ���ϵͳ      *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*        0.�˳�ϵͳ                               *" << endl;
    cout << "***************************************************" << endl;
    cout<<"��ѡ��"<<endl;
    char select;
    cin>>select;
    switch(select){
        case '1':
            //login(1);  // �ȵ�¼���ٽ�����������ϵͳ
            consumerMenu();  
            break;
        case '2':
          //  login(2);  // �ȵ�¼���ٽ����ʦ��ϵͳ
            chefMenu();  
            break;
        case '3':
        //	login(3);
       		serverSubsytemMenu();
        	break;
        case '4':
          //  login(4);  // �ȵ�¼���ٽ�������Ա��ϵͳ
            cashierMenu();  
            break;
        case '5': 
          //  login(5);  // �ȵ�¼���ٽ������Ա��ϵͳ
            manageMenu();  
            break;
        case '6':
          //  login(6);  // �ȵ�¼���ٽ�������ϰ���ϵͳ
            bossMenu();  
            break;
        case '0':
            exit(0);   //�����˳�ϵͳ 
            break;
        default:
            cout<<"�������룡����"<<endl;  //�������� 
            cout<<"���������룺"<<endl;
            cin>>select;  //��������
            mainmenu(); 
    }
}

int main() {
    // ��������
    loadSaleSummary(); // ����СƱ��Ҫ��Ϣ
    loadSaleDetail(); // ����СƱ��ϸ��Ϣ
    loadGoods(); // ���ṩ��Ʒ��Ϣ 
    loadTables(); // ���ز�����Ϣ
    loadUsers(); 
    mainmenu();
    return 0;
}

