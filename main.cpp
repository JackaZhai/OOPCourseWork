#include <iostream>
#include <iomanip>
#include <string>
#include<cstring>
#include <ctime> //�ṩ��ʱ������ڵĴ����ܡ�
#include <sstream>//���Խ�һ���ַ����ֽ�Ϊ����Ӵ�������������� iss>> 
#include <cstdlib> //�ṩ��һЩͨ�õ�ʵ�ú��� exit(0)�����������ڳ�����쳣��ֹ
#include <fstream> //�ļ����� 
#include <limits> //
#include <locale>//���Ĳ����룿 
using namespace std;
 
void mainmenu();//������ 
void showUserSelection(); // ��ʾ�û�ѡ�����
void registerUser();// ע���û�
void login();// ��¼����
void riqi();// ��ʾ����
void loadUsers();// �����û�����
void loadTables();// ���ز�λ���� 
void loadGoods();// ������Ʒ����
void loadSaleSummary();// ����СƱ��Ҫ��Ϣ
void loadSaleDetail();// ����СƱ��ϸ��Ϣ
void displayDishes();// ��ʾ���ṩ��Ʒ��Ϣ
void viewTables();// �鿴���еĲ�λ��Ϣ
void reserveTable();// Ԥ����λ
void manageTables();// �����λ��Ϣ /Ԥ�� �鿴 ������һ�� �˳� 
void saveGoods(); //������Ʒ��Ϣ���ļ�
void saveTables();// �����λ��Ϣ���ļ�tables.txt
void saveUsers();// �����û���Ϣ���ļ�users.txt
void showOrderedDishes(int n); //չʾ����nʱ ���Ӧ���ŵĲ�Ʒ 
void takeOrder();//��ͺ���
void consumerMenu();// �����߲˵�
void viewReceipt();// �鿴СƱ  СƱ��Ϣ�洢��receipt.txt�ļ��� ��ʽΪ����Ʒ���� ���� �۸�
void chefMenu();// ��ʦ�˵�
void chefViewReceipt();// ��ʦ�鿴СƱ ���� ������Ʒ���� ����
int findGoodsIdByName(const string& dishName);//�ҵ���Ʒ ID��������
void changeDishStatusByChef();// ��ʦ�ı��Ʒ״̬ �ı�dishes��i���е�״̬ 
void chefViewStatistics();// ��ʦ�鿴ͳ�� �����
void serverSubsytemMenu();//����Ա�˵�
void addDishes();//�Ӳ˺��� 
void dishOut(); ///���˺��� ����״̬Ϊ 2
void view_yichucai();//�鿴�ѳ���
void view_weichucai();//�鿴δ���� 
void printTableReceipt(); //����Ա��ӡСƱ �������� ��� ���� �۸� ���� 
void cashierMenu();// ����Ա�˵�
void cashierSettlement();// ����Ա�����շ�  �ı�״̬Ϊ3
void cashierStatistics();// ����Աͳ��
void cashierViewStatistics();// ����Ա�鿴ͳ��
void manageMenu();// ����Ա�˵� 
void addUserInformation(); //����û���Ϣ �û��� ���� ��ɫ 
void changeUserInformation(); // �޸��û���Ϣ
void viewUserInformation();// �鿴�����û���Ϣ���ϰ�͹���鿴 
void addGoodsMenu();//��Ӳ�Ʒ��Ϣ
void changeGoods();//�޸Ĳ�Ʒ��Ϣ
void bossMenu();// �ϰ�˵�
void shouru(); //�鿴������

void deleteGoods();//ɾ����Ʒ��Ϣ
void lookall(); //����ɺ�δ������� �ͽ��
void bossSearchByDanju();  //ͨ�����ݺŲ��Ҷ�Ӧ��Ĳ�Ʒ

// ��Ʒ�ṹ�� 
struct Goods {
    int id;
    string name;
    string category;
    double price;
};

// ��λ�ṹ��
struct zuowei {
    int number;
    string seat;
    int use;
    int people;
    string reservationTime; //Ԥ��ʱ�� 
    string userName; //�����û��� 
    int customerCount; // �����˿�������Ա����
};

// �û��ṹ��
struct User {
    string usname;
    string password;
    string role;
};

// ���ۼ�¼�ṹ��
struct SaleSummary {
    int danju; // ���ݺ� 
    double allmoney; // �ܽ�� 
};

// ����СƱ��ϸ����
struct SaleDetail {
    int danju; //���ݺ� 
    string dishName; //��Ʒ���� 
    double dishPrice; //���� 
    int quantity;//���� 
};

// ���ۼ�¼�ṹ��
struct Sale {
    int salenumber[100]; // ������� 100 �����ۼ�¼
    int goodsid[100];
    char salename[100][50]; // �������Ƴ��Ȳ����� 50
    double saledanjia[100];
    double allmoney; //�ܽ�� 
    int danju; //���ݺ� 
    int salenumberCount; // ���ڼ�¼ʵ�ʵ���������
    int goodsidCount;
    int salenameCount;
    int saledanjiaCount;
};

// ��ͽṹ��
struct Dish {
    string dishName;
    string dishCategory;
    double dishPrice;
    int dishStatus; // 0: δ׼��, 1: ׼����, 2: �����
    int quantity;
};



#define MAX_GOODS 1000  // ���������Ʒ����Ϊ 1000
#define MAX_TABLES 100  // ��������λ����Ϊ 100
#define MAX_SALES 100  // ����������ۼ�¼����Ϊ 100
#define MAX_USERS 100  // ��������û�����Ϊ 100
#define MAX_DISHES 1000 // ��������Ʒ����Ϊ 1000

Goods goods[MAX_GOODS]; //goods�ṹ������  ���ڴ洢�ܹ��ṩ�Ĳ�Ʒ 
int goodsCount = 0; //����  
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
Dish dishes[MAX_DISHES]; // ���� ���� �۸� ״̬ ����  
int dishCount = 0;//
int pass = 0;

//������ 
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
       		serverSubsytemMenu();//����Ա��ϵͳ 
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

// ��ʾ�û�ѡ�����
void showUserSelection() {
    cout << "***************************************************" << endl;
    cout << "               ��������ϵͳ�û�ѡ�����            " << endl;
    cout << "***************************************************" << endl;
    cout << "*        1. ��¼        2. ע���û�               *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*        3. �˳�ϵͳ                              *" << endl;
    cout << "*                                                 *" << endl;
    cout << "***************************************************" << endl;
    cout << "����������ѡ��";
}

