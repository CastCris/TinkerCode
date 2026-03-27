#include<LiquidCrystal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

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

/* Define min year and the week day of the min year */
#define REF_YEAR 1 // 2026
#define REF_WDAY MON // THU

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
typedef uint16_t T_MS;

typedef uint8_t T_SEC;
typedef uint8_t T_MIN;
typedef uint8_t T_HOUR;

typedef uint16_t T_YDAY;
typedef uint8_t T_WDAY;
typedef uint8_t T_MDAY;

typedef uint8_t T_WEEK;
typedef uint8_t T_MONTH;
typedef uint32_t  T_YEAR;


typedef int16_t T_SIGNED_YDAY;

/* Absolute time measure data type
 * These data types are used when a date is only represent as a single time measure.
 * Like represent 00:00 1/1/2026 as: 63902908800 seconds or 17750808 hours
 * from 1/1/1
 */
typedef uint64_t ABS_T_MS;

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
#define T_MS_F "%03u"

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

#define PRINT_MS \
    CLOCK_PRINTF_COMMON "ms"

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
    PRINT_MS "\n" \
    \
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
#define CLOCK_PRINTF_RESULT_MAX 55


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
    T_MS _ms;

    T_SEC _sec;
    T_MIN _min;
    T_HOUR _hour;
    
    T_YDAY _day;
    T_YEAR _year;
} Clock;


// Clock methods
Clock* Clock_create();
void Clock_reset(Clock*);
void Clock_sum(Clock*, ABS_T_SEC sec);
void Clock_sum_ms(Clock*r, ABS_T_MS ms);

void Clock_sprintf(Clock*, char to[], char format[]);
void Clock_data_from_format(Clock*, char to[], char format[]);

int Clock_same_time(Clock*, Clock*);
int Clock_same_date(Clock*, Clock*);

// int Clock_before_date(Clock*, ABS_T_SEC time);
// int Clock_after_date(Clock*, ABS_T_SEC time);

// Clock properties / setters
T_MS Clock_ms(Clock*);

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


void Clock_ms_def(Clock*, T_MS ms);

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
T_YEAR Calendar_yearsLeap_util_year(T_YEAR y);

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
        T_YDAY y1day, T_YEAR y1,
        T_YDAY y2day, T_YEAR y2
        );

// String methods
void str_copy(char to[], char from[]);
void str_clean(char str[]);
void str_add_char(char str[], int c);
void str_replace(char str[], char sub[], char nsub[]);
int str_search(char str[], char sub[], int index);

int is_substring(char str[], char sub[]);

// External/globals variables
Clock cDate;
Clock cAlarm;
Clock cStopw;
Clock cStopwSnap;
Clock cStopwMark;
char clock_output[CLOCK_PRINTF_RESULT_MAX];

#define RS_PIN 8
#define EN_PIN 9
#define D7_PIN 13
#define D6_PIN 12
#define D5_PIN 11
#define D4_PIN 10
// /*
LiquidCrystal clockDisplay(
  RS_PIN, EN_PIN,
  D4_PIN, D5_PIN, D6_PIN, D7_PIN
  );
// */

typedef uint8_t T_PIN;

#define PIN_BUTT_ADJUST 2
#define PIN_BUTT_MODE 3
#define PIN_BUTT_RESET 4
#define PIN_BUTT_24F 5
#define BUTT_DELAY 100

T_PIN buttAdj_val;
T_PIN buttMode_val;
T_PIN buttReset_val;
T_PIN butt24F_val;
unsigned long t, last_t;

enum {
  MODE_ADJUST_DATE,
  MODE_ADJUST_ALARM,
  MODE_ALARM_ON,
  MODE_STOPW_MARK,
  MODE_STOPW_DIFF,
  
  MODE_INIT,
  MODE_DATE,
  MODE_ALARM,
  MODE_STOPW,
  MODE_END
};

int mode = MODE_DATE;
int last_mode = MODE_DATE;
int mode_swapped = 1;

enum {
  ADJUST_DATE_INIT,
  ADJUST_DATE_SEC,
  ADJUST_DATE_MIN,
  ADJUST_DATE_HOUR,  
  ADJUST_DATE_MDAY,
  ADJUST_DATE_MONTH,
  ADJUST_DATE_YEAR,
  ADJUST_DATE_END,
  
  ADJUST_ALARM_INIT,
  ADJUST_ALARM_HOUR,
  ADJUST_ALARM_MIN,
  ADJUST_ALARM_SEC,
  ADJUST_ALARM_STATE,
  ADJUST_ALARM_END
};


