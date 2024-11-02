#pragma once
#include"CScreen.h"
#include"CBankClient.h"
#include"CInputValidate.h"

class CAddNewClientScreen : protected CScreen
{
private:

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

	static	void _PrintClient(CBankClient Client)
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

	static void _AddNewClient(string AccountNumber)
	{

		CBankClient NewClient = CBankClient::Get_AddNewClient_Object(AccountNumber);


		_ReadClientInfo(NewClient);

		CBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case  CBankClient::enSaveResult::svSucceeded:
		{
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
			break;
		}
		case CBankClient::enSaveResult::svFailedEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}
		case CBankClient::enSaveResult::svFailedAccountNumberExists:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}
		}

	}

public:

	static void ShowAddNewClientScreen()
	{
		if (!CScreen::CheckAccessRights(CUser::enPermissions::pAddNewClient))
		{
			return;
		}

		_DrawScreenHeader("\t  Add New Client Screen");

		string AccountNumber = "";


		AccountNumber = CInputValidate::ReadString("\nPlease Enter Account Number: ");

		while (CBankClient::IsClientExist(AccountNumber))
		{
			AccountNumber = CInputValidate::ReadString("\nAccount Number Is Already Used, Choose another one: ");
		}

		_AddNewClient(AccountNumber);
	}
};