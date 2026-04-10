#include<math.h>
#include<string.h>
#include<LiquidCrystal.h>

/*
 * MUSICAL NOTES
 */
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
enum{
  C_,
  D_,
  E_,
  F_,
  G_,
  A_,
  B_
};

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

#define HZ_NOTE(n, octv) hz_note(notes[n], octv)
const double notes[] = NOTES;
int hz_note(double note, int octave);

/*
 * GAME ATTRIBUTES
 */
// Colors index / ID
#define COLOR_MAX 4
enum {
  COLOR_INIT,
  COLOR_RED = COLOR_INIT,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_YELLOW,
  COLOR_END = COLOR_YELLOW
};

typedef uint8_t T_COLOR;

// Musical game notes
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
const int cNotes[] = COLORS_NOTES;

// Digital input / output
#define LED_RED_PIN 2
#define LED_GREEN_PIN 3
#define LED_BLUE_PIN 4
#define LED_YELLOW_PIN 5
#define LEDS_GAME { \
	LED_RED_PIN, \
    LED_GREEN_PIN, \
    LED_BLUE_PIN, \
    LED_YELLOW_PIN \
    }

#define BUTT_RED_PIN 8
#define BUTT_GREEN_PIN 9
#define BUTT_BLUE_PIN 10
#define BUTT_YELLOW_PIN 11
#define BUTTS_GAME { \
	BUTT_RED_PIN, \
    BUTT_GREEN_PIN, \
    BUTT_BLUE_PIN, \
    BUTT_YELLOW_PIN \
    }

const uint8_t cLeds_pin[] = LEDS_GAME;
const uint8_t cButts_pin[] = BUTTS_GAME;
uint8_t cButts_val[COLOR_MAX];

// Game Display
#define GDISPLAY_COLUMNS 16
#define GDISPLAY_LINES 2
#define RS_PIN 12
#define EN_PIN 13
#define D4_PIN A2
#define D5_PIN A3
#define D6_PIN A4
#define D7_PIN A5
LiquidCrystal gameDisplay(
  RS_PIN, EN_PIN,
  D4_PIN, D5_PIN, D6_PIN, D7_PIN
  );

// Player data struct
typedef uint8_t T_BOOL;
typedef uint8_t T_SCORE;

#define GAME_COLORS_PICK_MAX 50
#define PLAYER_NAME_MAX 10
typedef uint8_t T_HP;
typedef struct Player {
  T_HP _hp;
  
  char _name[PLAYER_NAME_MAX];
  T_COLOR _buffColors[GAME_COLORS_PICK_MAX];
  T_SCORE _score;
  size_t _buffColors_size;
  size_t _buffColors_idx;
};

T_HP Player_hp(Player*p);
T_SCORE Player_score(Player*p);
char * Player_name(Player*p);
T_COLOR Player_colorPicked(Player*p);
T_BOOL Player_colorPicked_end(Player*p);
size_t Player_colorsPicked_amt(Player*p);
T_BOOL Player_dead(Player*p);

void Player_hp_def(Player*p, T_HP hp);
void Player_hp_hit(Player*p, T_HP hit_hp);
void Player_score_def(Player*p, T_SCORE s);
void Player_score_up(Player*p);
void Player_name_def(Player*p, char*name);

void Player_colorPicked_next(Player*p);
void Player_colorPicked_prev(Player*p);
void Player_colorPicked_add(Player*p, T_COLOR c);

void Player_reset(Player*p);
void Player_reset_colorPicked_idx(Player*p);

