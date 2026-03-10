// #include"Adafruit_LEDBackpack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

#define PIN_BUTT_AJUST 2
#define PIN_BUTT_MODE 3
#define PIN_BUTT_RESET 4
#define PIN_BUTT_24F 5

//
enum {
    JAN_ = 1,
    FEB_,
    MAR_,
    ABR_,
    MAI_,
    JUN_,
    JUL_,
    AGO_,
    SEP_,
    OCT_,
    NOV_,
    DEC_
};

enum {
    SUN,
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT
};

#define LEAP_YEAR(y) \
( \
(!(y % 4) && y % 100) \
|| !(y % 400) \
)

// Set the month days
#define JAN_DAYS 31
#define FEB_DAYS(y) (LEAP_YEAR(y)?29: 28)
#define MAR_DAYS 31
#define ABR_DAYS 30
#define MAI_DAYS 31
#define JUN_DAYS 30
#define JUL_DAYS 31
#define AGO_DAYS 31
#define SEP_DAYS 30
#define OCT_DAYS 31
#define NOV_DAYS 30
#define DEC_DAYS 31

#define YEAR_DAYS(y) \
(LEAP_YEAR(y)? 366: 365)

/*
 * Some time measure
 */
#define SECS_MIN (60)
#define SECS_HOUR (60 * 60)
#define SECS_DAY ((uint32_t)60 * 60 * 24)

#define WEEK_SIZE 7

/*
 * Set the data type of each time measure
 * Data types used in storage of time measure
 */
typedef uint8_t T_SEC;
typedef uint8_t T_MIN;
typedef uint8_t T_HOUR;

typedef uint16_t T_YDAY;
typedef uint8_t T_WDAY;
typedef uint8_t T_MDAY;

typedef uint8_t T_WEEK;
typedef uint8_t T_MONTH;
typedef uint32_t  T_YEAR;

/* Absolute time measure data type
 * These data types are used when a date is only represent as a single time measure.
 * Like represent 00:00 1/1/2026 as: 63902908800 seconds or 17750808 hours
 * from 1/1/1
 */
typedef uint64_t ABS_T_SEC;
typedef uint64_t ABS_T_MIN;
typedef uint64_t ABS_T_HOUR;

typedef uint64_t ABS_T_YDAY;

typedef double ABS_T_WEEK;
typedef double ABS_T_MONTH;
typedef double ABS_T_YEAR;

/*
 * Theses macro define the data type of each time measure for input/ouput
 * operations
 */
#define T_SEC_F "%02u"
#define T_MIN_F "%02u"
#define T_HOUR_F "%02u"

#define T_YDAY_F "%u"
#define T_WDAY_F "%u"
#define T_WDAY_NAME_F "%s"
#define T_MDAY_F "%02u"

#define T_WEEK_F "%u"
#define T_MONTH_F "%02u"
#define T_MONTH_NAME_F "%s"
#define T_YEAR_F "%u"


/*
 * Macros formats for Clock_sprintf
 */
#define CLOCK_PRINTF_COMMON "%"

#define PRINT_SEC \
    CLOCK_PRINTF_COMMON "sec"
#define PRINT_MIN \
    CLOCK_PRINTF_COMMON "min"
#define PRINT_HOUR \
    CLOCK_PRINTF_COMMON "hour"

#define PRINT_YDAY \
    CLOCK_PRINTF_COMMON "yday"
#define PRINT_WDAY \
    CLOCK_PRINTF_COMMON "wday"
#define PRINT_WDAY_NAME \
    CLOCK_PRINTF_COMMON "Wday"
#define PRINT_MDAY \
    CLOCK_PRINTF_COMMON "mday"

#define PRINT_WEEK \
    CLOCK_PRINTF_COMMON "week"
#define PRINT_MONTH \
    CLOCK_PRINTF_COMMON "month"
#define PRINT_MONTH_NAME \
    CLOCK_PRINTF_COMMON "Month"
#define PRINT_YEAR \
    CLOCK_PRINTF_COMMON "year" 

