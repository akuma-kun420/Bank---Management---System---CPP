#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Account
{
public:
    int accNo;
    string name;
    double balance;
};

void createAccount()
{
    Account a;
    
    ofstream file("accounts.txt", ios::app);
    
    cout << "Enter Account Number: ";
    cin >> a.accNo;
    cin.ignore();
    
    cout << "Enter Name: ";
    getline(cin, a.name);
    
    cout << "Enter Initial Balance: ";
    cin >> a.balance;
    
    file << a.accNo << "," << a.name << "," << a.balance << endl;
    
    file.close();
    
    cout << "\nAccount Created Successfully\n";
}

void displayAccounts()
{
    ifstream file("accounts.txt");
    string line;
    
    cout << "\n===== ACCOUNT RECORDS =====\n";
    
    while(getline(file, line))
    {
        cout << line << endl;
    }
    
    file.close();
}

void depositMoney()
{
    int accNo;
    double amount;
    
    cout << "Enter Account Number: ";
    cin >> accNo;
    
    cout << "Enter Deposit Amount: ";
    cin >> amount;
    
    ifstream file("accounts.txt");
    ofstream temp("temp.txt");
    
    Account a;
    bool found = false;
    
    while(file >> a.accNo)
    {
        file.ignore();
        
        getline(file, a.name, ',');
        file >> a.balance;
        file.ignore();
        
        if(a.accNo == accNo)
        {
            a.balance += amount;
            found = true;
        }
        
        temp << a.accNo << "," << a.name << "," << a.balance << endl;
    }
    
    file.close();
    temp.close();
    
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    
    if(found)
        cout << "Deposit Successful\n";
    else
        cout << "Account Not Found\n";
}

void withdrawMoney()
{
    int accNo;
    double amount;
    
    cout << "Enter Account Number: ";
    cin >> accNo;
    
    cout << "Ener Withdrawl Amount: ";
    cin >> amount;
    
    ifstream file("accounts.txt");
    ofstream temp("temp.txt");
    
    Account a;
    bool found = false;
    
    while(file >> a.accNo)
    {
        file.ignore();
        
        getline(file, a.name, ',');
        file >> a.balance;
        file.ignore();
        
        if(a.accNo == accNo)
        {
            found = true;
            
            if(a.balance >= amount)
            {
                a.balance -= amount;
            }
            else
            {
                cout << "Insufficient Balance!\n";
            }
        }
        
        temp << a.accNo << "," << a.name << "," << a.balance << endl;
    }
    
    file.close();
    temp.close();
    
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    
    if(found)
        cout << "Withdrawal Process Completed!\n";
    else
        cout << "Account Not Found!\n";
}

void checkBalance()
{
    int accNo;
    
    cout << "Enter Account Number: ";
    cin >> accNo;
    
    ifstream file("accounts.txt");
    
    Account a;
    bool found = false;
    
    while(file >> a.accNo)
    {
        file.ignore();
        
        getline(file, a.name, ',');
        file >> a.balance;
        file.ignore();
        
        cout << "Reading Account: " << a.accNo << endl;
        
        if(a.accNo == accNo)
        {
            cout<< "\nAccount Holder: " << a.name;
            cout << "\nBalance: " << a.balance << endl;
            
            found = true;
            break;
        }
    }
    
    file.close();
    
    if(!found)
         cout << "Account Not Found\n";
}

int main()
{
    int choice;
    
    do
    {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Creat Account\n";
        cout << "2. Display Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Check Balance\n";
        cout << "6. Exit\n";
        cout << "Enter Choice: ";
        
        cin >> choice;
        
        switch(choice)
        {
            case 1:
            createAccount();
            break;
            
            case 2:
            displayAccounts();
            break;
            
            case 3:
            depositMoney();
            break;
            
            case 4:
            withdrawMoney();
            break;
            
            case 5:
            checkBalance();
            break;
            
            case 6:
            cout << "Exiting...\n";
            break;
            
            default:
            cout << "Invalid Choice!\n";
        }
    } while(choice != 6);
    
    return 0;
}
