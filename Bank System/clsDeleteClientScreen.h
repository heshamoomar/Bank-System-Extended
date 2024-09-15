#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen :protected clsScreen
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
    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
            return; //  exit ShowDeleteClientScreen() and don't continue
        }

        _DrawScreenHeader("\t Delete Client Screen");

        string AccountNumber;
        char choice;

        cout << "Please enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!(clsBankClient::clientExists(AccountNumber)))
        {
            cout << "Account " << AccountNumber << " not found, try again:   [type Exit to Cancel]\n";
            AccountNumber = clsInputValidate::ReadString();

            if (AccountNumber == "Exit")return;
        }

        clsBankClient client = clsBankClient::Find(AccountNumber);
        _PrintClient(client);

        cout << "Are you sure, do you want to delete this client record? [y/n]: ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (client.Delete()) {
                cout << "Client deleted successfully.\n";
                _PrintClient(client);
            }
            else {
                cout << "Error! Client was not deleted.\n";
            }
        }
        else {
            cout << "Client not deleted.\n";
        }
    }

};