#define CLOCK_PRINTF \
    PRINT_SEC "\n" \
    PRINT_MIN "\n" \
    PRINT_HOUR "\n" \
    \
    PRINT_YDAY "\n" \
    PRINT_WDAY "\n" \
    PRINT_WDAY_NAME "\n" \
    PRINT_MDAY "\n" \
    \
    PRINT_WEEK "\n" \
    PRINT_MONTH "\n" \
    PRINT_MONTH_NAME "\n" \
    PRINT_YEAR "\n"

#define CLOCK_PRINTF_MAX 10
#define CLOCK_PRINTF_RESULT_MAX 100


#define PRINT_DEFAULT \
    PRINT_HOUR ":" PRINT_MIN ":" PRINT_SEC " " \
    PRINT_MDAY "/" PRINT_MONTH "/" PRINT_YEAR "\n" \
    PRINT_WDAY_NAME ", " PRINT_MONTH_NAME

#define STR_REPLACE_MAX \
    ( CLOCK_PRINTF_RESULT_MAX * 2)

/*
 * The Clock struct is a portable way(at least I try!) of storage a date.
 * This struct storage a arbitrary date in the format:
 * seconds
 * minutes
 * hours
 *
 * year's day
 * year
 *
 * From those primitive data we can get precisious infos of a time,
 * like the weekday, monthday or the year's week.
 *
 * Additionally, the Clock struct storage if the clock is set to display
 * the time in a 24 hour format or not
 */
typedef struct{
    int f24;

    T_SEC _sec;
    T_MIN _min;
    T_HOUR _hour;
    
    T_YDAY _day;
    T_YEAR _year;
} Clock;


// Clock methods
Clock* Clock_create();
void Clock_sum(Clock*, ABS_T_SEC sec);

void Clock_sprintf(Clock*, char to[], char format[]);
void Clock_data_from_format(Clock*, char to[], char format[]);

// int Clock_before_date(Clock*, ABS_T_SEC time);
// int Clock_after_date(Clock*, ABS_T_SEC time);

// Clock properties / setters
T_SEC Clock_sec(Clock*);
T_MIN Clock_min(Clock*);
T_HOUR Clock_hour(Clock*);

T_YDAY Clock_yday(Clock*);
T_WDAY Clock_wday(Clock*);
void Clock_wday_name(Clock*, char to[]);
T_MDAY Clock_mday(Clock*);

T_WEEK Clock_week(Clock*);
T_MONTH Clock_month(Clock*);
void Clock_month_name(Clock*, char to[]);
T_YEAR Clock_year(Clock*);


void Clock_sec_def(Clock*, T_SEC sec);
void Clock_min_def(Clock*, T_MIN minutes);
void Clock_hour_def(Clock*, T_HOUR hour);

void Clock_yday_def(Clock*, T_YDAY yday);
void Clock_wday_def(Clock*, T_WDAY wday);
void Clock_mday_def(Clock*, T_MDAY mday);

void Clock_month_def(Clock*, T_MONTH month);
void Clock_year_def(Clock*, T_YEAR year);

void Clock_time_set(
        Clock*,
        T_HOUR, T_MIN, T_SEC
        );
void Clock_date_set(
        Clock*,
        T_MDAY, T_MONTH, T_YEAR
        );

// Calendar properties
int Calendar_year_leap(T_YEAR y);
T_YDAY Calendar_year_days(T_YEAR y);
ABS_T_WEEK Calendar_year_weeks(T_YEAR y);
T_WEEK Calendar_year_week(T_YDAY yday, T_YEAR year);

T_WDAY Calendar_week_day(T_YDAY yday, T_YEAR year);
void Calendar_week_day_name(T_WDAY wday, char str[]);
T_WDAY Calendar_week_days_to_init(T_WDAY wday);

T_MONTH Calendar_month(T_YDAY yday, T_YEAR year);
void Calendar_month_name(T_MONTH month, char str[]);
T_YDAY Calendar_month_days(T_MONTH m, T_YEAR y);
T_MDAY Calendar_month_day(T_YDAY yday, T_YEAR year);