uint8_t adjust;
uint8_t adjust_swapped;
#define ADJUST_BLINK_DELAY 300
uint16_t adjust_blink_delay;
uint8_t adjust_blink;

enum {
  ALARM_STATE_ENABLE,
  ALARM_STATE_DISABLE,
  ALARM_STATE_ON
};
uint8_t alarm_state = ALARM_STATE_DISABLE;
#define ALARM_ON_MSG "WAKE UP!"
#define ALARM_ON_MSG_BLINK_DELAY 250
uint16_t alarm_msg_blink_delay;
uint8_t alarm_msg_blink;

enum {
  STOPW_STATE_ENABLE,
  STOPW_STATE_DISABLE
};
uint8_t stopw_state = STOPW_STATE_DISABLE;

#define PIEZO_PIN 6

// /*
void Clock_display_modeDate();
void Clock_display_modeAlarm();
void Clock_display_modeAlarmOn();
void Clock_display_modeStopw();

void Clock_display_modeStopwMark();
void Clock_display_modeStopwDiff();
#define CLOCK_MIN_YEAR 1
#define CLOCK_MAX_YEAR 9999
void Clock_display_modeAdjustDate();
void Clock_display_modeAdjustDate_plus();
void Clock_display_modeAdjustDate_minus();

void Clock_display_modeAdjustAlarm();
void Clock_display_modeAdjustAlarm_plus();
void Clock_display_modeAdjustDate_minus();


void Clock_tone_switch_mode();


void setup()
{   
    pinMode(PIN_BUTT_ADJUST, INPUT);
    pinMode(PIN_BUTT_RESET, INPUT);
    pinMode(PIN_BUTT_MODE, INPUT);
    pinMode(PIN_BUTT_24F, INPUT);
    pinMode(PIEZO_PIN, OUTPUT);
  
    
    Serial.begin(9600);
    Serial.println("BEGIN CLOCK!");
    clockDisplay.begin(16, 2);
  
    Clock_reset(&cDate);
    Clock_reset(&cAlarm);
    Clock_reset(&cStopw);
  
    Clock_date_set(&cDate, 31, 12, 2026);
    Clock_time_set(&cDate, 23, 59, 50);
  
    Clock_time_set(&cAlarm, 23, 59, 50);
}