#define CHAR_HEART 0
byte BYTE_HEART[8] {
  0b00000,
  0b01010,
  0b10101,
  0b11011,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

// Game data
// Game state
enum {
  GSTATE_PLAYING,
  GSTATE_FINISH,
  GSTATE_MENU,
  GSTATE_BOOT
};
uint8_t game_state = GSTATE_BOOT;

// Game menu
enum {
  GMENU_INIT,
  
  GMENU_PLAY = GMENU_INIT,
  GMENU_SCORE,
  GMENU_GMODE,
  
  GMENU_END = GMENU_GMODE
};
uint8_t gameMenu = GMENU_INIT;

#define GSCORES_HOLD_MAX 20
T_SCORE gameScores[GSCORES_HOLD_MAX];
size_t gameScores_i;

#define GAME_MODES 7
enum {
  GMODE_INIT,
  
  GMODE_EASY = GMODE_INIT,
  GMODE_MEDIUM,
  GMODE_HARD,
  GMODE_INFINITY,
  GMODE_MULTIPLAYER_2X,
  GMODE_MULTIPLAYER_3X,
  GMODE_MULTIPLAYER_4X,
  
  GMODE_END = GMODE_MULTIPLAYER_4X
};
uint8_t gameMode = GMODE_INIT;
#define GMODE_ROUNDS_MAX GAME_COLORS_PICK_MAX
#define GMODE_ROUNDS_EASY 10
#define GMODE_ROUNDS_MEDIUM 20
#define GMODE_ROUNDS_HARD 30
#define GMODE_ROUNDS_INFINITY GMODE_ROUNDS_MAX
#define GMODE_ROUNDS_MULTIPLAYER_2X GMODE_ROUNDS_MAX
#define GMODE_ROUNDS_MULTIPLAYER_3X GMODE_ROUNDS_MAX
#define GMODE_ROUNDS_MULTIPLAYER_4X GMODE_ROUNDS_MAX

#define GMODE_HP_EASY 3
#define GMODE_HP_MEDIUM 3
#define GMODE_HP_HARD 3
#define GMODE_HP_INFINITY 3

#define GMODE_HP_MULTIPLAYER_2X 3
#define GMODE_HP_MULTIPLAYER_3X 3
#define GMODE_HP_MULTIPLAYER_4X 3

// Game data into GSTATE_PLAYING state
enum {
  GAME_ROUND_START,
  GAME_ROUND_ENDED,
  
  GAME_ENDED,
  
  GAME_WAIT_MOVE,
  GAME_MOVE_WRONG
};
uint8_t gamePlay_status;

#define GAME_PLAYERS_MAX 4
typedef uint8_t T_PLAYER;
enum {
  PLAYER_1,
  PLAYER_2,
  PLAYER_3,
  PLAYER_4
};
#define PLAYER_1_NAME "PLAYER 1"
#define PLAYER_2_NAME "PLAYER 2"
#define PLAYER_3_NAME "PLAYER 3"
#define PLAYER_4_NAME "PLAYER 4"
#define PLAYER_UNDEFINED_NAME "PLAYER UNDF."
Player gamePlay_players[GAME_PLAYERS_MAX];
size_t gamePlay_players_i;

typedef uint8_t T_ROUND;

// Game previous data
uint8_t last_game_state = game_state;
uint8_t last_gameMenu = gameMenu;

T_BOOL swapped_game_state;
T_BOOL swapped_gameMenu;

#define GAME_STATE_MARK do { \
	swapped_game_state = last_game_state != game_state; \
    swapped_gameMenu = last_gameMenu != gameMenu; \
	\
	last_game_state = game_state; \
    last_gameMenu = gameMenu; \
} while(0);

// Game messages
#define GAME_BOOT_MSG1 "HI THERE!"
#define GAME_BOOT_MSG2 "HOW ARE YOU?"

#define GAME_MENU_PLAY_TITLE "MENU PLAY"
#define GAME_MENU_PLAY_DIALOG "TRY DEFEAT ME!"

#define GAME_MENU_SCORE_TITLE "MENU SCORE"

#define GAME_MENU_MODE_TITLE "GAME MODE"
#define GAME_MENU_MODE_OPT_EASY "EASY"
#define GAME_MENU_MODE_OPT_MEDIUM "MEDIUM"
#define GAME_MENU_MODE_OPT_HARD "HARD"
#define GAME_MENU_MODE_OPT_INFINITY "INFINITY"
#define GAME_MENU_MODE_OPT_MULTIPLAYER_2X "MULTIPLAYER 2X"
#define GAME_MENU_MODE_OPT_MULTIPLAYER_3X "MULTIPLAYER 3X"
#define GAME_MENU_MODE_OPT_MULTIPLAYER_4X "MULTIPLAYER 4X"

#define GAME_PLAY_PLAYER_SCORE_MSG "SCORE: "
#define GAME_PLAY_PLAYER_START_ROUND_MSG "ROUND STATED!"
#define GAME_PLAY_PLAYER_ENDED_ROUND_MSG "ROUND ENDED"
#define GAME_PLAY_PLAYER_WIN_GAME_MSG "YOU WIN!(*0*)"
#define GAME_PLAY_PLAYER_LOST_GAME_MSG "YOU LOST! (^-^)"

/*
 *
 * GAME FUNCTIONS
 *
 */
// Display functions
enum {
  PRINT_CENTER,
  PRINT_FORWARD,
  PRINT_BACKWARD,
  PRINT_CONTINUE,
  PRINT_,
  
  PRINT_FORCE_CENTER,
  PRINT_FORCE_FORWARD,
  PRINT_FORCE_BACKWARD,
  
  CLEAN_LINE,
  CLEAN_COLUMN,
  CLEAN_DISPLAY,
};
typedef uint8_t T_POSITION;
typedef uint8_t T_LINE;
typedef uint8_t T_COLUMN;

#define POSITION_ARG(x, y) x, y
#define POSITION(x, y) POSITION_ARG(x, y)
#define NO_POSITION POSITION_ARG(0, 0)

void gDisplay_print(
  char msg[], T_POSITION p,
  T_COLUMN c, T_LINE l
);
void gDisplay_clean(T_POSITION p, T_COLUMN c, T_LINE l);

// Boot function
void game_boot();

// Menu functions
void game_menu();
void game_show_menuPlay();
void game_show_menuScore();
void game_show_menuGmode();

void gameMenu_next();

