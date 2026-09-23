#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct Food {
    string id;          
    string name;        
    double price;      
    int quantity;       
};

struct Order {
    string id;          
    string customerName;
    string address;     
    Food food;          
    int quantity;       
    string status;      
};

struct Restaurant {
    string name;        
    string address;     
    string phone;       

    Food foods[100];    
    int foodCount;

    Order orders[100];  
    int orderCount;
};

void inputRestaurant(Restaurant &r) {
    cin.ignore();

    cout << "\n===== NHAP THONG TIN CUA HANG =====\n";

    cout << "Ten cua hang: ";
    getline(cin, r.name);

    cout << "Dia chi: ";
    getline(cin, r.address);

    cout << "So dien thoai: ";
    getline(cin, r.phone);

    r.foodCount = 0;
    r.orderCount = 0;

    cout << "\nDa nhap thong tin cua hang!\n";
}
void addFood(Restaurant &r) {
    if (r.foodCount >= 100) {
        cout << "Danh sach mon an da day!\n";
        return;
    }

    Food &f = r.foods[r.foodCount];

    cout << "\n===== THEM MON AN =====\n";

    cin.ignore();

    cout << "Ma mon: ";
    getline(cin, f.id);

    cout << "Ten mon: ";
    getline(cin, f.name);

    cout << "Don gia: ";
    cin >> f.price;

    cout << "So luong: ";
    cin >> f.quantity;

    r.foodCount++;

    cout << "\nThem mon an thanh cong!\n";
}

void displayFoods(const Restaurant &r) {
    cout << "\n================ DANH SACH MON AN ================\n";

    if (r.foodCount == 0) {
        cout << "Chua co mon an nao!\n";
        return;
    }

    cout << left
         << setw(10) << "Ma"
         << setw(25) << "Ten mon"
         << setw(15) << "Don gia"
         << setw(15) << "So luong" << endl;

    cout << string(65, '-') << endl;

    for (int i = 0; i < r.foodCount; i++) {
        cout << left
             << setw(10) << r.foods[i].id
             << setw(25) << r.foods[i].name
             << setw(15) << fixed << setprecision(0) << r.foods[i].price
             << setw(15) << r.foods[i].quantity
             << endl;
    }
}
void searchFood(const Restaurant &r) {
    if (r.foodCount == 0) {
        cout << "Chua co mon an!\n";
        return;
    }

    int choice;

    cout << "\n===== TIM MON AN =====\n";
    cout << "1. Tim theo ten\n";
    cout << "2. Tim theo gia\n";
    cout << "Lua chon: ";
    cin >> choice;

    if (choice == 1) {
        cin.ignore();

        string keyword;
        cout << "Nhap ten mon can tim: ";
        getline(cin, keyword);

        bool found = false;

        for (int i = 0; i < r.foodCount; i++) {
            if (r.foods[i].name.find(keyword) != string::npos) {
                cout << "\nMa mon: " << r.foods[i].id;
                cout << "\nTen mon: " << r.foods[i].name;
                cout << "\nDon gia: " << r.foods[i].price;
                cout << "\nSo luong: " << r.foods[i].quantity << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "Khong tim thay mon an!\n";
        }
    }
    else if (choice == 2) {
        double price;

        cout << "Nhap gia can tim: ";
        cin >> price;

        bool found = false;

        for (int i = 0; i < r.foodCount; i++) {
            if (r.foods[i].price == price) {
                cout << "\nMa mon: " << r.foods[i].id;
                cout << "\nTen mon: " << r.foods[i].name;
                cout << "\nDon gia: " << r.foods[i].price;
                cout << "\nSo luong: " << r.foods[i].quantity << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "Khong tim thay mon co gia nay!\n";
        }
    }
    else {
        cout << "Lua chon khong hop le!\n";
    }
}
void updateFood(Restaurant &r) {
    cin.ignore();

    string id;

    cout << "\n===== CAP NHAT MON AN =====\n";
    cout << "Nhap ma mon: ";
    getline(cin, id);

    for (int i = 0; i < r.foodCount; i++) {

        if (r.foods[i].id == id) {

            cout << "Mon an: " << r.foods[i].name << endl;

            cout << "Gia moi: ";
            cin >> r.foods[i].price;

            cout << "So luong moi: ";
            cin >> r.foods[i].quantity;

            cout << "Cap nhat thanh cong!\n";
            return;
        }
    }

    cout << "Khong tim thay mon co ma " << id << "!\n";
}