void loop()
{  
    // Read the buttons input
    buttAdj_val = digitalRead(PIN_BUTT_ADJUST);
    buttMode_val = digitalRead(PIN_BUTT_MODE);
    buttReset_val = digitalRead(PIN_BUTT_RESET);
    butt24F_val = digitalRead(PIN_BUTT_24F);
  
    // Set last_mode to current mode
    last_mode = mode;
  
    // Check if cAlarm is same time of cDate
    if(Clock_same_time(&cDate, &cAlarm)
        && alarm_state == ALARM_STATE_ENABLE
      ){
        alarm_state = ALARM_STATE_ON;
        mode = MODE_ALARM_ON;
    }
    
    // Enable circular mode browser
    if(mode == MODE_END){
        mode = MODE_INIT + 1;
    }
    switch(mode){
        case MODE_DATE:
          Clock_display_modeDate();
      
          // Switch mode
          if(buttMode_val == HIGH){
              ++mode;
          }
          // Adjust the date
          else if(buttAdj_val == HIGH){
              mode = MODE_ADJUST_DATE;
          }
          else if(buttReset_val == HIGH){
            Serial.println("Reseted!");
          }
          else if(butt24F_val == HIGH){
              Serial.println(":)");
          }
      
          break;

        case MODE_ALARM:
          Clock_display_modeAlarm();
          
          // Swtich Mode
          if(buttMode_val == HIGH){ 
                ++mode;
            }
          // Adjust the alarm
          else if(buttAdj_val == HIGH){
                mode = MODE_ADJUST_ALARM;
            }
          else if(buttReset_val == HIGH){
                Serial.println("Reseted!");
            }
          else if(butt24F_val == HIGH){
            Serial.println(":)");
            }
            
          break;

        case MODE_STOPW:
          Clock_display_modeStopw();
      
          if(Clock_hour(&cStopw) == 23
               && Clock_min(&cStopw) == 59
               && Clock_sec(&cStopw) == 59
              ){
                Clock_reset(&cStopw);
            }
          
      // Swtich Mode
          if(buttMode_val == HIGH){
                ++mode;
            }
          else if(buttAdj_val == HIGH 
                   && stopw_state == STOPW_STATE_DISABLE
                   ){
                Clock_reset(&cStopw);
                Clock_reset(&cStopwSnap);
                Clock_reset(&cStopwMark);
            }
          else if(buttAdj_val == HIGH
                    && stopw_state == STOPW_STATE_ENABLE
                   ){
                mode = MODE_STOPW_MARK;
                Clock_ms_def(&cStopwSnap, Clock_ms(&cStopw));
                Clock_sec_def(&cStopwSnap, Clock_sec(&cStopw));
                Clock_min_def(&cStopwSnap, Clock_min(&cStopw));
                Clock_hour_def(&cStopwSnap, Clock_hour(&cStopw));
            }
          else if(buttReset_val == HIGH){
                stopw_state = 
                  (stopw_state == STOPW_STATE_DISABLE)?
                    STOPW_STATE_ENABLE: STOPW_STATE_DISABLE;
            }
          else if(butt24F_val == HIGH){
            }
        
          break;
      
        
        case MODE_STOPW_MARK:
          if(mode_swapped){
                Clock_display_modeStopwMark();
            }
          
          if(buttMode_val == HIGH){
                mode = MODE_STOPW_DIFF;
            }
          else if(buttAdj_val == HIGH){
                mode = MODE_STOPW;
              
                Clock_ms_def(&cStopwMark, Clock_ms(&cStopwSnap));
                Clock_sec_def(&cStopwMark, Clock_sec(&cStopwSnap));
                Clock_min_def(&cStopwMark, Clock_min(&cStopwSnap));
                Clock_hour_def(&cStopwMark, Clock_hour(&cStopwSnap));
            }
          else if(buttReset_val == HIGH){
            }
          else if(butt24F_val == HIGH){
            }
          break;
      
        case MODE_STOPW_DIFF:
          if(mode_swapped){
                Clock_display_modeStopwDiff();
            }
      
          if(buttMode_val == HIGH){
                mode = MODE_STOPW_MARK;
            }
          else if(buttAdj_val == HIGH){
                mode = MODE_STOPW;
              
                Clock_ms_def(&cStopwMark, Clock_ms(&cStopwSnap));
                Clock_sec_def(&cStopwMark, Clock_sec(&cStopwSnap));
                Clock_min_def(&cStopwMark, Clock_min(&cStopwSnap));
                Clock_hour_def(&cStopwMark, Clock_hour(&cStopwSnap));
            }
          else if(buttReset_val == HIGH){
            }
          else if(butt24F_val == HIGH){
            }
          
          break;
                
      
        case MODE_ADJUST_DATE:
          Clock_display_modeAdjustDate();
          adjust_swapped = 0;
      
          if(mode_swapped || adjust == ADJUST_DATE_END){
            adjust = ADJUST_DATE_INIT + 1;
            }
      
          // Switch Mode
          if(buttAdj_val == HIGH){
                mode = MODE_DATE;
            }
      
          if(buttMode_val == HIGH){
                ++adjust;
                adjust_swapped = 1;
            }
      
          if(buttReset_val == HIGH){
                // Clock_display_modeAdjustDate_plus();
                Clock_display_modeAdjustDate_minus();
            }
      
          if(butt24F_val == HIGH){
                // Clock_display_modeAdjustDate_minus();
                 Clock_display_modeAdjustDate_plus();
            }
          break;
      
        case MODE_ADJUST_ALARM:
          Clock_display_modeAdjustAlarm();
          adjust_swapped = 0;
      
          if(mode_swapped || adjust == ADJUST_ALARM_END){
            adjust = ADJUST_ALARM_INIT + 1;
            }
      
          // Switch Mode
          if(buttAdj_val == HIGH){
            mode = MODE_ALARM;
            }
      
          if(buttMode_val == HIGH){
                ++adjust;
                adjust_swapped = 1;
            }
      
          if(buttReset_val == HIGH){
                // Clock_display_modeAdjustAlarm_plus();
                Clock_display_modeAdjustAlarm_minus();
            }
      
          if(butt24F_val == HIGH){
                // Clock_display_modeAdjustAlarm_minus();
                Clock_display_modeAdjustAlarm_plus();
            }
          break;
     
        case MODE_ALARM_ON:
          Clock_display_modeAlarmOn();
          
          if(buttAdj_val == HIGH
               || buttMode_val == HIGH
               || buttReset_val == HIGH
               || butt24F_val == HIGH
              ){
                noTone(PIEZO_PIN);
                mode = MODE_INIT + 1;
                alarm_state = ALARM_STATE_ENABLE;
            }
          break;
          
        default:
          break;
    }
    mode_swapped = last_mode != mode;
    if(mode_swapped){
        Clock_tone_switch_mode();
    }
  
    t = millis();
    if(last_t < t){
      Clock_sum_ms(&cDate, t - last_t);
        Clock_sum_ms(
          &cStopw,
          (stopw_state == STOPW_STATE_DISABLE)?
            0: t - last_t
          );
    }
    else {
      Clock_sum_ms(
            &cDate,
            (ABS_T_SEC)
              (((ABS_T_SEC)1 << 32) - (ABS_T_SEC)last_t + t)
          );
        Clock_sum_ms(
            &cDate,
            (stopw_state == STOPW_STATE_DISABLE)?
            0: (((ABS_T_SEC)1 << 32) - (ABS_T_SEC)last_t + t)
          );
    }
    last_t = t;

    delay(BUTT_DELAY);
  
    // Blinks
    adjust_blink_delay %= ADJUST_BLINK_DELAY;
    adjust_blink_delay += BUTT_DELAY;
  
    alarm_msg_blink_delay %= ALARM_ON_MSG_BLINK_DELAY;
    alarm_msg_blink_delay += BUTT_DELAY;
  
    if(adjust_blink_delay >= ADJUST_BLINK_DELAY){
        adjust_blink = !adjust_blink;
    }
    if(alarm_msg_blink_delay >= ALARM_ON_MSG_BLINK_DELAY){
        alarm_msg_blink = !alarm_msg_blink;
    }
    
    if(mode_swapped){
        alarm_msg_blink = adjust_blink = 0;
        adjust_blink_delay = alarm_msg_blink_delay = 0;
    }
}