T_SCORE gameScore();
size_t gameScore_idx();
void gameScore_next();
void gameScore_prev();
void gameScore_add(T_SCORE s);

void gameGmode_next();
void gameGmode_prev();

// Play functions
void game_play();
#define GAME_INIT_DELAY 110
#define GAME_INIT_LOOP_MAX 1
void gamePlay_init();
void gamePlay_end();

void gamePlay_player_end();
#define NOTE_ENDED_BAD HZ_NOTE(G_, OCTV_2)
#define GAME_ENDED_BAD_DELAY 1000
void gamePlay_player_ended_bad();
#define NOTE_ENDED_GOOD HZ_NOTE(A_, OCTV_4)
#define GAME_ENDED_GOOD_DELAY 2000
void gamePlay_player_ended_good();

void gamePlay_print_player();

void gamePlay_pick_color();
#define GAME_SHOW_MOVE_DELAY 510
void gamePlay_show_move();
#define GAME_MOVE_DELAY 510
void gamePlay_move();

void gamePlay_player_hit();
Player* gamePlay_player_curr();
void gamePlay_player_next();
void gamePlay_player_end();
char* gamePlay_player_name(T_PLAYER p);
void gamePlay_player_win_round();
T_BOOL gamePlay_players_live();
T_HP gamePlay_players_hp();

T_ROUND gamePlay_rounds();
size_t gamePlay_players_amt(); // Amount players into a game

T_COLOR gamePlay_colorPicked();
void gamePlay_colorPicked_next();
void gamePlay_colorPicked_prev();
size_t gamePlay_colorsPicked_amt();
  
void gamePlay_reset_round();
void gamePlay_reset_game();
T_BOOL gamePlay_ended_round();
T_BOOL gamePlay_ended_game();
T_BOOL gamePlay_winned_round();
T_BOOL gamePlay_winned_game();

// Control external devices
void game_hide_color(int color);
void game_show_color(int color, int octave);
void game_just_hide_color(int color);
void game_just_show_color(int color);

//
void setup()
{
  size_t i;
  for(i=COLOR_INIT; i <= COLOR_END; ++i){
    pinMode(cLeds_pin[i], OUTPUT);
    pinMode(cButts_pin[i], INPUT);
  }
  pinMode(PIEZO_PIN, OUTPUT);
  
  gameDisplay.begin(GDISPLAY_COLUMNS, GDISPLAY_LINES);
  gameDisplay.createChar(CHAR_HEART, BYTE_HEART);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  // /*
  switch(game_state){
    case GSTATE_BOOT:
    	game_boot();
    	break;
    
    case GSTATE_MENU:
  		game_menu();
    	break;
    
    case GSTATE_PLAYING:
    	game_play();
    	break;
    
    default:
    	break;
  }
  
  GAME_STATE_MARK
  // */
}

//
T_HP Player_hp(Player*p)
{
  return p->_hp;
}

T_SCORE Player_score(Player*p)
{
  return p->_score;
}

char* Player_name(Player*p)
{
  return p->_name;
}

T_COLOR Player_colorPicked(Player*p)
{
  return p->_buffColors[p->_buffColors_idx];
}

T_BOOL Player_colorPicked_end(Player*p)
{
  return p->_buffColors_idx >= p->_buffColors_size;
}

size_t Player_colorsPicked_amt(Player*p)
{
  return p->_buffColors_size;
}

T_BOOL Player_dead(Player*p)
{
  return !Player_hp(p);
}


void Player_hp_def(Player*p, T_HP hp)
{
  p->_hp = hp;
}

void Player_hp_hit(Player*p, T_HP hit_hp)
{
  p->_hp -= hit_hp;
}

void Player_score_def(Player*p, T_SCORE s)
{
  p->_score = s;
}

void Player_score_up(Player*p)
{
  ++p->_score;
}

void Player_name_def(Player*p, char*name)
{
  strcpy(p->_name, name);
}

void Player_colorPicked_next(Player*p)
{
  if(p->_buffColors_idx > p->_buffColors_size){
    return;
  }
  
  ++p->_buffColors_idx;
}

void Player_colorPicked_prev(Player*p)
{
  if(p->_buffColors_idx == 0){
    return;
  }
  
  --p->_buffColors_idx;
}

void Player_colorPicked_add(Player*p, T_COLOR color)
{
  if(p->_buffColors_size >= GAME_COLORS_PICK_MAX){
    return;
  }
  
  p->_buffColors[p->_buffColors_size++] = color;
}


void Player_reset(Player*p)
{
  p->_buffColors_size =
    p->_buffColors_idx = 
    p->_score = 0;
  
  p->_hp = 1;
}

void Player_reset_colorPicked_idx(Player*p)
{
  p->_buffColors_idx = 0;
}

