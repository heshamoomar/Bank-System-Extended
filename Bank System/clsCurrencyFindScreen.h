#pragma once
#include <iomanip>
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyFindScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency curr)
	{
		cout << "Currency Card:\n";
		cout << "______________________";
		cout << left << setw(11) << "\nCountry" << ": " << curr.Country();
		cout << left << setw(11) << "\nCode" << ": " << curr.CurrencyCode();
		cout << left << setw(11) << "\nName" << ": " << curr.CurrencyName();
		cout << left << setw(11) << "\nRate (1$)" << ": " << curr.Rate();
		cout << "\n______________________\n";
	}

public:
	static void ShowCurrencyFindScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");

		cout << "\nFind by: [1] Code or [2] Country ? ";
		short choice = clsInputValidate::ReadShortNumberBetween(1, 2, "Enter 1 or 2? ");
		
		switch (choice)
		{
		case 1: {
			cout << "\nEnter country code: ";
			string code = clsInputValidate::ReadString();

			clsCurrency curr = clsCurrency::FindByCode(code);

			if (!curr.isEmpty()) 
			{
				cout << "\nCurrency Found.\n\n";
				_PrintCurrencyCard(curr);
			}
			else 
			{
				cout << "\nCurrency not found.\n";
			}
			break;
		}

		case 2: {
			cout << "Enter country name: ";
			string name = clsInputValidate::ReadString();

			clsCurrency curr = clsCurrency::FindByCountry(name);

			if (!curr.isEmpty())
			{
				cout << "\nCurrency Found.\n\n";
				_PrintCurrencyCard(curr);
			}
			else
			{
				cout << "\nCurrency not found.\n";
			}
			break;
		}
		}
	}
	
};

