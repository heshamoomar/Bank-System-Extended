#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen :protected clsScreen

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
    };

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) {
            return; //  exit ShowUpdateClientScreen() and don't continue
        }

        _DrawScreenHeader("\t Update Client Screen");

        string AccountNumber;
        short choice;

        cout << "Please enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!(clsBankClient::clientExists(AccountNumber)))
        {
            cout << "Account " << AccountNumber << " not found, try again:   [type Exit to Cancel]\n";
            AccountNumber = clsInputValidate::ReadString();

            if (AccountNumber == "Exit")return;
        }

        clsBankClient client = clsBankClient::Find(AccountNumber);
        cout << "Client Found.\n";
        _PrintClient(client);

        cout << "What do you want to update? ";
        cout << "All [1]";
        cout << ", FirstName [2]";
        cout << ", LastName [3]";
        cout << ", Email [4]";
        cout << ", Phone [5]";
        cout << ", Password [6]: ";

        switch (choice = clsInputValidate::ReadIntNumber(""))
        {
        case 1:
            cout << "Updating clinet info:\n";
            cout << "____________________________\n";
            read_client_info(client);
            break;
        case 2:
            cout << "Enter First name:\n";
            client.FirstName = clsInputValidate::ReadString();
            break;
        case 3:
            cout << "Enter Last name:\n";
            client.LastName = clsInputValidate::ReadString();
            break;
        case 4:
            cout << "Enter Email:\n";
            client.Email = clsInputValidate::ReadString();
            break;
        case 5:
            cout << "Enter Phone:\n";
            client.Phone = clsInputValidate::ReadString();
            break;
        case 6:
            cout << "Enter Password:\n";
            client.PinCode = clsInputValidate::ReadString();
            break;
        default:
            cout << "Invalid choice.\n";
            return;
        }

        clsBankClient::enSaveStatus saveResult;

        saveResult = client.Save();

        switch (saveResult)
        {
        case clsBankClient::svSucceeded:
            cout << "Account updated successfully.\n";
            _PrintClient(client);
            break;

        case clsBankClient::svFailed_empty_object:
            cout << "Error, cannot save an empty account.\n";
            break;
        }

    }
};