// ע���û�
void registerUser() {
    string username, password, role;
    cout << "�������û���: ";
    cin >> username;
    cout << "����������: ";
    cin >> password;
    cout << "�������ɫ: ";
    cin >> role;

    // ����û����Ƿ��Ѵ���
    bool exists = false;
    for (int i = 0; i < userCount; i++) {
        if (id[i].usname == username) {
            exists = true;
            cout << "���û����Ѵ��ڣ����������룡" << endl;
            registerUser(); // �ظ�ѭ��ע���û� 
        }
    }
    // ������û�
    id[userCount] = {username, password, role}; // ���浽�ļ�֮�� 
    userCount++;
    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        userFile << username << " " << password << " " << role << endl;
        userFile.close();
        cout << "�û�ע��ɹ���" << endl;
    } else {
        cout << "�޷����û��ļ�" << endl;
    }
    showUserSelection(); // �˴���¼Ӧ�������޸ģ���û�и� 
}

// ��¼���� 
void login(int a) {
    string username, password;
    int attempts = 3; // ���Ƶ�¼���Դ���
    while (attempts > 0) {
        cout << "�������û���: ";
        cin >> username;
        cout << "����������: ";
        cin >> password;
        bool found = false;
        for (int i = 0; i < userCount; i++) {
            if (id[i].usname == username && id[i].password == password) {
                pass = i;
                // ����û���ɫ�Ƿ�ƥ��
                if ((a == 1 && id[i].role == "consumer") || 
                    (a == 2 && id[i].role == "chef") || 
                    (a == 3 && id[i].role == "server") ||
                    (a == 4 && id[i].role == "cashier") || 
                    (a == 5 && id[i].role == "admin") || 
                    (a == 6 && id[i].role == "boss")) {
                    found = true;
                    break;
                } else {
                    cout << "��û��Ȩ�޽������ϵͳ�������µ�¼��" << endl;
                    break;
                }
            }
        }

        if (found) {
            break;
        } else {
            attempts--;
            cout << "�û�����������󣬻��� " << attempts << " �γ��Ի��ᣡ" << endl;
        }
    }

    if (attempts == 0) {
        cout << "��¼ʧ�ܣ��˳�����" << endl;
        exit(0);
    }
}

//��ʾ����//cout <<������ Сʱ������ 
void riqi() {
    time_t t = time(0);
    char tmp[32];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    cout << tmp << endl;
}

// �����û����� 
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
        cout << "�޷����û��ļ�" << endl;
    }
}

// ���ز�λ���ݵ�tables���� 
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
        cout << "�޷��򿪲�λ�ļ�" << endl;
    }
}

//���ز�Ʒ���� ��goods������ 
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
        cout << "�޷�����Ʒ�ļ�" << endl;
    }
}

// ����СƱ��Ҫ��Ϣ
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
                    cout << "���۸�Ҫ���ݴ洢�������޷�������ӡ�" << endl;
                    break;
                }
            } else {
                cout << "��ȡ���۸�Ҫ����ʱ��������" << endl;
                break;
            }
        }
        summaryFile.close();
    } else {
        cout << "�޷������۸�Ҫ�ļ���" << endl;
    }
}

//����СƱ��ϸ��Ϣ
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
                    cout << "СƱ��ϸ���ݴ洢�������޷�������ӡ�" << endl;
                    break;
                }
            } else {
                cout << "��ȡСƱ��ϸ����ʱ��������" << endl;
                break;
            }
        }
        detailFile.close();
    } else {
        cout << "�޷���СƱ��ϸ�ļ���" << endl;
    }
}

//��ʾ��Ʒ��Ϣ ���Ѿ���ǰ������goods������ ��Good�ṹ��Ϊ���� 
void displayDishes() {
    cout << "*************************ȫ����Ʒ��Ϣ����*************************" << endl;
    cout << "      ��Ʒ����       ��Ʒ���      ��Ʒ�۸�" << endl;
    for (int i = 0; i < goodsCount; i++) {
        cout <<setw(14)<< goods[i].name << setw(13) << goods[i].category << setw(13) << goods[i].price << endl;
    }
    cout << "*******************************************************************" << endl;
}

// ������еĲ�����Ϣ ���Ѿ���ǰ���ص�tables������ 
void viewTables() {
    cout << "**************************************ȫ����λ��Ϣ����**************************************" << endl;
    cout << "��λ���    ��λλ��    ��λ״̬    ����������          Ԥ��ʱ��        Ԥ���û�    �˿�����" << endl;
    for (int i = 0; i < tableCount; i++) {
        cout <<setw(3)<< tables[i].number << setw(16) << tables[i].seat << setw(11);
        if (tables[i].use == 0) {
            cout << "����";
        } else {
            cout << "��Ԥ��";
        }
        cout << setw(10) << tables[i].people << setw(26)<< tables[i].reservationTime << setw(11) << tables[i].userName << setw(10) << tables[i].customerCount << endl;
    }
    cout << "********************************************************************************************" << endl;
}

// Ԥ����λ
void reserveTable() {
    // ��������еĲ�����Ϣ
    viewTables();
    int number;
    int customerNum;
    string username;
    while (true) {
        cout << "������ҪԤ���Ĳ�λ��ţ�" << endl;
        cin >> number;
        bool k = false;
        for (int i = 0; i < tableCount; i++) {
            if (tables[i].number == number && tables[i].use == 0) {
                k = true;
                tables[i].use = 1; 
                cout << "������Ԥ����" << endl;
                cin >> username;
                // ��¼Ԥ���û����û���
                tables[i].userName = username; 
                // ���û�����˿�����
                cout << "����������Ĺ˿�������" << endl;
                cin >> customerNum;
                tables[i].customerCount = customerNum; 
                // ��¼Ԥ��ʱ��
                time_t t = time(0);
                char tmp[32] = {0};
                strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H:%M:%S", localtime(&t)); 
                tables[i].reservationTime = tmp; //����ʱ�� 
                saveTables();  //���� 
                break;
            }
        }
        if (!k) {
            cout << "û�п��õĸñ�Ų�λ��������ѡ��" << endl;
        } else {
            break;
        }
    }
    cout << "���롰���ء��Է���" << endl;
    string mm, mmm = "����";
    cin >> mm;
    if (mm == mmm) {
        manageTables(); 
    }
}

// �����λ��Ϣ
void manageTables() {
    int choice;
    while (true) {
        cout << "***************************************************" << endl;
        cout << "                 ��ѡ��Ҫ���еĲ���                " << endl;
        cout << "***************************************************" << endl;
        cout << "*        1.Ԥ����λ        2.�鿴��λ��Ϣ         *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*        3.�������˵�        4.�˳�               *" << endl;
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
            cout << "��Ч��ѡ�����������룡" << endl;
            continue;
        }
        system("pause"); 
        mainmenu();
    }
}
////////���ݱ��� 
// ������Ʒ��Ϣ���ļ�
void saveGoods() {
    ofstream goodsFile("goods.txt");
    if (goodsFile.is_open()) {
        for (int i = 0; i < goodsCount; i++) {
            goodsFile << goods[i].id << " " << goods[i].name << " " << goods[i].category << " " << goods[i].price << endl;
        }
        goodsFile.close();
    } else {
        cout << "�޷�����Ʒ�ļ�" << endl;
    }
}


