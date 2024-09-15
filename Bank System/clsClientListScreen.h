#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsClientListScreen :protected clsScreen
{

private:
    static void PrintClientRecordLine(clsBankClient client, int index)
    {

        cout << setw(7) << right << index << " ";
        cout << "| " << setw(15) << left << client.getAccountNumber();
        cout << "| " << setw(20) << left << client.getFullName();
        cout << "| " << setw(12) << left << client.Phone;
        cout << "| " << setw(21) << left << client.Email;
        cout << "| " << setw(10) << left << client.PinCode;
        cout << "| " << setw(7) << right << client.AccountBalance;

    }

public:


    static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients)) {
            return; //  exit ShowClientsList() and don't continue
        }

        vector <clsBankClient> vClients = clsBankClient::getClientsList();
        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "__________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(21) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "__________________________________________\n" << endl;

        if (vClients.size() == 0) {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else {
            int count = 1;
            for (clsBankClient Client : vClients)
            {

                PrintClientRecordLine(Client, count);
                cout << endl;
                count++;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "__________________________________________\n" << endl;

    }

};
