#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Forward declaration for Account class (needed for transferFunds)
class Account;

class Customer {
public:
    string customerId;
    string name;
    string address;
    string contactNumber;

    void createCustomer() {
        cout << "Enter Customer ID: ";
        cin >> customerId;
        cout << "Enter Name: ";
        getline(cin >> ws, name); // Reads an entire line, including spaces
        cout << "Enter Address: ";
        getline(cin >> ws, address);
        cout << "Enter Contact Number: ";
        cin >> contactNumber;
        cout << "Customer created successfully!" << endl;
    }

    void displayCustomerInfo() const {
        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Contact Number: " << contactNumber << endl;
    }
};

class Transaction {
public:
    string transactionId;
    string accountNumber;
    string type;
    double amount;
    string dateTime; // Store as a string for simplicity

    Transaction(string accNum, string t, double a, string dt) :
        accountNumber(accNum), type(t), amount(a), dateTime(dt) {
        // Generate a simple transaction ID (e.g., timestamp or random number)
        transactionId = "TRN" + to_string(time(0));
    }

    void displayTransaction() const {
        cout << "  ID: " << transactionId << ", Type: " << type << ", Amount: " << amount << ", Date/Time: " << dateTime << endl;
    }
};

class Account {
public:
    string accountNumber;
    string customerId;
    string accountType;
    double balance;
    vector<Transaction> transactions;

    void createAccount(const string& custId) {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        customerId = custId;
        cout << "Enter Account Type (Savings/Current): ";
        cin >> accountType;
        cout << "Enter Initial Deposit: ";
        cin >> balance;
        transactions.emplace_back(accountNumber, "Deposit", balance, "current_datetime"); // Add initial deposit as a transaction
        cout << "Account created successfully!" << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.emplace_back(accountNumber, "Deposit", amount, "current_datetime");
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.emplace_back(accountNumber, "Withdrawal", amount, "current_datetime");
            cout << "Withdrawal successful. New balance: " << balance << endl;
        } else {
            cout << "Insufficient balance or invalid withdrawal amount." << endl;
        }
    }

    void transferFunds(Account& targetAccount, double amount) {
        if (amount > 0 && amount <= balance) {
            withdraw(amount); //  Deduct from sender
            targetAccount.deposit(amount); // Add to recipient
            transactions.emplace_back(accountNumber, "Transfer Out", amount, "current_datetime");
            targetAccount.transactions.emplace_back(targetAccount.accountNumber, "Transfer In", amount, "current_datetime");
            cout << "Fund transfer successful!" << endl;
        } else {
            cout << "Invalid transfer amount or insufficient balance." << endl;
        }
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Customer ID: " << customerId << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: " << balance << endl;
        cout << "Transaction History:" << endl;
        for (const auto& trans : transactions) {
            trans.displayTransaction();
        }
    }
};

int main() {
    //  Demonstrate basic functionality (you would typically have a menu-driven interface)
    Customer customer1;
    customer1.createCustomer();

    Account account1;
    account1.createAccount(customer1.customerId);

    customer1.displayCustomerInfo();
    account1.displayAccountInfo();

    account1.deposit(500);
    account1.withdraw(200);

    Account account2;
    cout << "Creating second account..." << endl;
    account2.createAccount(customer1.customerId);

    account1.transferFunds(account2, 100);
    account1.displayAccountInfo();
    account2.displayAccountInfo();

    return 0;
}
