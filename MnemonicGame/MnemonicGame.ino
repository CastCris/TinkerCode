#include<math.h>

// MUSICAL NOTES
#define PIEZO_PIN 6

#define NOTE_C0 16.35 // Do
#define NOTE_D0 18.35 // Re
#define NOTE_E0 20.60 // Mi
#define NOTE_F0 21.83 // Fa
#define NOTE_G0 24.50 // Sol
#define NOTE_A0 27.50 // La
#define NOTE_B0 30.87 // Si

#define NOTES { \
	NOTE_C0, \
    NOTE_D0, \
    NOTE_E0, \
    NOTE_F0, \
    NOTE_G0, \
    NOTE_A0, \
    NOTE_B0 \
    }

#define OCTAVES 9
enum {
  OCTV_0,
  OCTV_1,
  OCTV_2,
  OCTV_3,
  OCTV_4,
  OCTV_5,
  OCTV_6,
  OCTV_7,
  OCTV_8
};

enum{
  C_,
  D_,
  E_,
  F_,
  G_,
  A_,
  B_
};

#define HZ_NOTE(n, octv) hz_note(notes[n], octv)
const double notes[] = NOTES;
int hz_note(double note, int octave);

// MUSICAL GAME NOTES
#define NOTE_RED C_
#define NOTE_GREEN E_
#define NOTE_BLUE G_
#define NOTE_YELLOW B_

#define COLORS_NOTES { \
	NOTE_RED, \
    NOTE_GREEN, \
    NOTE_BLUE, \
    NOTE_YELLOW \
    }

const int colors_notes[] = COLORS_NOTES;
int note_from_color(int color);

// GAME COLORS LEDS AND BUTTONS
#define LED_RED_PIN 2
#define LED_GREEN_PIN 3
#define LED_BLUE_PIN 4
#define LED_YELLOW_PIN 5

#define BUTT_RED_PIN 8
#define BUTT_GREEN_PIN 9
#define BUTT_BLUE_PIN 10
#define BUTT_YELLOW_PIN 11

#define LEDS_GAME { \
	LED_RED_PIN, \
    LED_GREEN_PIN, \
    LED_BLUE_PIN, \
    LED_YELLOW_PIN \
    }

#define BUTTS_GAME { \
	BUTT_RED_PIN, \
    BUTT_GREEN_PIN, \
    BUTT_BLUE_PIN, \
    BUTT_YELLOW_PIN \
    }

const int leds[] = LEDS_GAME;
const int butts[] = BUTTS_GAME;

int ledPin_from_color(int color);

// GAME FUNCTIONS
#define GAME_COLORS_DELAY 500
#define GAME_COLORS_MAX 4
enum {
  COLOR_RED,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_YELLOW,
};

int color_from_buttPin(int color);

#define GAME_INIT_DELAY 100
#define GAME_INIT_LOOP_MAX 1
void game_init();
void game_clean();
void game_end();

#define NOTE_ENDED_BAD HZ_NOTE(G_, OCTV_2)
#define GAME_ENDED_BAD_DELAY 1000
void game_ended_bad();
#define NOTE_ENDED_GOOD HZ_NOTE(A_, OCTV_4)
#define GAME_ENDED_GOOD_DELAY 2000
void game_ended_good();

void game_hide_color(int color);
void game_show_color(int color, int octave, int time);
void game_just_hide_color(int color);
void game_just_show_color(int color);

#define GAME_MAKE_MOVE_DELAY 500
void game_make_move();
#define GAME_MOVE_DELAY 500
void game_move();

#define GAME_COLORS_PICK_MAX 10
int colorsPicked[GAME_COLORS_PICK_MAX];
size_t colorsPicked_size;
size_t colorsPicked_i;

int game_winned;
enum {
  GAME_MOVE_WRONG,
  GAME_MOVE_WINNED,
  
  GAME_MOVE_CORRECT,
  GAME_MOVE_FIRST,
  
  GAME_MOVE_WAIT
};
int game_move_status;

//
void setup()
{
  size_t i;
  for(i=0; i < GAME_COLORS_MAX; ++i){
    pinMode(leds[i], OUTPUT);
  }
  
  for(i=0; i < GAME_COLORS_MAX; ++i){
    pinMode(butts[i], INPUT);
  }
  pinMode(PIEZO_PIN, OUTPUT);
  
  randomSeed(analogRead(0));
  Serial.begin(9600);
  game_init();
}

void loop()
{ 
  switch(game_move_status){
    case GAME_MOVE_WINNED:
    case GAME_MOVE_WRONG:
    	game_end();
    	break;
    
    case GAME_MOVE_CORRECT:
    case GAME_MOVE_FIRST:
    	game_make_move();
    	break; 
    
    case GAME_MOVE_WAIT:
    	game_move();
    	delay(10);
    	break;
    
    default:
    	break;
  }
}


void game_init()
{
  int i, j;
  
  // /*
  for(j=0; j < GAME_INIT_LOOP_MAX; ++j){
  	for(i=COLOR_RED; i <= COLOR_YELLOW; ++i){
    	game_show_color(i, OCTV_5, GAME_INIT_DELAY);
    	delay(GAME_INIT_DELAY + 10);
    	game_hide_color(i);
  	}
    
    for(i=COLOR_YELLOW; i >= COLOR_RED; --i){
    	game_show_color(i, OCTV_5, GAME_INIT_DELAY);
    	delay(GAME_INIT_DELAY + 10);
    	game_hide_color(i);
  	}
  }
  
  game_move_status = GAME_MOVE_FIRST;
  delay(500);
  // */
}

