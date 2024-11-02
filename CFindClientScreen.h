#pragma once
#include "CScreen.h"
#include "CBankClient.h"
#include "CInputValidate.h"

class CFindClientScreen : protected CScreen
{
	static void _PrintClient(CBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.GetAccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:
	static void ShowFindClientScreen()
	{
		if (!CScreen::CheckAccessRights(CUser::enPermissions::pFindClient))
		{
			return;
		}

		_DrawScreenHeader("\t Find Client Screen");

		string AccountNumber;

		AccountNumber = CInputValidate::ReadString("Please Enter Account Number ? ");

		while (!CBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = CInputValidate::ReadString("Account Number Not Found, Please Valid one ! ");
		}

		CBankClient Client = CBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
		}
		else
		{
			cout << "\nClient Was not Found :-( \n";
		}

		_PrintClient(Client);

	}
};

