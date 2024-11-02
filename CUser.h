#pragma once
#include <iostream>
#include <string>
#include "CPerson.h"
#include "CString.h"
#include "CDate.h"
#include "CUtil.h"
#include <vector>
#include <fstream>

using namespace std;

class CUser : public CPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	short _Permissions;
	bool _MarkedForDelete = false;

	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += CDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

	static CUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = CString::Split(Line, Seperator);

		return CUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], CUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));

	}

	static string _ConverUserObjectToLine(CUser User, string Seperator = "#//#")
	{

		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		UserRecord += CUtil::EncryptText(User.Password) + Seperator;
		UserRecord += to_string(User.Permissions);

		return UserRecord;

	}

	static  vector <CUser> _LoadUsersDataFromFile()
	{

		vector <CUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				CUser User = _ConvertLinetoUserObject(Line);

				vUsers.push_back(User);
			}

			MyFile.close();

		}

		return vUsers;

	}

	static void _SaveUsersDataToFile(vector <CUser> vUsers)
	{

		fstream MyFile;

		MyFile.open("Users.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (CUser U : vUsers)
			{
				if (U.MarkedForDeleted() == false)
				{
					//we only write records that are not marked for delete.  
					DataLine = _ConverUserObjectToLine(U);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}

	}

	bool _Update()
	{
		vector <CUser> _vUsers;

		_vUsers = _LoadUsersDataFromFile();

		for (CUser& U : _vUsers)
		{
			if (U.UserName == UserName)
			{
				if (U.Permissions != enPermissions::eAll)
				{
					U = *this;

					break;
				}

				else
					return false;
			}

		}

		_SaveUsersDataToFile(_vUsers);


	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static CUser _GetEmptyUserObject()
	{
		return CUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;


		vector <string> LoginRegisterDataLine = CString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[2]);

		return LoginRegisterRecord;

	}

public:

	CUser(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string UserName, string Password, int Permissions) :
		CPerson(FirstName, LastName, Email, Phone)

	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}


	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		int Permissions;

	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	string GetUserName()
	{
		return _UserName;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}

	short GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;

	static CUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				CUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();

		}

		return _GetEmptyUserObject();
	}

	static CUser Find(string UserName, string Password)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				CUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();

		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2, svFaildUserIsAdmin = 3 };

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128, pCurrencyExchange = 256
	};


	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			if (_Update())
				return enSaveResults::svSucceeded;
			else
				return enSaveResults::svFaildUserIsAdmin;
			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (CUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserExists;
			}

			else
			{
				_AddNew();
				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}

		}

	}

	static bool IsUserExist(string UserName)
	{
		CUser User = CUser::Find(UserName);
		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector <CUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (CUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{

				if (U.Permissions != enPermissions::eAll)
				{
					U._MarkedForDelete = true;
					break;
				}

				else
					return false;
			}

		}

		_SaveUsersDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}

	static CUser GetAddNewUserObject(string UserName)
	{
		return CUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <CUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;
		return ((Permission & this->Permissions) == Permission) ? true : false;
	}

	void LoginRegister()
	{

		string stDataLine = _PrepareLogInRecord();

		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static  vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{

				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);

			}

			MyFile.close();

		}

		return vLoginRegisterRecord;

	}

};

