#pragma once
#include <iostream>
#include <windows.h>
#include <cstdlib> // để sử dụng system("cls")
#include <conio.h> // Để sử dụng hàm _getch() trên Windows
#include <ctime>
#include <vector>

using namespace std;

void setColor(int color) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
}
void gotoXY(int x, int y)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

#pragma region Images
void imageTitle() {
    SetConsoleOutputCP(CP_UTF8); // Thiết lập mã hóa UTF-8

    // In từng phần của chữ nghệ thuật với màu sắc khác nhau
    setColor(9); // Màu xanh dương
    cout << "        ████  █   █  █   █  ███  █   █  ███     █████ ████  █  █   █  █   █" << endl;
    cout << "       █      █   █  █   █ █   █ █   █ █          █   █   █ █  ██  █  █   █" << endl;

    setColor(10); // Màu xanh lá
    cout << "       █      █████  █   █ █   █ █████ █  ██      █   ████  █  █ █ █  █████" << endl;
    cout << "       █      █   █  █   █ █   █ █   █ █   █      █   █ █   █  █  ██  █   █" << endl;

    setColor(12); // Màu đỏ
    cout << "        ████  █   █   ███   ███  █   █  ███       █   █  ██ █  █   █  █   █" << endl;
    cout << endl;

    setColor(14); // Màu vàng
    cout << " ███  █   █   ███   █   █     █     █   █     ████   ███   █   █    ████    ███   █   █" << endl;
    cout << "█   █ █   █  █   █  ██  █     █      █ █     █      █   █  ██  █    █   █  █   █   █ █ " << endl;

    setColor(11); // Màu xanh lam nhạt
    cout << "█   █ █   █  █████  █ █ █     █       █       ███   █████  █ █ █    ████   █████    █  " << endl;
    cout << "█  ██ █   █  █   █  █  ██     █       █          █  █   █  █  ██    █   █  █   █    █  " << endl;

    setColor(13); // Màu hồng
    cout << " ████  ███   █   █  █   █     █████   █      ████   █   █  █   █    ████   █   █    █  " << endl;
    cout << endl;

    // Đặt lại màu sắc về mặc định
    setColor(7);
}
#pragma endregion


#pragma region Data
struct MayBay {
    string soHieu;
    int soGhe;
};
class ChuyenBay {
public:
    string maChuyenBay;
    string soHieu;
    string ngayKhoiHanh;
    string sanBayDen;
    int trangThai; // 0 = huy chuyen, 1 = con ve, 2 = het ve, 3 = hoan tat
    vector<string> danhsachVe;
    vector<string> danhsachGheTrong;
    ChuyenBay() {
        maChuyenBay = "0";
        soHieu = "0";
        ngayKhoiHanh = "0";
        sanBayDen = "0";
        trangThai = -1;
        danhsachVe = {};
        danhsachGheTrong = {};
    }
    ChuyenBay(string ma, string sohieu, string ngay, string san, int status, vector<string> dsve, vector<string> dsghetrong) {
        maChuyenBay = ma;
        soHieu = sohieu;
        ngayKhoiHanh = ngay;
        sanBayDen = san;
        trangThai = status;
        danhsachVe = dsve;
        danhsachGheTrong = dsghetrong;
    }
    void trangThaiChuyenBay(int trangThai) {
        switch (trangThai) {
        case 0: setColor(12);cout << "Hủy chuyến"; setColor(7);break;
        case 1: cout << "Còn vé"; break;
        case 2: setColor(12);cout << "Hết vé"; setColor(7);break;
        case 3: cout << "Hoàn tất"; break;
        default: cout << "Trạng thái không hợp lệ"; break;
        }
    }
    void display() {
        setColor(10); cout << "|Mã chuyến bay: "; setColor(7); cout << maChuyenBay ;setColor(10); cout <<  "|Số hiệu: "; setColor(7); cout << soHieu<<endl ;
        setColor(10); cout <<  "|Ngày khởi hành: " ; setColor(7); cout << ngayKhoiHanh ; setColor(10); cout << "|Sân bay: " ; setColor(7); cout << sanBayDen ;
        setColor(10); cout << "| Trạng thái: " ; setColor(7); trangThaiChuyenBay(trangThai); cout <<" | " <<endl;
        setColor(6);cout << "Danh sách vé: "; setColor(7);
        for (int i = 0; i < danhsachVe.size(); i++) {
            cout << danhsachVe[i] << " ";
        }
        cout << endl;
        setColor(6);cout << "Danh sách ghế trống :";setColor(7);
        for (int i = 0; i < danhsachGheTrong.size(); i++) {
            cout << danhsachGheTrong[i] << " ";
        }
        setColor(9);
        cout << endl << "---------------------------------------------------------------------------------------------------------------------" << endl;
        setColor(7);
    }
    string writeFile() { // dùng để viết vào file txt
        string line = "";
        line += maChuyenBay + " ; ";
        line += soHieu + " ; ";
        line += ngayKhoiHanh + " ; ";
        line += sanBayDen + " ; ";
        line += to_string(trangThai) + " ; ";
        for (int i = 0; i < danhsachVe.size(); i++) {
            line += danhsachVe[i] + " ";
        }
        line += "; ";
        for (int i = 0; i < danhsachGheTrong.size(); i++) {
            line += danhsachGheTrong[i] + " ";
        }
        line += ";\n";
        return line;
    }

};
class KhachHang {
public :
    string CMND;
    string hoTen;
    int soThuTu;
    KhachHang() {
        CMND = "0";
        hoTen = "0";
        soThuTu = 0;
    }
    KhachHang(string cmnd, string hoten, int stt) {
        CMND = cmnd;
        hoTen = hoten;
        soThuTu = stt;
    }
};
struct Ve {
    string maVe; // maChuyenBay + sttGhe
    string maChuyenBay;
    string thongTinKH; // CMND + hoTen
    string sttGhe;
};
struct Account {
    string user;
    string password;
};

