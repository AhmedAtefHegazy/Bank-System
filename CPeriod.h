#pragma once

#include "CDate.h"

using namespace std;

class CPeriod
{
    CDate _StartDate;
    CDate _EndDate;

public:
    CPeriod()
    {
        _StartDate = CDate(1, 1, 1900);
        _EndDate = CDate(1, 1, 1900);
    }

    CPeriod(CDate StartDate, CDate EndDate)
    {
        _StartDate = StartDate;
        _EndDate = EndDate;
    }

    void SetStartDate(CDate StartDate)
    {
        _StartDate = StartDate;
    }

    CDate GetStartDate()
    {
        return _StartDate;
    }

    __declspec(property(get = GetStartDate, put = SetStartDate)) string StartDate;

    void SetEndDate(CDate EndDate)
    {
        _EndDate = EndDate;
    }

    CDate GetEndDate()
    {
        return _EndDate;
    }

    __declspec(property(get = GetEndDate, put = SetEndDate)) string EndDate;

    static bool IsOverlapPeriods(CPeriod Period1, CPeriod Period2)
    {
        return !(CDate::CompareDates(Period2._EndDate, Period1._StartDate) == CDate::enDateCompare::Before || CDate::CompareDates(Period1._EndDate, Period2._StartDate) == CDate::enDateCompare::Before);
    }

    bool IsOverLapWith(CPeriod Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    static CPeriod ReadPeriod()
    {
        CPeriod Period;
        cout << "\nEnter Start Date:\n";
        Period._StartDate = CDate::ReadFullDate();

        cout << "\nEnter End Date:\n";
        Period._EndDate = CDate::ReadFullDate();

        return Period;
    }

    static int PeriodLengthInDays(CPeriod Period, bool IncludeEndDate = false)
    {
        return CDate::GetDifferenceInDays(Period._StartDate, Period._EndDate, IncludeEndDate);
    }

    int PeriodLengthInDays(bool IncludeEndDate = false)
    {
        return PeriodLengthInDays(*this, IncludeEndDate);
    }

    static bool IsDateWithinPeriod(CPeriod Period, CDate DateToCheck)
    {
        return !(CDate::CompareDates(Period._StartDate, DateToCheck) == CDate::enDateCompare::After || CDate::CompareDates(Period._EndDate, DateToCheck) == CDate::enDateCompare::Before);
    }

    bool IsDateWithinPeriod(CDate DateToCheck)
    {
        return IsDateWithinPeriod(*this, DateToCheck);
    }

    static short CountOverlapedDays(CPeriod Period1, CPeriod Period2)
    {
        short Period1Lenght = PeriodLengthInDays(Period1, true);
        short Period2Lenght = PeriodLengthInDays(Period2, true);
        short OverlapedDays = 0;

        if (!IsOverlapPeriods(Period1, Period2))
            return 0;

        if (Period1Lenght < Period2Lenght)
        {
            while (CDate::IsDateBeforeDate2(Period1._StartDate, Period1._EndDate))
            {
                if (IsDateWithinPeriod(Period2, Period1._StartDate))
                    OverlapedDays++;

                Period1._StartDate = CDate::AddOneDay(Period1._StartDate);
            }
        }

        else
        {
            while (CDate::IsDateBeforeDate2(Period2._StartDate, Period2._EndDate))
            {
                if (IsDateWithinPeriod(Period1, Period2._StartDate))
                    OverlapedDays++;

                Period2._StartDate = CDate::AddOneDay(Period2._StartDate);
            }
        }

        return OverlapedDays;
    }

    short CountOverlapedDays(CPeriod Period2)
    {
        return CountOverlapedDays(*this, Period2);
    }

    void Print()
    {
        cout << "StartDate : " << CDate::DateToString(_StartDate) << endl;
        cout << "EndDate   : " << CDate::DateToString(_EndDate) << endl;
    }
};
