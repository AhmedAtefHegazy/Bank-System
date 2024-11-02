#pragma once
#include <iostream>
#include "CScreen.h"
#include "CCurrency.h"
#include "CInputValidate.h"

class CFindCurrencyScreen :protected CScreen
{

private:
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

	static void _ShowResults(CCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{

		_DrawScreenHeader("\t  Find Currency Screen");

		cout << "\nFind By: [1] Code or [2] Country ? ";
		short Answer = 1;
		Answer = CInputValidate::ReadShortNumber();

		if (Answer == 1)
		{
			string CurrencyCode;
			CurrencyCode = CInputValidate::ReadString("\nPlease Enter CurrencyCode: ");
			CCurrency Currency = CCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else
		{
			string Country;
			Country = CInputValidate::ReadString("\nPlease Enter Country Name: ");
			CCurrency Currency = CCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
	}

};