template <class type>
class Node {
public:
    type data;
    Node* next;
    Node() {
        data = NULL;
        next = NULL;
    }
    Node(type value) {
        data = value;
        next = nullptr;
    }
    void display() {
        data.display();
    }
};

template <class type>
class LinkedList {
private:
    Node<type>* head;
    Node<type>* tail;
    int size;
public:
    LinkedList() {
        head = tail = NULL;
    }
    ~LinkedList() { }

    void addTail(type value) {
        Node<type>* add = new Node<type>(value);
        if (head == NULL) {
            head = tail = add;
        }
        else {
            tail->next = add;
            tail = add;
        }
    }
    void addHead(type value) {
        Node<type>* add = new Node<type>(value);
        if (head == NULL) {
            head = tail = add;
        }
        else {
            add->next = head;
            head = add;
        }
    }
    void remove(type value) {
        Node<type>* pointer = head;
        Node<type>* temp = NULL;
        while (pointer != NULL && pointer->data != value) {
            temp = pointer;
            pointer = pointer->next;
        }
        if (pointer == NULL) return;
        if (temp != NULL) {
            if (pointer == tail) {
                tail = temp;
                tail->next = NULL;
            }
            temp->next = pointer->next;
            delete pointer;
            size--;
        }
    }
    void clear() {
        Node<type>* temp = head;
        while (temp) {
            Node<type>* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = NULL;
    }
    void display() {
        Node<type>* current = head;
        while (current != nullptr) {
            current->data.display();
            current = current->next;
        }
        cout << endl;
    }
    string writeFile() {
        Node<type>* current = head;
        string lines = "";
        while (current != nullptr) {
            lines += current->data.writeFile();
            current = current->next;
        }
        return lines;
    }

};

template <class type>
class Stack : public Node<type> {
private:
    Node<type>* top;
    int size;
public:
    Stack() {
        top = NULL;
    }
    ~Stack() {
        clear();
    }
    bool isEmpty() {
        return (top == NULL);
    }
    void push(type data) {
        Node<type>* temp = new Node<type>(data);
        temp->next = top;
        top = temp;
        size++;
    }
    type pop() {
        if (isEmpty()) { exit; }
        Node<type>* temp = top;
        type value = temp->data;
        top = temp->next;
        delete temp;
        size--;
        return value;
    }
    type peek() {
        if (isEmpty()) { exit; }
        return top->data;
    }
    void display() {
        if (isEmpty()) { exit; }
        for (Node<type>* temp = top; temp != NULL; temp = temp->next)
            temp->display();
    }
    void clear() {
        Node<type>* temp;
        while (top != NULL) {
            temp = top;
            top = temp->next;
            delete temp;
        }
        size = 0;
    }
    int getSize() {
        return size;
    }
};

template <class type>
class Queue : public Node<type> {
private:
    Node<type>* front;
    Node<type>* end;
    int size;
public:
    Queue() {
        front = end = NULL;
        size = 0;
    }
    ~Queue() {
        clear();
    }
    bool isEmpty() {
        return (front == NULL);
    }
    void enQueue(int data) {
        Node<type>* add = new Node<type>(data);
        if (add == NULL) exit;
        else {
            if (end == NULL) {
                front = add;
                end = add;
            }
            else {
                end->next = add;
                end = add;
            }
        }
        size++;
    }
    type deQueue() {
        if (isEmpty()) exit;
        Node<type>* temp = front;
        type value = temp->data;
        front = temp->next;
        delete temp;
        size--;
        if (front == NULL) end == NULL;
        return value;
    }
    type peek() {
        if (isEmpty()) { exit; }
        return front->data;
    }
    void display() {
        if (isEmpty()) { exit; }
        for (Node<type>* temp = front; temp != NULL; temp = temp->next)
            temp->display();
    }
    void clear() {
        Node<type>* temp;
        while (front != NULL) {
            temp = front;
            front = temp->next;
            delete temp;
        }
        size = 0;
        end = NULL;
    }
    int getSize() {
        return size;
    }
};


#pragma endregion

