static int no_leap[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int leap[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const int *daytab[] = {no_leap, leap};

/* day_of_year: set day of year from month & day */
int day_of_year(unsigned int year, int month, int day) {
  if (month > 12 || month < 1)
    return -1;

  int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

  if (day < 1 || day > daytab[leap][month])
    return -1;

  for (int i = 1; i < month; i++)
    day += daytab[leap][i];

  return day;
}

/* month_day: set month, day from day of year */
int month_day(unsigned int year, int yearday, int *pmonth, int *pday) {
  if (!pmonth || !pday)
    return -1;

  int i, leap;
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

  if (yearday < 1 || yearday > 365 + leap)
    return -1;

  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;

  return 0;
}
