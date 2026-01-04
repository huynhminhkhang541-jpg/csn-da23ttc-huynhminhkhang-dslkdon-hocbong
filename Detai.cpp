#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Student {
    string id;
    string name;
    double gpa;
    int conduct;
    string note;
    Student* next;
};

class LinkedList {
private:
    Student* head;
public:
    LinkedList() { head = NULL; }
    ~LinkedList() { clear(); }

    void clear() {
        Student* cur = head;
        while (cur) {
            Student* t = cur;
            cur = cur->next;
            delete t;
        }
        head = NULL;
    }

    bool isEmpty() { return head == NULL; }

    void insertBack(string id, string name, double gpa, int conduct, string note) {
        Student* node = new Student;
        node->id = id;
        node->name = name;
        node->gpa = gpa;
        node->conduct = conduct;
        node->note = note;
        node->next = NULL;
        if (head == NULL) {
            head = node;
        } else {
            Student* cur = head;
            while (cur->next != NULL)
                cur = cur->next;
            cur->next = node;
        }
    }

    void displayAll() {
        cout << left << setw(12) << "MSSV" << setw(30) << "Ho ten"
             << setw(8) << "GPA" << setw(12) << "RenLuyen" << setw(20) << "Ghi chu" << endl;
        cout << string(82, '-') << endl;
        Student* cur = head;
        while (cur) {
            cout << left << setw(12) << cur->id
                 << setw(30) << cur->name
                 << setw(8) << fixed << setprecision(2) << cur->gpa
                 << setw(12) << cur->conduct
                 << setw(20) << cur->note << endl;
            cur = cur->next;
        }
   } 

    void removeById(string id) {
        if (!head) return;
        if (head->id == id) {
            Student* t = head;
            head = head->next;
            delete t;
            cout << "Ða xoa sinh vien có MSSV " << id << endl;
            return;
        }
        Student* prev = head;
        Student* cur = head->next;
        while (cur) {
            if (cur->id == id) {
                prev->next = cur->next;
                delete cur;
                cout << "Ða xoa sinh vien có MSSV " << id << endl;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        cout << "Khong tim thay MSSV can xoa!\n";
    }

    void sortByGPA() {
        if (!head) return;
        bool swapped;
        do {
            swapped = false;
            Student* cur = head;
            while (cur->next) {
                if (cur->gpa < cur->next->gpa) {
                    swap(cur->id, cur->next->id);
                    swap(cur->name, cur->next->name);
                    swap(cur->gpa, cur->next->gpa);
                    swap(cur->conduct, cur->next->conduct);
                    swap(cur->note, cur->next->note);
                    swapped = true;
                }
                cur = cur->next;
            }
            } while (swapped);
    }

    void searchByName(string key) {
        bool found = false;
        Student* cur = head;
        while (cur) {
            string nameLower = cur->name;
            string keyLower = key;
            transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
            transform(keyLower.begin(), keyLower.end(), keyLower.begin(), ::tolower);
            if (nameLower.find(keyLower) != string::npos) {
                if (!found) {
                    cout << left << setw(12) << "MSSV" << setw(30) << "Ho tên"
                         << setw(8) << "GPA" << setw(12) << "RenLuyen" << setw(20) << "Ghi chu" << endl;
                    cout << string(82, '-') << endl;
                }
                found = true;
                cout << left << setw(12) << cur->id
                     << setw(30) << cur->name
                     << setw(8) << fixed << setprecision(2) << cur->gpa
                     << setw(12) << cur->conduct
                     << setw(20) << cur->note << endl;
            }
            cur = cur->next;
        }
        if (!found)
            cout << "Khong tim thay sinh vien co ten chua \"" << key << "\".\n";
    }

    void listScholarship(double minGPA, int minConduct) {
        cout << "\n  DANH SACH SINH VIEN DAT HOC BONG   \n";
        bool found = false;
        Student* cur = head;
        while (cur) {
            if (cur->gpa >= minGPA && cur->conduct >= minConduct) {
                if (!found) {
                    cout << left << setw(12) << "MSSV" << setw(30) << "Ho ten"
                         << setw(8) << "GPA" << setw(12) << "RenLuyen" << endl;
                    cout << string(62, '-') << endl;
                }
                found = true;
                cout << left << setw(12) << cur->id
                     << setw(30) << cur->name
                     << setw(8) << fixed << setprecision(2) << cur->gpa
                     << setw(12) << cur->conduct << endl;
            }
            cur = cur->next;
        }
        if (!found)
            cout << " Khong co sinh vien nao dat hoc bong theo tieu chi. \n";
    }

    void createSample() {
        clear();
        insertBack("SV001", "Nguyen Van A", 3.5, 85, "");
        insertBack("SV002", "Le Thi B", 3.8, 90, "");
        insertBack("SV003", "Huynh Van Bi", 3.0, 88, "");
        insertBack("SV004", "Pham Thi My Tien", 3.2, 86, "");
        insertBack("SV006", "Hoang Van Hieu", 3.4, 79, "");
        insertBack("SV007", "Huynh Minh Thien ", 4.0, 98, "");
        insertBack("SV008", "Nguyen Thi Dao", 3.3, 87, "");
  
    }
};

void menu() {
    cout << "\n    CHUONG TRINH XET HOC BONG    \n";
    cout << "1. Them sinh vien\n";
    cout << "2. Xoa ten sinh vien\n";
    cout << "3. Hien thi danh sach\n";
    cout << "4. Sap xep theo GPA cua sinh vien\n";
    cout << "5. Tim theo ten\n";
    cout << "6. Xet hoc bong\n";
    cout << "7. Tao du lieu mau cua sinh vien\n";
    cout << "0. Thoat\n";
    cout << "Chon phan muon kiem tra: ";
}

int main() {
    LinkedList list;
    int choice;
    do {
        menu();
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            string id, name, note;
            double gpa;
            int conduct;
            cout << "Nhap MSSV: "; getline(cin, id);
            cout << "Nhap ho ten: "; getline(cin, name);
            cout << "Nhap GPA cua sinh vien: "; cin >> gpa;
            cout << "Nhap diem ren luyen: "; cin >> conduct;
            cin.ignore();
            cout << "Ghi chu: "; getline(cin, note);
            list.insertBack(id, name, gpa, conduct, note);
        } else if (choice == 2) {
            string id;
            cout << "Nhap MSSV can xoa: "; getline(cin, id);
            list.removeById(id);
        } else if (choice == 3) {
            list.displayAll();
        } else if (choice == 4) {
            list.sortByGPA();
            cout << "Da sap xep danh sach theo GPA giam dan.\n";
        } else if (choice == 5) {
            string key;
            cout << "Nhap ten can tim: "; getline(cin, key);
            list.searchByName(key);
        } else if (choice == 6) {
            double minGPA; int minConduct;
            cout << "Nhap GPA toi thieu (>= 2.0): "; cin >> minGPA;
            cout << "Nhap diem ren luyen toi thieu (>= 50): "; cin >> minConduct;
            list.listScholarship(minGPA, minConduct);
        } else if (choice == 7) {
            list.createSample();
            cout << "Da tao du lieu mau cho sinh vien!\n";
        }
    } while (choice != 0);

    cout << "Ket thuc chuong trinh.\n";
    return 0;
}