// �����λ��Ϣ���ļ�
void saveTables() {
    ofstream myfile("tables.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < tableCount; i++) { 
            myfile << tables[i].number << " " << tables[i].seat << " " << tables[i].use << " " << tables[i].people << " " << tables[i].reservationTime << " " << tables[i].userName << " " << tables[i].customerCount << endl;
        }
        myfile.close();
    } else {
        cout << "�޷����ļ�" << endl;
    }
}

// �����û���Ϣ���ļ����û��� ���� ְλ 
void saveUsers() {
    ofstream userFile("users.txt");
    if (userFile.is_open()) {
        for (int i = 0; i < userCount; i++) {
            userFile << id[i].usname << " " << id[i].password << " " << id[i].role << endl;
        }
        userFile.close();
    } else {
        cout << "�޷����û��ļ�" << endl;
    }
}

// ��ʾָ�������ѵ�Ĳ�Ʒ��Ϣ
void showOrderedDishes(int tableNumber) {
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        bool foundTable = false;
        string line;
        cout << "�ѵ��Ʒ���£�" << endl;
        cout << "��Ʒ����     ����    ״̬    ����" << endl;
        while (getline(orderFile, line)) {
            istringstream iss(line);
            int storedTableNumber; //��� 
            string storedDishName; //���� 
            int storedQuantity; //����  
            int storedDishStatus; //״̬ 
            double storedDishPrice; // ����
            iss >> storedTableNumber >> storedDishName >> storedQuantity >> storedDishStatus >> storedDishPrice;
            if (storedTableNumber == tableNumber) {
                foundTable = true;
                cout << setw(8)<<storedDishName << "  " <<setw(6)<< storedQuantity << "  " <<setw(5)<< storedDishStatus << "  " <<setw(7) <<storedDishPrice << endl;
            }
        }
        orderFile.close();
        if (!foundTable) {
            cout << "��������δ��͡�" << endl;
        }
    } else {
        cout << "�޷����ļ�" << endl;
    }
}

// Ϊ�˿͵���Լ��˿͵�˾�ʹ����� 
void takeOrder() {
    int tableNumber;
    cout << "������Ҫ�Ӳ˵����ţ�" << endl;
    cin >> tableNumber;
    // ��ʾ�����ѵ�Ĳ�Ʒ
    showOrderedDishes(tableNumber);
    // ��ʾ��Ʒ��Ϣ
    displayDishes();
    ofstream orderFile("orders.txt", ios::app);
    if (!orderFile.is_open()) {
        cout << "�޷����ļ�" << endl;
        return;
    }
    cout << "������Ҫ��Ĳ�Ʒ��Ϣ�������ʽ����Ʒ���� ��Ʒ���������� ����ɡ� ������" << endl;
    string dishName;
    int quantity;
    while (true) {
        cin >> dishName;
        if (dishName == "���") {
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
            cout << "��Ʒ�����ڣ����������룡" << endl;
            continue;
        }
        orderFile << tableNumber << " " << dishName << " " << quantity << " 0 " << price << endl;
        cout << "��˳ɹ���" << endl;
    }
    orderFile.close();
}

//////////������ 
// �����߲˵�
void consumerMenu() {
    int choice;
    while (true) {
        cout << "***************************************************" << endl;
        cout << "                 �����߹��ܲ˵�                    " << endl;
        cout << "***************************************************" << endl;
        cout << "*        1.Ԥ����λ        2.���                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*        3.�鿴СƱ        4.�˳�                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "***************************************************" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            reserveTable(); //����Ԥ������ 
            break;
        case 2:
            takeOrder();//
            break;
        case 3:
            viewReceipt(); //�������Ų鿴СƱ 
            break;
        case 4:
        	mainmenu(); //���������˵� 
            break;
        default:
            cout << "��Ч��ѡ�����������룡" << endl;
            continue;
        }
        break;
    }
}


///3.�����ߡ��鿴СƱ������������������������Ϣ
void viewReceipt() {
    int tableNumber;
    cout << "������Ҫ�鿴СƱ�����ţ�" << endl;
    cin >> tableNumber;
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        bool foundTable = false;
        string line;
        cout << "       ��Ʒ����    ����    ����    �۸�    ״̬" << endl;
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
                double totalPrice = dishPrice * quantity;  // ����ò�Ʒ���ܼ�
                cout << setw(12) << dishName << setw(12) << quantity << setw(12) << dishPrice << setw(12) << totalPrice << setw(12) ;
				if(dishStatus==0) cout<< "�ѵ��"<< endl;
				else if(dishStatus==1) cout<< "�����"<< endl;
				else if(dishStatus==3) cout<< "���ϲ�"<< endl;
            }
        }
        orderFile.close();
        if (!foundTable) {
            cout << "��������δ��͡�" << endl;
        }
    } else {
        cout << "�޷��򿪶����ļ�" << endl;
    }
    cout << "���롰���ء��Է���" << endl;
    string back;
    cin >> back;
    if (back == "����") {
        // �����������˵�
        consumerMenu();
    } else {
        viewReceipt(); //����ѭ�����벢�鿴СƱ��Ϣ 
    }
}

//////////��ʦ
// ��ʦ�˵�
void chefMenu() {
    while (true) {
        cout << "***************************************************" << endl;
        cout << "                ��ӭ�����ʦ��ϵͳ                 " << endl;
        cout << "***************************************************" << endl;
        cout << "*        1.�鿴СƱ        2.����                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*        3.�鿴ͳ��        0.�˳������˵�         *" << endl;
        cout << "*                                                 *" << endl;
        cout << "***************************************************" << endl;
        cout<<"��ѡ��"<<endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            chefViewReceipt(); //�鿴СƱ 
            break;
        case 2:
            changeDishStatusByChef(); //���� �ı��Ʒ״̬��1
            break;
        case 3:
            chefViewStatistics(); //�鿴��ͳ�� ����ɺ�δ��ɵĲ�Ʒ 
            break;
        case 0:
            mainmenu();
            break;
        default:
            cout<<"�������룡����"<<endl; 
            cout<<"����������:"<<endl;
            continue;
        }
        break;
    }
} 

// 1.��ʦ�鿴СƱ
void chefViewReceipt() {
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        string line;
        cout << "       ����    ������Ʒ����    ����" << endl;
        while (getline(orderFile, line)) {
            istringstream iss(line);
            int tableNumber;
            string dishName;
            int quantity;
            int dishStatus;
            // ���� orders.txt ����Ϣ��ʽΪ ���� ��Ʒ���� ���� ��Ʒ״̬
            iss >> tableNumber >> dishName >> quantity >> dishStatus;
            if (dishStatus== 0) {
                cout << setw(10) << tableNumber << setw(14) << dishName << setw(10) << quantity << endl;
            }
        }
        orderFile.close();
    } else {
        cout << "�޷��򿪶����ļ�" << endl;
    }
}


