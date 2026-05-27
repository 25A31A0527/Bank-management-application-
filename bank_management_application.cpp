#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string name;
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() {
        cout << "\nAccount Number : " << accountNumber << endl;
        cout << "Account Holder : " << name << endl;
        cout << "Balance        : " << balance << endl;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    void deposit() {
        float amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        balance += amount;

        cout << "Amount deposited successfully.\n";
    }

    void withdraw() {
        float amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (amount > balance) {
            cout << "Insufficient balance.\n";
        } else {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        }
    }

    float getBalance() {
        return balance;
    }

    void saveToFile(ofstream &file) {
        file << accountNumber << "|" << name << "|" << balance << endl;
    }
};

void createNewAccount() {
    BankAccount acc;
    ofstream file("bank_data.txt", ios::app);

    acc.createAccount();
    acc.saveToFile(file);

    file.close();

    cout << "\nAccount created successfully.\n";
}

void displayAccounts() {
    ifstream file("bank_data.txt");
    string line;

    cout << "\n===== Bank Account Records =====\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void searchAccount() {
    ifstream file("bank_data.txt");
    string line;
    int accNo;
    bool found = false;

    cout << "Enter Account Number to search: ";
    cin >> accNo;

    while (getline(file, line)) {
        int storedAccNo = stoi(line.substr(0, line.find("|")));

        if (storedAccNo == accNo) {
            cout << "\nAccount Found:\n";
            cout << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nAccount not found.\n";
    }

    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n===== Bank Management Application =====\n";
        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createNewAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                cout << "\nExiting application...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