void Clock_tone_switch_mode()
{
    tone(PIEZO_PIN, 6115 - 87, 100);
}


void Clock_display_modeDate()
{   
    if(mode_swapped){
      clockDisplay.clear();
    }
  
    // HOUR:MIN:SEC
    if(
        (
        !Clock_sec(&cDate)
       && !Clock_min(&cDate)
         )
        || mode_swapped
      ){
      clockDisplay.setCursor(0, 0);
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_HOUR ":"
          );
        clockDisplay.print(clock_output);
    }
    if(!Clock_sec(&cDate) || mode_swapped){
        clockDisplay.setCursor(3, 0);
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_MIN ":"
          );
        clockDisplay.print(clock_output);
    }
  
    clockDisplay.setCursor(6, 0);
    Clock_sprintf(
        &cDate,
        clock_output,
        PRINT_SEC
      );
    clockDisplay.print(clock_output);
  
    // MDAY/MONTH/YEAR WDAY
    if(
        (
        !Clock_sec(&cDate)
         && !Clock_min(&cDate)
         && !Clock_hour(&cDate)
        ) || mode_swapped
      ){
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_MDAY "/" PRINT_MONTH_NAME "/" PRINT_YEAR " "
            PRINT_WDAY_NAME
          );
      
        clockDisplay.setCursor(0, 1);
        clockDisplay.print(clock_output);
    }
}

void Clock_display_modeAlarm()
{
    if(mode_swapped){
        clockDisplay.clear();
      
      clockDisplay.setCursor(0, 0);
      clockDisplay.print("ALARM");
    
      clockDisplay.setCursor(0, 1);
      Clock_sprintf(
          &cAlarm,
          clock_output,
          PRINT_HOUR ":" PRINT_MIN ":" PRINT_SEC
        );
      clockDisplay.print(clock_output);
      
        clockDisplay.setCursor(15, 1);
        clockDisplay.print(
          alarm_state == ALARM_STATE_DISABLE? "D": "E"
          );
    }
  
    // HH:MM
    if(
        !Clock_sec(&cAlarm)
        || mode_swapped
    ){
      clockDisplay.setCursor(11, 0);
      Clock_sprintf(
          &cDate,
          clock_output,
          PRINT_HOUR ":" PRINT_MIN
        );
      clockDisplay.print(clock_output);
    }
}

void Clock_display_modeAlarmOn()
{
    if(mode_swapped){
      clockDisplay.clear();
    }
  
    if(alarm_msg_blink){
        clockDisplay.setCursor(4, 0);
        clockDisplay.print("        ");
    } else {
        clockDisplay.setCursor(4, 0);
        clockDisplay.print(ALARM_ON_MSG);
    }
  
    if(alarm_msg_blink_delay >= ALARM_ON_MSG_BLINK_DELAY
         && !alarm_msg_blink
      ){
        tone(PIEZO_PIN, 1000);
    }
    else if(alarm_msg_blink_delay >= ALARM_ON_MSG_BLINK_DELAY
        && alarm_msg_blink
       ){
        noTone(PIEZO_PIN);
    }
  
    // HOUR:MIN:SEC
    // HOUR
    if(
      mode_swapped
      || (
        !Clock_min(&cDate)
        && !Clock_sec(&cDate)
        )
    ){
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_HOUR ":"
          );
      
        clockDisplay.setCursor(4, 1);
        clockDisplay.print(clock_output);
    }
  
    // MIN
    if(
      mode_swapped
      || !Clock_sec(&cDate)
    ){
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_MIN ":"
          );
      
        clockDisplay.setCursor(7, 1);
        clockDisplay.print(clock_output);
    }
  
    // SEC
    Clock_sprintf(
        &cDate,
        clock_output,
        PRINT_SEC
      );
  
    clockDisplay.setCursor(10, 1);
    clockDisplay.print(clock_output);
}

