#include <iostream>
using namespace std;


string regName, regRoll, regDept, regPassword;
bool isRegistered = false;


struct Book {
    string id;
    string name;
    bool borrowed;
    string borrowedBy;
    string dueDate;
};

Book books[100]; 
int bookCount = 0; 


void loginMenu();
void adminLogin();
void studentLogin();
void studentRegister();
void adminPortal();
void studentPortal();


int main() {
      cout<<"******* Welcome to Library manegment system *******"<<endl;
    loginMenu();
    return 0;
}


void loginMenu() {
    int choice;

    while (true) {
      
        cout << "\n===== LOGIN MENU =====\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Student Registration\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: adminLogin(); break;
            case 2: studentLogin(); break;
            case 3: studentRegister(); break;
            case 4: cout << "Allah Hafiz!\n"; return;
            default: cout << "Invalid choice!\n";
        }
    }
}


void adminLogin() {
    string user, pass;
    cout << "\n--- Admin Login ---\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user == "admin" && pass == "123")
        adminPortal();
    else
        cout << "Wrong credentials!\n";
}


void studentLogin() {
    string name, pass;
    cout << "\n--- Student Login ---\n";
    cout << "Name: ";
    cin >> name;
    cout << "Password: ";
    cin >> pass;

    if (!isRegistered) {
        cout << "Please register first!\n";
        return;
    }

    if (name == regName && pass == regPassword)
        studentPortal();
    else
        cout << "Wrong credentials!\n";
}


void studentRegister() {
    cout << "\n===== STUDENT REGISTRATION =====\n";
    cout << "Name: ";
    cin >> regName;
    cout << "Roll No: ";
    cin >> regRoll;
    cout << "Department: ";
    cin >> regDept;
    cout << "Password: ";
    cin >> regPassword;

    isRegistered = true;
    cout << "Registration successful!\n";
}


void adminPortal() {
    int choice;

    while (true) {
        cout << "\n===== ADMIN PORTAL =====\n";
        cout << "1. View Students\n";
        cout << "2. Add Book\n";
        cout << "3. View Books\n";
        cout << "4. View Borrowed Books\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (isRegistered) {
                    cout << "\nName: " << regName << endl;
                    cout << "Roll: " << regRoll << endl;
                    cout << "Department: " << regDept << endl;
                } else
                    cout << "No students registered.\n";
                break;
            }

            case 2: {
                if (bookCount >= 100) {
                    cout << "Book limit reached!\n";
                    break;
                }
                cout << "\n--- Add Book ---\n";
                cout << "Book ID: ";
                cin >> books[bookCount].id;
                cout << "Book Name: ";
                cin.ignore();
                getline(cin, books[bookCount].name);
                books[bookCount].borrowed = false;
                books[bookCount].borrowedBy = "";
                books[bookCount].dueDate = "";
                bookCount++;
                cout << "Book added successfully!\n";
                break;
            }

            case 3: {
                if (bookCount == 0) {
                    cout << "No books added yet.\n";
                } else {
                    cout << "\n--- Books List ---\n";
                    for (int i = 0; i < bookCount; i++) {
                        cout << i + 1 << ". " << books[i].name 
                             << " (ID: " << books[i].id << ") ";
                        if (books[i].borrowed)
                            cout << "- Borrowed by " << books[i].borrowedBy 
                                 << ", Due: " << books[i].dueDate << endl;
                        else
                            cout << "- Available" << endl;
                    }
                }
                break;
            }

            case 4: {
                cout << "\n--- Borrowed Books ---\n";
                bool anyBorrowed = false;
                for (int i = 0; i < bookCount; i++) {
                    if (books[i].borrowed) {
                        cout << books[i].name << " (ID: " << books[i].id << ") borrowed by "
                             << books[i].borrowedBy << ", Due: " << books[i].dueDate << endl;
                        anyBorrowed = true;
                    }
                }
                if (!anyBorrowed)
                    cout << "No books are borrowed yet.\n";
                break;
            }

            case 5:
                return;

            default:
                cout << "Invalid choice!\n";
        }
    }
}


void studentPortal() {
    int choice;

    while (true) {
        cout << "\n===== STUDENT PORTAL =====\n";
        cout << "1. View Profile\n";
        cout << "2. Borrow Book\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n--- Student Profile ---\n";
                cout << "Name: " << regName << endl;
                cout << "Roll No: " << regRoll << endl;
                cout << "Department: " << regDept << endl;
                cout << "\nBorrowed Books:\n";
                bool hasBorrowed = false;
                for (int i = 0; i < bookCount; i++) {
                    if (books[i].borrowed && books[i].borrowedBy == regName) {
                        cout << books[i].name << " (Due: " << books[i].dueDate << ")\n";
                        hasBorrowed = true;
                    }
                }
                if (!hasBorrowed)
                    cout << "No borrowed books.\n";
                break;
            }

            case 2: {
                cout << "\n--- Available Books ---\n";
                bool availableExists = false;
                for (int i = 0; i < bookCount; i++) {
                    if (!books[i].borrowed) {
                        cout << i + 1 << ". " << books[i].name 
                             << " (ID: " << books[i].id << ")\n";
                        availableExists = true;
                    }
                }
                if (!availableExists) {
                    cout << "No books available to borrow.\n";
                    break;
                }

                int bookChoice;
                cout << "Enter the number of the book to borrow: ";
                cin >> bookChoice;

                if (bookChoice < 1 || bookChoice > bookCount || books[bookChoice-1].borrowed) {
                    cout << "Invalid choice.\n";
                    break;
                }

                cin.ignore();
                cout << "Enter due date (DD/MM/YYYY): ";
                getline(cin, books[bookChoice-1].dueDate);

                books[bookChoice-1].borrowed = true;
                books[bookChoice-1].borrowedBy = regName;

                cout << "Book borrowed successfully!\n";
                break;
            }

            case 3:
                return;

            default:
                cout << "Invalid choice!\n";
        }
    }
}