//
void gDisplay_print(
  char msg[], T_POSITION p,
  T_COLUMN c, T_LINE l
)
{
  T_COLUMN column;
  T_LINE line;
  int8_t i;
  
  switch(p){
    case PRINT_CENTER:
    case PRINT_FORCE_CENTER:
    	column = (strlen(msg) / 2 >= c)? 0:
          (strlen(msg) / 2 + c > GDISPLAY_COLUMNS && p != PRINT_FORCE_CENTER)?
            GDISPLAY_COLUMNS - strlen(msg): c - strlen(msg) / 2
            ;
    	line = l;
    
    	gameDisplay.setCursor(column, line);
    	gameDisplay.print(
          (!column)?msg + strlen(msg) / 2 - c: msg
        );
    	break;
    
    case PRINT_FORWARD:
    case PRINT_FORCE_FORWARD:
    	column = (strlen(msg) + c > GDISPLAY_COLUMNS && p != PRINT_FORCE_FORWARD)?
          GDISPLAY_COLUMNS - strlen(msg): c;
    	line = l;
    
    	gameDisplay.setCursor(column, line);
    	gameDisplay.print(msg);
    	break;
    
    case PRINT_BACKWARD:
    case PRINT_FORCE_BACKWARD:
    	column = (strlen(msg) >= c)?
          0: c - strlen(msg)
            ;
    	line = l;
    
    	gameDisplay.setCursor(column, line);
    	gameDisplay.print(
          (!column)?msg + strlen(msg) + c: msg
        );
    	break;
    
    case PRINT_CONTINUE:
    case PRINT_:
    	gameDisplay.print(msg);
    	break;
    
    default:
    	break;
  }
}

void gDisplay_clean(T_POSITION p, T_COLUMN c, T_LINE l)
{
  T_COLUMN column;
  T_LINE line;
  int8_t i;
  
  switch(p){
    case CLEAN_LINE:
    	column = c;
    	line = l;
    
    	gameDisplay.setCursor(column, line);
    	for(i=0; i < GDISPLAY_COLUMNS; ++i){
          gameDisplay.print(" ");
        }
    	break;
    
    case CLEAN_DISPLAY:
    	gameDisplay.clear();
    	break;
    
    default:
    	break;
  }
}

//
void game_boot()
{
  gDisplay_clean(CLEAN_DISPLAY, 0, 0);
  
  game_state = GSTATE_MENU;
  
  uint8_t i;
  // HI THERE!
  for(i=0; i < 2; ++i){
    gDisplay_print(GAME_BOOT_MSG1, PRINT_CENTER, POSITION(8, 0));
  	delay(500);
    gDisplay_clean(CLEAN_LINE, POSITION(0, 0));
    delay(500);
  }
  gDisplay_print(GAME_BOOT_MSG1, PRINT_CENTER, POSITION(8, 0));
  delay(500);
  
  // HOW ARE YOU?
  char msg2[] = GAME_BOOT_MSG2;
  for(i=0; i < strlen(GAME_BOOT_MSG2); ++i){
    msg2[i] = GAME_BOOT_MSG2[i];
    msg2[i+1] = '\0';
    
    gDisplay_print(
      msg2,
      PRINT_CENTER
      , POSITION(8, 1)
    );
	delay(200);
    gDisplay_clean(CLEAN_LINE, POSITION(0, 1));
    delay(100);
  }
  gDisplay_print(GAME_BOOT_MSG2, PRINT_CENTER, POSITION(8, 1));
  delay(2000);
  gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  delay(500);
}


void game_menu()
{
  if(swapped_game_state){
    gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  }
  
  /*
  BUTTONS FUNCTIONS
  -----------------
  GMENU_PLAY
  =================
  COLOR_RED -> Start Game
  COLOR_GREEN -> Switch menu mode
  COLOR_BLUE -> Start Game
  COLOR_YELLOW -> Start Game
  
  GMENU_SCORE
  =================
  COLOR_RED -> Nothing
  COLOR_GREEN -> Switch menu mode
  COLOR_BLUE -> See next max score
  COLOR_YELLOW -> See next max score
  
  GMENU_GMODE
  ==================
  COLOR_RED -> Nothing
  COLOR_GREEN -> Switch menu
  COLOR_BLUE -> Set next game mode
  COLOR_YELLOW -> Set previous game mode
  */
  size_t i;
  for(i=COLOR_INIT; i <= COLOR_END; ++i){
    cButts_val[i] = digitalRead(cButts_pin[i]);
  }
  
  switch(gameMenu){
    case GMENU_PLAY:
    	if(swapped_game_state || swapped_gameMenu){
    		game_show_menuPlay();
        }
    
    	if(cButts_val[COLOR_RED] == HIGH
           || cButts_val[COLOR_BLUE] == HIGH
           || cButts_val[COLOR_YELLOW] == HIGH
          ){
          gamePlay_init();
        }
    	else if(cButts_val[COLOR_GREEN] == HIGH){
			gameMenu_next();
        }
      		
    	break;
    
    case GMENU_SCORE:
    	if(swapped_game_state || swapped_gameMenu){
    		game_show_menuScore();
        }
    
    	if(cButts_val[COLOR_RED] == HIGH){
        }
    	else if(cButts_val[COLOR_GREEN] == HIGH){
          gameMenu_next();
        }
    	else if(cButts_val[COLOR_BLUE] == HIGH){
          gameScore_next();
          game_show_menuScore();
        }
    	else if(cButts_val[COLOR_YELLOW] == HIGH){
          gameScore_prev();
          game_show_menuScore();
        }
    	break;
    
    case GMENU_GMODE:
    	if(swapped_game_state || swapped_gameMenu){
    		game_show_menuGmode();
        }
    
    	if(cButts_val[COLOR_RED] == HIGH){
        }
    	else if(cButts_val[COLOR_GREEN] == HIGH){
          gameMenu_next();
        }
    	else if(cButts_val[COLOR_BLUE] == HIGH){
          gameGmode_prev();
          game_show_menuGmode();
        }
    	else if(cButts_val[COLOR_YELLOW] == HIGH){
          gameGmode_next();
          game_show_menuGmode();
        }
    	break;
    
    default:
    	break;
  }
  
  delay(100);
}

