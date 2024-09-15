#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

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

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nChoose what to give access to: \n ";

        cout << "\nShow Client List? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow User Logs? [y/n]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += clsUser::enPermissions::pShowLogs;
        }

        return Permissions;
    }

public:
    static void ShowAddNewUserScreen()
    {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::userExists(UserName))
        {
            cout << "User " << UserName << " already exists:   [type Exit to Cancel]\n";
            UserName = clsInputValidate::ReadString();

            if (UserName == "Exit") return;
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;
        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully.\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty.";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }
};
