#pragma once
#pragma warning(disable : 4996)

#include "CString.h"
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

class CDate
{
private:
	short _Day = 1, _Month = 1, _Year = 1900;

public:
	CDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}

	CDate(string SDate)
	{
		vector<string> vDate = CString::Split(SDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	CDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	CDate(short DaysOrderInYear, short Year)
	{
		*this = GetDateFromDayOrderInYear(DaysOrderInYear, Year);
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	static string GetSystemDateTimeString()
	{
		//system datetime string
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		string Ho, Mi, Se;

		Hour = (Hour > 12) ? Hour - 12 : Hour;
		Ho = ((Hour <= 9) ? "0" + to_string(Hour) : to_string(Hour));
		Mi = ((Minute <= 9) ? "0" + to_string(Minute) : to_string(Minute));
		Se = ((Second <= 9) ? "0" + to_string(Second) : to_string(Second));

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ Ho + ":" + Mi + ":" + Se);

	}


	//! Not Secure Function (Recursion)
	static string NumberToText(int Number)
	{

		if (Number == 0)
			return "";

		if (Number >= 1 && Number <= 19)
		{
			string Arr[] = { "", "One", "Two", "Three",
							"Four", "Five", "Six", "Seven",
							"Eight", "Nine", "Ten", "Eleven",
							"Twelve", "Therteen", "Fourteen", "Fifteen",
							"Sixteen", "Seventeen", "Eighteen", "Ninteen" };

			return Arr[Number];
		}

		if (Number >= 20 && Number <= 99)
		{
			string Arr[] = { "", "", "Twenty", "Thirty", "Forty",
							"Fifty", "Sixty", "Seventy", "Eighty", "Ninty" };
			return Arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{

			return "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{

			return NumberToText(Number / 100) + " Hundred " +
				NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{

			return "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{

			return NumberToText(Number / 1000) + " Thousand " +
				NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{

			return "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 9999999)
		{

			return NumberToText(Number / 1000000) + " Million " +
				NumberToText(Number % 1000000);
		}

		if (Number >= 10000000 && Number <= 19999999)
		{

			return "One Billion " + NumberToText(Number % 10000000);
		}

		else
		{
			return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}
	}

	static int ReadNumber()
	{
		int Number;
		cout << "\nEnter a Number? ";
		cin >> Number;
		return Number;
	}

	static short ReadYear()
	{
		short Year;

		cout << "Enter a Year ? \n";
		cin >> Year;

		return Year;
	}

	static short ReadMonth()
	{
		short Month;

		cout << "Enter a Month ? \n";
		cin >> Month;

		return Month;
	}

	static short ReadDay()
	{
		short Day;

		cout << "Enter a Day ? \n";
		cin >> Day;

		return Day;
	}

	static bool IsLeapYear(short Year)
	{

		if (Year % 100 == 0)
		{
			if (Year % 400 == 0)
				return true;
			else
				return false;
		}

		else
		{

			if (Year % 4 == 0)
				return true;
			else
				return false;
		}
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(_Year);
	}

	static short NumberOfHoursInDay(short Year, short Month)
	{
		return NumberOfDaysInMonth(Year, Month) * 24;
	}

	short NumberOfHoursInDay()
	{
		return NumberOfHoursInDay(_Year, _Month);
	}

	static int NumberOfMinutesInHours(short Year)
	{
		return NumberOfMinutesInHours(Year) * 60;
	}

	int NumberOfMinutesInHours()
	{
		return NumberOfMinutesInHours(_Year);
	}

	static int NumberOfSecondsInMinutes(short Year)
	{
		return NumberOfMinutesInHours(Year) * 60;
	}

	int NumberOfSecondsInMinutes()
	{
		return NumberOfSecondsInMinutes(_Year);
	}

	static short NumberOfDaysInMonth(short Year, short Month)
	{
		if (Month <= 0 || Month > 12)
			return 0;

		else if (Month == 2)
			return IsLeapYear(Year) ? 29 : 28;

		else
		{
			short Arr[7] = { 1, 3, 5, 7, 8, 10, 12 };

			for (short i = 1; i <= 7; i++)
			{
				if (Arr[i - 1] == Month)
					return 31;
			}
		}

		return 30;
	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static int NumberOfMinutesInHours(short Year, short Month)
	{
		return NumberOfHoursInDay(Year, Month) * 60;
	}

	static int NumberOfSecondsInMinutes(short Year, short Month)
	{
		return NumberOfMinutesInHours(Year, Month) * 60;
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a = ((14 - Month) / 12);
		short y = Year - a;
		short m = Month + (12 * a) - 2;
		return ((Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);
	}

	static short DayOfWeekOrder(CDate Date)
	{
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}

	static string DayShortName(short DayOrder)
	{
		string Arr[7] = { "sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return Arr[DayOrder];
	}

	static string MonthShortName(short Month)
	{
		string Arr[13] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		return Arr[Month];
	}

	static void PrintMonthCalender(short Month, short Year)
	{
		short NumberOfDays = NumberOfDaysInMonth(Year, Month);
		short Current = DayOfWeekOrder(1, Month, Year);

		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short i;

		for (i = 0; i < Current; i++)
			printf("     ");

		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		cout << "\n  __________________________________\n\n";
	}

	void PrintMonthCalender()
	{
		PrintMonthCalender(_Month, _Year);
	}

	static void PrintYearCalender(short Year)
	{
		printf("\n ___________________________________\n\n");
		printf("            Calender - %d         \n", Year);
		printf(" ___________________________________\n");

		for (short i = 1; i <= 12; i++)
		{
			cout << '\n';
			PrintMonthCalender(i, Year);
		}

		cout << '\n';

		return;
	}

	void PrintYearCalender()
	{
		PrintYearCalender(_Year);
	}

	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{

		short TotalDays = 0;

		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(Year, i);
		}

		TotalDays += Day;

		return TotalDays;
	}

	static short NumberOfDaysFromTheBeginingOfTheYear(CDate Date)
	{
		return NumberOfDaysFromTheBeginingOfTheYear(Date._Day, Date._Month, Date._Year);
	}

	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(*this);
	}

	static CDate GetDateFromDayOrderInYear(short DaysOrderInYear, short Year)
	{

		CDate Date;
		short RemainingDays = DaysOrderInYear;
		short YearDays = 0;
		short MonthDays = 0;
		Date._Year = Year;
		Date._Month = 1;
		while (true)
		{
			YearDays = NumberOfDaysInYear(Date._Year + 1);
			MonthDays = NumberOfDaysInMonth(Year, Date._Month);
			if (RemainingDays > YearDays)
			{
				RemainingDays -= YearDays;
				Date._Year++;
			}

			else if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
			return 0;
		int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : days[Month - 1];
	}

	static CDate ReadFullDate()
	{
		CDate Date;

		Date._Day = ReadDay();
		Date._Month = ReadMonth();
		Date._Year = ReadYear();

		return Date;
	}

	void SetFullDate()
	{
		*this = ReadFullDate();
	}

	static short ReadDaysToAdd()
	{
		short Days;
		cout << "\nHow many days to add? ";
		cin >> Days;
		return Days;
	}

	static CDate DateAddDays(short Days, CDate Date)
	{
		short RemainingDays =
			Days + NumberOfDaysFromTheBeginingOfTheYear(Date._Day, Date._Month, Date._Year);

		short MonthDays = 0;

		Date._Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;

				if (Date._Month > 12)
				{
					Date._Month = 1;
					Date._Year++;
				}
			}

			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	void DateAddDays(short Days)
	{
		*this = DateAddDays(Days, *this);
	}

	static bool IsDateBeforeDate2(CDate Date1, CDate Date2)
	{

		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}

	bool IsDateBeforeSecondDate(CDate Date2)
	{
		return IsDateBeforeDate2(*this, Date2);
	}

	static bool IsDateEqualDate2(CDate Date1, CDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day) ? true : false) : false) : false;
	}

	bool IsDateEqualDate2(CDate Date2)
	{
		return IsDateEqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(CDate Date)
	{
		return (Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	static CDate AddOneDay(CDate Date)
	{

		if (IsLastDayInMonth(Date))
		{
			Date._Day = 1;

			if (IsLastMonthInYear(Date._Month))
			{
				Date._Month = 1;
				Date._Year++;
			}
			else
				Date._Month++;
		}

		else
		{
			Date._Day++;
		}

		return Date;
	}

	void AddOneDay()
	{
		*this = AddOneDay(*this);
	}

	static void SwapDates(CDate& Date1, CDate& Date2)
	{
		CDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	void SwapDates(CDate& Date)
	{
		SwapDates(*this, Date);
	}

	static int GetDifferenceInDays(CDate Date1, CDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!IsDateBeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDateBeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return (IncludeEndDay) ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	int GetDifferenceInDays(CDate Date, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date, IncludeEndDay);
	}

	static short CalculateMyAgeInDays(CDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, CDate::GetSystemDate(), true);
	}

	static CDate GetSystemDate()
	{

		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return CDate(Day, Month, Year);
	}

	static CDate IncreaseDateByXDay(CDate& Date, short Days)
	{
		for (short i = 0; i < Days; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDay(short Days)
	{
		*this = IncreaseDateByXDay(*this, Days);
	}

	static CDate IncreaseDateByOneWeek(CDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static CDate IncreaseDateByXWeek(CDate& Date, short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void IncreaseDateByXWeek(short Weeks)
	{
		*this = IncreaseDateByXWeek(*this, Weeks);
	}

	static CDate IncreaseDateByOneMonth(CDate& Date)
	{
		for (short i = 0; i < NumberOfDaysInAMonth(Date._Month + 1, Date._Year); i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static CDate IncreaseDateByXMonth(CDate& Date, short Months)
	{
		for (short i = 0; i < Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonth(short Months)
	{
		*this = IncreaseDateByXMonth(*this, Months);
	}

	static CDate IncreaseDateByOneYear(CDate& Date)
	{
		Date._Year++;

		return Date;
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static CDate IncreaseDateByXYear(CDate& Date, short Years)
	{
		for (short i = 0; i < Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	void IncreaseDateByXYear(short Years)
	{
		*this = IncreaseDateByXYear(*this, Years);
	}

	static CDate IncreaseDateByXYear_Faster(CDate& Date, short Years)
	{
		Date._Year += Years;

		return Date;
	}

	void IncreaseDateByXYear_Faster(short Years)
	{
		*this = IncreaseDateByXYear_Faster(*this, Years);
	}

	static CDate IncreaseDateByOneDecades(CDate& Date)
	{
		Date._Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecades()
	{
		*this = IncreaseDateByOneDecades(*this);
	}

	static CDate IncreaseDateByXDecades(CDate& Date, short Decadess)
	{
		for (short i = 0; i < Decadess; i++)
		{
			Date = IncreaseDateByOneDecades(Date);
		}

		return Date;
	}

	void IncreaseDateByXDecades(short Decadess)
	{
		*this = IncreaseDateByXDecades(*this, Decadess);
	}

	static CDate IncreaseDateByXDecades_Faster(CDate& Date, short Decades)
	{
		Date._Year += Decades * 10;

		return Date;
	}

	void IncreaseDateByXDecades_Faster(short Decades)
	{
		*this = IncreaseDateByXDecades_Faster(*this, Decades);
	}

	static CDate IncreaseDateByOneCentury(CDate& Date)
	{
		Date._Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static CDate IncreaseDateByOneMillennium(CDate& Date)
	{
		Date._Year += 1000;

		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static CDate DecreaseDateByOneDay(CDate& Date)
	{
		if (Date._Day == 1)
		{
			if (Date._Month == 1)
			{
				Date._Month = 12;
				Date._Day = 31;
				Date._Year--;
			}
			else
			{
				Date._Month--;
				Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
			}
		}
		else
		{
			Date._Day--;
		}
		return Date;
	}

	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static CDate DecreaseDateByXDay(CDate& Date, short Days)
	{
		for (short i = 0; i < Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByXDay(short Days)
	{
		*this = DecreaseDateByXDay(*this, Days);
	}

	static CDate DecreaseDateByOneWeek(CDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static CDate DecreaseDateByXWeek(CDate& Date, short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void DecreaseDateByXWeek(short Weeks)
	{
		*this = DecreaseDateByXWeek(*this, Weeks);
	}

	static CDate DecreaseDateByOneMonth(CDate& Date)
	{
		if (Date._Month == 1)
		{
			Date._Month = 12;
			Date._Year--;
		}

		else
			Date._Month--;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

		if (Date._Day > NumberOfDaysInCurrentMonth)
		{
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static CDate DecreaseDateByXMonth(CDate& Date, short Months)
	{
		for (short i = 0; i < Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void DecreaseDateByXMonth(short Months)
	{
		*this = DecreaseDateByXMonth(*this, Months);
	}

	static CDate DecreaseDateByOneYear(CDate& Date)
	{
		Date._Year--;

		return Date;
	}

	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static CDate DecreaseDateByXYear(CDate& Date, short Years)
	{
		for (short i = 0; i < Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByXYear(short Years)
	{
		*this = DecreaseDateByXYear(*this, Years);
	}

	static CDate DecreaseDateByXYear_Faster(CDate& Date, short Years)
	{
		Date._Year -= Years;
		return Date;
	}

	void DecreaseDateByXYear_Faster(short Years)
	{
		*this = DecreaseDateByXYear_Faster(*this, Years);
	}

	static CDate DecreaseDateByOneDecade(CDate& Date)
	{
		Date._Year -= 10;

		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static CDate DecreaseDateByXDecade(CDate& Date, short Decades)
	{
		for (short i = 0; i < Decades * 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByXDecade(short Decades)
	{
		*this = DecreaseDateByXDecade(*this, Decades);
	}

	static CDate DecreaseDateByXDecade_Faster(CDate& Date, short Decades)
	{
		Date._Year -= Decades * 10;
		return Date;
	}

	void DecreaseDateByXDecade_Faster(short Decades)
	{
		*this = DecreaseDateByXDecade_Faster(*this, Decades);
	}

	static CDate DecreaseDateByOneCentury(CDate& Date)
	{
		Date._Year -= 100;

		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	static CDate DecreaseDateByOneMillennium(CDate& Date)
	{
		Date._Year -= 1000;

		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}

	static void PrintDate(CDate Date)
	{
		string Day = DayShortName(DayOfWeekOrder(Date));

		printf("Today is %s , %d/%d/%d\n", Day.c_str(), Date._Day, Date._Month, Date._Year);
	}

	void PrintDate()
	{
		PrintDate(*this);
	}

	static bool IsEndOfWeek(CDate Date)
	{
		return DayOfWeekOrder(Date) == 6;
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekend(CDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date);

		return (DayIndex == 6 || DayIndex == 5);
	}

	bool IsWeekend()
	{
		return IsWeekend(*this);
	}

	static bool IsBusiness(CDate Date)
	{
		return !IsWeekend(Date);
	}

	bool IsBusiness()
	{
		return IsBusiness(*this);
	}

	static short DaysUntilTheEndOfWeek(CDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(CDate Date)
	{
		return NumberOfDaysInAMonth(Date._Month, Date._Year) - Date._Day + 1;
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(CDate Date)
	{
		return NumberOfDaysInYear(Date._Year) - NumberOfDaysFromTheBeginingOfTheYear(Date._Day, Date._Month, Date._Year);
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateVacationDays(CDate DateFrom, CDate DateTo)
	{
		short DaysCount = 0;

		while (IsDateBeforeDate2(DateFrom, DateTo))
		{
			if (IsWeekend(DateFrom))
			{
				DaysCount++;
			}
			DateFrom = AddOneDay(DateFrom);
		}

		return DaysCount;
	}

	short CalculateVacationDays(CDate DateTo)
	{
		return CalculateVacationDays(*this, DateTo);
	}

	static short CalculateBussinessDays(CDate DateFrom, CDate DateTo)
	{
		short DaysCount = 0;

		while (IsDateBeforeDate2(DateFrom, DateTo))
		{
			if (IsBusiness(DateFrom))
			{
				DaysCount++;
			}
			DateFrom = AddOneDay(DateFrom);
		}

		return DaysCount;
	}

	short CalculateBussinessDays(CDate DateTo)
	{
		return CalculateBussinessDays(*this, DateTo);
	}

	static CDate CalculateVacationDay(CDate Date, short VacationDays)
	{
		short WeekEndCount = 0;

		while (IsWeekend(Date))
		{
			Date = AddOneDay(Date);
		}

		for (short i = 0; i < VacationDays + WeekEndCount; i++)
		{
			if (IsWeekend(Date))
			{
				WeekEndCount++;
			}

			Date = AddOneDay(Date);
		}

		while (IsWeekend(Date))
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void CalculateVacationDay(short VacationDays)
	{
		*this = CalculateVacationDay(*this, VacationDays);
	}

	static bool IsDateAfterDate2(CDate Date1, CDate Date2)
	{
		return (!IsDateBeforeDate2(Date1, Date2) && !IsDateEqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(CDate Date2)
	{
		return IsDateAfterDate2(*this, Date2);
	}

	enum enDateCompare
	{
		Before = -1,
		Equal = 0,
		After = 1
	};

	static enDateCompare CompareDates(CDate Date1, CDate Date2)
	{
		return (IsDateAfterDate2(Date1, Date2)) ? enDateCompare::After
			: IsDateBeforeDate2(Date1, Date2) ? enDateCompare::Before
			: enDateCompare::Equal;
	}

	enDateCompare CompareDates(CDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static bool IsValidDate(CDate Date)
	{
		return (Date._Day < 1 || Date._Day > NumberOfDaysInAMonth(Date._Month, Date._Year)) ? false : (Date._Month < 1 || Date._Month > 12) ? false
			: true;
	}

	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static CDate StringToDate(string DateString, string Seperator = "/")
	{
		CDate Date;
		vector<string> vDate = CString::Split(DateString, Seperator);

		Date._Day = stoi(vDate[0]);
		Date._Month = stoi(vDate[1]);
		Date._Year = stoi(vDate[2]);

		return Date;
	}

	void ModifyDateByString(string DateString, string Seperator = "/")
	{
		*this = StringToDate(DateString, Seperator);
	}

	static string DateToString(CDate Date)
	{
		return to_string(Date._Day) + '/' + to_string(Date._Month) + '/' + to_string(Date._Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static string ReadStringDate(string Message)
	{
		string DateString;

		cout << Message;
		getline(cin >> ws, DateString);

		return DateString;
	}

	static string FormatDate(CDate Date, string FormatType = "dd/mm/yyyy")
	{
		string FormattedDateString = "";
		FormattedDateString = CString::ReplaceWordInString(FormatType, "dd", to_string(Date._Day));
		FormattedDateString = CString::ReplaceWordInString(FormattedDateString, "mm", to_string(Date._Month));
		FormattedDateString = CString::ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date._Year));

		return FormattedDateString;
	}

	string FormatDate(string FormatType = "dd/mm/yyyy")
	{
		return FormatDate(*this, FormatType);
	}
};
