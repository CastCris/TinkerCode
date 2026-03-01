// #include"Adafruit_LEDBackpack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define PIN_BUTT_AJUST 2
#define PIN_BUTT_MODE 3
#define PIN_BUTT_RESET 4
#define PIN_BUTT_24F 5

//
enum{
    JAN = 1,
    FEB,
    MAR,
    ABR,
    MAI,
    JUN,
    JUL,
    AGO,
    SEP,
    OCT,
    NOV,
    DEC
};

enum{
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
 * Set the data type of each time measure
 * Data types used in storage of time measure
 */
#define T_SEC  unsigned short
#define T_MIN T_SEC
#define T_HOUR T_MIN

#define T_YDAY T_HOUR
#define T_WDAY T_YDAY
#define T_MDAY T_YDAY

#define T_WEEK T_YDAY
#define T_MONTH T_WEEK
#define T_YEAR unsigned

/* Absolute time measure data type
 * These data types are used when a date is only represent as a single time measure.
 * Like represent 00:00 1/1/2026 as: 63902908800 seconds or 17750808 hours
 * from 1/1/1
 */
#define ABS_T_SEC unsigned long long 
#define ABS_T_MIN ABS_T_SEC
#define ABS_T_HOUR ABS_T_MIN

#define ABS_T_YDAY ABS_T_HOUR

#define ABS_T_WEEK double
#define ABS_T_MONTH double
#define ABS_T_YEAR ABS_T_YDAY

/*
 * Theses macro define the data type of each time measure for input/ouput
 * operations
 */
#define T_SEC_F "%u"
#define T_MIN_F T_SEC_F
#define T_HOUR_F T_MIN_F

#define T_YDAY_F T_HOUR_F
#define T_WDAY_F T_YDAY_F
#define T_WDAY_NAME_F "%s"
#define T_MDAY_F T_WDAY_F

#define T_WEEK_F T_MDAY_F
#define T_MONTH_F T_WEEK_F
#define T_MONTH_NAME_F "%s"
#define T_YEAR_F T_MONTH_F


#define PRINT_SEC "%sec"
#define PRINT_MIN "%min"
#define PRINT_HOUR "%hour"

#define PRINT_YDAY "%yday"
#define PRINT_WDAY "%wday"
#define PRINT_WDAY_NAME "%Wday"
#define PRINT_MDAY "%mday"

#define PRINT_WEEK "%week"
#define PRINT_MONTH "%month"
#define PRINT_MONTH_NAME "%Month"
#define PRINT_YEAR "%year"

#define CLOCK_PRINT_F \
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

#define PRINT_F_MAX 1000

#define PRINT_DEFAULT \
    PRINT_HOUR ":" PRINT_MIN ":" PRINT_SEC " " \
    PRINT_MDAY "/" PRINT_MONTH "/" PRINT_YEAR "\n" \
    PRINT_WDAY_NAME ", " PRINT_MONTH_NAME


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

    T_SEC sec;
    T_MIN min;
    T_HOUR hour;
    
    T_YDAY day;
    T_YEAR year;
} Clock;


// Clock methods
Clock *Clock_create();
void Clock_sum(Clock *clock, ABS_T_SEC sec);
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
void Clock_wday_name(Clock*, char[]);
T_MDAY Clock_mday(Clock*);

T_WEEK Clock_week(Clock*);
T_MONTH Clock_month(Clock*);
void Clock_month_name(Clock*, char[]);
T_YEAR Clock_year(Clock*);


void Clock_sec_def(Clock*, T_SEC sec);
void Clock_min_def(Clock*, T_MIN min);
void Clock_hour_def(Clock*, T_HOUR hour);
void Clock_yday_def(Clock*, T_YDAY yday);
void Clock_year_def(Clock*, T_YEAR year);

// Calendar properties
int Calendar_year_leap(T_YEAR year);
T_YDAY Calendar_year_days(T_YEAR year);

ABS_T_WEEK Calendar_year_weeks(T_YEAR);

T_YDAY Calendar_month_days(T_MONTH month, T_YEAR year);

ABS_T_YDAY Calendar_days_from_dates(
        T_YDAY y1day, T_YEAR year1,
        T_YDAY y2day, T_YEAR year2
        );

// String methods
void str_copy(char to[], char from[]);
void str_clean(char str[]);
void str_add_char(char str[], int c);
void str_replace(char str[], char sub[], char nsub[]);

// External/globals variables
// const Adafruit_7segment clock_display = Adafruit_7segment();
Clock *clock;

/*
void setup()
{
    Serial.begin(115200);
    Serial.print("Hello Wolrd!\n");
    
    pinMode(PIN_BUTT_AJUST, INPUT);
    pinMode(PIN_BUTT_RESET, INPUT);
    pinMode(PIN_BUTT_MODE, INPUT);
    pinMode(PIN_BUTT_24F, INPUT);
    
    pinMode(LED_BUILTIN, OUTPUT);
}
*/