// ���� orders.txt �еĲ�Ʒ״̬
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
                dishStatus = newStatus;  // ����Ʒ״̬����Ϊָ��״̬
                found = true;
            }
            tempFile << tableNumber << " " << storedDishName << " " << quantity << " " << dishStatus << dishiPrice<<endl;
        }
        orderFile.close();
        tempFile.close();
        if (found) {
            remove("orders.txt"); //ɾ���ļ� 
            rename("temp_orders.txt", "orders.txt"); //���������ļ����� 
            cout << "�����ļ��еĲ�Ʒ״̬�Ѹ��¡�" << endl;
        } else {
            remove("temp_orders.txt");
            cout << "δ�ҵ��ò�Ʒ�Ķ�����Ϣ����ȷ�������Ƿ���ȷ��" << endl;
        }
    } else {
        cout << "�޷��򿪶����ļ�����ʱ�ļ���" << endl;
    }
}



// ������Ʒ ID �ĸ�������
int findGoodsIdByName(const string& dishName) {
    for (int i = 0; i < goodsCount; ++i) {
        if (goods[i].name == dishName) {
            return goods[i].id;
        }
    }
    return -1;
}

// 2.  ����   ��ʦ�ı��Ʒ״̬
void changeDishStatusByChef() {
    bool found = false;
    bool done = false;
    while (!done) {
        // �򿪶����ļ�����ʱ�ļ�
        ifstream orderFile("orders.txt");
        ofstream tempFile("temp_orders.txt");
        try {
            // ����ļ��Ƿ�ɹ���
            if (!orderFile.is_open() ||!tempFile.is_open()) {
                throw ios_base::failure("�޷����ļ�");
            }
            string line;
            cout << "�����Ǵ����Ĳ�Ʒ��" << endl;
            while (getline(orderFile, line)) {
                istringstream iss(line);
                int tableNumber;
                string dishName;
                int quantity;
                int dishStatus;
                double dishPrice;
                iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice;
                if (dishStatus == 0 ) {
                    cout << "���ţ�" << tableNumber << " ��Ʒ��" << dishName << " ������" << quantity << " ���ۣ�" << dishPrice << endl;
                    cout << "���� 'Y' ȷ����ɲˣ�������������";
                    string choice;
                    cin >> choice;
                    // ��֤�û�����
                    if (choice == "Y" || choice == "y") {
                        dishStatus = 1; //״̬��Ϊ1 
                        found = true;
                    }
                }
                tempFile << tableNumber << " " << dishName << " " << quantity << " " << dishStatus << " " << dishPrice << endl;
            }
            orderFile.close();
            tempFile.close();
            if (found) {
                // ɾ��ԭ�ļ�������ʱ�ļ�������Ϊԭ�ļ�
                if (remove("orders.txt")!= 0) {
                    cerr << "ɾ��ԭ�ļ�ʧ��" << endl;
                }
                if (rename("temp_orders.txt", "orders.txt")!= 0) {
                    cerr << "�������ļ�ʧ��" << endl;
                }
                cout << "������Ϣ�Ѹ��¡�" << endl;
            } else {
                // ɾ����ʱ�ļ�
                if (remove("temp_orders.txt")!= 0) {
                    cerr << "ɾ����ʱ�ļ�ʧ��" << endl;
                }
                cout << "û�г��˲�����" << endl;
            }
        } catch (const ios_base::failure& e) {
            cerr << "�ļ������з�������: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "�����쳣: " << e.what() << endl;
        }
        cout << "���롰���ء��Է��أ������������������˲���" << endl;
        string back;
        cin >> back;
        if (back == "����") {
        	chefMenu(); //���س�ʦ���� 
            done = true;
        }
    }
}

//3.��ʦ�鿴ͳ��
void chefViewStatistics() {
    ifstream orderFile("orders.txt");
    if (orderFile.is_open()) {
        string line;
        cout << "��������ɵĲ�Ʒͳ�ƣ�" << endl;
        cout << "   ��Ʒ����      ����     ״̬" << endl;
        while (getline(orderFile, line)) { //���ж�ȡ 
            istringstream iss(line);
            int tableNumber;
            string dishName;
            int quantity;
            int dishStatus;
            double dishPrice;//�������� 
            iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice;
            if (dishStatus !=0) {
                cout <<setw(8)<< dishName << setw(12) << quantity << setw(12) ;
                if(dishStatus==0)cout<<"������"<<endl;
                else if(dishStatus==1)cout<<"������"<<endl;
                else if(dishStatus==3)cout<<"�ѽ���"<<endl;
                
            }
        }
        orderFile.close();
    } else {
        cout << "�޷��򿪶����ļ�" << endl;
    }

    cout << "���롰���ء��Է���" << endl;
    string back;
    cin >> back;
    if (back == "����") {
        chefMenu(); //���س�ʦ�˵� 
    } else {
        chefViewStatistics();
    }
}

/////////����Ա
//����Ա��ϵͳ�˵� 
void serverSubsytemMenu(){
	system("cls");
	cout << "***************************************************" << endl;
    cout << "           ��ӭ����ϵ����Ա��ϵͳϵͳ              " << endl;
    cout << "***************************************************" << endl;
    cout << "*               1.Ϊ�˿͵��                      *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               2.Ϊ�˿ͼӲ�                      *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               3.����                            *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               4.�鿴�ѳ����嵥                  *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               5.�鿴δ�����嵥                  *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               6.��ӡСƱ                        *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               7.�鿴������Ϣ                    *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*               0.�˳������˵�                    *" << endl;
    cout << "***************************************************" << endl;
	int select;
	while(1){
		cin>>select;
		switch(select)
		{
			case 1:
				takeOrder(); //Ϊ�˿͵�� 
				break;
			case 2:
				addDishes(); //�Ӳ� 
				break;
			case 3:
				dishOut(); //���� 
				break;
			case 4:
				view_yichucai(); //�鿴�ѳ��� 
				break;
			case 5:
				view_weichucai();//�鿴δ���� 
				break;
			case 6:
				printTableReceipt(); //����Ա��ӡСƱ 
				break;
			case 7:
				viewTables(); 
				break; 
			case 0:
				 mainmenu();
				 break;
			default:
                cout << "�����ѡ����Ч�����������룡" <<endl;
                continue;
		}
	}
	
}


