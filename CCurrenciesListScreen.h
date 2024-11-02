#pragma once

#include <iostream>
#include "CScreen.h"
#include "CCurrency.h"
#include <iomanip>

class CCurrenciesListScreen :protected CScreen
{

private:
	static void PrintCurrencyRecordLine(CCurrency Currency)
	{

		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
		cout << "| " << setw(8) << left << Currency.CurrencyCode();
		cout << "| " << setw(45) << left << Currency.CurrencyName();
		cout << "| " << setw(10) << left << Currency.Rate();

	}

public:


	static void ShowCurrenciesListScreen()
	{


		vector <CCurrency> vCurrencys = CCurrency::GetCurrenciesList();
		string Title = "\t  Currencies List Screen";
		string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency.";

		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		if (vCurrencys.size() == 0)
			cout << "\t\t\t\tNo Currencies Available In the System!";
		else

			for (CCurrency Currency : vCurrencys)
			{

				PrintCurrencyRecordLine(Currency);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

	}

};