int main()
{
    /*
    char a[100] = "aaaab";
    char b[100] = "yyy";

    str_copy(b, a);
    printf("%s %li\n", b, strlen(b));

    str_clean(b);
    printf("%s\n", b);

    str_add_char(b, 'H');
    printf("%s\n", b);

    str_copy(b, "aaa eee bbbb ccc");
    str_replace(b, "e", "-dd1-");
    printf("%s\n", b);
    // */

    // /*
    char output[PRINT_F_MAX];

    clock = Clock_create();
    // Clock_sec_def(clock, 27);
    // Clock_min_def(clock, 10);
    Clock_sec_def(clock, 0);
    Clock_min_def(clock, 0);
    Clock_hour_def(clock, 0);

    Clock_yday_def(clock, 1);
    Clock_year_def(clock, 2026);

    // /*
    for(;Clock_yday(clock) <= 31;){
        Clock_sum(clock, 1);
        Clock_sprintf(clock, output, PRINT_DEFAULT);

        printf("%s\n", output);
        // usleep(100 * 1000);
    }

    // */

    return 0;
}

// Clock methods
Clock *Clock_create()
{
    Clock *clock_new = (Clock*)malloc(sizeof(Clock));
    
    clock_new->sec = 
    clock_new->min =
    clock_new->hour = 0;
    
    clock_new->day = 1;
    clock_new->year = 1;
    
    return clock_new;
}

void Clock_sum(Clock *clock, ABS_T_SEC s)
{ 
    ABS_T_SEC sec = Clock_sec(clock);
    ABS_T_MIN min = Clock_min(clock);
    ABS_T_HOUR hour = Clock_hour(clock);
    ABS_T_YDAY day = Clock_yday(clock);
    ABS_T_YEAR year = Clock_year(clock);

    sec += s;
    min += sec / 60;
    hour += min / 60;
    day += hour / 24;
    
    T_YDAY year_days;
    while(day >
            (year_days = Calendar_year_days(year))
            ){
        day -= year_days;
        ++year;
    }
    
    clock->sec = sec % 60;
    clock->min = min % 60;
    clock->hour = hour % 24;
    clock->day = day;
    clock->year = year;
}

void Clock_sprintf(Clock *r, char t[], char f[])
{
    char clock_print_f[] = CLOCK_PRINT_F;
    char result[PRINT_F_MAX];

    char buff[PRINT_F_MAX] = "";
    char data[PRINT_F_MAX] = "";
    size_t i;
    int c;

    str_copy(result, f);
    i = 0;

    while((c = clock_print_f[i++]) != '\0'){
        if(c != '\n'){
            str_add_char(buff, c);
            continue;
        }
        Clock_data_from_format(r, data, buff);

        /*
        printf("buff: %s\n", buff);
        printf("data: %s\n", data);
        // */

        str_replace(result, buff, data);
        str_clean(buff);
    }

    // printf("%s\n", result);
    str_copy(t, result);
}

void Clock_data_from_format(Clock *r, char t[], char f[])
{
    char format[PRINT_F_MAX];
    if(!strcmp(f, PRINT_SEC)){
        str_copy(format, T_SEC_F);
        sprintf(t, format, Clock_sec(r));
    }
    else if(!strcmp(f, PRINT_MIN)){
        str_copy(format, T_MIN_F);
        sprintf(t, format, Clock_min(r));
    }
    else if(!strcmp(f, PRINT_HOUR)){
        str_copy(format, T_HOUR_F);
        sprintf(t, format, Clock_hour(r));
    }

    else if(!strcmp(f, PRINT_YDAY)){
        str_copy(format, T_YDAY_F);
        sprintf(t, format, Clock_yday(r));
    }
    else if(!strcmp(f, PRINT_WDAY)){
        str_copy(format, T_WDAY_F);
        sprintf(t, format, Clock_wday(r));
    }
    else if(!strcmp(f, PRINT_WDAY_NAME)){
        Clock_wday_name(r, t);
    }
    else if(!strcmp(f, PRINT_MDAY)){
        str_copy(format, T_MDAY_F);
        sprintf(t, format, Clock_mday(r));
    }

    else if(!strcmp(f, PRINT_WEEK)){
        str_copy(format, T_WEEK_F);
        sprintf(t, format, Clock_week(r));
    }
    else if(!strcmp(f, PRINT_MONTH)){
        str_copy(format, T_MONTH_F);
        sprintf(t, format, Clock_month(r));
    }
    else if(!strcmp(f, PRINT_MONTH_NAME)){
        Clock_month_name(r, t);
    }
    else if(!strcmp(f, PRINT_YEAR)){
        str_copy(format, T_YEAR_F);
        sprintf(t, format, Clock_year(r));
    }
}

// Clock properties
T_SEC Clock_sec(Clock*r)
{
    return r->sec;
}