ABS_T_YDAY Calendar_days_from_dates(
        T_YDAY y1day, T_YEAR year1,
        T_YDAY y2day, T_YEAR year2
        );

// String methods
void str_copy(char to[], char from[]);
void str_clean(char str[]);
void str_add_char(char str[], int c);
void str_replace(char str[], char sub[], char nsub[]);
int str_search(char str[], char sub[], int index);

int is_substring(char str[], char sub[]);

// External/globals variables
// const Adafruit_7segment clock_display = Adafruit_7segment();
Clock *clock;
char clock_output[CLOCK_PRINTF_RESULT_MAX];

/*
void setup()
{
    Serial.begin(9600);
    // Serial.println("Hello Wolrd!\n");
    
    pinMode(PIN_BUTT_AJUST, INPUT);
    pinMode(PIN_BUTT_RESET, INPUT);
    pinMode(PIN_BUTT_MODE, INPUT);
    pinMode(PIN_BUTT_24F, INPUT);
    
    pinMode(LED_BUILTIN, OUTPUT);
  
  	clock = Clock_create();
  	// Clock_year_def(clock, 2026);
  	// Clock_month_def(clock, 3);
  	// Clock_date_set(clock, 7, 3, 2026);
}

void loop(){
  	Clock_sprintf(clock,
                 clock_output, 
                 PRINT_DEFAULT
                 );
  
  	// Serial.println(output);
  	Serial.println(clock_output);
  
  	Clock_sum(clock, SECS_DAY);
  	// delay(1000);
}
// */

// /*
int main()
{
    printf("%lu\n",
            Calendar_days_from_dates(1, 1, 1, 0)
          );

    printf("%i\n", 
            Calendar_week_day(366, 0) == TUE
          );
    /*
    clock = Clock_create();

    Clock_date_set(clock, 1, 1, 2018);
    Clock_date_set(clock, 1, 1, 1);
    
    Clock_wday_def(clock, SUN);
    Clock_sprintf(clock, clock_output, PRINT_DEFAULT);

    printf("%s\n", clock_output);
    */
}
// */


// Clock methods
Clock* Clock_create()
{
    Clock *clock_new = (Clock*)malloc(sizeof(Clock));

    Clock_sec_def(clock_new, 0);
    Clock_min_def(clock_new, 0);
    Clock_hour_def(clock_new, 0);
    
    Clock_yday_def(clock_new, 1);
    Clock_year_def(clock_new, 1);

    return clock_new;
}

void Clock_sum(Clock*r, ABS_T_SEC time_s)
{
    ABS_T_SEC sec;
    ABS_T_MIN min;
    ABS_T_HOUR hour;
    ABS_T_YDAY yday, year_days;
    ABS_T_YEAR year;

    sec = Clock_sec(r) + time_s;
    min = Clock_min(r) + sec / 60;
    hour = Clock_hour(r) + min / 60;
    yday = Clock_yday(r) +  hour / 24;
    year = Clock_year(r);

    while(yday >
            (year_days = Calendar_year_days(year))
            ){
      	yday -= year_days;
        ++year;
    }

    Clock_sec_def(r, sec % 60);
    Clock_min_def(r, min % 60);
    Clock_hour_def(r, hour % 24);
  	Clock_yday_def(r, yday);
  	Clock_year_def(r, year);
}

void Clock_sprintf(Clock*r, char t[], char f[])
{
    char clock_printf[] = CLOCK_PRINTF;
    char data[CLOCK_PRINTF_RESULT_MAX];
    char buff[CLOCK_PRINTF_MAX];

    int c;
    size_t i;

  	str_clean(buff);
    str_copy(t, f);
    for(i=0; (c = clock_printf[i]) != '\0'; ++i){
        if(c != '\n'){
            str_add_char(buff, c);
            continue;
        }
        Clock_data_from_format(r, data, buff);
        str_replace(t, buff, data);
        str_clean(buff);
    }
}


