#pragma once
#include <iostream>
#include "CScreen.h"
#include "CCurrency.h"
#include "CInputValidate.h"

class CCurrencyCalculatorScreen :protected CScreen

{
private:

	static float _ReadAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		float Amount = 0;

		Amount = CInputValidate::ReadFloatNumber();
		return Amount;
	}

	static CCurrency _GetCurrency(string Message)
	{

		string CurrencyCode;

		CurrencyCode = CInputValidate::ReadString(Message);

		while (!CCurrency::IsCurrencyExist(CurrencyCode))
		{
			CurrencyCode = CInputValidate::ReadString("\nCurrency is not found, choose another one: ");
		}

		CCurrency Currency = CCurrency::FindByCode(CurrencyCode);
		return Currency;

	}


	static  void _PrintCurrencyCard(CCurrency Currency, string Title = "Currency Card:")
	{

		cout << "\n" << Title << "\n";
		cout << "_____________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCode          : " << Currency.CurrencyCode();
		cout << "\nName          : " << Currency.CurrencyName();
		cout << "\nRate(1$) =    : " << Currency.Rate();
		cout << "\n_____________________________\n\n";

	}

	static void _PrintCalculationsResults(float Amount, CCurrency Currency1, CCurrency Currency2)
	{

		_PrintCurrencyCard(Currency1, "Convert From:");

		float AmountInUSD = Currency1.ConvertToUSD(Amount);

		cout << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmountInUSD << " USD\n";

		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConverting from USD to:\n";

		_PrintCurrencyCard(Currency2, "To:");

		float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

		cout << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();

	}


public:

	static void ShowCurrencyCalculatorScreen()
	{
		char Continue = 'y';

		while (Continue == 'y' || Continue == 'Y')
		{
			system("cls");

			_DrawScreenHeader("\tUpdate Currency Screen");

			CCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
			CCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");

			float Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another calculation? y/n ? ";
			cin >> Continue;

		}


	}
};