// Menu functions
void game_show_menuPlay()
{
  gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  gDisplay_print(
    GAME_MENU_PLAY_TITLE,
    PRINT_CENTER,
    POSITION(8, 0)
    );
  
  gDisplay_print(
    GAME_MENU_PLAY_DIALOG,
    PRINT_CENTER,
    POSITION(8, 1)
    );
}

void game_show_menuScore()
{ 
  gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  char idx[5], score[5];
  sprintf(idx, "%i", gameScore_idx());
  sprintf(score, "%i", gameScore());
  
  gDisplay_print(
    GAME_MENU_SCORE_TITLE,
    PRINT_CENTER,
    POSITION(8, 0)
    );
  
  gDisplay_print(
    "#",
    PRINT_FORWARD,
    POSITION(0, 1)
    );
  gDisplay_print(
    idx,
    PRINT_,
    NO_POSITION
    );
  gDisplay_print(
    ": ",
    PRINT_,
    NO_POSITION
    );
  
  gDisplay_print(
    score,
    PRINT_,
    NO_POSITION
    );
}

void game_show_menuGmode()
{
  gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  
  gDisplay_print(
    GAME_MENU_MODE_TITLE,
    PRINT_CENTER,
    POSITION(8, 0)
    );
  
  char msg[20];
  switch(gameMode){
    case GMODE_EASY:
    	strcpy(msg, GAME_MENU_MODE_OPT_EASY);
    	break;
    
    case GMODE_MEDIUM:
    	strcpy(msg, GAME_MENU_MODE_OPT_MEDIUM);
    	break;
    
    case GMODE_HARD:
    	strcpy(msg, GAME_MENU_MODE_OPT_HARD);
    	break;
    
    case GMODE_INFINITY:
    	strcpy(msg, GAME_MENU_MODE_OPT_INFINITY);
    	break;
    
    case GMODE_MULTIPLAYER_2X:
    	strcpy(msg, GAME_MENU_MODE_OPT_MULTIPLAYER_2X);
    	break;
    
    case GMODE_MULTIPLAYER_3X:
    	strcpy(msg, GAME_MENU_MODE_OPT_MULTIPLAYER_3X);
    	break;
    
    case GMODE_MULTIPLAYER_4X:
    	strcpy(msg, GAME_MENU_MODE_OPT_MULTIPLAYER_4X);
    	break;
    
    default:
    	break;
  }
  
  gDisplay_print(
    msg, PRINT_CENTER,
    POSITION(8, 1)
    );
}

void gameMenu_next()
{
  gameMenu = (gameMenu == GMENU_END)?
    GMENU_INIT: gameMenu + 1;
}


T_SCORE gameScore()
{
  return gameScores[gameScores_i];
}

size_t gameScore_idx()
{
  return gameScores_i + 1;
}

void gameScore_next()
{
  gameScores_i = (gameScores_i > 0)?
    gameScores_i - 1: GSCORES_HOLD_MAX - 1;
}

void gameScore_prev()
{
  gameScores_i = (gameScores_i + 1) % GSCORES_HOLD_MAX;
}

void gameScore_add(T_SCORE s)
{
  T_SCORE t;
  size_t i;
  
  for(i=0; i < GSCORES_HOLD_MAX; ++i){
    if(gameScores[i] < s){
      break;
    }
  }
  
  t = s;
  for(; i < GSCORES_HOLD_MAX; ++i){
    gameScores[i] += t;
    t = gameScores[i] - t;
    gameScores[i] -= t;
  }
} 


void gameGmode_next()
{
  gameMode = (gameMode == GMODE_END)?
    GMODE_INIT: gameMode + 1;
}

void gameGmode_prev()
{
  gameMode = (gameMode > 0)?
    gameMode - 1: GMODE_END;
}