void Clock_data_from_format(Clock*r, char to[], char f[])
{
    char format[CLOCK_PRINTF_MAX];

    if(!strcmp(f, PRINT_SEC)){
        str_copy(format, T_SEC_F);
        sprintf(to, format, Clock_sec(r));
    }
    else if(!strcmp(f, PRINT_MIN)){
        str_copy(format, T_MIN_F);
        sprintf(to, format, Clock_min(r));
    }
    else if(!strcmp(f, PRINT_HOUR)){
        str_copy(format, T_HOUR_F);
        sprintf(to, format, Clock_hour(r));
    }

    else if(!strcmp(f, PRINT_YDAY)){
        str_copy(format, T_YDAY_F);
        sprintf(to, format, Clock_yday(r));
    }
    else if(!strcmp(f, PRINT_WDAY)){
        str_copy(format, T_WDAY_F);
        sprintf(to, format, Clock_wday(r));
    }
    else if(!strcmp(f, PRINT_WDAY_NAME)){
        Clock_wday_name(r, to);
    }
    else if(!strcmp(f, PRINT_MDAY)){
        str_copy(format, T_MDAY_F);
        sprintf(to, format, Clock_mday(r));
    }

    else if(!strcmp(f, PRINT_WEEK)){
        str_copy(format, T_WEEK_F);
        sprintf(to, format, Clock_week(r));
    }
    else if(!strcmp(f, PRINT_MONTH)){
        str_copy(format, T_MONTH_F);
        sprintf(to, format, Clock_month(r));
    }
    else if(!strcmp(f, PRINT_MONTH_NAME)){
        Clock_month_name(r, to);
    }
    else if(!strcmp(f, PRINT_YEAR)){
        str_copy(format, T_YEAR_F);
        sprintf(to, format, Clock_year(r));
    }
}

// Clock properties
T_SEC Clock_sec(Clock*r)
{
    return r->_sec;
}

T_MIN Clock_min(Clock*r)
{
    return r->_min;
}

T_HOUR Clock_hour(Clock*r)
{
    return r->_hour;
}


T_YDAY Clock_yday(Clock*r)
{
    return r->_day;
}

T_WDAY Clock_wday(Clock*r)
{
    return Calendar_week_day(Clock_yday(r), Clock_year(r));
}

void Clock_wday_name(Clock*r, char str[])
{
    Calendar_week_day_name(Clock_wday(r), str);
}

T_MDAY Clock_mday(Clock*r)
{
    return Calendar_month_day(Clock_yday(r), Clock_year(r));
}


T_WEEK Clock_week(Clock*r)
{
    return Calendar_year_week(Clock_yday(r), Clock_year(r));
}

T_MONTH Clock_month(Clock*r)
{
    return Calendar_month(Clock_yday(r), Clock_year(r));
}

void Clock_month_name(Clock*r, char str[])
{
    Calendar_month_name(Clock_month(r), str);
}

T_YEAR Clock_year(Clock*r)
{
    return r->_year;
}

// Clock setters
void Clock_sec_def(Clock*r, T_SEC s)
{
    r->_sec = s;
}

void Clock_min_def(Clock*r, T_MIN m)
{
    r->_min = m;
}

void Clock_hour_def(Clock*r, T_HOUR h)
{
    r->_hour = h;
}


void Clock_yday_def(Clock*r, T_YDAY yday)
{
    r->_day = yday;
}

void Clock_wday_def(Clock*r, T_WDAY wday)
{
    T_YDAY week_yday_init;
    T_YEAR week_year_init;
    T_WDAY t;

    if((t = Calendar_week_days_to_init(Clock_wday(r)))
            < Clock_yday(r)
            ){
        week_year_init = Clock_year(r);
        week_yday_init = Clock_yday(r) - t;
    }
    else{
        week_year_init = Clock_year(r) - 1;
        week_yday_init = Calendar_year_days(week_year_init) - t;
    }
    printf("%i %i\n", week_year_init, week_yday_init);

    Clock_year_def(r, week_year_init);
    Clock_yday_def(r, week_yday_init);

    while(Clock_wday(r) != wday){
        Clock_sum(r, SECS_DAY);
    }
}

void Clock_mday_def(Clock*r, T_MDAY mday)
{
    T_YDAY mday_yday;
    mday_yday = Clock_yday(r) - Clock_mday(r);

    Clock_yday_def(r, mday_yday + mday);
}


