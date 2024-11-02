//! static cannot call non static members
#pragma once

#include "CPerson.h"
#include "CString.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class CBankClient : public CPerson
{
	enum enMode
	{
		EmptyMode = 1,
		UpdateMode = 2,
		AddNewMode = 3,
	};

	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDeleted = false;

	static CBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vString = CString::Split(Line, Seperator);

		return CBankClient(enMode::UpdateMode, vString[0], vString[1],
			vString[2], vString[3], vString[4], vString[5], stod(vString[6]));
	}

	static string _ConvertClientObjectToLine(CBankClient Client, string Seperator = "#//#")
	{
		string Line = "";

		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.AccountNumber + Seperator;
		Line += Client.PinCode + Seperator;
		Line += to_string(Client.AccountBalance);

		return Line;
	}

	static CBankClient _GetEmptyClientObject()
	{
		return CBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static void _SaveCleintsDataToFile(vector <CBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (CBankClient C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();

		}
	}

	static  vector <CBankClient> _LoadClientsDataFromFile()
	{

		vector <CBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				CBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}

	static void _AddDateLineToFile(string stDataLine)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <CBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (CBankClient& C : _vClients)
		{
			if (C.GetAccountNumber() == GetAccountNumber())
			{
				C = *this;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);

	}

	void _AddNew()
	{
		_AddDateLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareLogInRecord(double AmountToTransfer, CBankClient DestinationClient, string UserName, string Seperator = "#//#")
	{
		string TransferRecord = "";
		TransferRecord += CDate::GetSystemDateTimeString() + Seperator;
		TransferRecord += AccountNumber + Seperator;
		TransferRecord += DestinationClient.AccountNumber + Seperator;
		TransferRecord += to_string(AmountToTransfer) + Seperator;
		TransferRecord += to_string(AccountBalance) + Seperator;
		TransferRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferRecord += UserName;

		return TransferRecord;
	}

	void _TransferRegister(double AmountToTransfer, CBankClient DestinationClient, string UserName, string Seperator = "#//#")
	{

		string stDataLine = _PrepareLogInRecord(AmountToTransfer, DestinationClient, UserName, Seperator);

		fstream MyFile;

		MyFile.open("TransferRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	struct stTrnsferLogRecord;

	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = CString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;

	}

public:

	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;

	};

	CBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double AccountBalance)
		: CPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDeleted;
	}

	string GetAccountNumber()
	{
		return _AccountNumber;
	}

	__declspec(property(get = GetAccountNumber)) string AccountNumber;

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return _AccountBalance;
	}

	_declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	// we are using the ui in the ui classes not here
	//void Print()
	//{
	//	cout << "\nClient Card:";
	//	cout << "\n___________________";
	//	cout << "\nFirstName   : " << GetFirstName();
	//	cout << "\nLastName    : " << GetLastName();
	//	cout << "\nFull Name   : " << FullName();
	//	cout << "\nEmail       : " << GetEmail();
	//	cout << "\nPhone       : " << GetPhone();
	//	cout << "\nAcc. Number : " << _AccountNumber;
	//	cout << "\nPassword    : " << _PinCode;
	//	cout << "\nBalance     : " << _AccountBalance;
	//	cout << "\n___________________\n";
	//}

	static CBankClient Find(string AccountNumber)
	{
		vector<CBankClient> vClient;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				CBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();

					return Client;
				}
			}
		}

		return _GetEmptyClientObject();
	}

	static CBankClient Find(string AccountNumber, string PinCode)
	{
		vector<CBankClient> vClient;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				CBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.GetAccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		CBankClient Client = Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	enum enSaveResult
	{
		svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2
	};

	enSaveResult Save()
	{
		// دايما حاول تفصل ui عن اللي جوا في الكلاس

		switch (_Mode)
		{
		case CBankClient::EmptyMode:

			if (IsEmpty())
			{
				return enSaveResult::svFailedEmptyObject;
			}

			break;

		case CBankClient::UpdateMode:

			_Update();

			return enSaveResult::svSucceeded;

			break;

		case CBankClient::AddNewMode:

			if (IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFailedAccountNumberExists;
			}

			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}

			break;
		}
	}

	static CBankClient Get_AddNewClient_Object(string AccountNumber)
	{
		return CBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{

		vector<CBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (CBankClient& C : vClients)
		{
			if (C.AccountNumber == _AccountNumber)
			{
				C._MarkedForDeleted = true;
				break;
			}
		}

		_SaveCleintsDataToFile(vClients);
		*this = _GetEmptyClientObject();

		return true;

	}

	static vector<CBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	void Deposite(double DepostieAmount)
	{
		_AccountBalance += DepostieAmount;
		Save();
	}

	bool WithDraw(double WithDrawAmount)
	{
		if (WithDrawAmount > _AccountBalance)
		{
			return false;
		}

		else
		{
			_AccountBalance -= WithDrawAmount;
			Save();
		}
	}

	static double GetTotalBalances()
	{
		double TotalBalances = 0;
		vector<CBankClient> vClient = _LoadClientsDataFromFile();

		for (short i = 0; i < vClient.size(); i++)
		{
			TotalBalances += vClient[i].GetAccountBalance();
		}

		return TotalBalances;
	}

	bool Transfer(double Amount, CBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		WithDraw(Amount);
		DestinationClient.Deposite(Amount);
		_TransferRegister(Amount, DestinationClient, UserName);

		return true;
	}



	static  vector <stTrnsferLogRecord> GetTransfersLogList()
	{
		vector <stTrnsferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferRegister.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stTrnsferLogRecord TransferRecord;

			while (getline(MyFile, Line))
			{

				TransferRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferRecord);

			}

			MyFile.close();

		}

		return vTransferLogRecord;

	}
};
