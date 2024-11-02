#pragma once
#include "CScreen.h"
#include "CUser.h"
#include "CInputValidate.h"

class CDeleteUserScreen : protected CScreen
{
private:
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

public:
	static void ShowDeleteUserScreen()
	{

		_DrawScreenHeader("\tDelete User Screen");

		string UserName = "";

		UserName = CInputValidate::ReadString("\nPlease Enter UserName: ");
		while (!CUser::IsUserExist(UserName))
		{
			UserName = CInputValidate::ReadString("\nUser is not found, choose another one: ");
		}

		CUser User1 = CUser::Find(UserName);
		_PrintUser(User1);

		cout << "\nAre you sure you want to delete this User y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (User1.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUser(User1);
			}
			else
			{
				cout << "\a\nDelete this User is Failed, because you can't delete an Admin\n";
			}
		}
	}

};