void Clock_month_def(Clock*r, T_MONTH m)
{
    T_MONTH month;
    T_MDAY month_days;
    T_MDAY mday;

    month = JAN_;
    mday = Clock_mday(r);
    Clock_yday_def(r, 0);

    while(month < m){
        month_days = Calendar_month_days(month++, Clock_year(r));
        Clock_sum(r, month_days * SECS_DAY);
    }

    Clock_sum(r, mday * SECS_DAY);
}

void Clock_year_def(Clock*r, T_YEAR y)
{
    r->_year = y;
}


void Clock_time_set(
        Clock*r,
        T_HOUR h, T_MIN m, T_SEC s
        )
{
    Clock_sec_def(r, s);
    Clock_min_def(r, m);
    Clock_hour_def(r, h);
}

void Clock_date_set(
        Clock*r,
        T_MDAY mday, T_MONTH month, T_YEAR year
        )
{
    Clock_year_def(r, year);
    Clock_month_def(r, month);
    Clock_mday_def(r, mday);
}

// Calendar
int Calendar_year_leap(T_YEAR y)
{
    return LEAP_YEAR(y);
}

T_YDAY Calendar_year_days(T_YEAR y)
{
    return YEAR_DAYS(y);
}

ABS_T_WEEK Calendar_year_weeks(T_YEAR y)
{
    if(Calendar_year_leap(y))
        return 52.0 + 2.0 / 7.0;
    return 52 + 1.0 / 7.0;
}

T_WEEK Calendar_year_week(T_YDAY yday, T_YEAR year)
{
    ABS_T_YDAY days;
    ABS_T_WEEK week;
    T_YEAR y;

    days = Calendar_days_from_dates(
            1, 1,
            yday, year
            );

    week = (days + 1) / 7.0;
    y = 1;

    // printf("days: %lli\n", days);
    while(week > Calendar_year_weeks(y)){
        week -= Calendar_year_weeks(y++);
        // printf("week: %lf\n", week);
    }

    return week + 1;
}


T_WDAY Calendar_week_day(T_YDAY yday, T_YEAR year)
{
    ABS_T_YDAY days_since_1;  
    
    days_since_1 = Calendar_days_from_dates(
            1, 1, // from a monday
            yday, year
            );
    // We plus one for define sunday as the first day of week
    return ( days_since_1 + 1) % 7;
}

void Calendar_week_day_name(T_WDAY wday, char str[])
{
    switch(wday){
        case SUN:
            str_copy(str, "SUN");
            break;

        case MON:
            str_copy(str, "MON");
            break;

        case TUE:
            str_copy(str, "TUE");
            break;

        case WED:
            str_copy(str, "WED");
            break;

        case THU:
            str_copy(str, "THU");
            break;

        case FRI:
            str_copy(str, "FRI");
            break;

        case SAT:
            str_copy(str, "SAT");
            break;

        default:
            break;
    }
}

T_WDAY Calendar_week_days_to_init(T_WDAY wday)
{
    return wday - SUN;
}


T_MONTH Calendar_month(T_YDAY yday, T_YEAR year)
{
    T_MDAY mday;
    T_MONTH month;
    
    month = JAN_;
    while(yday >
            (mday = Calendar_month_days(month, year))
            ){
        yday -= mday;
        ++month;
    }
    
    return month;
}

T_MDAY Calendar_month_day(T_YDAY yday, T_YEAR year)
{
    T_MDAY mday;
    T_MONTH month;
    
    month = JAN_;
    while(yday >
            (mday = Calendar_month_days(month, year))
            ){
        yday -= mday;
        ++month;
    }
    
    return yday;
}