void Clock_display_modeStopw()
{
    if(mode_swapped){
      clockDisplay.clear();
      clockDisplay.setCursor(0, 0);
      clockDisplay.print("STOPW");
    }
  
    // HOUR:MIN:SEC MS
    // HOUR
    if(
        (
          !Clock_min(&cStopw)
          && !Clock_sec(&cStopw)
         )
        || mode_swapped
    ){
        Clock_sprintf(
            &cStopw,
            clock_output,
            PRINT_HOUR ":"
          );
      
        clockDisplay.setCursor(0, 1);
        clockDisplay.print(clock_output);
    }
  
    // MIN
    if(
        !Clock_sec(&cStopw)
        || mode_swapped
    ){
        Clock_sprintf(
            &cStopw,
            clock_output,
            PRINT_MIN ":"
          );
      
        clockDisplay.setCursor(3, 1);
        clockDisplay.print(clock_output);
    }
  
    // SEC
    Clock_sprintf(
        &cStopw,
        clock_output,
        PRINT_SEC
      );
    clockDisplay.setCursor(6, 1);
    clockDisplay.print(clock_output);
  
    Clock_sprintf(
        &cStopw,
        clock_output,
        PRINT_MS
      );
    clockDisplay.setCursor(9, 1);
    clockDisplay.print(clock_output);
  
    // HOUR:MIN
    if(
        mode_swapped
        || !Clock_sec(&cDate)
    ){
        clockDisplay.setCursor(11, 0);
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_HOUR ":" PRINT_MIN
          );
        clockDisplay.print(clock_output);
    }
}


void Clock_display_modeStopwMark()
{
  clockDisplay.clear();
      
    clockDisplay.setCursor(0, 0);
    clockDisplay.print("STOPW MARK");
  
    Clock_sprintf(
        &cStopwSnap,
        clock_output,
        PRINT_HOUR ":" PRINT_MIN ":" PRINT_SEC " " PRINT_MS
    );
  clockDisplay.setCursor(0, 1);
  clockDisplay.print(clock_output);
}


