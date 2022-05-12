#include "SSSTurnkeySys.h"
/*
Author: Shaonan Hu & Jiahao Chen
Last Modified Date: Nov 18th 2021
Function:
	-Encode the current date
	-Decode the Encoded date
Referenced from: 
*/


//Define the amount of the days for different month
unsigned monthday[2][12] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

//Function to encode the date
long EncodeDate(unsigned day, unsigned month, unsigned year) {
	int yearcheck;
	unsigned daypased=0;

	//check for leap year
	yearcheck = LEAPYEAR(year);

	//Check if the year lower than start year
	if (year <STARTYR) {
		printf("Invalid Year %d", year);
		return-1;
	}
	//Check if the month is valid
	if (month > 12) {
		printf("Invalid Month %d", month);
		return -1;
	}

	//Check if the day is valid
	if (day > monthday[LEAPYEAR(year)][month-1]) {
		printf("Invalid Day %d", day);
		return -1;
	}

	//Sum the day passed by adding 
	//the the day of the passed month together

	for (unsigned int monthcout = 0; monthcout < month-1; monthcout++) {
		//Jan+Feb+Mar+Apr
		//0+1+2+3+4
		//31+28+31+30
		daypased += monthday[yearcheck][monthcout];
	}

	//Encode the total day passed from the Start year (1990) to current date
	daypased = (day - 1) + daypased + (year - STARTYR) * MAXDAYYR;
	return daypased;
}

//Fucntion definiation for decode the encoded date
void DecodeDate(unsigned long datecode, unsigned *day, unsigned*month, unsigned*year) {
	int yearcheck;
	unsigned y, encodeday;
	unsigned m = 0, days=0;
	//Decode the year of encoded date
	y = STARTYR + datecode / MAXDAYYR;
	//check if it is a leap year;
	yearcheck = LEAPYEAR(y);

	//Decode the daypassed at the current year
	encodeday = datecode % MAXDAYYR;

	//Decode the month
	while (encodeday > days && m < 11) {
		days += monthday[yearcheck][m];
		m++;
	}
	//Return the Day / Month / Year
	*day = encodeday - days + 1;
	*month = m + 1;
	*year = y;
}



