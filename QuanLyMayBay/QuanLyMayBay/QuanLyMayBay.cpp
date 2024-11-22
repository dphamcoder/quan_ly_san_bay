#include <iostream>
#include <windows.h>
#include <cstdlib> // để sử dụng system("cls")
#include <conio.h> // Để sử dụng hàm _getch() trên Windows ( va cai kbhit())
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include "Declare.h"

using namespace std;


#pragma region KhaiBao
LinkedList<ChuyenBay> dsChuyenBay;
LinkedList<KhachHang> dsKhachHang;
LinkedList<MayBay> dsMayBay;
#pragma endregion

/* Chức năng số 3*/
void inputPassword(string& password) { // Tham chiếu & để cập nhật chuỗi password
    char ch;
    // Nhập từng ký tự và hiển thị dấu *
    while ((ch = _getch()) != '\r') { // '\r' là Enter
        if (ch == '\b') { // Xử lý phím Backspace
            if (!password.empty()) {
                cout << "\b \b"; // Xóa ký tự * vừa nhập
                password.pop_back();
            }
        }
        else {
            password += ch;
            cout << '*'; // In dấu * thay vì ký tự thật
        }
    }
    cout << endl;
}
bool functionDangNhap() {
    int timeSaiPass = 0;
    string user, password;
    while (timeSaiPass <= 2) {
        system("cls");
        setColor(14);
        cout << R"(          **************************   )" << endl;
        cout << "          *"; setColor(10); cout << "   ĐĂNG NHẬP HỆ THỐNG   "; setColor(14); cout << "*" << endl;
        cout << R"(          **************************   )" << endl;
    if (GetAsyncKeyState(VK_ESCAPE)) {
            setColor(7);
            cout << "Thoát khỏi màn hình đăng nhập !" << endl;
            system("pause");
            return false;  // Thoát nếu nhấn ESC
        }
        gotoXY(10, 3);
        setColor(2); cout << "User : ";

        gotoXY(10, 5);
        setColor(2); cout << "Password : ";
        gotoXY(22, 3);
        setColor(7); cin >> user;
        gotoXY(22, 5);
        setColor(7); inputPassword(password);
        cout << endl;
        if (user == "admin" && password == "123456") {
            cout << "Đăng nhập thành công!" << endl;
            return true;
        } else {
            timeSaiPass++;
            if (timeSaiPass > 2) {
                setColor(4);
                cout << "Quá số lần đăng nhập sai, dăng nhập thất bại ." << endl;
                setColor(7);
                system("pause");
                return false;
            }
            setColor(4);
            cout << "Tên người dùng hoặc mật khẩu không chính xác !" << endl;
            setColor(7);
            cout << "Nhấn esc để thoát khỏi màn hình đăng nhập"<<endl;
            system("pause");
        }
    }
    return false;
}
/****************/




/*Chức năng số 1*/
void readFileKhachHang() {
    system("cls");
    fstream file("KhachHang.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        exit;
    }
    string line;
    vector<string> currentline;
    vector<vector<string>> matrixlines;
    stringstream ss(line);
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> currentLine;
        while (getline(ss, item, ';')) {
            currentLine.push_back(item);
        }
        matrixlines.push_back(currentLine);
    }
    for (vector<string> line : matrixlines) {
        KhachHang khtemp;
        if (line.size() >= 3) {
            khtemp.CMND = line[0];
            khtemp.hoTen = line[1];
            khtemp.soThuTu = stoi(line[2]);
            dsKhachHang.addTail(khtemp);
        }
    }
}

