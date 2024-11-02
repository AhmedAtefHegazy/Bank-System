#pragma once
#include "CScreen.h"
#include "CBankClient.h"
#include "CInputValidate.h"

class CUpdateClientScreen :public CScreen
{
	static 	void _ReadClientInfo(CBankClient& Client)
	{
		Client.SetFirstName(CInputValidate::ReadString("Enter First Name:"));

		Client.SetLastName(CInputValidate::ReadString("Enter Last Name:"));

		Client.SetEmail(CInputValidate::ReadString("Enter Email:"));

		Client.SetPhone(CInputValidate::ReadString("Enter Phone:"));

		Client.SetPinCode(CInputValidate::ReadString("Enter Pin Code:"));

		cout << "Enter Account Balance:" << endl;
		Client.SetAccountBalance(CInputValidate::ReadDblNumber());
	}

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

	static void _Update(CBankClient Client)
	{
		_ReadClientInfo(Client);

		CBankClient::enSaveResult SaveResult;

		SaveResult = Client.Save();

		switch (SaveResult)
		{
		case CBankClient::svFailedEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;
		case CBankClient::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";

			_PrintClient(Client);
			break;
		}


	}

public:
	static void ShowUpdateClientScreen()
	{
		if (!CScreen::CheckAccessRights(CUser::enPermissions::pUpdateClients))
		{
			return;
		}

		_DrawScreenHeader("\tUpdate Client Screen");

		string AccountNumber = "";

		AccountNumber = CInputValidate::ReadString("\nPlease Enter client Account Number: ");

		while (!CBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = CInputValidate::ReadString("\nAccount number is not found, choose another one: ");
		}

		CBankClient Client1 = CBankClient::Find(AccountNumber);

		_PrintClient(Client1);

		cout << "\nAre you sure you want to update this client y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			cout << "\n\nUpdate Client Info:";
			cout << "\n____________________\n";

			_Update(Client1);
		}
	}
};

