#pragma once
#include <iostream>
#include "Global.h"
#include "clsScreen.h"


class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.getFullName();
        cout << "\nAcc. Number : " << Client.getAccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter account number: ";
        cin >> AccountNumber;
        return AccountNumber;
    }

    static string _PrepareTransferLogRecord(float Amount, clsBankClient client1, clsBankClient client2, clsUser User, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::clsDate().DateTimeToString() + Seperator;
        TransferLogRecord += client1.getAccountNumber() + Seperator;
        TransferLogRecord += client2.getAccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(client1.AccountBalance) + Seperator;
        TransferLogRecord += to_string(client2.AccountBalance) + Seperator;
        TransferLogRecord += currentUser.UserName;
        return TransferLogRecord;
    }

    static void _RegisterTransferLog(float Amount, clsBankClient client1, clsBankClient client2, clsUser User)
    {
        string DataLine = _PrepareTransferLogRecord(Amount, client1, client2, currentUser);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);
        if (MyFile.is_open()) {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }

    static void _Transfer(float Amount, clsBankClient& client1, clsBankClient& client2) {
        client1.Withdraw(Amount);
        client2.Deposit(Amount);
        _RegisterTransferLog(Amount, client1, client2, currentUser);
    }


public:
	static void ShowTransferScreen() {
        _DrawScreenHeader("\t    Transfer Screen");
        cout << endl;

        float amount = 0.0;
        string Account1Number;
        string Account2Number;

        cout << "Enter account number to transfer from: ";
        cin >> Account1Number;

        while (!(clsBankClient::clientExists(Account1Number)))
        {
            cout << "Account " << Account1Number << " not found, try again:   [type Exit to Cancel]\n";
            Account1Number = clsInputValidate::ReadString();

            if (Account1Number == "Exit")return;
        }

        clsBankClient client1 = clsBankClient::Find(Account1Number);
        _PrintClient(client1);


        cout << "Enter account number to transfer to: ";
        cin >> Account2Number;

        while (!(clsBankClient::clientExists(Account2Number)))
        {
            cout << "Account " << Account2Number << " not found, try again:   [type Exit to Cancel]\n";
            Account2Number = clsInputValidate::ReadString();

            if (Account2Number == "Exit")return;
        }

        clsBankClient client2 = clsBankClient::Find(Account2Number);
        _PrintClient(client2);

        cout << "Please enter transfer amount: ";
        cin >> amount;

        while (amount > client1.getAccountBalance() || amount <= 0) {

            if (amount > client1.getAccountBalance()) {
            cout << "Amount exceeds available balance, enter another amount: ";
            cin >> amount;
            }
            else {
                cout << "Please enter a positive amount: ";
                cin >> amount;
            }
        }

        cout << "\nAre you sure, do you want to perform this operation [y/n]: ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            _Transfer(amount, client1, client2);
            cout << "\nTransfer done successfully.\n";
            _PrintClient(client1);
            _PrintClient(client2);
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

	}

};

