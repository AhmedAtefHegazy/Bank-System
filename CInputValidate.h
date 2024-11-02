#pragma once

#include "CDate.h"
#include "CUtil.h"
#include <limits>

using namespace std;

class CInputValidate
{
public:
	static bool IsNumberBetween(short Number, short From, short To)
	{
		return !((Number > To || Number < From) ? true : false);
	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return !((Number > To || Number < From) ? true : false);
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		return !((Number > To || Number < From) ? true : false);
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return !((Number > To || Number < From) ? true : false);
	}

	static bool IsDateBetween(CDate Date, CDate DateFrom, CDate DateTo)
	{
		if (CDate::CompareDates(DateFrom, DateTo) == CDate::After)
			CUtil::Swap(DateFrom, DateTo);

		return ((CDate::CompareDates(Date, DateFrom) == CDate::After ||
			CDate::CompareDates(Date, DateFrom) == CDate::Equal) &&
			(CDate::CompareDates(Date, DateTo) == CDate::Before ||
				CDate::CompareDates(Date, DateTo) == CDate::Equal));
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again: ")
	{
		int Num;

		cin >> Num;

		while (cin.fail() /*or !(cin >> Num)*/)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Num;
		}

		return Num;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within the range, it should be between ")
	{
		int Num = ReadIntNumber();

		while (!IsNumberBetween(Num, From, To))
		{
			cout << ErrorMessage << From << " and " << To << endl;
			Num = ReadIntNumber();
		}

		return Num;
	}

	static int ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again: ")
	{
		short Num;

		cin >> Num;

		while (cin.fail() /*or !(cin >> Num)*/)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Num;
		}

		return Num;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within the range, it should be between ")
	{
		short Num = ReadIntNumber();

		while (!IsNumberBetween(Num, From, To))
		{
			cout << ErrorMessage << From << " and " << To << endl;
			Num = ReadShortNumber();
		}

		return Num;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again:")
	{
		double Num;

		cin >> Num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Num;
		}

		return Num;
	}

	static double ReadDblBetween(double From, double To, string ErrorMessage = "Number is not within the range, it should be between ")
	{
		double Num = ReadDblNumber();

		while (!IsNumberBetween(Num, From, To))
		{
			cout << ErrorMessage << From << " and " << To << endl;
			Num = ReadDblNumber();
		}

		return Num;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again:")
	{
		float Num;

		cin >> Num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage << endl;
			cin >> Num;
		}

		return Num;
	}

	static float ReadFloatBetween(float From, float To, string ErrorMessage = "Number is not within the range, it should be between ")
	{
		float Num = ReadFloatNumber();

		while (!IsNumberBetween(Num, From, To))
		{
			cout << ErrorMessage << From << " and " << To << endl;
			Num = ReadFloatNumber();
		}

		return Num;
	}

	static string ReadString(string Sentence = "Enter a string :")
	{
		string S1 = "";

		cout << Sentence << endl;
		getline(cin >> ws, S1);

		return S1;
	}

	static bool IsValidDate(CDate DateToCheck)
	{
		return CDate::IsValidDate(DateToCheck);
	}
};