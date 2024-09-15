#pragma once
#include "clsInputValidate.h"
#include "clsCurrencyListScreen.h"
#include "clsCurrencyFindScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen :clsScreen
{
private:
	enum enMenuOptions
	{
		eListCurrencies = 1,
		eFindCurrency = 2,
		eUpdateRate = 3,
		eCurrencyCalculator = 4,
		eMainMenu = 5, 
	};

	static short _ChooseMenuOption() {
		short choice;
		cout << "\t\t\t\t     Choose what do you want to do: [1 to 5]? ";
		choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return choice;
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowCurrnecyExchangeScreen();
	}

	static void _ShowListCurrenciesScreen()
	{
		clsCurrencyListScreen::ShowCurrencyListScreen();
	}
	static void _ShowFindCurrenciesScreen()
	{
		clsCurrencyFindScreen::ShowCurrencyFindScreen();
	}
	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _ShowCalculateCurrenciesScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformMenuOptions()
	{
		switch (_ChooseMenuOption())
		{
		case clsCurrencyExchangeScreen::eListCurrencies: {
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsCurrencyExchangeScreen::eFindCurrency: {
			system("cls");
			_ShowFindCurrenciesScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsCurrencyExchangeScreen::eUpdateRate: {
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsCurrencyExchangeScreen::eCurrencyCalculator: {
			system("cls");
			_ShowCalculateCurrenciesScreen();
			_GoBackToTransactionsMenue();
			break;
		}
		case clsCurrencyExchangeScreen::eMainMenu:
			//	do nothing here
			break;
		}
	}

public:


	static void ShowCurrnecyExchangeScreen() {
		system("cls");
		_DrawScreenHeader("   Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exchange Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformMenuOptions();
	}
};

