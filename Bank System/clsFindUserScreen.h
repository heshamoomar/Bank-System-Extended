#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsInputValidate.h"

class clsFindUserScreen :protected clsScreen
{

private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.getFullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:

    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\t  Find User Screen");
        string UserName;

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::userExists(UserName))
        {
            cout << "\nUser not found, choose another one:   [type Exit to Cancel]\n";
            UserName = clsInputValidate::ReadString();

            if (UserName == "Exit") return;
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.isEmpty())
        {
            cout << "\nUser Found.\n";
        }
        else
        {
            cout << "\nUser was not Found.\n";
        }
        _PrintUser(User1);
    }
};
