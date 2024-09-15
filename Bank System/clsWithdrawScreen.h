#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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

    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

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
        cout << "\nPlease enter withdraw amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        while (Amount > client1.AccountBalance || Amount <= 0) {

            cout << "\nPlease enter valid withdraw amount [type -1 to cancel]: ";
            Amount = clsInputValidate::ReadDblNumber();
            if (Amount == -1) {
                return;
            }
        }

        cout << "\nAre you sure, do you want to perform this transaction [y/n]: ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            client1.Withdraw(Amount);
            cout << "\nAmount withdrawn successfully.\n";
            cout << "\nNew balance is: " << client1.AccountBalance;

        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};
