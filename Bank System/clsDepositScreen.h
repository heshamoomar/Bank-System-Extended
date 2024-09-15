#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n____________________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.getFullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.getAccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n____________________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter account number: ";
        cin >> AccountNumber;
        return AccountNumber;
    }


public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");

        string AccountNumber = _ReadAccountNumber();


        while (!(clsBankClient::clientExists(AccountNumber)))
        {
            cout << "Account " << AccountNumber << " not found, try again:   [type Exit to Cancel]\n";
            AccountNumber = clsInputValidate::ReadString();

            if (AccountNumber == "Exit")return;
        }

        clsBankClient client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure, do you want to perform this transaction [y/n]: ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            client1.Deposit(Amount);
            cout << "\nAmount deposited successfully.\n";
            cout << "\nNew balance is: " << client1.AccountBalance;

        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};