void Calendar_month_name(T_MONTH month, char str[])
{
    switch(month){
        case JAN_:
            str_copy(str, "JAN");
            break;

        case FEB_:
            str_copy(str, "FEB");
            break;

        case MAR_:
            str_copy(str, "MAR");
            break;

        case ABR_:
            str_copy(str, "ABR");
            break;

        case MAI_:
            str_copy(str, "MAI");
            break;

        case JUN_:
            str_copy(str, "JUN");
            break;

        case JUL_:
            str_copy(str, "JUL");
            break;

        case AGO_:
            str_copy(str, "AGO");
            break;

        case SEP_:
            str_copy(str, "SEP");
            break;
            
        case OCT_:
            str_copy(str, "OCT");
            break;

        case NOV_:
            str_copy(str, "NOV");
            break;

        case DEC_:
            str_copy(str, "DEC");
            break;

        default:
            break;
    }
}

T_YDAY Calendar_month_days(T_MONTH m, T_YEAR y)
{
    switch(m){
        case JAN_:
            return JAN_DAYS;
            break;
        
        case FEB_:
            return FEB_DAYS(y);
            break;
        
        case MAR_:
            return MAR_DAYS;
            break;
        
        case ABR_:
            return ABR_DAYS;
            break;
        
        case MAI_:
            return MAI_DAYS;
            break;
        
        case JUN_:
            return JUN_DAYS;
            break;
        
        case JUL_:
            return JUL_DAYS;
            break;
        
        case AGO_:
            return AGO_DAYS;
            break;
        
        case SEP_:
            return SEP_DAYS;
            break;
        
        case OCT_:
            return OCT_DAYS;
            break;
        
        case NOV_:
            return NOV_DAYS;
            break;
        
        case DEC_:
            return DEC_DAYS;
            break;

        default:
            break;
    }

    return 0;
}

ABS_T_YDAY Calendar_days_from_dates(
        T_YDAY y1day, T_YEAR year1,
        T_YDAY y2day, T_YEAR year2
        )
{
    ABS_T_YDAY days;

    if(year1 > year2){
        year1 += year2;
        year2 = year1 - year2;
        year1 -= year2;

        y1day += y2day;
        y2day = y1day - y2day;
        y1day -= y2day;
    }

    days = 0;
    while(year1 < year2){
        days += Calendar_year_days(year1++);
        // printf("%i\n", year1);
    }

    days += y2day;
    days -= y1day;

    return days;
}

//
void str_copy(char t[], char f[])
{
    size_t i, j;

    i = j = 0;
    while((t[i++] = f[j++]) != '\0');
}

void str_clean(char s[])
{
    s[0] = '\0';
}

void str_add_char(char s[], int c)
{
    size_t i;

    i = 0;
    while(s[i] != '\0')
        ++i;

    s[i] = c;
    s[i + 1] = '\0';
}

void str_replace(char str[], char sub[], char nsub[])
{
    char result[STR_REPLACE_MAX];
    int i, j, t;

    str_clean(result);
    i = t = 0;
    while((i = str_search(str, sub, t)) != -1){
        for(j=t; j < i; ++j)
            str_add_char(result, str[j]);

        t = i + strlen(sub);
        strcat(result, nsub);
      
      /*
		Serial.print(sub);
      	Serial.print(" ");
      	Serial.print(i);
      	Serial.print(" ");
      	Serial.print(j);
      	Serial.print(" ");
      	Serial.println(t);
      // */
        // printf("%i %i %i\n", i, j, t);
    }

    strcat(result, str + t);
    str_copy(str, result);
}

int str_search(char str[], char sub[], int index)
{
    int result;
    return (
            (result = is_substring(str + index, sub)) != -1
           )? result + index: -1;
}

int is_substring(char str[], char sub[])
{
    size_t str_len, sub_len;
    size_t remain_sub_chars;
    size_t i, j, t;
    
    str_len = strlen(str);
    sub_len = strlen(sub);
    i = j = 0;
    
    while(i < str_len){
        remain_sub_chars = sub_len;
        j = 0;
        t = i;
        
        while(
            remain_sub_chars
                && t < str_len && j < sub_len
                && str[t] == sub[j]
            ){
            ++j;
            ++t;
            
            --remain_sub_chars;
        }
        // printf("%li %li\n", t, j);
        
        if(!remain_sub_chars)
            return i;
            
        i = t + !j;
    }
    
    return -1;
}

