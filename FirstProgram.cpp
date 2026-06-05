#include <iostream>
//Terst

using namespace std;


struct Date
{
	int year;
	int month;
	int day;
};

bool isLeap(int year)
{
	if (year % 4 != 0)
		return false;
	else if (year % 100 != 0)
		return true;
	else if (year % 400 != 0)
		return false;
	else
		return true;
}

int monthLength(int year, int month)
{
	switch (month) {
	case  1:
	case  3:
	case  5:
	case  7:
	case  8:
	case 10:
	case 12: return 31;
	case  4:
	case  6:
	case  9:
	case 11: return 30;
	case 2: if (isLeap(year)) return 29; else return 28;
	default: return 0;
	}
}

int dayOfYear(Date date)
{
	int days = 0;

	for (int mo = 1; mo < date.month; mo++)
	{
		days += monthLength(date.year, mo);
	}

	days += date.day;

	return days;
}

int daysBetween(Date d1, Date d2)
{
	if (d1.year > d2.year)
		return -1;
	else if (d1.year == d2.year)
	{
		if (d1.month > d2.month)
			return -1;
		else if (d1.month == d2.month)
		{
			if (d1.day > d2.day)
				return -1;
			return d2.day - d1.day;
		}
		return dayOfYear(d2) - dayOfYear(d1);
	}

	int days;

	Date Dec31 = { d1.year, 12, 31 };

	days = dayOfYear(Dec31) - dayOfYear(d1);

	for (int yr = d1.year + 1; yr < d2.year; yr++)
	{
		if (isLeap(yr))
			days += 366;
		else
			days += 365;
	}

	days += dayOfYear(d2);
	return days;
}

int main(void) 
{
	while (true)
	{
		int program;
		cout << "Press 1 to Check number of Days between 2 Dates\nPress 2 to Check number of Days is that Date of the Year\nPress 3 to Check number of Days are in that Month of that Year\nPress 4 to Check if that year is a leap year\nPress anything else to Exit Program\n";
		cin >> program;

		if (program == 1)
		{
			Date since, to;
			cout << "Enter first date (y m d): ";
			cin >> since.year >> since.month >> since.day;
			cout << "Enter second date (y m d): ";
			cin >> to.year >> to.month >> to.day;
			cout << "Number of Days Between: " << daysBetween(since, to) << endl;
		}
		else if (program == 2)
		{
			Date date;
			cout << "Enter a date (y m d): ";
			cin >> date.year >> date.month >> date.day;
			cout << "Number of Days Passed: " << dayOfYear(date) << endl;
		}
		else if (program == 3)
		{
			int yr, m;
			cout << "Enter the year: ";
			cin >> yr;
			cout << "Enter the month: ";
			cin >> m;
			cout << "Number of Days in the month: " << monthLength(yr, m) << endl;
		}
		else if (program == 4)
		{
			int y;
			bool leap;
			cout << "Enter the year: ";
			cin >> y;
			leap = isLeap(y);
			if (leap == true)
				cout << "It is a Leap Year!" << endl;
			else if (leap == false)
				cout << "It is not a Leap Year!" << endl;

		}
		else
		{
			return 0;
		}
	}
}