void game_end()
{
  colorsPicked_i = colorsPicked_size = 0;
  
  if(game_move_status == GAME_MOVE_WRONG){
    game_ended_bad();
  }
  else if(game_move_status == GAME_MOVE_WINNED){
    game_ended_good();
  }
  
  delay(1000);
  game_init();
}

void game_ended_bad()
{
  tone(PIEZO_PIN, NOTE_ENDED_BAD, GAME_ENDED_BAD_DELAY);
  delay(GAME_ENDED_BAD_DELAY + 500);
}

void game_ended_good()
{
  int i, d;
  
  d = 0;
  // tone(PIEZO_PIN, NOTE_ENDED_GOOD, GAME_ENDED_GOOD_DELAY);
  while(d < GAME_ENDED_GOOD_DELAY){
  	for(i=COLOR_RED; i <= COLOR_YELLOW; ++i){
    	game_show_color(i, OCTV_4, 100);
      	delay(100);
      	game_hide_color(i);
    
    	d += 100;
    }
  }
}


void game_make_move()
{
  game_move_status = GAME_MOVE_WAIT;
  colorsPicked_i = 0;
  
  if(colorsPicked_size == GAME_COLORS_PICK_MAX){
    game_winned = 1;
    game_move_status = GAME_MOVE_WINNED;
    return;
  }
  
  size_t i;
  colorsPicked[colorsPicked_size++] = random(GAME_COLORS_MAX);
  
  for(i=0; i < colorsPicked_size; ++i){
    game_show_color(colorsPicked[i], OCTV_4, GAME_MAKE_MOVE_DELAY);
    delay(GAME_MAKE_MOVE_DELAY + 10);
    game_hide_color(colorsPicked[i]);
    delay(100);
    
    Serial.println(colorsPicked[i]);
  }
}

void game_move()
{
  size_t i;
  int butt_val;
  int color;
  
  /*
  Serial.print("colorsPicked_i: ");
  Serial.print(colorsPicked_i);
  Serial.print(" ");
  Serial.println(colorsPicked[colorsPicked_i]);
  // */
  
  if(colorsPicked_i == colorsPicked_size){
    game_move_status = GAME_MOVE_CORRECT;
    return;
  }
  
  for(i=0; i < GAME_COLORS_MAX; ++i){
    butt_val = digitalRead(butts[i]);
    color = color_from_buttPin(butts[i]);
    
    if(butt_val == HIGH){
      game_show_color(color, OCTV_4, GAME_MOVE_DELAY);
      delay(GAME_MOVE_DELAY + 10);
      game_hide_color(color);
      delay(500);
    }
    
    // /*
    if(color == colorsPicked[colorsPicked_i] 
       && butt_val == HIGH
      ){
      colorsPicked_i++;
    }
    else if(color != colorsPicked[colorsPicked_i]
            && butt_val == HIGH
           ){
      game_move_status = GAME_MOVE_WRONG;
      return;
    }
    // */
  }
}


void game_hide_color(int c)
{
  int led_pin;
  
  led_pin = ledPin_from_color(c);
  
  digitalWrite(led_pin, LOW);
  digitalWrite(PIEZO_PIN, LOW);
}

void game_show_color(int c, int octv, int ms)
{
  int led_pin, note;
  
  led_pin = ledPin_from_color(c);
  note = note_from_color(c);
  
  digitalWrite(led_pin, HIGH);
  tone(PIEZO_PIN, HZ_NOTE(note, octv), ms);
}

void game_just_hide_color(int c)
{
  int led_pin;
  
  led_pin = ledPin_from_color(c);
  digitalWrite(led_pin, LOW);
}

void game_just_show_color(int c)
{
  int led_pin;
  
  led_pin = ledPin_from_color(c);
  digitalWrite(led_pin, HIGH);
}

//
int note_from_color(int c)
{
  int note;
  switch(c){
    case COLOR_RED:
    	note = NOTE_RED;
    	break;
    
    case COLOR_GREEN:
    	note = NOTE_GREEN;
    	break;
    
    case COLOR_BLUE:
    	note = NOTE_BLUE;
    	break;
    
    case COLOR_YELLOW:
    	note = NOTE_YELLOW;
    	break;
    
    default:
    	break;
  }
  
  return note;
}

int ledPin_from_color(int c)
{
  int led_pin;
  switch(c){
    case COLOR_RED:
    	led_pin = LED_RED_PIN;
    	break;
    
    case COLOR_GREEN:
    	led_pin = LED_GREEN_PIN;
    	break;
    
    case COLOR_BLUE:
    	led_pin = LED_BLUE_PIN;
    	break;
    
    case COLOR_YELLOW:
    	led_pin = LED_YELLOW_PIN;
    	break;
    
    default:
    	break;
  }
  
  return led_pin;
}

int color_from_buttPin(int buttPin)
{
  int color;
  switch(buttPin){
    case BUTT_RED_PIN:
    	color = COLOR_RED;
    	break;
    
    case BUTT_GREEN_PIN:
    	color = COLOR_GREEN;
    	break;
    
    case BUTT_BLUE_PIN:
    	color = COLOR_BLUE;
    	break;
    
    case BUTT_YELLOW_PIN:
    	color = COLOR_YELLOW;
    	break;
    
    default:
    	break;
  }
  
  return color;
}


//
int hz_note(double note, int octave)
{
  return (note * pow(2.0, octave));
}
