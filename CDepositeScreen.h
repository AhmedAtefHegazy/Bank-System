#pragma once
#include "CScreen.h"
#include "CBankClient.h"
#include "CInputValidate.h"

class CDepositeScreen : protected CScreen
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

	static void ShowDepositeScreen()
	{
		_DrawScreenHeader("\t   Deposite Screen ");

		string AccountNumber = CInputValidate::ReadString("Please Enter Account Number ?");

		while (!CBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = CInputValidate::ReadString("Client With [" + AccountNumber + "] Does Not Exist !\n\nPlease Enter Account Number ?");
		}

		CBankClient Client = CBankClient::Find(AccountNumber);

		_PrintClient(Client);



		cout << "\nEnter Depostie Amount ?";
		double DepositeAmount = CInputValidate::ReadDblNumber();

		while (DepositeAmount <= 0)
		{
			cout << "\nDepostie Amount Should be greater than (zero), Enter Depostie Amount ?";
			DepositeAmount = CInputValidate::ReadDblNumber();
		}

		char Sure = 'n';

		cout << "\nAre You Sure You Want To Perform This Transaction " << endl;
		cin >> Sure;

		if (Sure == 'y' || Sure == 'Y')
		{
			Client.Deposite(DepositeAmount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << Client.AccountBalance;
		}

		else
		{
			cout << "\nOperation was cancelled.\n";
		}


	}
};