///2.�Ӳ˺���
void addDishes() {
    int tableNumber;
    cout << "������Ҫ�Ӳ˵����ţ�" << endl;
    cin >> tableNumber;
    // ��ʾ�����ѵ�Ĳ�Ʒ
    showOrderedDishes(tableNumber); //չʾ�����ѵ��Ʒ 
    // ��ʾ��Ʒ��Ϣ
    displayDishes();
    ofstream orderFile("orders.txt", ios::app);
    if (!orderFile.is_open()) {
        cout << "�޷����ļ�" << endl;
        return;
    }
    cout << "������Ҫ�ӵĲ�Ʒ��Ϣ�������ʽ����Ʒ���� ��Ʒ���������� ����ɡ� ������" << endl;
    string dishName;
    int quantity;
    while (true) {
        cin >> dishName;
        if (dishName == "���") {
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
            cout << "��Ʒ�����ڣ����������룡" << endl;
            continue;
        }
        orderFile << tableNumber << " " << dishName << " " << quantity << " 0 " << price << endl;
        cout << "�Ӳ˳ɹ���" << endl;
    }
    orderFile.close();
}
//3.���˺��� ���˺��˳����� 
void dishOut() {
    // �򿪶����ļ�����ʱ�ļ�
    ifstream orderFile("orders.txt");
    ofstream tempFile("temp_orders.txt");
    string line;
    bool found = false;
    cout << "�����Ǵ����˵Ĳ�Ʒ��" << endl;
    // ���ж�ȡ�����ļ�
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int tableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice; // �������۱���
        // �����н������š���Ʒ���ơ�������״̬�͵���
        iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice;
        // ����Ʒ״̬Ϊδ׼����׼����
        if ( dishStatus == 1) {
            cout << "���ţ�" << tableNumber << " ��Ʒ��" << dishName << " ������" << quantity << " ���ۣ�" << dishPrice << endl;
            cout << "���� 'Y' ȷ�ϳ��ˣ�������������";
            string choice;
            cin >> choice;
            if (choice == "Y" || choice == "y") {
                dishStatus = 2;  // ��״̬����Ϊ�����
                found = true;
            }
        }
        // �����º����Ϣд����ʱ�ļ� ���� ���� ���� ״̬ ����
        tempFile << tableNumber << " " << dishName << " " << quantity << " " << dishStatus << " " << dishPrice << endl;
    }
    orderFile.close();
    tempFile.close();
    // ���г��˲�����ɾ��ԭ�����ļ�������ʱ�ļ�������Ϊ�����ļ�
    if (found) {
        remove("orders.txt");//ɾ��ԭ�����ļ� 
        rename("temp_orders.txt", "orders.txt"); //�����µ��ļ� 
        cout << "������Ϣ�Ѹ��¡�" << endl;
    } else {
        remove("temp_orders.txt");
        cout << "û�г��˲�����" << endl;
    }
    exit(0);
}

//4.���ѳ����嵥
void view_yichucai() {
    ifstream orderFile("orders.txt");
    bool found = false;
    string line;
    cout << "�ѳ����嵥��" << endl;
    cout << "����       ��Ʒ����       ����         ����" << endl;
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int tableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice; // �����������ڴ洢����
        iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice; // ��ȡ������Ϣ
        if (dishStatus == 2||dishStatus == 3) {
            found = true;
            cout << tableNumber << setw(16) << dishName << setw(10) << quantity << setw(11) << dishPrice << endl;
        }
    }
    orderFile.close();
    if (!found) {
        cout << "û���ѳ��˵Ĳ�Ʒ��" << endl;
    }
    cout << "���롰���ء��Է��ط���Ա����" << endl;
    string back;
    cin >> back;
    if (back == "����") {
        serverSubsytemMenu(); //���ط���Ա���� 
    } else {
        view_yichucai();
    }
}

//5.�鿴δ�����嵥
void view_weichucai() {
    ifstream orderFile("orders.txt");
    bool found = false;
    string line;
    cout << "δ�����嵥��" << endl;
    cout << "����       ��Ʒ����        ����       ����" << endl;
    while (getline(orderFile, line)) {
        istringstream iss(line);
        int tableNumber;
        string dishName;
        int quantity;
        int dishStatus;
        double dishPrice; // �����������ڴ洢����
        iss >> tableNumber >> dishName >> quantity >> dishStatus >> dishPrice; // ���� 
        if (dishStatus == 0 || dishStatus == 1) {
            found = true;
            cout << tableNumber << setw(16) << dishName << setw(10) << quantity << setw(12) << dishPrice << endl;
        }
    }
    orderFile.close();
    if (!found) {
        cout << "û��δ���˵Ĳ�Ʒ��" << endl;
    }
    cout << "���롰���ء��Է��ط���Ա����" << endl;
    string back;
    cin >> back;
    if (back == "����") {
        serverSubsytemMenu(); //���ط���Ա���� 
    } else {
        view_weichucai();
    }
}

//6.����Ա��ӡСƱ
void printTableReceipt() {
    int tableNumber;
    cout << "������Ҫ��ӡСƱ�����ţ�" << endl;
    cin >> tableNumber;


    ifstream orderFile("orders.txt");
    if (!orderFile.is_open()) {
        cout << "�޷��򿪶����ļ�" << endl;
        return;
    }


    bool found = false;
    cout << "--------------------------- СƱ��Ϣ ---------------------------" << endl;
    cout << "���ţ�" << tableNumber << endl;
    cout << "     ��Ʒ����       ��Ʒ�۸�       ����" << endl;
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
        cout << "δ�ҵ������ŵĶ�����Ϣ" << endl;
    }
    cout << "--------------------------- ���� --------------------------------" << endl;
    exit(0); 
}


///////////////����Ա 
// ����Ա�˵�
void cashierMenu() {
    int choice;
    while (true) {
        cout << "***************************************************" << endl;
        cout << "                 ����Ա���ܲ˵�                " << endl;
        cout << "***************************************************" << endl;
        cout << "*        1.�����շ�        2.ͳ��                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*        3.�鿴ͳ��        4.�˳�                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "***************************************************" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            cashierSettlement(); //����Ա���� 
            break;
        case 2:
            cashierViewStatistics(); //����Աͳ�� 
            break;
        case 3:
            cashierViewStatistics();  //�鿴ͳ�� 
            break;
        case 4: 
            exit(0);
            break;
        default:
            cout << "��Ч��ѡ�����������룡" << endl;
            continue;
        }
        break;
    }
}