void Clock_display_modeStopwDiff()
{
    clockDisplay.clear();
  
    clockDisplay.setCursor(0, 0);
    clockDisplay.print("STOPW DIFF");
  
    uint16_t secs_diff = 
      (
        Clock_hour(&cStopwSnap) * SECS_HOUR
        + Clock_min(&cStopwSnap) * SECS_MIN
        + Clock_sec(&cStopwSnap)
        // + Clock_ms(&cStopwSnap)
        -
        ( Clock_hour(&cStopwMark) * SECS_HOUR
         + Clock_min(&cStopwMark) * SECS_MIN
         + Clock_sec(&cStopwMark)
         // + Clock_ms(&cStopwSnap)
         )
      )
      ;
    // +HOUR:MIN:SEC MS
    // +HOUR
    clockDisplay.setCursor(0, 1);
    clockDisplay.print("+");
    clockDisplay.print(
        ( secs_diff / SECS_HOUR ) % 24
      );
    clockDisplay.print(":");
  
    // MIN
    clockDisplay.print(
        ( secs_diff / SECS_MIN ) % 60
      );
    clockDisplay.print(":");
  
    // SEC
    clockDisplay.print(
        secs_diff % 60
      );
    clockDisplay.print(" ");
  
    // MS
    // /*
    clockDisplay.print(
        (
          Clock_sec(&cStopwSnap) * 1000
          + Clock_ms(&cStopwSnap)
          -
          ( Clock_sec(&cStopwMark) * 1000
           + Clock_ms(&cStopwMark)
           )
          ) % 1000
      );
     // */
}
      
      
void Clock_display_modeAdjustDate()
{
    if(mode_swapped){
      clockDisplay.clear();
    }
  
    // HOUR:MIN:SEC
    // HOUR
    if(adjust == ADJUST_DATE_HOUR &&
       adjust_blink
      ){
      clockDisplay.setCursor(0, 0);
        clockDisplay.print("  ");
    }
    else if(
        mode_swapped
        || adjust == ADJUST_DATE_HOUR
        || adjust_swapped
        || (
            !Clock_min(&cDate)
            && !Clock_sec(&cDate)
          )
    ){
        Clock_sprintf(
          &cDate,
          clock_output,
          PRINT_HOUR ":"
        );
        
        clockDisplay.setCursor(0, 0);
        clockDisplay.print(clock_output);
    }
  
    // MIN
    if(adjust == ADJUST_DATE_MIN 
         && adjust_blink
      ){
        clockDisplay.setCursor(3, 0);
        clockDisplay.print("  ");
    }
    else if(
        mode_swapped
        || adjust == ADJUST_DATE_MIN
        || adjust_swapped
        || !Clock_sec(&cDate)
    ){
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_MIN ":"
          );
      
        clockDisplay.setCursor(3, 0);
        clockDisplay.print(clock_output);
    }
  
    // SEC
    if(adjust == ADJUST_DATE_SEC
         && adjust_blink
      ){
        clockDisplay.setCursor(6, 0);
        clockDisplay.print("  ");
    }
    else{
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_SEC
          );
        
        clockDisplay.setCursor(6, 0);
        clockDisplay.print(clock_output);
    }
  
    // MDAY/MONTH/YEAR
    // MDAY
    if(adjust == ADJUST_DATE_MDAY 
         && adjust_blink
      ){
        clockDisplay.setCursor(0, 1);
        clockDisplay.print("  ");
    }
    else if(
        mode_swapped
        || adjust == ADJUST_DATE_MDAY
        || adjust_swapped
        ||  (
            !Clock_hour(&cDate)
            && !Clock_min(&cDate)
            && !Clock_sec(&cDate)
          )
    ){
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_MDAY "/"
          );
        
        clockDisplay.setCursor(0, 1);
        clockDisplay.print(clock_output);
    }
  
    // MONTH
    if(adjust == ADJUST_DATE_MONTH
       && adjust_blink
      ){
        clockDisplay.setCursor(3, 1);
        clockDisplay.print("   ");
    }
    else if(
        mode_swapped
        || adjust == ADJUST_DATE_MONTH
        || adjust_swapped
        || (
            !Clock_hour(&cDate)
            && !Clock_min(&cDate)
            && !Clock_sec(&cDate)
          )
    ){
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_MONTH_NAME "/"
          );
      
        clockDisplay.setCursor(3, 1);
        clockDisplay.print(clock_output);
    }
  
    // YEAR
    if(adjust == ADJUST_DATE_YEAR 
         && adjust_blink
      ){
        clockDisplay.setCursor(7, 1);
        clockDisplay.print("    ");
    }
    else if(
        mode_swapped
        || adjust == ADJUST_DATE_YEAR
        || adjust_swapped
        || (
            !Clock_hour(&cDate)
            && !Clock_min(&cDate)
            && !Clock_sec(&cDate)
          )
    ){
        Clock_sprintf(
            &cDate,
            clock_output,
            PRINT_YEAR
          );
      
        clockDisplay.setCursor(7, 1);
        clockDisplay.print(clock_output);
    }
}
      
void Clock_display_modeAdjustDate_plus()
{
    if(adjust == ADJUST_DATE_SEC){
      Clock_sec_def(&cDate, 0);
    }
    else if(adjust == ADJUST_DATE_MIN){
      Clock_min_def(
            &cDate,
            (Clock_min(&cDate) + 1) % 60
        );
    }
    else if(adjust == ADJUST_DATE_HOUR){
      Clock_hour_def(
            &cDate, 
            (Clock_hour(&cDate) + 1) % 24
        );
    }
  
    else if(adjust == ADJUST_DATE_MDAY){
        T_MDAY mday_new;
      
        mday_new = 
          (Clock_mday(&cDate) + 1) % (Calendar_month_days(Clock_month(&cDate), Clock_year(&cDate)) + 1);
        Clock_mday_def(
            &cDate,
            (mday_new)? mday_new: 1
        );
    }
    else if(adjust == ADJUST_DATE_MONTH){
        Clock_month_def(
            &cDate,
            (Clock_month(&cDate) + 1) % (DEC_ + 1)
          );
    }
    else if(adjust == ADJUST_DATE_YEAR){
        Clock_year_def(
            &cDate,
            (Clock_year(&cDate) < CLOCK_MAX_YEAR)?
              Clock_year(&cDate) + 1:
              CLOCK_MIN_YEAR
          );
    }
}