// Play functions
void game_play()
{
  // /*
  if(!gamePlay_players_live()){
    gamePlay_end();
    return;
  }
  // */

  switch(gamePlay_status){
    case GAME_ROUND_START:
    	gamePlay_print_player();
    	delay(1000);
    
    	gamePlay_pick_color();
    	gamePlay_show_move();
    
    	gamePlay_print_player();
    	break; 
    
    case GAME_WAIT_MOVE:
    	gamePlay_move();
    	delay(10);
    	break;
    
    case GAME_MOVE_WRONG:
    	gamePlay_player_hit();
    
    	gamePlay_print_player();
  		gamePlay_status = GAME_WAIT_MOVE;
    	delay(1000);
    	gamePlay_print_player();
    
    	break;
    
    default:
    	break;
  }
  
  // /*
  if(gamePlay_ended_game()){
    gamePlay_status = GAME_ENDED;
    gamePlay_print_player();
    gamePlay_player_end();
    
    gamePlay_player_next();
  }
  else if(gamePlay_ended_round()
         && gamePlay_status != GAME_MOVE_WRONG
         ){
  	gamePlay_player_next();
    gamePlay_reset_round();
  }
  // */
}

void gamePlay_init()
{
  int i, j;
  
  // /*
  for(j=0; j < GAME_INIT_LOOP_MAX; ++j){
  	for(i=COLOR_INIT; i <= COLOR_END; ++i){
    	game_show_color(i, OCTV_5);
    	delay(GAME_INIT_DELAY);
    	game_hide_color(i);
  	}
    
    for(i=COLOR_END; i >= COLOR_INIT; --i){
    	game_show_color(i, OCTV_5);
    	delay(GAME_INIT_DELAY);
    	game_hide_color(i);
  	}
  }
  
  gamePlay_status = GAME_ROUND_START;
  game_state = GSTATE_PLAYING;
  gamePlay_reset_game();
  delay(500);
  // */
}

void gamePlay_end()
{
  size_t i;
  char score[10];
 
  gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  gDisplay_print(
    "PLAYERS SCORES",
    PRINT_CENTER,
    POSITION(8, 0)
    );
  delay(3000);
  gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  
  for(i=PLAYER_1; i < gamePlay_players_amt(); ++i){
    sprintf(score, "%03u", Player_score(&gamePlay_players[i]));
    
    gDisplay_print(
      Player_name(&gamePlay_players[i]),
      PRINT_FORWARD,
      POSITION(0, 0)
    );
    
    gDisplay_print(
      "SCORE: ",
      PRINT_FORWARD,
      POSITION(0, 1)
      );
    gDisplay_print(
      score,
      PRINT_,
      NO_POSITION
      );
    
    gameScore_add(
      Player_score(&gamePlay_players[i])
    );
    
    delay(1700);
  }
  
  gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  gDisplay_print(
    "CONGRATULATIONS!",
    PRINT_CENTER,
    POSITION(8, 0)
    );
  delay(2000);
  
  game_state = GSTATE_MENU;
}

void gamePlay_player_end()
{
  if(Player_dead(gamePlay_player_curr())){
    gamePlay_player_ended_bad();
  }
  else{
    gamePlay_player_ended_good();
  }

  Player_hp_def(gamePlay_player_curr(), 0);
  gamePlay_status = GAME_ROUND_START;
  
  delay(1000);
}


void gamePlay_player_ended_bad()
{
  tone(PIEZO_PIN, NOTE_ENDED_BAD);
  delay(GAME_ENDED_BAD_DELAY);
  noTone(PIEZO_PIN);
}

void gamePlay_player_ended_good()
{
  int i, d;
  
  d = 0;
  // tone(PIEZO_PIN, NOTE_ENDED_GOOD, GAME_ENDED_GOOD_DELAY);
  while(d < GAME_ENDED_GOOD_DELAY){
  	for(i=COLOR_RED; i <= COLOR_YELLOW; ++i){
    	game_show_color(i, OCTV_4);
      	delay(100);
      	game_hide_color(i);
    
    	d += 100;
    }
  }
}

