#pragma once
#include "CScreen.h"
#include "CBankClient.h"
#include "CInputValidate.h"
#include "CDepositeScreen.h"
#include "CWithDrawScreen.h"
#include "CTotalBalancesScreen.h"
#include "CTransferScreen.h"
#include "CTransferLogScreen.h"

class CTransactionsScreen : protected CScreen
{
private:

	static enum _enTransactionsMenueOptions
	{
		eDeposite = 1, eWithDraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eMainMenue = 6
	};

	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]? ";
		short Choice = CInputValidate::ReadShortNumberBetween(1, 6);
		return Choice;
	}

	static  void _GoBackToTransactionsMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";

		system("pause>0");

		ShowTransactionsMenue();
	}

	static void _PerfromTransactionsMenueOption(_enTransactionsMenueOptions TransactionsMenueOption)
	{
		switch (TransactionsMenueOption)
		{
		case CTransactionsScreen::eDeposite:
			system("cls");
			_ShowDepositeScreen();
			_GoBackToTransactionsMenue();

			break;

		case CTransactionsScreen::eWithDraw:
			system("cls");
			_ShowWithDrawScreen();
			_GoBackToTransactionsMenue();

			break;

		case CTransactionsScreen::eTotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();

			break;

		case CTransactionsScreen::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();

			break;

		case CTransactionsScreen::eTransferLog:
			system("cls");
			_ShowTransferlogScreen();
			_GoBackToTransactionsMenue();

			break;

		case CTransactionsScreen::eMainMenue:

			break;
		}
	}

	static void _ShowDepositeScreen()
	{
		//cout << "Depostie Screen Will Be Here ! " << endl;
		CDepositeScreen::ShowDepositeScreen();
	}

	static void _ShowWithDrawScreen()
	{
		//cout << "With Draw Screen Will Be Here ! " << endl;
		CWithDrawScreen::ShowWithDrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		//cout << "Total Balances Screen Will Be Here ! " << endl;
		CTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen()
	{
		//cout << "Transfer Screen Screen Will Be Here ! " << endl;
		CTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferlogScreen()
	{
		cout << "Transfer Screen Screen Will Be Here ! " << endl;
		CTransferLogScreen::ShowTransferLogScreen();
	}

public:


	static void ShowTransactionsMenue()
	{
		system("cls");

		if (!CScreen::CheckAccessRights(CUser::enPermissions::pTranactions))
		{
			return;
		}

		_DrawScreenHeader("\tTransactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposite.\n";
		cout << setw(37) << left << "" << "\t[2] With Draw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromTransactionsMenueOption((_enTransactionsMenueOptions)_ReadTransactionsMenueOption());
	}

};

