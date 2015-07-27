#include <windows.h>
#include <stdio.h>

void get_date();
void get_time();
void get_datetime();

char nowdate[11];
char nowtime[6];

void main()
{
	get_date();
	get_time();
	printf(nowdate);
	printf("\n");
	printf(nowtime);
}


void get_date(){
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	/*printf("Year:%d\nMonth:%d\nDate:%d\nHour:%d\nMin:%d\nSecond:% d\n"
	,str_t.wYear,str_t.wMonth,str_t.wDay
	,str_t.wHour,str_t.wMinute,str_t.wSecond);*/
	sprintf(nowdate, "%d-%d-%d", str_t.wDay,str_t.wMonth,str_t.wYear);
}

void get_time(){

	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	/*printf("Year:%d\nMonth:%d\nDate:%d\nHour:%d\nMin:%d\nSecond:% d\n"
	,str_t.wYear,str_t.wMonth,str_t.wDay
	,str_t.wHour,str_t.wMinute,str_t.wSecond);*/
	sprintf(nowtime, "%d:%d", str_t.wHour,str_t.wHour);
}
/*
NAME: get_datetime()
OUTPUT: NONE
INPUT: NONE
DESCRIPTION:	It saves the date and the time into the global variables nowdate and nowtime.
				We have to declare this variables:
						char nowdate[11]
						char nowtime[6]
						We can ask for: str_t.wYear,str_t.wMonth,str_t.wDay,str_t.wHour,str_t.wMinute,str_t.wSecond
*/
void get_datetime(){
	
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	sprintf(nowdate, "%d-%d-%d", str_t.wDay,str_t.wMonth,str_t.wYear);
	sprintf(nowtime, "%d:%d", str_t.wHour,str_t.wHour);

}