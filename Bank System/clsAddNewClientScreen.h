#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
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

    static void read_client_info(clsBankClient& client)
    {
        cout << "Enter First name: ";
        client.FirstName = clsInputValidate::ReadString();
        cout << "Enter Last name: ";
        client.LastName = clsInputValidate::ReadString();
        cout << "Enter Email: ";
        client.Email = clsInputValidate::ReadString();
        cout << "Enter Phone: ";
        client.Phone = clsInputValidate::ReadString();
        cout << "Enter Pin Code: ";
        client.PinCode = clsInputValidate::ReadString();
        cout << "Enter Account balance: ";
        client.AccountBalance = clsInputValidate::ReadFloatNumber();
    };

public:

    static void ShowAddNewClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
            return; //  exit ShowAddNewClientScreen() and don't continue
        }

        _DrawScreenHeader("\t Add New Client Screen");

        string AccountNumber;

        cout << "Please enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::clientExists(AccountNumber))
        {
            cout << "Account " << AccountNumber << " already exists:   [type Exit to Cancel]\n";
            AccountNumber = clsInputValidate::ReadString();

            if (AccountNumber == "Exit") return;
        }
        clsBankClient new_client = clsBankClient::add_new_client_object(AccountNumber);
        read_client_info(new_client);

        clsBankClient::enSaveStatus saveResult;

        saveResult = new_client.Save();

        switch (saveResult)
        {
        case clsBankClient::svSucceeded:
            cout << "Account added successfully.\n";
            _PrintClient(new_client);
            break;

        case clsBankClient::svFailed_empty_object:
            cout << "Error, cannot save an empty account.\n";
            break;
        case clsBankClient::svFailed_account_number_exists:
            cout << "Error, cannot save because account number already in use.\n";
            break;
        }
    }
};
