#pragma once
#include <iostream>
#include "CScreen.h"
#include "CCurrency.h"
#include "CInputValidate.h"

class CUpdateCurrencyRateScreen :protected CScreen

{
private:

	static float _ReadRate()
	{
		cout << "\nEnter New Rate: ";
		float NewRate = 0;

		NewRate = CInputValidate::ReadFloatNumber();

		return NewRate;
	}

	static void _PrintCurrency(CCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";

	}

public:

	static void ShowUpdateCurrencyRateScreen()
	{

		_DrawScreenHeader("\tUpdate Currency Screen");

		string CurrencyCode = "";

		CurrencyCode = CInputValidate::ReadString("\nPlease Enter Currency Code: ");

		while (!CCurrency::IsCurrencyExist(CurrencyCode))
		{
			CurrencyCode = CInputValidate::ReadString("\nCurrency is not found, choose another one: ");
		}

		CCurrency Currency = CCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			cout << "\n\nUpdate Currency Rate:";
			cout << "\n____________________\n";

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);


		}

	}
};