///1.����Ա�����շ�
void cashierSettlement() {
    int tableNumber;
    cout << "���������ţ�" << endl;
    cin >> tableNumber;

    // �洢����ɲ�Ʒ����Ϣ
    int completedDishCount = 0;
    string completedDishNames[MAX_DISHES];
    int completedDishQuantities[MAX_DISHES];
    double mo = 0; // �ܽ��

    // �� orders ���ҳ������ŵ�����ɲ�Ʒ
    ifstream orderFile("orders.txt");
    if (!orderFile.is_open()) {
        cout << "�޷��򿪶����ļ�" << endl;
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
        // ���� orders.txt ����Ϣ��ʽΪ ���� ��Ʒ���� ���� ��Ʒ״̬ ����
        if (iss >> storedTableNumber >> dishName >> quantity >> dishStatus >> dishPrice) {
            if (storedTableNumber == tableNumber && dishStatus == 2) {
                completedDishNames[completedDishCount] = dishName;
                completedDishQuantities[completedDishCount] = quantity;
                mo += dishPrice * quantity;
                completedDishCount++;

                // �洢�� sale �ṹ����
                sale[saleCount].salenumber[completedDishCount - 1] = completedDishCount;
                // ������Ʒ ID
                sale[saleCount].goodsid[completedDishCount - 1] = findGoodsIdByName(dishName);
                // ʹ�� strncpy �����ַ����� char ����
                strncpy(sale[saleCount].salename[completedDishCount - 1], dishName.c_str(), sizeof(sale[saleCount].salename[completedDishCount - 1]) - 1);
                sale[saleCount].salename[completedDishCount - 1][sizeof(sale[saleCount].salename[completedDishCount - 1]) - 1] = '\0';
                sale[saleCount].saledanjia[completedDishCount - 1] = dishPrice;
            }
        }
    }
    orderFile.close();

    // �������۵��ݺ�
    sale[saleCount].danju = saleCount + 1; // ���ݺ�����
    sale[saleCount].allmoney = mo;
    sale[saleCount].salenumberCount = completedDishCount;

    // ��ӡСƱ
    system("cls");
    cout << " " << endl;
    cout << "     ��ӭ����666������" << endl;
    system("color 70"); //���ĵ�ɫ 
    cout << "..................................." << endl;
    cout << "      ���ݺţ�" << saleSummaryCount << endl;
    cout << "      ���ڣ�";
    riqi();
    cout << "..................................." << endl;
    cout << "  ����           �� ��        ����       �ܽ��" << endl;
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
    cout << "      лл�ݹˣ���ӭ�´ι��٣�" << endl;

    // ����������ϸ���ļ�
    ofstream saleFile("sales_detail.txt", ios::app); // СƱ��ϸ�ļ�
    ofstream summaryFile("sales_summary.txt", ios::app); // СƱ��Ҫ�ļ�
    if (saleFile.is_open() && summaryFile.is_open()) {
        // ����СƱ��Ҫ��Ϣ
        summaryFile << saleSummaryCount << " " << mo << endl;

        // ����СƱ��ϸ��Ϣ
        for (int i = 0; i < completedDishCount; ++i) {
            saleFile << saleSummaryCount << " " << sale[saleCount].salename[i] << " " << sale[saleCount].saledanjia[i] << " " << completedDishQuantities[i] << endl;
        }
        saleFile.close();
        summaryFile.close();
    } else {
        cout << "�޷����ļ�" << endl;
    }

    // ���¶���״̬
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
                    dishStatus = 3; // �������ŵĶ���״̬��Ϊ 3���ѽ��ˣ�
                }
                tempFile << storedTableNumber << " " << dishName << " " << quantity << " " << dishStatus << " " << dishPrice << endl;
            }
        }
        orderFile2.close();
        tempFile.close();
        remove("orders.txt");
        rename("temp_orders.txt", "orders.txt");
    }

    // ����Ӧ����״̬��Ϊ 0 ����ʱ����Ϊ "NULL" �Լ����û�����Ϊ "NULL"
    bool foundTable = false;
    for (int i = 0; i < tableCount; ++i) {
        if (tables[i].number == tableNumber) {
            tables[i].use = 0; // ������״̬��Ϊ 0�����У�
            tables[i].reservationTime = "��"; // ��ʱ����Ϊ "NULL"
            tables[i].userName = "��"; // ���û�����Ϊ "NULL"
            foundTable = true;
            break;
        }
    }
    saveTables();
    if (!foundTable) {
        cout << "δ�ҵ������Ŷ�Ӧ�Ĳ�����Ϣ��" << endl;
    }

    // ��ӡ������Ϣ
    cout << "������Ϣ��" << endl;
    cout << "������Ʒ����������" << completedDishCount << endl;
    cout << "������Ʒ��" << mo << endl;

    // ��ӡ orders ��״̬Ϊ 1 �Ĳ�Ʒ��Ϣ
    ifstream orderFile3("orders.txt");
    if (orderFile3.is_open()) {
        cout << "������״̬Ϊ 0 or 1 �Ĳ�Ʒ��Ϣ��" << endl;
        cout << "����    ��Ʒ����    ����    ״̬" << endl;
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
					if(dishStatus==0)cout<<"δ����" << endl;
					if(dishStatus==1)cout<<"δ�ϲ�" << endl;
                }
            }
        }
        orderFile3.close();
    } else {
        cout << "�޷��򿪶����ļ�" << endl;
    }

    cout << "�������֡�1���Է���" << endl;
    string nm, mmmm = "1";
    while (true) {
        cin >> nm;
        if (nm == mmmm) {
            cashierMenu();
            break;
        } else {
            cout << "����������" << endl;
        }
    }
    saleCount++;

    // ���������Ϣ
    saveTables();
}

////2.����Աͳ�ƣ�δʹ�� 
void cashierStatistics() {
    int completedDishCount[MAX_DISHES] = {0}; // �洢ÿ������ɲ�Ʒ������
    double completedDishAmount[MAX_DISHES] = {0}; // �洢ÿ������ɲ�Ʒ���ܽ��
    int pendingDishCount[MAX_DISHES] = {0}; // �洢ÿ�ִ�����Ʒ������
    double pendingDishAmount[MAX_DISHES] = {0}; // �洢ÿ�ִ�����Ʒ���ܽ��
    // �򿪶����ļ�
    ifstream orderFile("orders.txt");
    if (!orderFile.is_open()) {
        cout << "�޷��򿪶����ļ�" << endl;
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
        // ���� order.txt ����Ϣ��ʽΪ ���� ��Ʒ���� ���� ��Ʒ״̬ ��Ʒ�۸�
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
                // ����Ӹ����ƵĴ������߼���������ʱ�������ʾ��Ϣ
                cerr << "��Ʒ " << dishName << " δ�� dishes �������ҵ�" << endl;
            }
        } else {
            // ����������󣬿���Ӹ����ƵĴ������߼�
            cerr << "���������ļ��г���" << line << endl;
        }
    }
    orderFile.close();


    cout << "����ͳ����Ϣ��" << endl;


    // �������ɲ�Ʒ����
    cout << "������Ʒ������" << endl;
    for (int i = 0; i < dishCount; i++) {
        if (completedDishCount[i] > 0) {
            cout << dishes[i].dishName << ": " << completedDishCount[i] << endl;
        }
    }


    // �������ɲ�Ʒ���
    cout << "������Ʒ��" << endl;
    for (int i = 0; i < dishCount; i++) {
        if (completedDishAmount[i] > 0) {
            cout << dishes[i].dishName << ": " << fixed << setprecision(2) << completedDishAmount[i] << endl;
        }
    }


    // ���������Ʒ����
    cout << "������Ʒ������" << endl;
    for (int i = 0; i < dishCount; i++) {
        if (pendingDishCount[i] > 0) {
            cout << dishes[i].dishName << ": " << pendingDishCount[i] << endl;
        }
    }


    // ���������Ʒ���
    cout << "������Ʒ��" << endl;
    for (int i = 0; i < dishCount; i++) {
        if (pendingDishAmount[i] > 0) {
            cout << dishes[i].dishName << ": " << fixed << setprecision(2) << pendingDishAmount[i] << endl;
        }
    }


    // �Ľ������߼�
    cout << "�������֡�1���Է���" << endl;
    string input;
    while (true) {
        cin >> input;
        if (input == "1") {
            cashierMenu();
            break;
        } else {
            cout << "����������" << endl;
        }
    }
}

