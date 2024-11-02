#pragma once
#include "CScreen.h"
#include "CUser.h"
#include "CInputValidate.h"

class CFindUserScreen : protected CScreen
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
		cout << "\nUserName    : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

public:

	static void ShowFindUserScreen()
	{

		_DrawScreenHeader("\t  Find User Screen");

		string UserName;

		UserName = CInputValidate::ReadString("\nPlease Enter UserName: ");
		while (!CUser::IsUserExist(UserName))
		{
			UserName = CInputValidate::ReadString("\nUser is not found, choose another one: ");
		}

		CUser User1 = CUser::Find(UserName);

		if (!User1.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}

		_PrintUser(User1);

	}
};