void readFileChuyenBay() {
    system("cls");
    ifstream file("ChuyenBay.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        exit;
    }
    string line;
    vector<string> currentline;
    vector<vector<string>> matrixlines;
    stringstream ss(line);
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> currentLine;
        while (getline(ss, item, ';')) {
            currentLine.push_back(item);
        }
        matrixlines.push_back(currentLine);
    }
    for (vector<string> line : matrixlines) {
        ChuyenBay cbtemp;
        if (line.size() >= 7) {
            cbtemp.maChuyenBay = line[0];
            cbtemp.soHieu = line[1];
            cbtemp.ngayKhoiHanh = line[2];
            cbtemp.sanBayDen = line[3];
            cbtemp.trangThai = stoi(line[4]); // stoi() string to int
            cbtemp.danhsachVe.push_back(line[5]);
            cbtemp.danhsachGheTrong.push_back(line[6]);
            dsChuyenBay.addTail(cbtemp);
        }
    }
}
void writeFileChuyenBay() {
    ofstream file("Admin.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        exit;
    }
    file << dsChuyenBay.writeFile();
}
bool functionDSChuyenBay() {
    dsChuyenBay.clear();
    readFileChuyenBay();
    dsChuyenBay.display();
    cout << endl << "Nhấn nút bất kì để quay về, nhấn nút esc để thoát .";
    char ch = _getch();
    if (ch != 27) {
        return false;
    }
}
/******************/

/* Chức nang số 2*/
bool functionDatVe() {
    system("cls");
    setColor(14);
    cout << R"(          **************************   )" << endl;
    cout << "          *"; setColor(10); cout << "         ĐẶT VÉ         "; setColor(14); cout << "*" << endl;
    cout << R"(          **************************   )" << endl;
    string hoten;
    string cmnd;
    string machuyenbay;

    setColor(2);
    gotoXY(10, 3);
    cout << "Họ tên khách hàng : ";

    gotoXY(10, 5);
    cout << "Số CMND / CCCD : ";

    gotoXY(10, 7);
    cout << "Mã chuyến bay : ";

    setColor(7);
    gotoXY(30, 3);
    getline(cin, hoten);

    gotoXY(30, 5);
    cin >> cmnd;

    gotoXY(30, 7);
    cin >> machuyenbay;

    cout << " INPUT: " << hoten << ";" << cmnd << ";" << machuyenbay << endl;

    cout << endl << "Nhấn nút bất kì để quay về, nhấn nút esc để thoát .";
    char ch = _getch();
    if (ch != 27) {
        return false;
    }
}
/* Chức nang số 2 */

/* Chức nang menu */
void displayMenu(int option, const string menu[], int menuSize) {
    system("cls");
    imageTitle();
    cout << endl;
    for (int i = 0; i < menuSize; i++) {
        if (i == option) {
            setColor(10);
            cout << "> " << menu[i] << " <" << endl;
            setColor(7);
        }
        else {
            cout << "  " << menu[i] << endl;
        }
    }
}
int menu() {
    string menu[] = { " 1. Hiển thị danh sách chuyến bay ", " 2. Đặt vé máy bay ", " 3. Quản lý chuyến bay ", " 4. Thoát " };
    int menuSize = size(menu);
    int option = 0;
    while (true) {
        displayMenu(option, menu, menuSize);

        char key = _getch();

        if (key == 72) { // Arrow up key
            option = (option - 1 + menuSize) % menuSize; // Move up, wrapping around
        }
        else if (key == 80) { // Arrow down key
            option = (option + 1) % menuSize; // Move down, wrapping around
        }
        else if (key == 13) { // enter key
            if (option == menuSize) {
                cout << "Exiting..." << endl;
                break;
            }
            else {
                cout << "You selected: " << menu[option] << endl;
                return option + 1;
            }
        }
    }
}


void functionMenu() {
    int c = menu();
    if (c == 1) {
        if (functionDSChuyenBay() == false) functionMenu();
        else cout << "Thoat";
    }
    else if (c == 2) {
        if (functionDatVe() == false) functionMenu();
        cout << "Thanh cong! ";
    }
    else if (c == 3) {
        if (functionDangNhap() == false) functionMenu();
        cout << "Thanh cong! ";
    }
    else return;
}
/* Chức nang menu */

int main() {
    readFileChuyenBay();
    functionMenu();
    return 0;
}

