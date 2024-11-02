#pragma once
#include "CScreen.h"
#include "CUser.h"
#include "CInputValidate.h"
#include <iomanip>
#include "Global.h"

class CAddNewUserScreen : protected CScreen
{
	static void _ReadUserInfo(CUser& User)
	{
		User.FirstName = CInputValidate::ReadString("\nEnter FirstName: ");

		User.LastName = CInputValidate::ReadString("\nEnter LastName: ");

		User.Email = CInputValidate::ReadString("\nEnter Email: ");

		User.Phone = CInputValidate::ReadString("\nEnter Phone: ");

		User.Password = CInputValidate::ReadString("\nEnter Password: ");

		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static void _PrintUser(CUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

	static short _ReadPermissionsToSet()
	{

		int Permissions = 0;
		char Answer = 'n';


		//in This case The Admin is the only one can give admin permission 
		if (CurrentUser.Permissions == -1)
		{
			cout << "\nDo you want to give full access? y/n? ";
			cin >> Answer;

			if (Answer == 'y' || Answer == 'Y')
			{
				return -1;
			}
		}


		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Client List? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pUpdateClients;
		}

		cout << "\nFind Client? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pTranactions;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pManageUsers;
		}

		cout << "\Log Register? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pLoginRegister;
		}

		cout << "\Currency Exchange? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pCurrencyExchange;
		}

		return Permissions;

	}

public:

	static void ShowAddNewUserScreen()
	{

		_DrawScreenHeader("\t  Add New User Screen");

		string UserName = "";

		UserName = CInputValidate::ReadString("\nPlease Enter UserName: ");

		while (CUser::IsUserExist(UserName))
		{
			UserName = CInputValidate::ReadString("\nUserName Is Already Used, Choose another one: ");
		}

		CUser NewUser = CUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		CUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case  CUser::enSaveResults::svSucceeded:
		{
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}
		case CUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError User was not saved because it's Empty";
			break;

		}
		case CUser::enSaveResults::svFaildUserExists:
		{
			cout << "\nError User was not saved because UserName is used!\n";
			break;

		}
		}
	}

};

