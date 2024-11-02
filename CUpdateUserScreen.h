#pragma once
#include "CScreen.h"
#include "CUser.h"
#include "CInputValidate.h"

class CUpdateUserScreen : protected CScreen
{

private:


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

	static int _ReadPermissionsToSet()
	{

		int Permissions = 0;
		char Answer = 'n';


		cout << "\nDo you want to give full access? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			return -1;
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

		cout << "\nLog Register? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pLoginRegister;
		}

		cout << "\nCurrency Exchange? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += CUser::enPermissions::pCurrencyExchange;
		}

		return Permissions;

	}

public:

	static void ShowUpdateUserScreen()
	{

		_DrawScreenHeader("\tUpdate User Screen");

		string UserName = "";


		UserName = CInputValidate::ReadString("\nPlease Enter User UserName: ");

		while (!CUser::IsUserExist(UserName))
		{
			UserName = CInputValidate::ReadString("\nAccount number is not found, choose another one: ");
		}

		CUser User1 = CUser::Find(UserName);

		_PrintUser(User1);

		cout << "\nAre you sure you want to update this User y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";


			_ReadUserInfo(User1);

			CUser::enSaveResults SaveResult;

			SaveResult = User1.Save();

			switch (SaveResult)
			{
			case  CUser::enSaveResults::svSucceeded:
			{
				cout << "\nUser Updated Successfully :-)\n";

				_PrintUser(User1);
				break;
			}
			case CUser::enSaveResults::svFaildEmptyObject:
			{
				cout << "\a\nError User was not saved because it's Empty";
				break;

			}

			case CUser::enSaveResults::svFaildUserIsAdmin:

				cout << "\a\nThis Is Admin Can't Be Updated !\n";
				break;

			}

		}

	}

};