//3.�����鿴ͳ��
void cashierViewStatistics() {
    int completedDishCount[MAX_GOODS] = {0};


    // �򿪶����ļ�
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
            // ���� order.txt ����Ϣ��ʽΪ ���� ��Ʒ���� ���� ��Ʒ״̬ ��Ʒ�۸�
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
                        // ����Ӹ����ƵĴ������߼���������ʱ�������ʾ��Ϣ
                        cerr << "��Ʒ " << dishName << " δ�� goods �������ҵ�" << endl;
                    }
                }
            } else {
                // ����������󣬿���Ӹ����ƵĴ������߼�
                cerr << "���������ļ��г���" << line << endl;
            }
        }
        orderFile.close();
    } else {
        cout << "�޷��򿪶����ļ�" << endl;
        return;
    }


    cout << "��������ɲ�Ʒͳ�ƣ�����Ƕȣ���" << endl;
    cout << "    ��Ʒ����           ����         �ܽ��" << endl;
    for (int i = 0; i < goodsCount; i++) {
        if (completedDishCount[i] > 0) {
            double totalAmount = goods[i].price * completedDishCount[i];
            cout << setw(8) << goods[i].name << setw(12) << completedDishCount[i] << setw(12) << fixed << setprecision(2) << totalAmount << endl;
        }
    }


    cout << "�������֡�1���Է���" << endl;
    string nm, mmmm = "1";
    while (true) {
        cin >> nm;
        if (nm == mmmm) {
            cashierMenu();
            break;
        } else {
            cout << "����������" << endl;
        }
    }
}



/////////////////ϵͳ����Ա 
// ����Ա 
void manageMenu() {
	system("cls");
    while (true) {
        cout << "***************************************************" << endl;
        cout << "              ��ӭ����ϵͳ����Աϵͳ               " << endl;
        cout << "***************************************************" << endl;
        cout << "*              1.����û���Ϣ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              2.�޸��û���Ϣ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              3.�鿴�û���Ϣ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              4.��Ӳ�Ʒ��Ϣ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              5.ɾ����Ʒ��Ϣ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              6.���Ĳ�Ʒ��Ϣ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              7.�鿴��Ʒ��Ϣ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              0.�˳������˵�                     *" << endl;
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
            cout << "��Ч��ѡ�����������룡" << endl;
            continue;
        }
        system("pause");
        manageMenu();
    }
}

// 1.����û���Ϣ
void addUserInformation() {
    string username, password, role;
    cout << "������Ҫ��ӵ��û���Ϣ(���� Q ʱ�˳������������������������ Q �˳�)" << endl;
    cout << "�����ʽ���û��� ���� ��ɫ" << endl;
    while (true) {
        cin >> username;
        if (username == "Q") {
            cout << "****��ӳɹ��������˳�****" << endl;
            saveUsers();
            break;
        }
        cin >> password >> role;
        id[userCount++] = {username, password, role};
    }
}


//2. �޸��û���Ϣ
void changeUserInformation() {
    string targetUsername;
    cout << "������Ҫ�޸ĵ��û����û�����" << endl;
    cin >> targetUsername;
    bool found = false;
    for (int i = 0; i < userCount; i++) {
        if (id[i].usname == targetUsername) {
            found = true;
            cout << "���ҵ����û����������µ��û���Ϣ�������ʽ���û��� ���� ��ɫ����" << endl;
            string newUsername, newPassword, newRole;
            cin >> newUsername >> newPassword >> newRole;
            id[i].usname = newUsername;
            id[i].password = newPassword;
            id[i].role = newRole;
            saveUsers();   //���浽�ļ��� (���ú��� 
            cout << "�û���Ϣ�޸ĳɹ���" << endl;
            break;
        }
    }
    if (!found) {
        cout << "δ���ҵ�Ҫ�޸ĵ��û�����ȷ���Ƿ���������" << endl;
        manageMenu();//���ص�ϵͳ����Ա���� 
    }
}

//3.�鿴���е��û���Ϣ���ϰ�� ����Աδ�ֿ����� 
void viewUserInformation() {
    cout << "*************************ȫ���û���Ϣ����*************************" << endl;
    cout << "           �û���        ����        ��ɫ" << endl;
    for (int i = 0; i < userCount; i++) {
        cout <<setw(18)<< id[i].usname << setw(12) << id[i].password << setw(12) << id[i].role << endl;
    }
    cout << "*******************************************************************" << endl;
    system("pause");//������ͣ 
    exit(0); 
}

