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
void createOrder(Restaurant &r) {

    if (r.orderCount >= 100) {
        cout << "Danh sach don hang da day!\n";
        return;
    }

    cin.ignore();

    Order &o = r.orders[r.orderCount];

    cout << "\n========== TAO DON HANG ==========\n";

    cout << "Ma don hang: ";
    getline(cin, o.id);

    cout << "Ten khach hang: ";
    getline(cin, o.customerName);

    cout << "Dia chi giao hang: ";
    getline(cin, o.address);

    string foodId;

    cout << "Nhap ma mon muon dat: ";
    getline(cin, foodId);

    // Tim mon
    int foodIndex = -1;

    for (int i = 0; i < r.foodCount; i++) {
        if (r.foods[i].id == foodId) {
            foodIndex = i;
            break;
        }
    }

    if (foodIndex == -1) {
        cout << "Khong tim thay mon an!\n";
        return;
    }

    cout << "Mon: " << r.foods[foodIndex].name << endl;

    cout << "Nhap so luong: ";
    cin >> o.quantity;

    // Kiem tra so luong
    if (o.quantity <= 0) {
        cout << "So luong khong hop le!\n";
        return;
    }

    if (o.quantity > r.foods[foodIndex].quantity) {
        cout << "Khong du so luong mon an!\n";
        cout << "Con lai: " << r.foods[foodIndex].quantity << endl;
        return;
    }

    // Gan mon an vao don hang
    o.food = r.foods[foodIndex];

    // Tru kho
    r.foods[foodIndex].quantity -= o.quantity;

    // Trang thai ban dau
    o.status = "Cho xu ly";

    r.orderCount++;

    cout << "\nTao don hang thanh cong!\n";
}
void checkFood(const Restaurant &r) {

    cin.ignore();

    string id;

    cout << "\n===== KIEM TRA MON AN =====\n";
    cout << "Nhap ma mon: ";
    getline(cin, id);

    for (int i = 0; i < r.foodCount; i++) {

        if (r.foods[i].id == id) {

            cout << "\nMon an: " << r.foods[i].name << endl;
            cout << "So luong con lai: "
                 << r.foods[i].quantity << endl;

            if (r.foods[i].quantity > 0)
                cout << "Trang thai: CON MON\n";
            else
                cout << "Trang thai: HET MON\n";

            return;
        }
    }

    cout << "Khong tim thay mon an!\n";
}
double calculateTotal(const Order &o) {
    return o.food.price * o.quantity;
}
void displayOrder(const Restaurant &r) {

    if (r.orderCount == 0) {
        cout << "Chua co don hang!\n";
        return;
    }

    cout << "\n================ CHI TIET DON HANG ================\n";

    for (int i = 0; i < r.orderCount; i++) {

        const Order &o = r.orders[i];

        cout << "\nMa don hang: " << o.id;
        cout << "\nKhach hang: " << o.customerName;
        cout << "\nDia chi: " << o.address;
        cout << "\nMon an: " << o.food.name;
        cout << "\nDon gia: " << fixed << setprecision(0)
             << o.food.price;
        cout << "\nSo luong: " << o.quantity;

        cout << "\nTong tien: "
             << calculateTotal(o);

        cout << "\nTrang thai: " << o.status;

        cout << "\n--------------------------------------\n";
    }
}
void updateOrderStatus(Restaurant &r) {

    cin.ignore();

    string id;

    cout << "\n===== CAP NHAT TRANG THAI =====\n";

    cout << "Nhap ma don hang: ";
    getline(cin, id);

    for (int i = 0; i < r.orderCount; i++) {

        if (r.orders[i].id == id) {

            cout << "\nTrang thai hien tai: "
                 << r.orders[i].status << endl;

            cout << "\n1. Cho xu ly";
            cout << "\n2. Dang giao";
            cout << "\n3. Da giao";
            cout << "\n4. Da huy";

            int choice;

            cout << "\nLua chon: ";
            cin >> choice;

            switch (choice) {

                case 1:
                    r.orders[i].status = "Cho xu ly";
                    break;

                case 2:
                    r.orders[i].status = "Dang giao";
                    break;

                case 3:
                    r.orders[i].status = "Da giao";
                    break;

                case 4:
                    r.orders[i].status = "Da huy";
                    break;

                default:
                    cout << "Lua chon khong hop le!\n";
                    return;
            }

            cout << "Cap nhat thanh cong!\n";
            return;
        }
    }

    cout << "Khong tim thay don hang!\n";
}
