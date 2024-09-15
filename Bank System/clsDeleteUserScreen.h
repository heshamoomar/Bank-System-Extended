#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
{

private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n____________________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.getFullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n____________________________\n";

    }

public:
    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::userExists(UserName))
        {
            cout << UserName << " not found, try again:   [type Exit to Cancel]\n";
            UserName = clsInputValidate::ReadString();

            if (UserName == "Exit")return;
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User? [y/n]: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (User1.Delete()) {
                cout << "\nUser deleted successfully.\n";
            }
            else {
                cout << "\nUser was not Deleted\n";
            }
        }
    }
};
