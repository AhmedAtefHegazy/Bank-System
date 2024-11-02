#pragma once
#include "CScreen.h"
#include "CBankClient.h"
#include "CInputValidate.h"
#include "CUser.h"
#include "CShowListUsersMenue.h"
#include "CAddNewUserScreen.h"
#include "CDeleteUserScreen.h"
#include "CUpdateUserScreen.h"
#include "CFindUserScreen.h"

class CManageUsersMenue : protected CScreen
{

	enum _enManageUsersMenueOptions { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, ManageMenue = 6 };

	static short _ReadManageUsersMenueOption()
	{
		short Choice;

		cout << "\t\t\t\t     Choose what do you want to do [1 to 6] ? ";
		Choice = CInputValidate::ReadShortNumberBetween(1, 6);

		return Choice;
	}

	static  void _GoBackToManageMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menue...\n";

		system("pause>0");

		ShowManageUsersScreen();
	}

	static void _PerfromManageUsersMenueOption(_enManageUsersMenueOptions ManageUsersMenueOptions)
	{
		switch (ManageUsersMenueOptions)
		{
		case CManageUsersMenue::eListUsers:

			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageMenue();

			break;
		case CManageUsersMenue::eAddNewUser:

			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageMenue();

			break;
		case CManageUsersMenue::eDeleteUser:

			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageMenue();

			break;
		case CManageUsersMenue::eUpdateUser:

			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageMenue();

			break;
		case CManageUsersMenue::eFindUser:

			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageMenue();

			break;

		}
	}

	static void _ShowListUsersScreen()
	{
		//cout << "List Users Screen Will Be Here ! " << endl;
		CListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		//cout << "Add New Users Screen Will Be Here ! " << endl;
		CAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		//cout << "Delete Users Screen Will Be Here ! " << endl;
		CDeleteUserScreen::ShowDeleteUserScreen();

	}

	static void _ShowUpdateUserScreen()
	{
		//cout << "Update Users Screen Will Be Here ! " << endl;
		CUpdateUserScreen::ShowUpdateUserScreen();

	}

	static void _ShowFindUserScreen()
	{
		//cout << "Find Users Screen Will Be Here ! " << endl;
		CFindUserScreen::ShowFindUserScreen();
	}


public:

	static void ShowManageUsersScreen()
	{
		system("cls");

		if (!CScreen::CheckAccessRights(CUser::enPermissions::pManageUsers))
		{
			return;
		}

		_DrawScreenHeader("\t Manage Users Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tManage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Users.\n";
		cout << setw(37) << left << "" << "\t[4] Update Users.\n";
		cout << setw(37) << left << "" << "\t[5] Find Users.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerfromManageUsersMenueOption((_enManageUsersMenueOptions)_ReadManageUsersMenueOption());
	}


};

