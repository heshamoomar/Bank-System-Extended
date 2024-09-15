#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsFindClientScreen :protected clsScreen
{

private:
    static void _PrintClient(clsBankClient client)
    {
        cout << "\nClient Info:";
        cout << "\n____________________________";
        cout << "\nFirstName   : " << client.FirstName;
        cout << "\nLastName    : " << client.LastName;
        cout << "\nFull Name   : " << client.getFullName();
        cout << "\nEmail       : " << client.Email;
        cout << "\nPhone       : " << client.Phone;
        cout << "\nAcc. Number : " << client.getAccountNumber();
        cout << "\nPassword    : " << client.getPinCode();
        cout << "\nBalance     : " << client.getAccountBalance();
        cout << "\n____________________________\n";

    }

public:

    static void ShowFindClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
            return; //  exit ShowFindClientScreen() and don't continue
        }

        _DrawScreenHeader("\t Find Client Screen");

        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!(clsBankClient::clientExists(AccountNumber)))
        {
            cout << "Account " << AccountNumber << " not found, try again:   [type Exit to Cancel]\n";
            AccountNumber = clsInputValidate::ReadString();

            if (AccountNumber == "Exit")return;
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.isEmpty())
        {
            cout << "Client found. \n";
        }
        else
        {
            cout << "Client not found. \n";
        }

        _PrintClient(Client1);

    }

};