void Clock_display_modeAdjustDate_minus()
{
    if(adjust == ADJUST_DATE_SEC){
        Clock_sec_def(&cDate, 0);
    }
    else if(adjust == ADJUST_DATE_MIN){
        Clock_min_def(
            &cDate,
            (Clock_min(&cDate) > 0)? Clock_min(&cDate) - 1: 59
          );
    }
    else if(adjust == ADJUST_DATE_HOUR){
        Clock_hour_def(
            &cDate,
            (Clock_hour(&cDate) > 0)? Clock_hour(&cDate) - 1: 23
          );
    }
  
    else if(adjust == ADJUST_DATE_MDAY){
        T_MDAY mday, month_days;
        
        mday = Clock_mday(&cDate);
        month_days = Calendar_month_days(Clock_month(&cDate), Clock_year(&cDate));
        Clock_mday_def(
            &cDate,
            (mday > 1)? mday - 1: month_days
          );
    }
    else if(adjust == ADJUST_DATE_MONTH){
        Clock_month_def(
            &cDate,
            (Clock_month(&cDate) > JAN_)?
              Clock_month(&cDate) - 1: DEC_
          );
    }
    else if(adjust == ADJUST_DATE_YEAR){
        Clock_year_def(
            &cDate,
            (Clock_year(&cDate) > CLOCK_MIN_YEAR)?
              Clock_year(&cDate) - 1: CLOCK_MAX_YEAR
          );
    }
}


void Clock_display_modeAdjustAlarm()
{
    if(mode_swapped){
        clockDisplay.clear();
        clockDisplay.setCursor(0, 0);
      
        clockDisplay.print("ALARM");
    }
  
    // HOUR:MIN:SEC
    // HOUR
    if(adjust == ADJUST_ALARM_HOUR
         && adjust_blink
      ){
        clockDisplay.setCursor(0, 1);
        clockDisplay.print("  ");
    }
    else if(adjust == ADJUST_ALARM_HOUR
         || mode_swapped
         || adjust_swapped
       ){
        Clock_sprintf(
            &cAlarm,
            clock_output,
            PRINT_HOUR ":"
          );
        clockDisplay.setCursor(0, 1);
        clockDisplay.print(clock_output);
    }
  
    // MIN
    if(adjust == ADJUST_ALARM_MIN
         && adjust_blink
      ){
        clockDisplay.setCursor(3, 1);
        clockDisplay.print("  ");
    }
    else if(adjust == ADJUST_ALARM_MIN
        || mode_swapped
        || adjust_swapped
       ){
        Clock_sprintf(
            &cAlarm,
            clock_output,
            PRINT_MIN ":"
          );
        clockDisplay.setCursor(3, 1);
        clockDisplay.print(clock_output);
    }
  
    // SEC
    if(adjust == ADJUST_ALARM_SEC
    && adjust_blink
      ){
        clockDisplay.setCursor(6, 1);
        clockDisplay.print("  ");
    }
    else if(adjust == ADJUST_ALARM_SEC
         || mode_swapped
         || adjust_swapped
       ){
        Clock_sprintf(
            &cAlarm,
            clock_output,
            PRINT_SEC
          );
      
        clockDisplay.setCursor(6, 1);
        clockDisplay.print(clock_output);
    }
  
    // ALARM STATE
    if(adjust == ADJUST_ALARM_STATE
         && adjust_blink
      ){
        clockDisplay.setCursor(13, 1);
        clockDisplay.print("   ");
    }
    else if(adjust == ADJUST_ALARM_STATE
         || mode_swapped
         || adjust_swapped
       ){
        clockDisplay.setCursor(15, 1);
        clockDisplay.print(
          alarm_state == ALARM_STATE_DISABLE? "D": "E"
          );
    }
}


void Clock_display_modeAdjustAlarm_plus()
{
    if(adjust == ADJUST_ALARM_HOUR){
        Clock_hour_def(
            &cAlarm,
            (Clock_hour(&cAlarm) + 1) % 24
          );
    }
    else if(adjust == ADJUST_ALARM_MIN){
        Clock_min_def(
            &cAlarm,
            (Clock_min(&cAlarm) + 1) % 60
          );
    }
    else if(adjust == ADJUST_ALARM_SEC){
        Clock_sec_def(
            &cAlarm,
            (Clock_sec(&cAlarm) + 1) % 60
          );
    }
    else if(adjust == ADJUST_ALARM_STATE){
        alarm_state = 
          (alarm_state == ALARM_STATE_DISABLE)?
            ALARM_STATE_ENABLE: ALARM_STATE_DISABLE;
    }
}

