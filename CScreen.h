#pragma once
#include "Global.h"

using namespace std;

class CScreen
{



protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t\t______________________________________";
		cout << "\n\n\t\t\t\t\t  " << Title;
		if (SubTitle != "")
		{
			cout << "\n\t\t\t\t\t  " << SubTitle;
		}
		cout << "\n\t\t\t\t\t______________________________________\n\n";

		cout << "\n\t\t\t\t\tUser:" << CurrentUser.UserName;
		cout << "\n\t\t\t\t\tDate:" << CDate::DateToString(CDate()) << "\n\n";


	}

	static bool CheckAccessRights(CUser::enPermissions Permission)
	{


		if (!CurrentUser.CheckAccessPermission(Permission))
		{
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________\n\n";
			return false;
		}
		else
			return true;


	}


};