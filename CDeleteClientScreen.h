#pragma once
#include"CScreen.h"
#include"CBankClient.h"
#include"CInputValidate.h"

class CDeleteClientScreen :protected CScreen
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

	void static	showDeleteClientScreen()
	{
		if (!CScreen::CheckAccessRights(CUser::enPermissions::pDeleteClient))
		{
			return;
		}

		_DrawScreenHeader("\tDelete Client Screen");

		string AccountNumber = "";

		AccountNumber = CInputValidate::ReadString("\nPlease Enter Account Number: ");

		while (!CBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = CInputValidate::ReadString("\nAccount number is not found, choose another one: ");
		}

		CBankClient Client1 = CBankClient::Find(AccountNumber);

		_PrintClient(Client1);

		cout << "\nAre you sure you want to delete this client y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{


			if (Client1.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client1);
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}
	}
};