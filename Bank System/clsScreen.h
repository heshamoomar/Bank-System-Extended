#pragma once
#include <iostream>
#include "Global.h"
#include "clsDate.h"


using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout << "\t\t\t\t\tUser: ";
        cout << currentUser.UserName;
        
        cout << endl;

        cout << "\t\t\t\t\tDate: ";
        clsDate date;
        date.PrintDate();
        // or clsDate::clsDate().PrintDate();

    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!currentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }
        
    }
};
