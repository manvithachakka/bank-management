#include <iostream>
#include <fstream>
#include <map>
#include <string>

#define MIN_BAL 500
using namespace std;

class Accounts
{
private:
    float balance;
    string fname, lname;
    long accountnumber;
    static long count;

public:
    Accounts() {}
    Accounts(string firstname, string lastname, float balance)
    {
        fname = firstname;
        lname = lastname;
        accountnumber = ++count;
        this->balance = balance;
    }
    string getfirstname() { return fname; }
    string getlastname() { return lname; }
    float getbalance() { return balance; }
    long getaccountnumber() { return accountnumber; }
    static void setcount(long a);
    static long getcount();
    void Deposit(float amount);
    void Withdrawal(float amount);
    friend ostream &operator<<(ostream &out, Accounts &acc);
    friend ofstream &operator<<(ofstream &out, Accounts &acc);
    friend ifstream &operator>>(ifstream &ifs, Accounts &acc);
};

class Bank
{
private:
    map<long, Accounts> m;

public:
    Bank();
    Accounts OpenAccount(string firstname, string lastname, float balance);
    Accounts BalanceEnquiry(long accountnumber);
    Accounts Deposit(long accountnumber, float amount);
    Accounts Withdrawal(long accountnumber, float amount);
    void CloseAccount(long accountnumber);
    void ShowAllAccounts();
    ~Bank();
};

class InsufficientFunds {};

int main()
{
    cout << "***Banking System***" << endl << endl;
    int choice;
    string fname, lname;
    float balance, amount;
    long accountnumber;
    Accounts acc;
    Bank b;

    do
    {
        cout << "\n\tSelect one option below" << endl;
        cout << "\t1 Open An Account" << endl;
        cout << "\t2 Balance Enquiry" << endl;
        cout << "\t3 Deposit" << endl;
        cout << "\t4 Withdrawal" << endl;
        cout << "\t5 Close an Account" << endl;
        cout << "\t6 Show All Accounts" << endl;
        cout << "\t7 Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        try
        {
            switch (choice)
            {
            case 1:
                cout << "Enter First Name: ";
                cin >> fname;
                cout << "Enter Last Name: ";
                cin >> lname;
                cout << "Enter Initial Balance: ";
                cin >> balance;
                if (balance < MIN_BAL)
                {
                    throw InsufficientFunds();
                }
                acc = b.OpenAccount(fname, lname, balance);
                cout << endl << "Congratulations Account is Created" << endl;
                cout << acc;
                break;
            case 2:
                cout << "Enter Account Number: ";
                cin >> accountnumber;
                acc = b.BalanceEnquiry(accountnumber);
                cout << endl << "Your Account Details" << endl;
                cout << acc;
                break;
            case 3:
                cout << "Enter Account Number: ";
                cin >> accountnumber;
                cout << "Enter Amount: ";
                cin >> amount;
                acc = b.Deposit(accountnumber, amount);
                cout << endl << "Amount is Deposited" << endl;
                cout << acc;
                break;
            case 4:
                cout << "Enter Account Number: ";
                cin >> accountnumber;
                cout << "Enter Amount: ";
                cin >> amount;
                acc = b.Withdrawal(accountnumber, amount);
                cout << endl << "Amount is Withdrawn" << endl;
                cout << acc;
                break;
            case 5:
                cout << "Enter Account Number: ";
                cin >> accountnumber;
                b.CloseAccount(accountnumber);
                break;
            case 6:
                cout << endl;
                b.ShowAllAccounts();
                break;
            case 7:
                break;
            default:
                cout << "\nEnter correct choice";
                exit(0);
            }
        }
        catch (InsufficientFunds)
        {
            cout << "\nError: Insufficient Funds!" << endl;
        }
        catch (exception &e)
        {
            cout << "\nError: " << e.what() << endl;
        }
    } while (choice != 7);

    return 0;
}

ostream &operator<<(ostream &out, Accounts &acc)
{
    out << "First Name: " << acc.getfirstname() << endl;
    out << "Last Name: " << acc.getlastname() << endl;
    out << "Account Number: " << acc.getaccountnumber() << endl;
    out << "Balance: " << acc.getbalance() << endl << endl;
    return out;
}

ofstream &operator<<(ofstream &out, Accounts &acc)
{
    out << acc.getfirstname() << endl;
    out << acc.getlastname() << endl;
    out << acc.getaccountnumber() << endl;
    out << acc.getbalance() << endl;
    return out;
}

ifstream &operator>>(ifstream &ifs, Accounts &acc)
{
    ifs >> acc.fname >> acc.lname >> acc.accountnumber >> acc.balance;
    return ifs;
}

long Accounts::count = 0;

Accounts Bank::OpenAccount(string firstname, string lastname, float balance)
{
    Accounts acc(firstname, lastname, balance);
    m.insert(pair<long, Accounts>(acc.getaccountnumber(), acc));
    
    ofstream outfile("my.txt", ios::trunc);
    map<long, Accounts>::iterator itr;
    for (itr = m.begin(); itr != m.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
    return acc;
}

Accounts Bank::BalanceEnquiry(long accountnumber)
{
    map<long, Accounts>::iterator itr;
    itr = m.find(accountnumber);
    return itr->second;
}

Accounts Bank::Deposit(long accountnumber, float amount)
{
    map<long, Accounts>::iterator itr;
    itr = m.find(accountnumber);
    itr->second.Deposit(amount);
    return itr->second;
}

void Accounts::Deposit(float amount)
{
    balance += amount;
}

void Accounts::Withdrawal(float amount)
{
    if (balance - amount < MIN_BAL)
    {
        throw InsufficientFunds();
    }
    balance -= amount;
}

Accounts Bank::Withdrawal(long accountnumber, float amount)
{
    map<long, Accounts>::iterator itr;
    itr = m.find(accountnumber);
    itr->second.Withdrawal(amount);
    return itr->second;
}

void Bank::ShowAllAccounts()
{
    map<long, Accounts>::iterator itr;
    for (itr = m.begin(); itr != m.end(); itr++)
    {
        cout << "Account " << itr->first << endl << itr->second;
    }
}

void Bank::CloseAccount(long accountnumber)
{
    map<long, Accounts>::iterator itr;
    itr = m.find(accountnumber);
    cout << "Account is Closed" << endl;
    cout << itr->second << endl;
    m.erase(accountnumber);
}

Bank::Bank()
{
    Accounts acc;
    ifstream infile;
    infile.open("my.txt");
    if (!infile)
    {
        return;
    }
    while (infile >> acc)
    {
        m.insert(pair<long, Accounts>(acc.getaccountnumber(), acc));
    }
    
    if (!m.empty())
    {
        Accounts::setcount(m.rbegin()->first);
    }
    infile.close();
}

void Accounts::setcount(long a)
{
    count = a;
}

long Accounts::getcount()
{
    return count;
}

Bank::~Bank()
{
    ofstream outfile("my.txt", ios::trunc);
    map<long, Accounts>::iterator itr;
    for (itr = m.begin(); itr != m.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
}