void Clock_display_modeAdjustAlarm_minus()
{
    if(adjust == ADJUST_ALARM_SEC){
        Clock_sec_def(
            &cAlarm,
            (Clock_sec(&cAlarm) > 0)? Clock_sec(&cAlarm) - 1: 59
          );
    }
    else if(adjust == ADJUST_ALARM_MIN){
        Clock_min_def(
            &cAlarm,
            (Clock_min(&cAlarm) > 0)? Clock_min(&cAlarm) - 1: 59
          );
    }
    else if(adjust == ADJUST_ALARM_HOUR){
        Clock_hour_def(
            &cAlarm,
            (Clock_hour(&cAlarm) > 0)?
              Clock_hour(&cAlarm) - 1: 23
          );
    }
    else if(adjust == ADJUST_ALARM_STATE){
        alarm_state =
          (alarm_state == ALARM_STATE_DISABLE)?
          ALARM_STATE_ENABLE: ALARM_STATE_DISABLE;
    }
}
// */

// Clock methods
Clock* Clock_create()
{
    Clock *clock_new = (Clock*)malloc(sizeof(Clock));
    Clock_reset(clock_new);

    return clock_new;
}

void Clock_reset(Clock*r)
{
    Clock_ms_def(r, 0);
    Clock_sec_def(r, 0);
    Clock_min_def(r, 0);
    Clock_hour_def(r, 0);

    Clock_yday_def(r, 1);
    Clock_year_def(r, 1);
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

void Clock_sum_ms(Clock*r, ABS_T_MS time_ms)
{
    ABS_T_MS ms;
    ABS_T_SEC sec;

    ms = Clock_ms(r) + time_ms;
    sec = ms / 1000;

    if(sec){
      Clock_sum(r, sec);
    }
    Clock_ms_def(r, ms % 1000);
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
        
        if(is_substring(t, buff) != -1){
          Clock_data_from_format(r, data, buff);
          str_replace(t, buff, data);
        }
        str_clean(buff);
    }
}


void Clock_data_from_format(Clock*r, char to[], char f[])
{
    char format[CLOCK_PRINTF_MAX];

    if(!strcmp(f, PRINT_MS)){
        str_copy(format, T_MS_F);
        sprintf(to, format, Clock_ms(r));
    }

    else if(!strcmp(f, PRINT_SEC)){
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


int Clock_same_time(Clock*r1, Clock*r2)
{
    return
      Clock_sec(r1) == Clock_sec(r2)
      && Clock_min(r1) == Clock_min(r2)
      && Clock_hour(r1) == Clock_hour(r2);
}

int Clock_same_date(Clock*r1, Clock*r2)
{
    return
      Clock_year(r1) == Clock_year(r2)
      && Clock_month(r1) == Clock_month(r2)
      && Clock_mday(r1) == Clock_mday(r2);
}

// Clock properties
T_MS Clock_ms(Clock*r)
{
    return r->_ms;
}


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
void Clock_ms_def(Clock*r, T_MS ms)
{
    r->_ms = ms;
}


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

    week_yday_init = Clock_yday(r) - Calendar_week_days_to_init(Clock_wday(r));
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

T_YEAR Calendar_yearsLeap_util_year(T_YEAR y)
{
  return (y / 4 - y / 100 + y / 400);
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

    week = days / 7.0;
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
    ABS_T_YDAY days_since_yref;  
    
    days_since_yref = Calendar_days_from_dates(
            1, REF_YEAR,
            yday, year
            );

    if(year >= REF_YEAR){
        // We plus the REF_WDAY for define sunday
        // as the first day of week
        return ( days_since_yref + REF_WDAY ) % 7;
    }
    else {
        return (7 - (days_since_yref % 7) + REF_WDAY) % 7;
    }
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
        T_YDAY y1day, T_YEAR y1,
        T_YDAY y2day, T_YEAR y2
        )
{
    if(y1 > y2){
        y1 += y2;
        y2 = y1 - y2;
        y1 -= y2;

        y1day += y2day;
        y2day = y1day - y2day;
        y1day -= y2day;
    }

    T_YEAR yearsLeap_betw_y1_y2;
    yearsLeap_betw_y1_y2 =
        Calendar_yearsLeap_util_year(y2 - 1) - Calendar_yearsLeap_util_year(y1 - 1)
        ;

    return
        (y2 - y1) * 365
        + yearsLeap_betw_y1_y2
        + ((T_SIGNED_YDAY)y2day - (T_SIGNED_YDAY)y1day)
        ;
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
