/*
 rec04_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
    string name;
    int number;
};
// Task 2
// Define an Account class
class AccountClass{
    friend ostream& operator<<(ostream& os, const AccountClass& accountClass);
private:
    string name;
    int number;
public:
    AccountClass(const string& classname,int classnumber):name(classname){
        number = classnumber;
    }
    const string& getname()const{
        return name;
    }
    int getnumber() const {
        return number;
    }
};

ostream& operator<<(ostream& os, const AccountClass& accountClass){
    //os << accountClass.getname() << accountClass.getnumber() << endl;
    //return os;
    os << accountClass.name << " " << accountClass.number << endl;
    return os;
}



// Task 3
// Define an Account and Transaction classes
class Transaction{
    friend ostream& operator<<(ostream& os, const Transaction& transaction);
private:
    string transaction_type;
    int transaction_amount;
public:
    Transaction(const string& type,int amount):transaction_type(type),transaction_amount(amount){
        //amount = transaction_amount;
    };
};
ostream& operator<<(ostream& os, const Transaction& transaction){
    os << transaction.transaction_type << "  "<< transaction.transaction_amount << endl;
    return os;
}

class AccountHistory{
    friend ostream& operator<<(ostream& os, const AccountHistory& account_history);

public:
    AccountHistory(const string& nameAccount,int numberAccount):account_name(nameAccount),account_number(numberAccount),account_balance(0){}


    int number_getter2() const {
        return account_number;
    }

    void deposit_check(int amount) {
        account_balance = account_balance + amount;
        transaction_history.emplace_back("deposit", amount);
    }

    void withdraw_check(int amount) {
        if (account_balance >= amount) {
            account_balance = account_balance - amount;
            transaction_history.emplace_back("withdrawal", amount);
        } else {
            cout << "Account#" << " " << account_number << " has only " << account_balance << "."<< " Insufficient for withdrawal of "<< amount << "."<< endl;
        }
    }

private:
    string account_name;
    int account_number;
    vector<Transaction> transaction_history;
    int account_balance = 0;

};
ostream& operator<<(ostream& os, const AccountHistory& account_history){
    os << account_history.account_name << "  "<< account_history.account_number << ":" << endl;
    for(size_t position = 0; position < account_history.transaction_history.size(); ++position){
        os << "   " << account_history.transaction_history[position] << endl;
    }
    return os;
}
size_t search_curser(const vector<AccountHistory> &account_history, int account_number) {
    for (size_t pos = 0; pos < account_history.size(); ++pos) {
        if (account_number == account_history[pos].number_getter2()) {
            return pos;
        }
    }
    return account_history.size();
}

// Task 4
// Define an Account with a nested public Transaction class

// Task 5
// Define an Account with a nested private Transaction class


int main() {
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream ifs("accounts.txt");
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    if (ifs) {
        Account bank_account;
        vector<Account> account_info;
        while (ifs >> bank_account.name >> bank_account.number) {
            account_info.push_back(bank_account);
        }
        for (size_t account_index = 0; account_index < account_info.size(); ++account_index) {
            cout << account_info[account_index].name << " " << account_info[account_index].number << endl;
        }
        ifs.close();

        //      1b
        cout << "Task1b:\n";
        cout << "Filling vector of struct objects, using {} initialization:\n";
        account_info.clear();

        ifs.open("accounts.txt");
        if (!ifs) {
            cerr << "Could not open the file.\n";
            exit(1);
        }
        if (ifs) {
            string name;
            int number;
            while (ifs >> name >> number) {
                Account bank_account{name, number};
                account_info.push_back(bank_account);
            };

        }
        for (size_t account_index = 0; account_index < account_info.size(); ++account_index) {
            cout << account_info[account_index].name << " " << account_info[account_index].number << endl;
        }
        ifs.close();
        ifs.clear();
        //==================================
        // Task 2: account as class

        //      2a
        cout << "==============\n";
        cout << "\nTask2a:";
        cout << "\nFilling vector of class objects, using local class object:\n";
        ifs.open("accounts.txt");
        if (!ifs) {
            cerr << "Could not open the file.\n";
            exit(1);
        }

        string name2;
        int number2;
        vector<AccountClass> accountclass_vector;
        while (ifs >>name2 >> number2) {
            AccountClass new_account(name2,number2);
            accountclass_vector.push_back(new_account);
        }
        for (size_t account_index = 0; account_index < accountclass_vector.size(); ++account_index) {
            cout << accountclass_vector[account_index].getname() << " "
                 << accountclass_vector[account_index].getnumber() << endl;
        }
        ifs.close();
        ifs.clear();
        cout << "\nTask2b:\n";
        cout << "output using output operator with getters\n";
        ifs.open("accounts.txt");
        if (!ifs) {
            cerr << "Could not open the file.\n";
            exit(1);
        }
        for (size_t account_index = 0; account_index < accountclass_vector.size(); ++account_index) {
            cout << accountclass_vector[account_index];
        }
        ifs.close();


        cout << "\nTask2c:\n";
        cout << "output using output operator as friend without getters\n";
        ifs.open("accounts.txt");
        if (!ifs) {
            cerr << "Could not open the file.\n";
            exit(1);
        }

        for (size_t account_index = 0; account_index < accountclass_vector.size(); ++account_index) {
            cout << accountclass_vector[account_index]<< endl;
        }

        ifs.close();

        cout << "\nTask2d:\n";
        cout << "Filling vector of class objects, using temporary class object:\n";

        ifs.open("accounts.txt");
        if (!ifs) {
            cerr << "Could not open the file.\n";
            exit(1);
        }
        string newest_name;
        accountclass_vector.clear();
        int newest_number;
        while (ifs >> newest_name >> newest_number) {
            accountclass_vector.push_back(AccountClass(newest_name, newest_number));
        }
        for (size_t account_index = 0; account_index < accountclass_vector.size(); ++account_index) {
            cout << accountclass_vector[account_index]<< endl;
        }

        ifs.close();




        cout << "\nTask2e:\n";
        cout << "Filling vector of class objects, using emplace_back:\n";
        ifs.open("accounts.txt");
        if (!ifs) {
            cerr << "Could not open the file.\n";
            exit(1);
        }

        string newest_name2;
        accountclass_vector.clear();
        int newest_number2;
        while (ifs >> newest_name2 >> newest_number2) {
            accountclass_vector.emplace_back(newest_name2, newest_number2);
        }
        for (size_t account_index = 0; account_index < accountclass_vector.size(); ++account_index) {
            cout << accountclass_vector[account_index]<< endl;
        }

        ifs.close();


        cout << "==============\n";
        cout << "\nTask 3:\nAccounts and Transaction:\n";

        accountclass_vector.clear();
        vector<AccountHistory> history_check;
        vector<Transaction> transaction_check;
        ifs.open("transactions.txt");

        if (!ifs) {
            cerr << "Could not open the file.\n";
            exit(1);
        }
        string check_type;
        while(ifs >> check_type){
            if(check_type == "Account"){
                string name;
                int account_num;
                ifs >> name >> account_num;
                history_check.emplace_back(name, account_num);
            }

            else if(check_type == "Withdraw"){
                int account_num0;
                int amount;
                ifs >> account_num0 >> amount;
                size_t index = search_curser(history_check, account_num0);
                if(index != history_check.size()) {
                    history_check[index].withdraw_check(amount);
                }
            }

            else if(check_type == "Deposit"){
                int account_num1;
                int amount;
                ifs >> account_num1 >> amount;
                size_t index = search_curser(history_check, account_num1);
                if(index != history_check.size()) {
                    history_check[index].deposit_check(amount);
                }
            }
        }

        for(size_t count = 0; count < history_check.size(); ++count){
            cout << history_check[count] << endl;
        }

        cout << "==============\n";
        cout << "\nTask 4:\nTransaction nested in public section of Account:\n";

        cout << "==============\n";
        cout << "\nTask 5:\nTransaction nested in private section of Account:\n";


    }
}