T_MIN Clock_min(Clock*r)
{
    return r->min;
}

T_HOUR Clock_hour(Clock*r)
{
    return r->hour;
}


T_YDAY Clock_yday(Clock*r)
{
    return r->day;
}

T_WDAY Clock_wday(Clock*r)
{
    ABS_T_YDAY days_since_1;  
    
    days_since_1 = Calendar_days_from_dates(
            1, 1, // from a monday
            Clock_yday(r), Clock_year(r) 
            );
    // We plus one for define sunday as the first day of week
    return ( days_since_1 + 1) % 7;
}

void Clock_wday_name(Clock*r, char str[])
{
    switch(Clock_wday(r)){
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

T_MDAY Clock_mday(Clock*r)
{
    T_YDAY yday;
    T_MDAY mday;
    T_MONTH month;
    T_YEAR y;

    yday = Clock_yday(r);
    month = 0;
    y = Clock_year(r);
    while(yday >
            (mday = Calendar_month_days(month++, y)))
        yday -= mday;

    return yday;
}


T_WEEK Clock_week(Clock*r)
{
    ABS_T_YDAY days;
    ABS_T_WEEK week;
    T_YEAR y;

    days = Calendar_days_from_dates(
            1, 1,
            Clock_yday(r), Clock_year(r)
            );

    week = days / 7.0;
    y = 1;

    // printf("days: %lli\n", days);

    while(week > Calendar_year_weeks(y)){
        week -= Calendar_year_weeks(y++);
        // printf("week: %lf\n", week);
    }

    return week + 1;
}

T_MONTH Clock_month(Clock*r)
{
    T_YDAY yday;
    T_MDAY mday;
    T_MONTH month;
    T_YEAR y;
    
    yday = Clock_yday(r);
    month = 1;
    y = Clock_year(r);
    while(yday >
            (mday = Calendar_month_days(month, y))
            ){
        yday -= mday;
        ++month;
    }
    
    return month;
}

void Clock_month_name(Clock*r, char str[])
{
    switch(Clock_month(r)){
        case JAN:
            str_copy(str, "JAN");
            break;

        case FEB:
            str_copy(str, "FEB");
            break;

        case MAR:
            str_copy(str, "MAR");
            break;

        case ABR:
            str_copy(str, "ABR");
            break;

        case JUN:
            str_copy(str, "JUN");
            break;

        case JUL:
            str_copy(str, "JUL");
            break;

        case AGO:
            str_copy(str, "AGO");
            break;

        case SEP:
            str_copy(str, "SEP");
            break;
            
        case OCT:
            str_copy(str, "OCT");
            break;

        case NOV:
            str_copy(str, "NOV");
            break;

        case DEC:
            str_copy(str, "DEC");
            break;

        default:
            break;
    }
}

T_YEAR Clock_year(Clock*r)
{
    return r->year;
}


void Clock_sec_def(Clock *r, T_SEC s)
{
    r->sec = s;
}

void Clock_min_def(Clock *r, T_MIN m)
{
    r->min = m;
}

void Clock_hour_def(Clock *r, T_HOUR h)
{
    r->hour = h;
}

void Clock_yday_def(Clock *r, T_YDAY yday)
{
    r->day = yday;
}

void Clock_year_def(Clock *r, T_YEAR y)
{
    r->year = y;
}

//
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


T_YDAY Calendar_month_days(T_MONTH m, T_YEAR y)
{
    switch(m){
    case JAN:
    return JAN_DAYS;
    break;
    
    case FEB:
    return FEB_DAYS(y);
    break;
    
    case MAR:
    return MAR_DAYS;
    break;
    
    case ABR:
    return ABR_DAYS;
    break;
    
    case MAI:
    return MAI_DAYS;
    break;
    
    case JUN:
    return JUN_DAYS;
    break;
    
    case JUL:
    return JUL_DAYS;
    break;
    
    case AGO:
    return AGO_DAYS;
    break;
    
    case SEP:
    return SEP_DAYS;
    break;
    
    case OCT:
    return OCT_DAYS;
    break;
    
    case NOV:
    return NOV_DAYS;
    break;
    
    case DEC:
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
    char *result;
    // char result[PRINT_F_MAX] = "";
    char *psub;
    char *c;
    size_t i;

    // /*
    result = malloc(sizeof(char) * strlen(str) * (strlen(nsub) + 1));
    result[0] = '\0';
    // */
    psub = strstr(str, sub);
    i = 0;

    while(psub != NULL){
        while(
                (c = &(str[i])) != psub
             ){
            str_add_char(result, *c);
            ++i;
        }
        strcat(result, nsub);
        // printf("%li ^%s$ ^%s$\n", i, psub, str + i);

        i += strlen(sub);
        psub = strstr(str + i, sub);
    }
    strcat(result, str + i);
    str_copy(str, result);

    // free(result);

    // printf("%s\n", result);
}