void gamePlay_print_player()
{ 
  char hp[10], score[10];
  sprintf(hp, "%02u", Player_hp(gamePlay_player_curr()));
  sprintf(score, "%03u",Player_score(gamePlay_player_curr()));
  
  gDisplay_clean(CLEAN_DISPLAY, NO_POSITION);
  gDisplay_print(
    Player_name(gamePlay_player_curr()),
    PRINT_FORWARD,
    POSITION(0, 0)
    );
  gDisplay_print(
    hp,
    PRINT_FORWARD,
    POSITION(13, 0)
    );
  gameDisplay.write(byte(CHAR_HEART));
  
  switch(gamePlay_status){
    case GAME_WAIT_MOVE:
    	gDisplay_print(
          GAME_PLAY_PLAYER_SCORE_MSG,
          PRINT_FORWARD,
          POSITION(0, 1)
    	);
    	gDisplay_print(
          score,
          PRINT_,
          NO_POSITION
          );
          
    	break;
    
    case GAME_ROUND_START:
    	gDisplay_print(
          GAME_PLAY_PLAYER_START_ROUND_MSG,
          PRINT_FORWARD,
          POSITION(0, 1)
          );
    	break;
    
    case GAME_ROUND_ENDED:
    	gDisplay_print(
          GAME_PLAY_PLAYER_ENDED_ROUND_MSG,
          PRINT_FORWARD,
          POSITION(0, 1)
          );
    	break;
    
    case GAME_MOVE_WRONG:
    	gDisplay_print(
          "YOU MISS! >:D",
          PRINT_FORWARD,
          POSITION(0, 1)
          );
    	break;
    
    case GAME_ENDED:
    	if(Player_dead(gamePlay_player_curr())){
          gDisplay_print(
            GAME_PLAY_PLAYER_LOST_GAME_MSG,
            PRINT_FORWARD,
            POSITION(0, 1)
            );
        }
    	else {
          gDisplay_print(
            GAME_PLAY_PLAYER_WIN_GAME_MSG,
            PRINT_FORWARD,
            POSITION(0, 1)
            );
        }
    	break;
    
    default:
    	break;
  }       
}

  
void gamePlay_pick_color()
{
  Player_colorPicked_add(
    gamePlay_player_curr(),
    random(COLOR_INIT, COLOR_END + 1)
    );
}

void gamePlay_show_move()
{
  gamePlay_status = GAME_WAIT_MOVE;
  
  if(gamePlay_ended_game()){
    return;
  }
  
  //
  T_COLOR c;
  size_t i;
  for(i=0; i < gamePlay_colorsPicked_amt(); ++i){
    c = gamePlay_colorPicked();
    game_show_color(c, OCTV_4);
    delay(GAME_SHOW_MOVE_DELAY);
    game_hide_color(c);
    delay(200);
    
    // Serial.println(gamePlay_colorsPicked_amt());
    gamePlay_colorPicked_next();
  }
  
  for(i=0; i < gamePlay_colorsPicked_amt(); ++i){
    gamePlay_colorPicked_prev();
  }
}

void gamePlay_move()
{
  T_COLOR c;
  T_COLOR colorPicked;
  
  /*
  Serial.println(
    (gamePlay_player_curr())->_buffColors_idx
    );
  Serial.println(
    (gamePlay_player_curr())->_buffColors_size
    );
  // */
  
  if(gamePlay_ended_round()){
    return;
  } 
  
  colorPicked = gamePlay_colorPicked();
  for(c=COLOR_INIT; c <= COLOR_END; ++c){
    cButts_val[c] = digitalRead(cButts_pin[c]);
    
    if(cButts_val[c] == HIGH){
      game_show_color(c, OCTV_4);
      delay(GAME_MOVE_DELAY);
      game_hide_color(c);
      delay(100);
    }
    
    
    if(c == colorPicked && cButts_val[c] == HIGH){
      gamePlay_colorPicked_next();
      return;
    }
    else if(c != colorPicked && cButts_val[c] == HIGH){
      gamePlay_status = GAME_MOVE_WRONG;
      return;
    }
  }
}


void gamePlay_player_hit()
{
  Player_hp_hit(gamePlay_player_curr(), 1);
}

Player* gamePlay_player_curr()
{
  Player *p;
  p = &gamePlay_players[gamePlay_players_i];
  
  return p;
}

void gamePlay_player_next()
{
  Player p;
  T_PLAYER i;
  
  i = gamePlay_players_i;
  do {
  	i = (i + 1) % gamePlay_players_amt();
  	p = gamePlay_players[i];
    
    if(i == gamePlay_players_i){
      return;
    }
  } while(Player_dead(&p));
  
  gamePlay_players_i = i;
}

void gamePlay_player_win_round()
{
  Player_score_up(
    gamePlay_player_curr()
    );
}

char* gamePlay_player_name(T_PLAYER p)
{
  switch(p){
    case PLAYER_1:
    	return PLAYER_1_NAME;
    	break;
    
    case PLAYER_2:
    	return PLAYER_2_NAME;
    	break;
    
    case PLAYER_3:
    	return PLAYER_3_NAME;
    	break;
    
    case PLAYER_4:
    	return PLAYER_4_NAME;
    	break;
    
    default:
    	return PLAYER_UNDEFINED_NAME;
    	break;
  }
}

T_BOOL gamePlay_players_live()
{
  T_PLAYER i;
  for(i=PLAYER_1; i <= PLAYER_4; ++i){
    if(!Player_dead(&gamePlay_players[i])){
       return 1;
    }
  }
  
  return 0;
}

