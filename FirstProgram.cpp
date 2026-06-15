#include <iostream>
#include <ctime>

using namespace std;

//A Structure for a Date System using y,m,d
struct Date
{
	int year;
	int month;
	int day;
};

//(Program 4) Checks if the inputted year is a leap year
bool isLeap(int year)
{
	//If Statements to check if the year is a leap year or not and returns it
	if (year % 4 != 0)
		return false;
	else if (year % 100 != 0)
		return true;
	else if (year % 400 != 0)
		return false;
	else
		return true;
}

//(Program 3) Checks how many days are in the inputted month and year
int monthLength(int year, int month)
{
	//Switches to check how many days each month has and returns it
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
	//Uses Program 4 to check if the year is a leap year
	case 2: if (isLeap(year)) return 29; else return 28;
	}
}

//(Program 2) Checks how many days have passed in the inputted date
int dayOfYear(Date date)
{
	//"total days passed"
	int days = 0;

	//Uses For loop to check number of days each month has based on the number of months passed
	for (int mo = 1; mo < date.month; mo++)
	{
		//Uses Program 3 to check the number of days the month has and add it to "total days passed"
		days += monthLength(date.year, mo);
	}

	//Adds remaining days passed to the "total days passed"
	days += date.day;

	//Returns "total days passed"
	return days;
}

//(Program 1) Checks how many days are between two inputted dates
int daysBetween(Date d1, Date d2)
{
	//Switches Date if first inputted year is bigger than second inputted year
	if (d1.year > d2.year)
	{
		Date d3 = d1;
		d1 = d2;
		d2 = d3;
	}
	//Checks if inputted years are the same
	else if (d1.year == d2.year)
	{
		//Switches Date if first inputted month is bigger than second inputted month
		if (d1.month > d2.month)
		{
			Date d3 = d1;
			d1 = d2;
			d2 = d3;
		}
		//Checks if inputted months are the same
		else if (d1.month == d2.month)
		{
			//Switches Date if first inputted day is bigger than second inputted day
			if (d1.day > d2.day)
			{
				Date d3 = d1;
				d1 = d2;
				d2 = d3;
			}
			//Returns number of days between the 2 inputted days
			return d2.day - d1.day;
		}
		//Uses Program 2 to return number of days between the 2 inputted years
		return dayOfYear(d2) - dayOfYear(d1);
	}

	//"total days between"
	int days;

	//last date of the year of the inputted oldest date
	Date Dec31 = { d1.year, 12, 31 };

	/*Uses Program 2 to checks number of days between the last date of the year of the inputted oldest date 
	and the inputted oldest date and adds it to "total days between"*/
	days = dayOfYear(Dec31) - dayOfYear(d1);

	//Uses For Loop to add number of days passed in the years between the 2 inputted dates
	for (int yr = d1.year + 1; yr < d2.year; yr++)
	{
		//Uses Program 4 to add total number of days in the year to the "total days between" based on if the year is a leap year
		if (isLeap(yr))
			days += 366;
		else
			days += 365;
	}

	//Uses Program 2 to add total numbers of days passed in the inputted newest date and adds it to "total days between"
	days += dayOfYear(d2);
	//Return "total days between"
	return days;
}

//(Program 5) Checks the Day of the Week in a Date
int DayoftheWeek(Date date)
{
	tm time_in = {};

	time_in.tm_year = date.year - 1900;
	time_in.tm_mon = date.month - 1;
	time_in.tm_mday = date.day;

	mktime(&time_in);
	return time_in.tm_wday + 1;
}

//To Calculate Easter
bool isEaster(Date date)
{
	int em,ed;

	int a = date.year % 19;
	int b = date.year / 100;
	int c = date.year % 100;
	int d = b / 4;
	int e = b % 4;
	int f = (b + 8) / 25;
	int g = (b - f + 1) / 3;
	int h = (19 * a + b - d - g + 15) % 30;
	int i = c / 4;
	int k = c % 4;
	int l = (32 + 2 * e + 2 * i - h - k) % 7;
	int m = (a + 11 * h + 22 * 1) / 451;

	em = (h + 1 - 7 * m + 114) / 31;
	ed = ((h+ 1 - 7 * m + 114) % 31) + 1;
	
	return (date.day == ed && date.month == em);
}

