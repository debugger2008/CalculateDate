/*应朋友要求，做一小程序，实现输入一个年月日的日期，再输入过去的天数，立刻算出过去这个天数后的年月日。
开始以为很简单，没想到上手写起来还真费脑。写了一百多行才搞定。程序用C99编写，目前版本Version 1.0。
无非法字符检查输入机制，无日期正确与否检查机制，待有空增加输入二个日期后，求出相隔天数的功能。如果用API来解
决，可以参考DateAdd(timeinterval,number,date)，或者JAVA里的LocalDate，Duration和Period。
git
*/



#include <stdio.h>
#include <stdbool.h>
struct date
{
	int month;
	int day;
	int year;
};
const int daysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
const int daysPerMonthLeap[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
char *message = "请输入当时的日期(yy mm dd):";
int restOfdays = 0; //设一个全局变量用来记录年份确认后剩下的天数

bool isLeap(struct date);
int yearsConvertDays(struct date );
int daysConvertYear(int days);
int monthConvertDays (struct date d);


int main(void)
{
	struct date sourceDate,objectDate;
	int numberOfDays = 0; //记录过去的天数(输入的天数)
	int yearToDay; //记录年转换天数
	int monthToDay; //记录月转换天数
	int finalConvertedDays; //记录年，月，日最终的转换天数
	int calDays; //记录用来计算的天数
	
	while(true)
	{	
		printf("%s",message);
		scanf("%d %d %d",&sourceDate.year, &sourceDate.month, &sourceDate.day);
		printf("请输入过去的天数: ");
		scanf("%d",&numberOfDays);
		int n = numberOfDays; //备用 ^_^
	

		yearToDay = yearsConvertDays(sourceDate) ;
		//printf("yearToDay= %d\n", yearToDay);
		monthToDay = monthConvertDays (sourceDate);
		//printf("monthToDay = %d\n",monthToDay );
		finalConvertedDays = yearToDay + monthToDay + sourceDate.day;
		calDays = finalConvertedDays + numberOfDays;
		//printf("calDays = %d\n", calDays);

		objectDate.year = daysConvertYear(calDays);
		//printf("restOfdays = %d\n",restOfdays);
		if(isLeap(objectDate))
		{	
			int i;
			//printf("restOfdays = %d\n",restOfdays);
			for(i=0;restOfdays>daysPerMonthLeap[i];i++)
			{
				restOfdays -= daysPerMonthLeap[i];
			}
			objectDate.month = i+1;
		}
		else
		{
			int i;
			for(i=0;restOfdays>daysPerMonth[i];i++)
			{
				restOfdays -= daysPerMonth[i];
			}
			objectDate.month = i+1;
		}
		//printf("%d\n",objectDate.year);
		//printf("%d\n",objectDate.month );
		//printf("%d\n",restOfdays );
		objectDate.day = restOfdays;
	
		printf("%d天后的日期为 %d-%d-%d\n\n",n,objectDate.year,objectDate.month,objectDate.day);

	}
}


int yearsConvertDays(struct date d) //年份转换成天数
{
	int i;
	int days = 0;
	i = d.year;

	for(;i>1;i--)
	{
		if(((i-1)%4==0&&(i-1)%100!=0)||(i-1)%400==0)
		{
			days += 366;
		}
		else
		{
			days += 365;
		}
		
	}
	return days;
}



int daysConvertYear(int days)//天数转换成年份
{
	int i;
	int year;
	
	i = days;
	int j = 1;

	for(;i>=365;)
	{
		if((j%4==0&&j%100!=0)||j%400==0)
		{
			i -= 366;
		}
		else
		{
			i -= 365;
		}
		//printf("i = %d\n",i);
		j++;
	}
	restOfdays = i; //把所剩的天数记录下来
	year = j;

	return year;
}


int monthConvertDays (struct date d) //月份转换天数
{
	int monthsConvertdays = 0;
	if(isLeap(d))
	{
		for(int i=0;i<(d.month-1);i++ )
		{
			monthsConvertdays += daysPerMonthLeap[i];
		}
	}
	else
	{
		for(int i=0;i<(d.month-1);i++ )
		{
			monthsConvertdays += daysPerMonth[i];
		}	
	}
	
	return monthsConvertdays;
}


bool isLeap (struct date d) //判断是否为闰年，是为true,否为false
{	bool leap = false;
	if ((d.year%4==0&&d.year%100!=0)||d.year%400==0)
		leap = true;
	return leap;
}



