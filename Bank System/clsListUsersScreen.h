#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsListUsersScreen :protected clsScreen
{

private:
    static void _PrintUserRecordLine(clsUser User, int index)
    {
        cout << setw(7) << right << index << " ";
        cout << "| " << setw(12) << left << User.UserName;
        cout << "| " << setw(23) << left << User.getFullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(21) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(11) << right << User.Permissions;

    }

public:

    static void ShowUsersList()
    {
        vector <clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(23) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(21) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0) {
            cout << "\t\t\t\tNo Users Available In the System!";
        }
        else {
            int count = 1;
            for (clsUser User : vUsers)
            {

                _PrintUserRecordLine(User, count);
                cout << endl;
                count++;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }

};
