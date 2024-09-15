#pragma once
#include <iostream>
#include <iomanip>
#include "Global.h"
#include "clsUser.h"
#include "clsScreen.h"
#include "clsMainScreen.h"


class clsLoginScreen : clsScreen
{
private:
	static bool _Login() 
	{

		bool loginFailed = false;
		string userName, Password;
		short trials = 3;

		do
		{
			if (trials == 1) {
				cout << "\nYou are locked after 3 failed trails.\n";
				return false;
			}
			if (loginFailed) {
				cout << "\nInvalid UserName / Password!\n";
				cout << "You have " << trials - 1 << " more trial(s) to login.\n\n";
				trials--;
			}

			cout << "Enter Username: ";
			cin >> userName;

			cout << "Enter Password: ";
			cin >> Password;

			currentUser = clsUser::Find(userName, Password);

			loginFailed = currentUser.isEmpty();

		} while (loginFailed);

		//	here I have logged in successfully
		clsUser::_StoreUserLog(userName, Password, currentUser.Permissions);
		clsMainScreen::ShowMainMenue();
		return true;
	}


public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");
		return _Login();
	}
};

