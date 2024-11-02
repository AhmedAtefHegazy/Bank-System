#pragma once
#include "CScreen.h"
#include "CBankClient.h"
#include "CInputValidate.h"

class CTransferScreen : protected CScreen
{
	static void _PrintClientCard(CBankClient Client)
	{
		cout << "\nClient Card:" << endl;
		cout << "\n___________________________________\n";
		cout << "\nFull Name    :" << Client.FullName();
		cout << "\nAcc. Number  :" << Client.AccountNumber;
		cout << "\nBalance	    :" << Client.AccountBalance;
		cout << "\n___________________________________\n";
	}

	static string _PrepareLogInRecord(string SourceAccNumber, string DestinationAccNumber, double AmountToTransfer
		, double SourceBalance, double DestinationBalance, string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += CDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += SourceAccNumber + Seperator;
		LoginRecord += DestinationAccNumber + Seperator;
		LoginRecord += to_string(AmountToTransfer) + Seperator;
		LoginRecord += to_string(SourceBalance) + Seperator;
		LoginRecord += to_string(DestinationBalance) + Seperator;
		LoginRecord += CurrentUser.UserName;

		return LoginRecord;
	}

	static void TransferRegister(string SourceAccNumber, string DestinationAccNumber, double AmountToTransfer
		, double SourceBalance, double DestinationBalance, string Seperator = "#//#")
	{

		string stDataLine = _PrepareLogInRecord(SourceAccNumber, DestinationAccNumber, AmountToTransfer
			, SourceBalance, DestinationBalance, Seperator);

		fstream MyFile;

		MyFile.open("TransferRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t    Transfer Screen");

		string SourceAccNumber = CInputValidate::ReadString("Please Enter Account Number To Transfer From:\n");

		CBankClient SourceClient = CBankClient::Find(SourceAccNumber);

		while (!CBankClient::IsClientExist(SourceAccNumber))
		{
			SourceAccNumber = CInputValidate::ReadString("Invalid Account Number, Please Enter Account Number To Transfer From:");
			SourceClient = CBankClient::Find(SourceAccNumber);
		}

		_PrintClientCard(SourceClient);

		string DestinationAccNumber = CInputValidate::ReadString("\nPlease Enter Account Number To Transfer To:\n");

		CBankClient DestinationClient = CBankClient::Find(DestinationAccNumber);

		while ((DestinationClient.AccountNumber == SourceClient.AccountNumber) || !(CBankClient::IsClientExist(DestinationAccNumber)))
		{

			if ((DestinationClient.AccountNumber == SourceClient.AccountNumber))
			{
				DestinationAccNumber = CInputValidate::ReadString("Can't be the same Account Number, Please Enter Account Number To Transfer To:\n");
				DestinationClient = CBankClient::Find(DestinationAccNumber);

			}

			if (!CBankClient::IsClientExist(DestinationAccNumber))
			{
				DestinationAccNumber = CInputValidate::ReadString("Invalid Account Number, Please Enter Account Number To Transfer To:\n");
				DestinationClient = CBankClient::Find(DestinationAccNumber);
			}

		}

		_PrintClientCard(DestinationClient);


		double AmountToTransfer;

		cout << "\nEnter Transfer Amount ?" << endl;
		AmountToTransfer = CInputValidate::ReadDblBetween(0, SourceClient.AccountBalance, "Amount Exceeds the available Balance, Enter another Amount ?");

		char Confirm;
		cout << "\nAre you sure want to perform this operation (y/n) ?" << endl;
		cin >> Confirm;

		if (Confirm == 'Y' || Confirm == 'y')
		{
			if (SourceClient.Transfer(AmountToTransfer, DestinationClient, CurrentUser.UserName))
				cout << "\nTransfer done successfully." << endl;
			else
				cout << "\nTransfer Failed." << endl;



			_PrintClientCard(SourceClient);
			_PrintClientCard(DestinationClient);


		}

	}
};