//(Program 6) Checks if imputted date is a Holiday
bool isHoliday(Date date)
{
	if (date.month == 1)
	{
		if (date.day == 1)
		{
			cout << "Happy New Years! What is my Resolution!\n";
			return true;
		}
		else if (DayoftheWeek(date) == 2 && date.day > 14 && date.day <= 21)
		{
			cout << "Happy Martin Luther King Jr. Day! We will miss you\n";
			return true;
		}
		return false;
	}
	else if (date.month == 2)
	{
		if (date.day == 14)
		{
			cout << "Happy Valentine's Day! Will you be my Valentine?\n";
			return true;
		}
		else if (DayoftheWeek(date) == 2 && date.day > 14 && date.day <= 21)
		{
			cout << "Happy President's Day! Bless America!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 3)
	{
		if (date.day == 17)
		{
			cout << "Happy Saint Patrick's Day! Give me the Gold!\n";
			return true;
		}
		if (isEaster(date))
		{
			cout << "Happy Easter! Time to go Egg Hunting!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 4)
	{
		if (isEaster(date))
		{
			cout << "Happy Easter! Time to go Egg Hunting!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 5)
	{
		if (DayoftheWeek(date) == 2 && date.day >= 25)
		{
			cout << "Happy Memorial Day! Thank You for Serving our Country!\n";
			return true;
		}
		else if (DayoftheWeek(date) == 1 && date.day > 7 && date.day <= 14)
		{
			cout << "Happy Mother's Day! Thank Your Mother!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 6)
	{
		if (date.day == 19)
		{
			cout << "Happy Juneteenth! Freedom is Great!\n";
			return true;
		}
		else if (DayoftheWeek(date) == 1 && date.day > 14 && date.day / 7 <= 21)
		{
			cout << "Happy Father's Day! Thank Your Father!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 7)
	{
		if (date.day == 4)
		{
			cout << "Happy Independence Day! Freedom is Great!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 8)
		return false;
	else if (date.month == 9)
	{
		if (DayoftheWeek(date) == 2 && date.day > 0 && date.day <= 7)
		{
			cout << "Happy Labor Day! No work for Today!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 10)
	{
		if (date.day == 31)
		{
			cout << "Happy Halloween! Boo!\n";
			return true;
		}
		else if (DayoftheWeek(date) == 2 && date.day > 7 && date.day <= 14)
		{
			cout << "Happy Colombus Day! To America!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 11)
	{
		if (date.day == 11)
		{
			cout << "Happy Veterans Day! Your Service will be Honored!\n";
			return true;
		}
		else if (DayoftheWeek(date) == 5 && date.day > 21 && date.day <= 28)
		{
			cout << "Happy Thanksgiving! Time to eat Turkey!\n";
			return true;
		}
		return false;
	}
	else if (date.month == 12)
	{
		if (date.day == 25)
		{
			cout << "Merry Christmas! Time for some Presents!\n";
			return true;
		}
		else if (date.day == 31)
		{
			cout << "Happy New Years Eve! Time for the Countdown!\n";
			return true;
		}
		return false;
	}
}

int main(void) 
{
	//Loop that ends if you press any key other than 1, 2, 3, and 4
	while (true)
	{
		//Used to choose Specific Program
		int program;
		//Press 1 to use Program 1
		cout << "Press 1 to Check number of Days between 2 Dates\n"
		//Press 2 to use Program 2
		<< "Press 2 to Check number of Days is that Date of the Year\n"
		//Press 3 to use Program 3
		<< "Press 3 to Check number of Days are in that Month of that Year\n"
		//Press 4 to use Program 4
		<< "Press 4 to Check if that year is a leap year\n"
		// Press 5 to use Program 5
		<< "Press 5 to Check the Day of the Week in a Date\n"
		//Press 6 to use Program 6
		<< "Press 6 to Check if the Date is a Holiday\n"
		// Press any other key to exit
		<< "Press any other key else to Exit Program\n";
		//Input Specific Program
		cin >> program;

		//Program 1 or Days Between
		if (program == 1)
		{
			//fd = first date and sd = second date
			Date fd, sd;
			//Boolean to check if Variables are Valid
			bool valid;
			//Do while loop to check if Inputted First Date is Valid
			do
			{
				//Turn Valid True
				valid = true;
				cout << "Enter first date (y m d): ";
				//Input y, m, and d of fd
				cin >> fd.year >> fd.month >> fd.day;
				//If statement to check if Inputted Variables is Invalid
				if (fd.month > 12 || fd.month < 1)
				{
					//Prints out Invalid Month
					cout << "Inputted Invalid Month. Try Again.";
					//Changes Valid to False to continue Loop
					valid = false;
				}
				else if (fd.day > monthLength(fd.year, fd.month) || fd.day < 1)
				{
					//Prints out Invalid Day
					cout << "Inputted Invalid Day. Try Again";
					//Changes Valid to False to continue Loop
					valid = false;
				}
			}while (valid == false);
			//Do while loop to check if Inputted Second Date is Valid
			do
			{
				//Turn Valid True
				valid = true;
				cout << "Enter second date (y m d): ";
				//Input y, m, and d of sd
				cin >> sd.year >> sd.month >> sd.day;
				//If statement to check if Inputted Variables is Invalid
				if (sd.month > 12 || sd.month < 1)
				{
					//Prints out Invalid Month
					cout << "Inputted Invalid Month. Try Again.";
					//Changes Valid to False to continue Loop
					valid = false;
				}
				else if (sd.day > monthLength(sd.year, sd.month) || sd.day < 1)
				{
					//Prints out Invalid Day
					cout << "Inputted Invalid Day. Try Again";
					//Changes Valid to False to continue Loop
					valid = false;
				}
			}while (valid == false);
			//Prints out answer of Days Between
			cout << "Number of Days Between: " << daysBetween(fd, sd) << endl;
		}
		//Program 2 or Days Passed
		else if (program == 2)
		{
			//date
			Date dt;
			//Boolean to check if Variables are Valid
			bool valid;
			//Do while loop to check if Inputted Date is Valid
			do
			{
				//Turn Valid True
				valid = true;
				cout << "Enter a date (y m d): ";
				//Input y, m, and d of the date
				cin >> dt.year >> dt.month >> dt.day;
				//If statement to check if Inputted Variables is Invalid
				if (dt.month > 12 || dt.month < 1)
				{
					//Prints out Invalid Month
					cout << "Inputted Invalid Month. Try Again.";
					//Changes Valid to False to continue Loop
					valid = false;
				}
				else if (dt.day > monthLength(dt.year, dt.month) || dt.day < 1)
				{
					//Prints out Invalid Day
					cout << "Inputted Invalid Day. Try Again";
					//Changes Valid to False to continue Loop
					valid = false;
				}
			}while (valid == false);
			//Prints out answer of Days Passed
			cout << "Number of Days Passed: " << dayOfYear(dt) << endl;
		}
		//Program 3 or Days in the Month
		else if (program == 3)
		{
			//yr = year and m = month
			int yr, m;
			//Boolean to check if Variables are Valid
			bool valid;

			cout << "Enter the year: ";
			//Input year
			cin >> yr;
			//Do while loop to check if Inputted Month is Valid
			do
			{
				//Turn Valid True
				valid = true;
				cout << "Enter the month: ";
				//Input month
				cin >> m;
				//If statement to check if Inputted Month is Invalid
				if (m > 12 || m < 1)
				{
					//Prints out Invalid Month
					cout << "Inputted Invalid Month. Try Again.";
					//Changes Valid to False to continue Loop
					valid = false;
				}
			}while (valid == false);
			//Prints out answer of Days in the Month
			cout << "Number of Days in the month: " << monthLength(yr, m) << endl;
		}
		//Program 4 or Leap Year
		else if (program == 4)
		{
			//y = year
			int y;
			//Used to store if the year is a leap year or not
			bool leap;
			cout << "Enter the year: ";
			//Input year
			cin >> y;
			//Checks if the year is a leap year or not and stores it in a boolean
			leap = isLeap(y);
			//Checks if Leap Year is true and prints it
			if (leap == true)
				cout << "It is a Leap Year!" << endl;
			//Checks if Leap Year is false and prints it
			else if (leap == false)
				cout << "It is not a Leap Year!" << endl;

		}
		//Program 5 or Day of the Week
		else if (program == 5)
		{
			//date
			Date dt;
			//Boolean to check if Variables are Valid
			bool valid;
			//Integer to store Day of the Week
			int dotw;
			//Do while loop to check if Inputted Date is Valid
			do
			{
				//Turn Valid True
				valid = true;
				cout << "Enter a date (y m d) (1900 and above): ";
				//Input y, m, and d of the date
				cin >> dt.year >> dt.month >> dt.day;
				//If statement to check if Inputted Variables is Invalid
				if (dt.month > 12 || dt.month < 1)
				{
					//Prints out Invalid Month
					cout << "Inputted Invalid Month. Try Again.";
					//Changes Valid to False to continue Loop
					valid = false;
				}
				else if (dt.day > monthLength(dt.year, dt.month) || dt.day < 1)
				{
					//Prints out Invalid Day
					cout << "Inputted Invalid Day. Try Again";
					//Changes Valid to False to continue Loop
					valid = false;
				}
				else if (dt.year < 1900)
				{
					//Prints out Invalid Year
					cout << "Inputted Invalid Year. Try Again";
					//Changes Valid to False to continue Loop
					valid = false;
				}
			}while (valid == false);
			//Checks the Day of the Week
			dotw = DayoftheWeek(dt);
			//Prints Day of the Week
			switch (dotw)
			{
				case 1: cout << "Day of the Week is Sunday!\n"; break;
				case 2: cout << "Day of the Week is Monday!\n"; break;
				case 3: cout << "Day of the Week is Tuesday!\n"; break;
				case 4: cout << "Day of the Week is Wednesday!\n"; break;
				case 5: cout << "Day of the Week is Thursday!\n"; break;
				case 6: cout << "Day of the Week is Friday!\n"; break;
				case 7: cout << "Day of the Week is Saturday!\n"; break;
			}
		}
		//Program 6 or Holiday
		else if (program == 6)
		{
			//date
			Date dt;
			//Boolean to check if Variables are Valid
			bool valid, holiday;
			//Do while loop to check if Inputted Date is Valid
			do
			{
				//Turn Valid True
				valid = true;
				cout << "Enter a date (y m d) (1900 and above): ";
				//Input y, m, and d of the date
				cin >> dt.year >> dt.month >> dt.day;
				//If statement to check if Inputted Variables is Invalid
				if (dt.month > 12 || dt.month < 1)
				{
					//Prints out Invalid Month
					cout << "Inputted Invalid Month. Try Again.";
					//Changes Valid to False to continue Loop
					valid = false;
				}
				else if (dt.day > monthLength(dt.year, dt.month) || dt.day < 1)
				{
					//Prints out Invalid Day
					cout << "Inputted Invalid Day. Try Again";
					//Changes Valid to False to continue Loop
					valid = false;
				}
				else if (dt.year < 1900)
				{
					//Prints out Invalid Year
					cout << "Inputted Invalid Year. Try Again";
					//Changes Valid to False to continue Loop
					valid = false;
				}
			}while (valid == false);
			//Checks if Holiday is True or False
			holiday = isHoliday(dt);
			//Prints out if Date is a Holiday or not
			if (holiday == true)
				cout << "It is a Holiday!\n";
			else if (holiday == false)
				cout << "It is not a Holiday\n";
		}
		//Ends Program
		else
		{
			return 0;
		}
	}
}