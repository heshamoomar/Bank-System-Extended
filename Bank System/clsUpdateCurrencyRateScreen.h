#pragma once
#include <iomanip>
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
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
	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\tUpdate Currency Screen");

		cout << "Enter currency code: ";
		string code = clsInputValidate::ReadString();

		clsCurrency curr = clsCurrency::FindByCode(code);

		if (!curr.isEmpty())
		{
			cout << endl;
			_PrintCurrencyCard(curr);
			cout << "\nAre you sure, do you want to update the rate of this currency? [y/n]: ";
			char choice;
			cin >> choice;

			if (choice == 'Y' || choice == 'y') 
			{
				cout << "\nUpdate Currency Rate: ";
				cout << "\n_____________________\n";
				cout << "New Rate: ";

				float rate;
				cin >> rate;
				curr.UpdateRate(rate);

				cout << "Currency Rate updated.\n\n";
				_PrintCurrencyCard(curr);
			}

			else 
			{
				cout << "\nCancelled.\n";
			}
		}
		else
		{
			cout << "\nCurrency not found.\n";
		}
	}
};

