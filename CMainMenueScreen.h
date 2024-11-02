#pragma once
#include <iostream>
#include "CScreen.h"
#include "CInputValidate.h"
#include "CClientListScreen.h"
#include "CAddNewClientScreen.h"
#include "CDeleteClientScreen.h"
#include "CUpdateClientScreen.h"
#include "CFindClientScreen.h"
#include "CTransactionsScreen.h"
#include "CManageUsersMenue.h"
#include "CLoginRegisterMenue.h"
#include "CCurrencyExchangeMenue.h"
#include "Global.h"
#include <iomanip>

using namespace std;

class CMainMenueScreen :protected CScreen
{

private:

	enum _enMainMenueOptions
	{
		eListClients = 1, eAddNewClient = 2
		, eDeleteClient = 3, eUpdateClient = 4
		, eFindClient = 5, eShowTransactionsMenue = 6
		, eManageUsers = 7, eLoginRegister = 8, eCurrencyExcahnge = 9, eExit = 10
	};

	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 10]? ";
		short Choice = CInputValidate::ReadShortNumberBetween(1, 10);

		return Choice;
	}

	static  void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");

		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		CClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		//cout << "\nAdd New Client Screen Will be here...\n";
		CAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		//cout << "\nDelete Client Screen Will be here...\n";
		CDeleteClientScreen::showDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		//cout << "\nUpdate Client Screen Will be here...\n";
		CUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		//cout << "\nFind Client Screen Will be here...\n";
		CFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		//cout << "\nTransactions Menue Will be here...\n";
		CTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenue()
	{
		//cout << "\nUsers Menue Will be here...\n";
		CManageUsersMenue::ShowManageUsersScreen();
	}

	static void _ShowLoginRegisterMenue()
	{
		//cout << "\nLogin Register Menue Will be here...\n";
		CLoginRegisterMenue::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMenue()
	{
		//cout << "\nLogin Register Menue Will be here...\n";
		CCurrencyExchangeMenue::ShowCurrenciesMenue();
	}

	static void _Logout()
	{
		//cout << "\nEnd Screen Will be here...\n";
		CurrentUser = CUser::Find("", "");

	}

	static void _PerfromMainMenueOption(_enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case _enMainMenueOptions::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case _enMainMenueOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;

		case _enMainMenueOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;

		case _enMainMenueOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;

		case _enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;

		case _enMainMenueOptions::eShowTransactionsMenue:
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;

		case _enMainMenueOptions::eManageUsers:
			system("cls");
			_ShowManageUsersMenue();
			_GoBackToMainMenue();
			break;

		case _enMainMenueOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegisterMenue();
			_GoBackToMainMenue();
			break;

		case _enMainMenueOptions::eCurrencyExcahnge:
			system("cls");
			_ShowCurrencyExchangeMenue();
			_GoBackToMainMenue();
			break;

		case _enMainMenueOptions::eExit:
			system("cls");
			_Logout();



			break;
		}

	}

public:

	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1]  Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2]  Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3]  Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4]  Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5]  Find Client.\n";
		cout << setw(37) << left << "" << "\t[6]  Transactions.\n";
		cout << setw(37) << left << "" << "\t[7]  Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8]  Login Register.\n";
		cout << setw(37) << left << "" << "\t[9]  Currency Excahnge.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromMainMenueOption((_enMainMenueOptions)_ReadMainMenueOption());
	}
};

