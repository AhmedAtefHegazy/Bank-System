#pragma once
#include "CScreen.h"
#include <vector>

class CLoginRegisterMenue : protected CScreen
{

	static void PrintLoginRegisterRecordLine(CUser::stLoginRegisterRecord LoginRegisterRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
		cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
		cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CScreen::CheckAccessRights(CUser::enPermissions::pLoginRegister))
		{
			return;
		}

		vector <CUser::stLoginRegisterRecord> vLoginRegisterRecord = CUser::GetLoginRegisterList();

		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vLoginRegisterRecord.size() == 0)
			cout << "\t\t\t\tNo Logins Available In the System!";
		else

			for (CUser::stLoginRegisterRecord Record : vLoginRegisterRecord)
			{

				PrintLoginRegisterRecordLine(Record);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};