T_HP gamePlay_players_hp()
{
  switch(gameMode){
    case GMODE_EASY:
    	return GMODE_HP_EASY;
    	break;
    
    case GMODE_MEDIUM:
    	return GMODE_HP_MEDIUM;
    	break;
    
    case GMODE_HARD:
    	return GMODE_HP_HARD;
    	break;
    
    case GMODE_INFINITY:
    	return GMODE_HP_INFINITY;
    	break;
    
    case GMODE_MULTIPLAYER_2X:
    	return GMODE_HP_MULTIPLAYER_2X;
    	break;
    
    case GMODE_MULTIPLAYER_3X:
    	return GMODE_HP_MULTIPLAYER_3X;
    	break;
    
    case GMODE_MULTIPLAYER_4X:
    	return GMODE_HP_MULTIPLAYER_4X;
    	break;
    
    default:
    	return 1;
    	break;
  }
}



T_COLOR gamePlay_colorPicked()
{
  return Player_colorPicked(gamePlay_player_curr());
}

void gamePlay_colorPicked_next()
{
  Player_colorPicked_next(gamePlay_player_curr());
}

void gamePlay_colorPicked_prev()
{
  Player_colorPicked_prev(gamePlay_player_curr());
}

size_t gamePlay_colorsPicked_amt()
{
  return Player_colorsPicked_amt(gamePlay_player_curr());
}


T_ROUND gamePlay_rounds()
{
  switch(gameMode){
    case GMODE_EASY:
    	return GMODE_ROUNDS_EASY;
    	break;
    
    case GMODE_MEDIUM:
    	return GMODE_ROUNDS_MEDIUM;
    	break;
    
    case GMODE_HARD:
    	return GMODE_ROUNDS_HARD;
    	break;
    
    case GMODE_INFINITY:
    	return GMODE_ROUNDS_INFINITY;
    	break;
    
    case GMODE_MULTIPLAYER_2X:
    	return GMODE_ROUNDS_MULTIPLAYER_2X;
    	break;
    
    case GMODE_MULTIPLAYER_3X:
    	return GMODE_ROUNDS_MULTIPLAYER_3X;
    	break;
    
    case GMODE_MULTIPLAYER_4X:
    	return GMODE_ROUNDS_MULTIPLAYER_4X;
    	break;
    
    default:
    	return 0;
    	break;
  }
}

size_t gamePlay_players_amt()
{
  switch(gameMode){
    case GMODE_EASY:
      	return 1;
      	break;

    case GMODE_MEDIUM:
     	return 1;
      	break;

    case GMODE_HARD:
      	return 1;
      	break;

    case GMODE_INFINITY:
      	return 1;
      	break;

    case GMODE_MULTIPLAYER_2X:
      	return 2;
      	break;
    
    case GMODE_MULTIPLAYER_3X:
    	return 3;
    	break;
    
    case GMODE_MULTIPLAYER_4X:
    	return 4;
    	break;

    default:
      	break;
  }
}

void gamePlay_reset_round()
{
  Player_reset_colorPicked_idx(gamePlay_player_curr());
  if(gamePlay_status != GAME_MOVE_WRONG){
  	gamePlay_status = GAME_ROUND_START;
    gamePlay_player_win_round();
  }
}

void gamePlay_reset_game()
{
  T_PLAYER i;
  for(i=PLAYER_1; i < gamePlay_players_amt(); ++i){
    Player_reset(&gamePlay_players[i]);
    Player_name_def(
      &gamePlay_players[i],
      gamePlay_player_name(i)
    );
    Player_hp_def(
      &gamePlay_players[i],
      gamePlay_players_hp()
      );
  }
  gamePlay_players_i = 0;
}

T_BOOL gamePlay_ended_round()
{
  return gamePlay_winned_round() ||
    gamePlay_status == GAME_MOVE_WRONG;
}

T_BOOL gamePlay_ended_game()
{
  return gamePlay_winned_game() ||
    Player_dead(gamePlay_player_curr());
}

T_BOOL gamePlay_winned_round()
{
  return Player_colorPicked_end(gamePlay_player_curr());
}

T_BOOL gamePlay_winned_game()
{
  return gamePlay_colorsPicked_amt() > gamePlay_rounds();
}

//
void game_hide_color(int c)
{
  digitalWrite(cLeds_pin[c], LOW);
  noTone(PIEZO_PIN);
}

void game_show_color(int c, int octv)
{ 
  digitalWrite(cLeds_pin[c], HIGH);
  tone(PIEZO_PIN, HZ_NOTE(cNotes[c], octv));
}

void game_just_hide_color(int c)
{
  digitalWrite(cLeds_pin[c], LOW);
}

void game_just_show_color(int c)
{
  digitalWrite(cLeds_pin[c], HIGH);
}

//
int color_from_pin(int pin)
{
  int color;
  switch(pin){
    case BUTT_RED_PIN:
    case LED_RED_PIN:
    	color = COLOR_RED;
    	break;
    
    case BUTT_GREEN_PIN:
    case LED_GREEN_PIN:
    	color = COLOR_GREEN;
    	break;
    
    case BUTT_BLUE_PIN:
    case LED_BLUE_PIN:
    	color = COLOR_BLUE;
    	break;
    
    case BUTT_YELLOW_PIN:
    case LED_YELLOW_PIN:
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