//4.// �����Ʒ�˵�
void addGoodsMenu() {
    string name, category;
    double price;
    char choice;
    do {
        // �Զ����� id����������Ϊ goodsCount
        int id = goodsCount;
        cout << "��������Ʒ�����ƣ�";
        cin >> name;
        cout << "��������Ʒ�����";
        cin >> category;
        cout << "��������Ʒ�ļ۸�";
        cin >> price;

        // ����Ʒ��Ϣ��ӵ� goods ������
        if (goodsCount < MAX_GOODS) {
            goods[goodsCount].id = id+1;
            goods[goodsCount].name = name;
            goods[goodsCount].category = category;
            goods[goodsCount].price = price;
            goodsCount++;

            // ������Ʒ��Ϣ���ļ�
            saveGoods();
        } else {
            cout << "��Ʒ�����Ѵﵽ���ޣ��޷��������Ʒ��" << endl;
        }

        cout << "�Ƿ���������Ʒ��(Y/N) ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
}


//6.�޸Ĳ�Ʒ��Ϣ����
void changeGoods() {
    if (goodsCount == 0) {
        cout << "��ǰû�в�Ʒ�ɹ��޸ġ�" << endl;
        return;
    }
    string name;
    cout << "������Ҫ�޸ĵĲ�Ʒ���ƣ�" << endl;
    cin >> name;
    bool found = false;
    for (int i = 0; i < goodsCount; ++i) {
        if (goods[i].name == name) {
            found = true;
            // ���ԭ�еĲ�Ʒ��Ϣ
            cout << "ԭ�еĲ�Ʒ��Ϣ���£�" << endl;
            cout << "��Ʒ���ƣ�" << goods[i].name << endl;
            cout << "��Ʒ���" << goods[i].category << endl;
            cout << "��Ʒ�۸�" << goods[i].price << endl;
            string newName, newCategory;
            double newPrice;
            cout << "�������µĲ�Ʒ���ƣ�" << endl;
            cin >> newName;
            cout << "�������µĲ�Ʒ���" << endl;
            cin >> newCategory;
            cout << "�������µĲ�Ʒ�۸�" << endl;
            cin >> newPrice;
            goods[i].name = newName;
            goods[i].category = newCategory;
            goods[i].price = newPrice;
            cout << "��Ʒ " << name << " ���޸ĳɹ���" << endl;
            break;
        }
    }
    if (!found) {
        cout << "δ�ҵ���Ϊ " << name << " �Ĳ�Ʒ��" << endl;
        return;
    }
    // ������º�Ĳ�Ʒ��Ϣ���ļ�
    saveGoods();
} 



/////////////�ϰ�
// �ϰ�˵�
void bossMenu() {
	system("cls");
    while (true) {
        cout << "***************************************************" << endl;
        cout << "              ��ӭ��������ϰ���ϵͳ               " << endl;
        cout << "***************************************************" << endl;
        cout << "*              1.�鿴�������������               *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              2.�鿴��Ʒ�������                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              3.�鿴���������δ���             *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              4.�鿴��λʹ�����                 *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              5.�鿴Ա����Ϣ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              6.�鿴�˵�                         *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              7.���뵥�ݺŲ�������               *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              8.ɾ��ĳ����Ʒ                     *" << endl;
        cout << "*                                                 *" << endl;
        cout << "*              0.�˳������˵�                     *" << endl;
        cout << "***************************************************" << endl;
        cout<<"��ѡ��"<<endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
        	shouru(); //�鿴������������� ����������СƱ��Ҫ������ 
         	break;
        case 2:
        	cashierViewStatistics();//����ʹ���˺�����һ���ĺ��� (�е����� 
        	break;
        case 3:
        	lookall();    //
            break;
        case 4:
        	viewTables();    //�鿴��λʹ�����
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
            cout<<"�������룡����"<<endl; 
            cout<<"����������:"<<endl;
            continue;
        }
        break;
    }
}

//1.�������������
void shouru() {
    double totalIncome = 0;

    // �����۸�Ҫ�ļ�
    ifstream salesSummaryFile("sales_summary.txt");
    if (salesSummaryFile.is_open()) {
        string line;

        // ���ж�ȡ�ļ�
        while (getline(salesSummaryFile, line)) {
            istringstream iss(line);
            int danju;  // ���ݺ�
            double allmoney;  // �õ��ݵ��ܽ��

            // �ӵ�ǰ�н������ݺź��ܽ��
            if (iss >> danju >> allmoney) {
                // ���õ��ݵ��ܽ���ۼӵ�������
                totalIncome += allmoney;
            } else {
                // ����ʧ��ʱ���������Ϣ
                cerr << "�������۸�Ҫ�ļ��г���" << line << endl;
            }
        }
        salesSummaryFile.close();
    } else {
        cout << "�޷������۸�Ҫ�ļ�" << endl;
        return;
    }

    // ������������룬������λС��
    cout << "���������룺" << fixed << setprecision(2) << totalIncome << endl;
}


//3.�鿴���������δ���
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
            // ���� orders.txt ����Ϣ��ʽΪ ���� ��Ʒ���� ���� ��Ʒ״̬ ��Ʒ�۸�
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
        cout << "�޷��򿪶����ļ�" << endl;
        return;
    }


    cout << "����ɲ�Ʒ������" << completedDishCount << " ����ɲ�Ʒ��" << fixed << setprecision(2) << completedDishAmount << endl;
    cout << "δ��ɲ�Ʒ������" << pendingDishCount << " δ��ɲ�Ʒ��" << fixed << setprecision(2) << pendingDishAmount << endl;


    // ���δ��ɲ�Ʒ�����ƺ�����
    if (pendingDishIndex > 0) {
        cout << "δ��ɲ�Ʒ��Ϣ��" << endl;
        cout << "��Ʒ����    ����" << endl;
        for (int i = 0; i < pendingDishIndex; ++i) {
            cout << setw(12) << pendingDishNames[i] << setw(12) << pendingDishQuantities[i] << endl;
        }
    }
}

// 7.�ϰ���ݵ��ݺŲ���СƱ��ϸ��Ϣ
void bossSearchByDanju() {
    int inputDanju;
    cout << "�����뵥�ݺ�: ";
    cin >> inputDanju;


    ifstream detailFile("sales_detail.txt");
    if (!detailFile.is_open()) {
        cout << "�޷���������ϸ�ļ���" << endl;
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
                cout << "��Ʒ����: " << detail.dishName << " ����: " << detail.quantity << " ����: " << fixed << setprecision(2) << detail.dishPrice << endl;
            }
        } else {
            cout << "����������ϸ��Ϣ�г���" << endl;
        }
    }
    detailFile.close();


    if (!found) {
        cout << "δ�ҵ��õ��ݺŶ�Ӧ��������Ϣ��" << endl;
    }

    cout << "�������֡�1���Է���" << endl;
    string input;
    while (true) {
        cin >> input;
        if (input == "1") {
            bossMenu();
            break;
        } else {
            cout << "����������" << endl;
        }
    }
} 

//8. ɾ����Ʒ����
void deleteGoods() {
    if (goodsCount == 0) {
        cout << "��ǰû�в�Ʒ�ɹ�ɾ����" << endl;
        return;
    }
    string nameToDelete;
    cout << "������Ҫɾ���Ĳ�Ʒ���ƣ�" << endl;
    cin >> nameToDelete;
    bool found = false;
    for (int i = 0; i < goodsCount; ++i) {
        if (goods[i].name == nameToDelete) {
            found = true;
            for (int j = i; j < goodsCount - 1; ++j) {
                goods[j] = goods[j + 1];
            }
            goodsCount--;
            cout << "��Ʒ " << nameToDelete << " ��ɾ���ɹ���" << endl;
            break;
        }
    }
    if (!found) {
        cout << "δ�ҵ���Ϊ " << nameToDelete << " �Ĳ�Ʒ��" << endl;
    }
    // ������Ʒ�� id
    for (int i = 0; i < goodsCount; ++i) {
        goods[i].id = i + 1;
    }
    saveGoods();
}

int main() {
    // ��������
   
    loadSaleSummary(); // ����СƱ��Ҫ��Ϣ
    loadSaleDetail();// ����СƱ��ϸ��Ϣ
    loadGoods(); //���ṩ��Ʒ��Ϣ 
    loadTables();//���ز�����Ϣ 
    
    loadUsers(); 
    mainmenu();
    return 0;
}

