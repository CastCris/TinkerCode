#include<LiquidCrystal.h>
#include<avr/pgmspace.h>

/*
 * Led Matrix struct
 */
#define LMATRIX_LINES_MAX 10
#define LMATRIX_COLMS_MAX 10

typedef uint8_t T_LINE_PIN;
typedef uint8_t T_COLM_PIN;
typedef uint8_t T_LINE;
typedef uint8_t T_COLM;

typedef uint32_t T_FIGURE;
typedef uint8_t T_BOOL;

typedef uint32_t T_TIME_DELAY;


typedef struct {
  T_LINE_PIN _lines_pin[LMATRIX_LINES_MAX];
  T_COLM_PIN _colms_pin[LMATRIX_COLMS_MAX];
  
  T_LINE _lines_amt;
  T_COLM _colms_amt;

  T_TIME_DELAY _draw_last_time;
  size_t _draw_figure_i;
  T_BOOL _drawed_figure;
} LMatrix;

// getters
T_LINE_PIN LMatrix_line_pin(
  LMatrix*lm,
  T_LINE line
  );
T_COLM_PIN LMatrix_colm_pin(
  LMatrix*lm,
  T_COLM colm
  );

T_LINE LMatrix_lines_amt(LMatrix*lm);
T_COLM LMatrix_colms_amt(LMatrix*lm);

// Properties for LMatrix_draw
T_TIME_DELAY LMatrix_draw_last_time(LMatrix*lm);
size_t LMatrix_draw_figure_i(LMatrix*lm);
T_BOOL LMatrix_drawed_figure(LMatrix*lm);

// setters
void LMatrix_line_pin_def(
  LMatrix*lm,
  T_LINE_PIN line_pin,
  T_LINE line
  );
void LMatrix_colm_pin_def(
  LMatrix*lm,
  T_COLM_PIN colm_pin,
  T_COLM colm
  );


void LMatrix_lines_def(
  LMatrix*lm,
  const T_LINE_PIN lines_pin[],
  const T_LINE lines_amt
  );
void LMatrix_colms_def(
  LMatrix*lm,
  const T_COLM_PIN colms_pin[],
  const T_COLM colms_amt
  );

void LMatrix_draw_last_time_def(
    LMatrix*lm,
    T_TIME_DELAY t
    );

// methods
void LMatrix_reset(LMatrix*lm);
void LMatrix_setup(LMatrix*lm);
void LMatrix_led_up(
  LMatrix*lm,
  const T_COLM x,
  const T_LINE y
  );
void LMatrix_led_down(
  LMatrix*lm,
  const T_COLM x,
  const T_LINE y
  );

// #define LMATRIX_DRAW_DELAY 25
void LMatrix_draw(
  LMatrix*lm,
  const T_FIGURE figure[],
  T_TIME_DELAY time_delay
  );

/*
 * GAME 
 *
 */
// Direction
#define DIRECTIONS_COUNT 4
enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT,
  
  DIRECTION_INVALID
};
Direction Direction_opossed(Direction d);
Direction Direction_next_clockwise(Direction d);
Direction Direction_next_counterclockwise(Direction d);

// Snake Piece
typedef struct {
  T_COLM _x;
  T_LINE _y;
  Direction _d;
} SnakePiece;
SnakePiece* SnakePiece_create(T_COLM x, T_LINE y, Direction d);
SnakePiece* SnakePiece_clone(const SnakePiece*sp);

T_COLM SnakePiece_x(const SnakePiece*sp);
T_LINE SnakePiece_y(const SnakePiece*sp);
Direction SnakePiece_direction(const SnakePiece*sp);

void SnakePiece_x_def(SnakePiece*sp, const T_COLM x);
void SnakePiece_y_def(SnakePiece*sp, const T_LINE y);
void SnakePiece_direction_def(SnakePiece*sp, Direction d);

T_BOOL SnakePiece_equal(const SnakePiece*a, const SnakePiece*b);
T_BOOL SnakePiece_forward(SnakePiece*sp);
T_BOOL SnakePiece_backward(SnakePiece*sp);

void SnakePiece_turn_clockwise(SnakePiece*sp);
void SnakePiece_turn_counterclockwise(SnakePiece*sp);


// Snake
typedef uint16_t T_SNAKE_SIZE;

#define SNAKE_TABLE_COLMS 6
#define SNAKE_TABLE_LINES 4
#define SNAKE_SIZE_MAX SNAKE_TABLE_COLMS * SNAKE_TABLE_LINES
typedef struct {
  SnakePiece _body[SNAKE_SIZE_MAX];
  T_SNAKE_SIZE _size;

  // Attribute for Snake_move_forward_with_delay
  T_TIME_DELAY _move_last_time;
} Snake;

T_SNAKE_SIZE Snake_size(const Snake*s);
SnakePiece* Snake_piece(Snake*s, const T_SNAKE_SIZE idx);

SnakePiece* Snake_piece_search(Snake*s, T_COLM x, T_LINE y);
#define SNAKE_INIT_X 0
#define SNAKE_INIT_Y 0
#define SNAKE_INIT_DIRECTION UP
void Snake_reset(Snake*s);
void Snake_increase(Snake*s);
void Snake_decrease(Snake*s);

T_BOOL Snake_move_forward(Snake*s);
T_BOOL Snake_move_forward_with_delay(
    Snake*s,
    T_TIME_DELAY time_delay
    );

void Snake_turn_clockwise(Snake*s);
void Snake_turn_counterclockwise(Snake*s);

#define CHAR_EMPTY_TILE '.'
#define CHAR_SNAKE_BODY '#'
#define CHAR_DIRECTION_UP 'U'
#define CHAR_DIRECTION_RIGHT 'R'
#define CHAR_DIRECTION_DOWN 'D'
#define CHAR_DIRECTION_LEFT 'L'
#define CHAR_DIRECTION_UNKNOW '?'
void Snake_print_cli(Snake*s);
void Snake_print_direction_cli(Snake*s);
void Snake_print_LMatrix(
    Snake*s,
    LMatrix*lm,
    T_TIME_DELAY time_delay
    );

void Snake_LMatrix_figure(
    Snake*s,
    T_FIGURE figure[]
    );

// Snake food
typedef struct{
  T_COLM _x;
  T_LINE _y;
} Food;

// Food getters
T_COLM Food_x(Food*f);
T_LINE Food_y(Food*f);

// Food setters
void Food_x_def(Food*f, T_COLM x);
void Food_y_def(Food*f, T_LINE y);

// Food methods
void Food_generate(Food*f, Snake*s);
void Food_LMatrix_figure(
    Food*f,
    T_FIGURE figure[]
    );
T_BOOL Food_Snake_catch(Food*f, Snake*s);

// Game
// game input
void gameInput_read();

// game state
enum GState{
  GSTATE_BOOTING,
  GSTATE_MENU,
  GSTATE_PLAYING
};
GState gstate = GSTATE_BOOTING;
GState gstate_last = GSTATE_BOOTING;
#define gstate_swapped (gstate != gstate_last)
void gstate_update();
void gstate_action();

// game main functions
#define GAME_BOOT_DELAY 8000
void game_boot();
#define GAME_MENU_DELAY 100
void game_menu();
#define GAME_PLAY_DELAY 500
void game_play();

// game menu
enum GMenu{
  __GMENU_INIT,

  GMENU_PLAY,
  GMENU_SCORE,
  GMENU_LEVEL,
  
  __GMENU_END,
};
#define GMENU_INIT ((GMenu)(__GMENU_INIT + 1))
#define GMENU_END ((GMenu)(__GMENU_END - 1))
GMenu gmenu = GMENU_INIT;
GMenu gmenu_last = GMENU_INIT;
#define gmenu_swapped (gmenu != gmenu_last)
void gmenu_next();
void gmenu_update();

void gmenu_play();
void gmenu_score();
void gmenu_level();

// game level
enum GLevel {
  __GLEVEL_INIT,

  GLEVEL_CLASSIC,

  __GLEVEL_END ,
};
#define GLEVEL_INIT ((GLevel)(__GLEVEL_INIT + 1))
#define GLEVEL_END ((GLevel)(__GLEVEL_END - 1))
GLevel glevel = GLEVEL_INIT;
void glevel_next();
char* glevel_name();

typedef uint8_t T_HP;
#define GLEVEL_CLASSIC_HP 1
T_HP glevel_hp();

// game score
typedef uint8_t T_SCORE;
#define GSCORE_MAX 20
T_SCORE gscore[GSCORE_MAX];
size_t gscore_idx;

void gscore_next();
size_t gscore_i();
void gscore_i_reset();
T_SCORE gscore_curr();
void gscore_add(T_SCORE s);

// Snake input handle time
#define snake_can_turn \
  (millis() - snake_turned_last_time >= GAME_PLAY_DELAY)
T_TIME_DELAY snake_turned_last_time;

// Game play functions
T_HP gplay_hp;
T_SCORE gplay_score;

void gplay_init();
void gplay_end();
void gplay_update();
enum {
  CHAR_ARROW_UP,
  CHAR_ARROW_DOWN,
  CHAR_ARROW_RIGHT,
  CHAR_ARROW_LEFT
};
Direction printed_last_snake_direction;
T_SCORE printed_last_gplay_score;
void gplay_print_infos();

void gplay_classic();

void gplay_ended_bad();
void gplay_ended_good();


/*
 * Display functions
 */
// print function
enum VALUE_TYPE {
  VALUE_TYPE_INT,
  VALUE_TYPE_CHAR,
  VALUE_TYPE_FLOAT,
  VALUE_TYPE_STRING,
  VALUE_TYPE_CUSTOM_CHAR,
};

enum PRINT_ORIENTATION {
  CENTER,
  FORWARD,
  BACKWARD,
};

#define PRINTF_INT(a, f, o) \
  a, 0, 0, 0, 0, VALUE_TYPE_INT, f, o

#define PRINTF_CHAR(a, f, o) \
  0, a, 0, 0, 0, VALUE_TYPE_CHAR, f, o

#define PRINTF_FLOAT(a, f, o) \
  0, 0, a, 0, 0, VALUE_TYPE_FLOAT, f, o

#define PRINTF_STRING(a, f, o) \
  0, 0, 0, a, 0, VALUE_TYPE_STRING, f, o

#define PRINTF_CUSTOM_CHAR(a, f, o) \
  0, 0, 0, 0, a, VALUE_TYPE_CUSTOM_CHAR, f, o

#define PRINT_INT(a, o) PRINTF_INT(a, "%i", o)
#define PRINT_CHAR(a, o) PRINTF_CHAR(a, "%c", o)
#define PRINT_FLOAT(a, o) PRINTF_CHAR(a, "%f", o)
#define PRINT_STRING(a, o) PRINTF_STRING(a, "%s", o)
#define PRINT_CUSTOM_CHAR(a, o) PRINTF_CUSTOM_CHAR(a, "", o)

#define POSITION(x, y) 1, x, y
#define NO_POSITION 0, 0, 0


#define PRINT_VALUE_SIZE_MAX 20

typedef int8_t T_CURSOR_X;
typedef int8_t T_CURSOR_Y;

T_CURSOR_X cursor_x;
T_CURSOR_Y cursor_y;

#define GDISPLAY_COLMS 16
#define GDISPLAY_LINES 2
#define GDISPLAY_CENTER_X (GDISPLAY_COLMS / 2)
#define GDISPLAY_CENTER_Y (GDISPLAY_LINES / 2)
void gDisplay_print(
  int print_val_int,
  char print_val_char,
  float print_val_float,
  char print_val_string[],
  uint8_t print_val_customChar,
  
  VALUE_TYPE value_type,
  char format[],
  PRINT_ORIENTATION print_order,
  
  T_BOOL passed_position,
  int8_t x,
  int8_t y
  );

// clean function
enum CleanOrientation {
  __CLEAN_LINE,
  __CLEAN_COLM,
  __CLEAN_FORWARD,
  __CLEAN_BACKWARD,

  __CLEAN_DISPLAY
};

#define CLEAN_LINE(y) __CLEAN_LINE, POSITION(0, y)
#define CLEAN_COLM(x) __CLEAN_COLM, POSITION(x, 0)
#define CLEAN_FORWARD(x, y) __CLEAN_FORWARD, POSITION(x, y)
#define CLEAN_BACKWARD(x, y) __CLEAN_BACKWARD, POSITION(x, y)

#define CLEAN_DISPLAY __CLEAN_DISPLAY, NO_POSITION

void gDisplay_clean(
    CleanOrientation c,

    T_BOOL passed_position,
    T_CURSOR_X x,
    T_CURSOR_Y y
    );

// Custom Characters
void gDisplay_create_char(
    byte c[],
    uint8_t c_id
    );

/*
 * Animation
 */
// Sprite date type
#define SPRITE_RAW_LINES 8
#define SPRITE_CHAR_SLOTS_MAX 8
typedef struct{
  byte _raw[SPRITE_RAW_LINES];
  T_CURSOR_X _x;
  T_CURSOR_Y _y;
} Sprite;

byte* Sprite_raw(Sprite*s);
T_CURSOR_X Sprite_x(Sprite*s);
T_CURSOR_Y Sprite_y(Sprite*s);

void Sprite_raw_def(Sprite*s, byte*raw);
void Sprite_x_def(Sprite*s, T_CURSOR_X x);
void Sprite_y_def(Sprite*s, T_CURSOR_Y y);

void Sprite_copy(Sprite*to, Sprite*from);
void Sprite_print(Sprite*s, uint8_t char_slot);

// Animation data type
#define ANIMATIONLCD_SPRITE_MAX 8
typedef struct{
  Sprite _sprites[ANIMATIONLCD_SPRITE_MAX];
  size_t _sprites_amt;
} AnimationLCD;

size_t AnimationLCD_sprites_amt(
    AnimationLCD*a
    );

void AnimationLCD_sprites_def(
    AnimationLCD*a,
    Sprite sprites[],
    size_t sprites_amt
    );
void AnimationLCD_print(
    AnimationLCD*a,
    T_TIME_DELAY time_delay
    );

/*
 * Global variables
 */
#define BUTT_RIGHT_PIN 13
uint8_t buttRight_val;
#define BUTT_LEFT_PIN 12
uint8_t buttLeft_val;


#define RS_PIN A0
#define EN_PIN A1
#define D4_PIN A2
#define D5_PIN A3
#define D6_PIN A4
#define D7_PIN A5
LiquidCrystal gameDisplay(
  RS_PIN, EN_PIN,
  D4_PIN, D5_PIN, D6_PIN, D7_PIN
  );

#define LINES_AMT 4
#define LINE_1_PIN 11
#define LINE_2_PIN 10
#define LINE_3_PIN 9
#define LINE_4_PIN 8

#define COLMS_AMT 6
#define COLM_1_PIN 7
#define COLM_2_PIN 6
#define COLM_3_PIN 5
#define COLM_4_PIN 4
#define COLM_5_PIN 3
#define COLM_6_PIN 2
LMatrix lm;
const T_LINE_PIN lines_pin[] = {
  LINE_1_PIN,
  LINE_2_PIN,
  LINE_3_PIN,
  LINE_4_PIN
};
const T_COLM_PIN colms_pin[] = {
  COLM_1_PIN,
  COLM_2_PIN,
  COLM_3_PIN,
  COLM_4_PIN,
  COLM_5_PIN,
  COLM_6_PIN
};

/*
T_FIGURE circle[] = {
  0b011110,
  0b101101,
  0b101101,
  0b011110
};
// */

Snake snake;
Food snake_food;

T_BOOL snake_catch_food;
T_BOOL snake_hit_wall;

/*
PROGMEM Sprite bootAnimation_sprites[] = 
{
  {
    {
        0b00000,
        0b00000,
        0b01000,
        0b11111,
        0b11100,
        0b10000,
        0b00000,
        0b00000
    },
    2, 1
  },

  {
    {
        0b00000,
        0b00000,
        0b00100,
        0b11111,
        0b11111,
        0b11011,
        0b00000,
        0b00000
    },
    1, 1
  },

  {
    {
        0b01110,
        0b01110,
        0b01110,
        0b01111,
        0b00111,
        0b00011,
        0b00000,
        0b00000
    },
    0, 1
  },

  {
    {
        0b00111,
        0b01110,
        0b11100,
        0b11100,
        0b01110,
        0b01110,
        0b00111,
        0b00111
    },
    0, 0
  },

  {
    {
        0b01110,
        0b00111,
        0b00111,
        0b00111,
        0b01110,
        0b01110,
        0b01110,
        0b01110
    },
    15, 0
  },

  {
    {
        0b01110,
        0b00111,
        0b00111,
        0b11111,
        0b11110,
        0b11000,
        0b00000,
        0b00000
    },
    15, 1
  },

  {
    {
        0b00000,
        0b00000,
        0b00011,
        0b10110,
        0b01100,
        0b10011,
        0b00000,
        0b00000
    },
    14, 1
  },

  {
    {
        0b00000,
        0b00000,
        0b00011,
        0b00110,
        0b00100,
        0b00011,
        0b00000,
        0b00000
    },
    14, 1
  }
};
// */
AnimationLCD game_boot_animation = {
{
  {
    {
        0b00000,
        0b00000,
        0b01000,
        0b11111,
        0b11100,
        0b10000,
        0b00000,
        0b00000
    },
    2, 1
  },

  {
    {
        0b00000,
        0b00000,
        0b00100,
        0b11111,
        0b11111,
        0b11011,
        0b00000,
        0b00000
    },
    1, 1
  },

  {
    {
        0b01110,
        0b01110,
        0b01110,
        0b01111,
        0b00111,
        0b00011,
        0b00000,
        0b00000
    },
    0, 1
  },

  {
    {
        0b00111,
        0b01110,
        0b11100,
        0b11100,
        0b01110,
        0b01110,
        0b00111,
        0b00111
    },
    0, 0
  },

  {
    {
        0b01110,
        0b00111,
        0b00111,
        0b00111,
        0b01110,
        0b01110,
        0b01110,
        0b01110
    },
    15, 0
  },

  {
    {
        0b01110,
        0b00111,
        0b00111,
        0b11111,
        0b11110,
        0b11000,
        0b00000,
        0b00000
    },
    15, 1
  },

  {
    {
        0b00000,
        0b00000,
        0b00011,
        0b10110,
        0b01100,
        0b10011,
        0b00000,
        0b00000
    },
    14, 1
  },

  {
    {
        0b00000,
        0b00000,
        0b00011,
        0b00110,
        0b00100,
        0b00011,
        0b00000,
        0b00000
    },
    14, 1
  }
}
, 8
}
;

//
void setup()
{
  // /*
  pinMode(BUTT_RIGHT_PIN, INPUT);
  pinMode(BUTT_LEFT_PIN, INPUT);
  gameDisplay.begin(16, 2);
  Serial.begin(9600);
  
  LMatrix_lines_def(&lm, lines_pin, LINES_AMT);
  LMatrix_colms_def(&lm, colms_pin, COLMS_AMT);
  LMatrix_setup(&lm);

  Snake_reset(&snake);

  /*
  gameDisplay.setCursor(0, 0);
  gameDisplay.print(F("HELLO!"));
  
  Snake_reset(&snake);
  int i;
  for(i=0; i < 14; ++i){
    Snake_increase(&snake);
    Snake_print_cli(&snake);
    Serial.println();
    delay(500);
  }
  Snake_print_cli(&snake);
  Snake_print_direction_cli(&snake);
  Serial.println();
  
  // /*
  for(i=0; i < 1; ++i){
    Snake_move_forward(&snake);
  
    Snake_print_direction_cli(&snake);
    Serial.println();
    delay(500);
  }

  T_FIGURE snake_figure[SNAKE_TABLE_LINES];
  Snake_LMatrix_figure(&snake, snake_figure);

  for(i=0; i < LINES_AMT; ++i){
    Serial.println(snake_figure[i], 2);
  }

  Food_generate(&snake_food, &snake);

  Serial.print(Food_x(&snake_food));
  Serial.print(", ");
  Serial.println(Food_y(&snake_food));

  // */
    
   /*
  gDisplay_print(PRINT_STRING("1234567890", CENTER), POSITION(-5, 0));
  Serial.println(cursor_x);
  
  delay(1000);  
  gDisplay_print(PRINT_STRING(" JJJ", FORWARD), NO_POSITION);
  Serial.println(cursor_x);
  
  delay(1000);  
  gDisplay_print(PRINT_STRING(" XXX", FORWARD), NO_POSITION);
  Serial.println(cursor_x);
  
  delay(1000);  
  gDisplay_print(PRINT_STRING("AAA", BACKWARD), NO_POSITION);
  Serial.println(cursor_x);
  
  delay(1000);  
  gDisplay_print(PRINT_STRING("CCC", CENTER), POSITION(8, 1));
  Serial.println(cursor_x);
  
  delay(1000);
  gDisplay_print(PRINT_STRING("1234", FORWARD), NO_POSITION);
  
  delay(1000);
  gDisplay_clean(CLEAN_COLM(7));
  
  delay(1000);
  gDisplay_clean(CLEAN_FORWARD(5, 0));
  
  delay(1000);
  gDisplay_clean(CLEAN_LINE(1));
  
  delay(1000);
  byte smile[] = {
    0b00000,
    0b01010,
    0b01010,
    0b00000,
    0b10001,
    0b01110,
    0b00000,
    0b00000,
  }
  
  gDisplay_create_char(smile, 0);
  gDisplay_print(PRINT_STRING("SMILE: ", FORWARD), POSITION(0, 1));
  gDisplay_print(PRINT_CUSTOM_CHAR(0, FORWARD), NO_POSITION);
  
  delay(1000);
  gDisplay_clean(CLEAN_DISPLAY);
  // */ 


  // Animation test
  /*
  Serial.println(sizeof(AnimationLCD));
  while(1){
    AnimationLCD_print(
        &game_boot_animation,
        200
        );
  }

  // */
}

void loop()
{
  gstate_action();

  /*
  T_FIGURE f_snake[SNAKE_TABLE_LINES];
  T_FIGURE f_food[SNAKE_TABLE_LINES];

  Snake_LMatrix_figure(
      &snake,
      f_snake
      );
  Food_LMatrix_figure(
      &snake_food,
      f_food
      );

  size_t i;
  for(i=0; i < SNAKE_TABLE_LINES; ++i){
    f_snake[i] += f_food[i];
  }

  LMatrix_draw(&lm, f_snake, 25);
  // */

  /*
  T_FIGURE smile[] = {
    0b010000,
    0b010100,
    0b100010,
    0b011100,
  };
  LMatrix_draw(
      &lm,
      smile,
      25
      );
      // */
  /*
  Snake_print_LMatrix(&snake, &lm, 25);
  Snake_move_forward_with_delay(&snake, 500);
  // */
}

/*
 * LMatrix
 */
T_LINE_PIN LMatrix_line_pin(
  LMatrix*lm,
  T_LINE line
  )
{
  return lm->_lines_pin[line];
}

T_COLM_PIN LMatrix_colm_pin(
  LMatrix*lm,
  T_COLM colm
  )
{
  return lm->_colms_pin[colm];
}


T_LINE LMatrix_lines_amt(LMatrix*lm)
{
  return lm->_lines_amt;
}

T_COLM LMatrix_colms_amt(LMatrix*lm)
{
  return lm->_colms_amt;
}

T_TIME_DELAY LMatrix_draw_last_time(LMatrix*lm)
{
  return lm->_draw_last_time;
}

size_t LMatrix_draw_figure_i(LMatrix*lm)
{
  return lm->_draw_figure_i;
}

T_BOOL LMatrix_drawed_figure(LMatrix*lm)
{
  return lm->_drawed_figure;
}


//
void LMatrix_line_pin_def(
  LMatrix*lm,
  T_LINE_PIN line_pin,
  T_LINE line
  )
{
  lm->_lines_pin[line] = line_pin;
}

void LMatrix_colm_pin_def(
  LMatrix*lm,
  T_COLM_PIN colm_pin,
  T_COLM colm
  )
{
  lm->_colms_pin[colm] = colm_pin;
}


void LMatrix_lines_def(
  LMatrix*lm,
  const T_LINE_PIN lines_pin[],
  const T_LINE lines_amt
  )
{
  T_LINE i;
  lm->_lines_amt = 0;
  
  for(i=0; i < lines_amt && i < LMATRIX_LINES_MAX; ++i){
    LMatrix_line_pin_def(lm, lines_pin[i], i);
    ++lm->_lines_amt;
  }
}

void LMatrix_colms_def(
  LMatrix*lm,
  const T_COLM_PIN colms_pin[],
  const T_COLM colms_amt
  )
{
  T_COLM i;
  lm->_colms_amt = 0;
  
  for(i=0; i < colms_amt && i < LMATRIX_COLMS_MAX; ++i){
    LMatrix_colm_pin_def(lm, colms_pin[i], i);
    ++lm->_colms_amt;
  }
}

void LMatrix_draw_last_time_def(LMatrix*lm, T_TIME_DELAY t)
{
  lm->_draw_last_time = t;
}

void LMatrix_drawed_figure_def(LMatrix*lm, T_BOOL b)
{
  lm->_drawed_figure = b;
}

//
void LMatrix_reset(LMatrix*lm)
{
  T_LINE l;
  T_COLM c;
  
  for(l=0; l < LMatrix_lines_amt(lm); ++l){
    digitalWrite(LMatrix_line_pin(lm, l), LOW);
  }
  for(c=0; c < LMatrix_colms_amt(lm); ++c){
    digitalWrite(LMatrix_colm_pin(lm, c), HIGH);
  }
}

void LMatrix_setup(LMatrix*lm)
{
  T_LINE l;
  T_COLM c;
  
  for(l=0; l < LMatrix_lines_amt(lm); ++l){
    pinMode(LMatrix_line_pin(lm, l), OUTPUT);
  }
  
  for(c=0; c < LMatrix_colms_amt(lm); ++c){
    pinMode(LMatrix_colm_pin(lm, c), OUTPUT);
  }
  
  LMatrix_draw_last_time_def(lm, 0);
  LMatrix_reset(lm);
}


void LMatrix_led_up(
  LMatrix*lm,
  const T_COLM x,
  const T_LINE y
  )
{
  digitalWrite(
    LMatrix_colm_pin(lm, x),
    LOW
    );
  digitalWrite(
    LMatrix_line_pin(lm, y),
    HIGH
    );
}

void LMatrix_led_down(
  LMatrix*lm,
  const T_COLM x,
  const T_LINE y
  )
{ 
  digitalWrite(
    LMatrix_colm_pin(lm, x),
    HIGH
    );
  digitalWrite(
    LMatrix_line_pin(lm, y),
    LOW
    );
}

void LMatrix_draw(
  LMatrix*lm,
  const T_FIGURE figure[],
  T_TIME_DELAY time_delay
  )
{
  T_LINE l;
  T_COLM c;
  T_COLM colms_amt;
  
  /*
   * A row of the figure is set by a binary address.
   * By bitwise ( figure[y] >> x ) & 1 
   * we can find out if the position x,y must be light.
   *
   * However, just make >> column mirror the image.
   * So, for fix it, we do >> ( LMatrix_colms_amt(lm) - c - 1).
   */
  colms_amt = LMatrix_colms_amt(lm) - 1;
  for(l=0; l < LMatrix_lines_amt(lm); ++l){
    if(l != LMatrix_draw_figure_i(lm)){
      continue;
    }

    for(c=0;
        c < LMatrix_colms_amt(lm) && !LMatrix_drawed_figure(lm); ++c){
      if(!((figure[l] >> (colms_amt - c)) & 1)){
        continue;
      }
      LMatrix_led_up(lm, c, l);
    }
    LMatrix_drawed_figure_def(lm, 1);

    if(millis() - LMatrix_draw_last_time(lm) < time_delay){
      continue;
    }
    LMatrix_reset(lm);
    LMatrix_draw_last_time_def(lm, millis());
    LMatrix_drawed_figure_def(lm, 0);
    ++lm->_draw_figure_i;
    break;
  }

  lm->_draw_figure_i %= LMatrix_lines_amt(lm);
}

// Direction
Direction Direction_opossed(Direction d)
{
  switch(d){
    case UP:
      return DOWN;
      break;
    
    case RIGHT:
      return LEFT;
      break;
    
    case DOWN:
      return UP;
      break;
    
    case LEFT:
      return RIGHT;
      break;
    
    default:
      return DIRECTION_INVALID;
      break;
  }
}

Direction Direction_next_clockwise(Direction d)
{
  switch(d){
    case UP:
      return RIGHT;
      break;
    
    case RIGHT:
      return DOWN;
      break;
    
    case DOWN:
      return LEFT;
      break;
    
  case LEFT:
      return UP;
      break;
    
    default:
      return DIRECTION_INVALID;
      break;
  }
}

Direction Direction_next_counterclockwise(Direction d)
{
  switch(d){
    case UP:
      return LEFT;
      break;
    
    case RIGHT:
      return UP;
      break;
    
    case DOWN:
      return RIGHT;
      break;
    
    case LEFT:
      return DOWN;
      break;
    
    default:
      return DIRECTION_INVALID;
      break;
  }
}
// */
    
// SnakePiece
// Constructors
SnakePiece* SnakePiece_create(T_COLM x, T_LINE y, Direction d)
{
  SnakePiece *sp = (SnakePiece*)malloc(sizeof(SnakePiece));
  SnakePiece_x_def(sp, x);
  SnakePiece_y_def(sp, y);
  SnakePiece_direction_def(sp, d);
  
  return sp;
}
// /*
SnakePiece* SnakePiece_clone(const SnakePiece*sp)
{
  return SnakePiece_create(
    SnakePiece_x(sp),
    SnakePiece_y(sp),
    SnakePiece_direction(sp)
    );
}
// */

// Properties
T_COLM SnakePiece_x(const SnakePiece*sp)
{
  return sp->_x;
}

T_LINE SnakePiece_y(const SnakePiece*sp)
{
  return sp->_y;
}

Direction SnakePiece_direction(const SnakePiece*sp)
{
  return sp->_d;
}

// Setters
void SnakePiece_x_def(SnakePiece*sp, const T_COLM x)
{
  sp->_x = x;
}

void SnakePiece_y_def(SnakePiece*sp, const T_LINE y)
{
  sp->_y = y;
}

void SnakePiece_direction_def(SnakePiece*sp, Direction d)
{
  sp->_d = d;
}

// Methods
T_BOOL SnakePiece_equal(const SnakePiece*a, const SnakePiece*b)
{
  return SnakePiece_x(a) == SnakePiece_x(b)
    && SnakePiece_y(a) == SnakePiece_y(b)
    ;
}

T_BOOL SnakePiece_forward(SnakePiece*sp)
{
  switch(SnakePiece_direction(sp)){
    case UP:
      if(SnakePiece_y(sp) >= SNAKE_TABLE_LINES - 1){
          break;
        }
      ++sp->_y;
      return 1;
    
    case RIGHT:
      if(SnakePiece_x(sp) >= SNAKE_TABLE_COLMS - 1){
          break;
        }
        ++sp->_x;
      return 1;
    
    case DOWN:
      if(SnakePiece_y(sp) == 0){
          break;
        }
    --sp->_y;
      return 1;
    
    case LEFT:
      if(SnakePiece_x(sp) == 0){
          break;
        }
        --sp->_x;
      return 1;

    default:
      break;
  }
  return 0;
}

T_BOOL SnakePiece_backward(SnakePiece*sp)
{
  switch(SnakePiece_direction(sp)){
    case UP:
      if(SnakePiece_y(sp) == 0){
          break;
        }
    --sp->_y;
        return 1;
    
    case RIGHT:
      if(SnakePiece_x(sp) == 0){
          break;
        }
         --sp->_x;
      return 1;
    
    case DOWN:
      if(SnakePiece_y(sp) >= SNAKE_TABLE_LINES - 1){
          break;
        }
        ++sp->_y;
        return 1;
    
    case LEFT:
      if(SnakePiece_x(sp) >= SNAKE_TABLE_COLMS - 1){
          break;
        }
        ++sp->_x;
        return 1;
  }
  
  return 0;
}


void SnakePiece_turn_clockwise(SnakePiece*sp)
{
  SnakePiece_direction_def(
    sp, 
  Direction_next_clockwise(SnakePiece_direction(sp))
    );
}

void SnakePiece_turn_counterclockwise(SnakePiece*sp)
{
  SnakePiece_direction_def(
    sp,
    Direction_next_counterclockwise(SnakePiece_direction(sp))
    );
}

// Snake
// Properties
T_SNAKE_SIZE Snake_size(const Snake*s)
{
  return s->_size;
}

SnakePiece* Snake_piece(Snake*s, const T_SNAKE_SIZE idx)
{
  return &(s->_body[idx]);
}

// Methods
SnakePiece* Snake_piece_search(Snake*s, T_COLM x, T_LINE y)
{
  T_SNAKE_SIZE i;
  SnakePiece *sp;
  
  for(i=0; i < Snake_size(s); ++i){
    sp = Snake_piece(s, i);
    
    if(SnakePiece_x(sp) == x
       && SnakePiece_y(sp) == y
      ){
      return sp;
    }
  }
  
  return NULL;
}

  

void Snake_reset(Snake*s)
{
  s->_size = 1;
  SnakePiece_x_def(Snake_piece(s, 0), SNAKE_INIT_X);
  SnakePiece_y_def(Snake_piece(s, 0), SNAKE_INIT_Y);
  
  SnakePiece_direction_def(
    Snake_piece(s, 0),
    SNAKE_INIT_DIRECTION
  );  

  s->_move_last_time = 0;
}

void Snake_increase(Snake*s)
{
  if(Snake_size(s) >= SNAKE_SIZE_MAX){
    return;
  }
  
  SnakePiece pieces_next[DIRECTIONS_COUNT] = {0};
  uint8_t pieces_next_en[DIRECTIONS_COUNT] = {0};
  
  SnakePiece *sp, *tail, *t, *piece_new;
  uint8_t free_pieces;
  
  sp = Snake_piece(s, Snake_size(s) - 1);
  tail = Snake_piece(s, Snake_size(s));
  piece_new = NULL;
  free_pieces = 0;
  
  /*
   * Get potentional next pieces positions
   */
  // Up
  if(SnakePiece_y(sp) + 1 < SNAKE_TABLE_LINES){
    t = &(pieces_next[UP]);
    pieces_next_en[UP] = 1;
    // Serial.println("UP!");
    
    SnakePiece_x_def(t, SnakePiece_x(sp));
    SnakePiece_y_def(t, SnakePiece_y(sp) + 1);
    // SnakePiece_direction_def(t, UP);
    SnakePiece_direction_def(t, DOWN);
    ++free_pieces;
  }
  
  // Right
  if(SnakePiece_x(sp) + 1 < SNAKE_TABLE_COLMS){
    t = &(pieces_next[RIGHT]);
    pieces_next_en[RIGHT] = 1;
    // Serial.println("RIGHT!");
    
    SnakePiece_x_def(t, SnakePiece_x(sp) + 1);
    SnakePiece_y_def(t, SnakePiece_y(sp));
    // SnakePiece_direction_def(t, RIGHT);
    SnakePiece_direction_def(t, LEFT);
    ++free_pieces;
  }
  
  // Down
  if(SnakePiece_y(sp) != 0){
    t = &(pieces_next[DOWN]);
    pieces_next_en[DOWN] = 1;
    // Serial.println("DOWN!");
    
    SnakePiece_x_def(t, SnakePiece_x(sp));
    SnakePiece_y_def(t, SnakePiece_y(sp) - 1);
    // SnakePiece_direction_def(t, DOWN);
    SnakePiece_direction_def(t, UP);
    ++free_pieces;
  }
  
  // Left
  if(SnakePiece_x(sp) != 0){
    t = &(pieces_next[LEFT]);
    pieces_next_en[LEFT] = 1;
    // Serial.println("LEFT!");
    
    SnakePiece_x_def(t, SnakePiece_x(sp) - 1);
    SnakePiece_y_def(t, SnakePiece_y(sp));
    // SnakePiece_direction_def(t, LEFT);
    SnakePiece_direction_def(t, RIGHT);
    ++free_pieces;
  }
  
  /*
   * Check if some of positions( up, right, dow, left)
   * are already used by Snake's body
   */
  T_SNAKE_SIZE i;
  size_t j;
  for(i=0; i < Snake_size(s) && free_pieces; ++i){
    t = Snake_piece(s, i);
    for(j=0; j < DIRECTIONS_COUNT; ++j){
      if(
        pieces_next_en[j]
         && SnakePiece_equal(&(pieces_next[j]), t)
      ){
        pieces_next_en[j] = 0;
        --free_pieces;
      }
    }
  }
  
  /*
   * If the Snake's size is one, is necessary check if
   * the next piece position is ahead of the head
  */
  Direction head_direction;
  head_direction = SnakePiece_direction(Snake_piece(s, 0));
  
  for(j=0; j < DIRECTIONS_COUNT && Snake_size(s) == 1; ++j){
    if(pieces_next_en[j] && j == head_direction){
      pieces_next_en[j] = 0;
      --free_pieces;
    }
  }
  
  
  //
  if(!free_pieces){
    return;
  }
  
  switch(SnakePiece_direction(sp)){
    case DOWN:
      if(pieces_next_en[UP]){
          piece_new = &pieces_next[UP];
        }
      break;
    
    case LEFT:
      if(pieces_next_en[RIGHT]){
          piece_new = &pieces_next[RIGHT];
        }
      break;
    
    case UP:
      if(pieces_next_en[DOWN]){
          piece_new = &pieces_next[DOWN];
        }
      break;
    
    case RIGHT:
      if(pieces_next_en[LEFT]){
          piece_new = &pieces_next[LEFT];
        }
      break;
    
    default:
      break;
  }
  
  for(j=0; j < DIRECTIONS_COUNT && piece_new == NULL; ++j){
    if(pieces_next_en[j] == 0)
      continue;
    
    piece_new = &pieces_next[j];
  }
  
  //
  SnakePiece_x_def(tail, SnakePiece_x(piece_new));
  SnakePiece_y_def(tail, SnakePiece_y(piece_new));
  SnakePiece_direction_def(tail, SnakePiece_direction(piece_new));
  
  ++s->_size;
}

void Snake_decrease(Snake*s)
{
  if(Snake_size(s) == 0){
    return;
  }
  
  --s->_size;
}



T_BOOL Snake_move_forward(Snake*s)
{
  SnakePiece *t, *r;
  T_LINE head_x;
  T_COLM head_y;
  
  // Firstly, we check if Snake's head can move
  t = Snake_piece(s, 0);
  if(!SnakePiece_forward(t)){
    return 0;
  }
  head_x = SnakePiece_x(t);
  head_y = SnakePiece_y(t);
  SnakePiece_backward(t);
  /*
  Serial.print(head_x);
  Serial.print(", ");
  Serial.println(head_y);
  // */
  
  if(Snake_piece_search(s, head_x, head_y)){
    return 0;
  }
  SnakePiece_forward(t);
  
  // After it, we just move the remain Snake's piece one unit
  T_SNAKE_SIZE i;
  for(i=1; i < Snake_size(s); ++i){
    t = Snake_piece(s, i);
    SnakePiece_forward(t);
  }
  
  // /*
  
  for(i=Snake_size(s) - 1; i > 0; --i){
    t = Snake_piece(s, i);
     r = Snake_piece(s, i - 1);
    
    SnakePiece_direction_def(t, SnakePiece_direction(r));
  }
  // */
  return 1;
}

T_BOOL Snake_move_forward_with_delay(
    Snake*s,
    T_TIME_DELAY time_delay
    )
{
  if(millis() - s->_move_last_time < time_delay){
    return 1;
  }

  s->_move_last_time = millis();
  return Snake_move_forward(s);
}


void Snake_turn_clockwise(Snake*s)
{
  SnakePiece_turn_clockwise(Snake_piece(s, 0));
}

void Snake_turn_counterclockwise(Snake*s)
{
  SnakePiece_turn_counterclockwise(Snake_piece(s, 0));
}


void Snake_print_cli(Snake*s)
{
  T_COLM x;
  T_LINE y;
  
  for(y=0; y < SNAKE_TABLE_LINES ; ++y){
    for(x=0; x < SNAKE_TABLE_COLMS; ++x){
      if(Snake_piece_search(s, x, SNAKE_TABLE_LINES - y  -1 ) != NULL){
        Serial.print(CHAR_SNAKE_BODY);
        continue;
      }
      
      Serial.print(CHAR_EMPTY_TILE);
    }
    Serial.println();
  }
}

void Snake_print_direction_cli(Snake*s)
{
  T_COLM x;
  T_LINE y;
  SnakePiece *t;
  
  for(y=0; y < SNAKE_TABLE_LINES; ++y){
    for(x=0; x < SNAKE_TABLE_COLMS; ++x){
      if((t = Snake_piece_search(s, x, SNAKE_TABLE_LINES - y - 1)) == NULL){
        Serial.print(CHAR_EMPTY_TILE);
        continue;
      }
      
      switch(SnakePiece_direction(t)){
        case UP:
          Serial.print(CHAR_DIRECTION_UP);
          break;
        
        case RIGHT:
      Serial.print(CHAR_DIRECTION_RIGHT);
          break;
        
        case DOWN:
          Serial.print(CHAR_DIRECTION_DOWN);
          break;
        
        case LEFT:
          Serial.print(CHAR_DIRECTION_LEFT);
          break;
        
        default:
          Serial.print(CHAR_DIRECTION_UNKNOW);
          break;
      }
    }
    Serial.println();
  }
}

void Snake_print_LMatrix(
    Snake*s,
    LMatrix*lm,
    T_TIME_DELAY time_delay
    )
{
  T_FIGURE figure_snake[SNAKE_TABLE_LINES];
  Snake_LMatrix_figure(s, figure_snake);

  LMatrix_draw(lm, figure_snake, time_delay);
}

void Snake_LMatrix_figure(
    Snake*s,
    T_FIGURE figure[]
    )
{
  SnakePiece* sp;
  T_SNAKE_SIZE i;

  for(i=0; i < SNAKE_TABLE_LINES; ++i){
    figure[i] = 0;
  }

  for(i=0; i < Snake_size(s); ++i){
    sp = Snake_piece(s, i);
    figure[SnakePiece_y(sp)] |= (1 << SnakePiece_x(sp));
  }

  /*
  // Reverse each column
  T_FIGURE t;
  for(i=0; i < SNAKE_TABLE_LINES; ++i){
    t = figure[i];
    figure[i] = 0;

    while(t){
      figure[i] = ((figure[i] << 1) + (t & 1));
      t >>= 1;
    }
  }

  // Reverse the lines
  /*
  T_SNAKE_SIZE idx;
  for(i=0; i < SNAKE_TABLE_LINES / 2; ++i){
    idx = SNAKE_TABLE_LINES - i - 1;

    figure[i] += figure[idx];
    figure[idx] = figure[i] - figure[idx];
    figure[i] -= figure[idx];
  }
  // */
}

// Food
T_COLM Food_x(Food*f)
{
  return f->_x;
}

T_LINE Food_y(Food*f)
{
  return f->_y;
}


void Food_x_def(Food*f, T_COLM x)
{
  f->_x = x;
}

void Food_y_def(Food*f, T_LINE y)
{
  f->_y = y;
}


void Food_generate(Food*f, Snake*s)
{
  uint16_t free_positions[SNAKE_TABLE_LINES * SNAKE_TABLE_COLMS] = {0};
  size_t free_positions_size = 0;

  T_LINE i;
  T_COLM j;
  for(i=0; i < SNAKE_TABLE_LINES; ++i){
    for(j=0; j < SNAKE_TABLE_COLMS; ++j){
      if(Snake_piece_search(s, j, i) != NULL){
        continue;
      }

      free_positions[free_positions_size++] =
        i * SNAKE_TABLE_COLMS + j;
    }
  }

  size_t idx;
  long seed;

  seed = micros() ^ analogRead(A0) ^ millis();
  Serial.println(seed);
  
  randomSeed(seed);
  idx = random(free_positions_size);

  Food_x_def(f, free_positions[idx] % SNAKE_TABLE_COLMS);
  Food_y_def(f, free_positions[idx] / SNAKE_TABLE_COLMS);
}

void Food_LMatrix_figure(
    Food*f,
    T_FIGURE figure[]
    )
{
  size_t i;
  for(i=0; i < SNAKE_TABLE_LINES; ++i){
    figure[i] = 0;
  }

  figure[Food_y(f)] = 1 << Food_x(f);
}


T_BOOL Food_Snake_catch(Food*f, Snake*s)
{
  return 
    Food_x(f) == SnakePiece_x(Snake_piece(s, 0))
    && Food_y(f) == SnakePiece_y(Snake_piece(s, 0));
}


// Game functions
// game input
void gameInput_read()
{
  buttRight_val = digitalRead(BUTT_RIGHT_PIN);
  buttLeft_val = digitalRead(BUTT_LEFT_PIN);
}


//game state
void gstate_action()
{

  switch(gstate){
    case GSTATE_BOOTING:
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

  gstate_update();
}

void gstate_update()
{
  gstate_last = gstate;
  switch(gstate){
    case GSTATE_BOOTING:
      gstate = GSTATE_MENU;
      break;

    case GSTATE_MENU:
      if(
          gmenu == GMENU_PLAY
          && buttRight_val == HIGH
          ){
        gstate = GSTATE_PLAYING;
      }
      break;

    case GSTATE_PLAYING:
      if(!gplay_hp
          || Snake_size(&snake) == SNAKE_SIZE_MAX){
        gstate = GSTATE_MENU;
      }
      break;

    default:
      break;
  }
}

// game menu
void gmenu_next()
{
  if(gmenu == GMENU_END){
    gmenu = GMENU_INIT;
    return;
  }

  // For some reason, Tinkercad forbiden the expression
  // ++gmenu because of gmenu's data type (0_0)
  gmenu = (GMenu)(gmenu + 1);
}

// game score
void gscore_next()
{
  gscore_idx = (gscore_idx + 1) % GSCORE_MAX;
}

size_t gscore_i()
{
  return gscore_idx;
}

void gscore_i_reset()
{
  gscore_idx = 0;
}

T_SCORE gscore_curr()
{
  return gscore[gscore_idx];
}

void gscore_add(T_SCORE s)
{
  size_t i;
  T_SCORE t;

  i = 0;
  while(gscore[i++] >= s && i < GSCORE_MAX);
  --i;

  t = s;
  do{
    gscore[i] += t;
    t = gscore[i] - t;
    gscore[i] -= t;
  }while((++i) < GSCORE_MAX);
}


// game play
void gplay_init()
{
  snake_catch_food = 0;
  snake_hit_wall = 0;

  Snake_reset(&snake);
  gplay_hp = glevel_hp();
  gplay_score = 0;
}

void gplay_end()
{
  LMatrix_reset(&lm);
  gscore_add(gplay_score);
  
  if(Snake_size(&snake) == SNAKE_SIZE_MAX){
    gplay_ended_good();
  }
  else{
    gplay_ended_bad();
  }
}

void gplay_update()
{
  if(!gplay_hp || Snake_size(&snake) == SNAKE_SIZE_MAX){
    gplay_end();
  }
}

void gplay_print_infos()
{
  if(gplay_score == printed_last_gplay_score
      && SnakePiece_direction(Snake_piece(&snake, 0)) == printed_last_snake_direction){
    return;
  }

  byte arrow_up[] = {
      0b00100,
      0b01110,
      0b11111,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b00000
  };
  byte arrow_down[] = {
      0b00000,
      0b00100,
      0b00100,
      0b00100,
      0b00100,
      0b11111,
      0b01110,
      0b00100
  };
  byte arrow_right[] = {
      0b00000,
      0b00000,
      0b00100,
      0b00110,
      0b11111,
      0b00110,
      0b00100,
      0b00000
  };
  byte arrow_left[] = {
      0b00000,
      0b00000,
      0b00100,
      0b01100,
      0b11111,
      0b01100,
      0b00100,
      0b00000
  };

  gDisplay_create_char(arrow_up, CHAR_ARROW_UP);
  gDisplay_create_char(arrow_down, CHAR_ARROW_DOWN);
  gDisplay_create_char(arrow_right, CHAR_ARROW_RIGHT);
  gDisplay_create_char(arrow_left, CHAR_ARROW_LEFT);

  //
  gDisplay_clean(CLEAN_DISPLAY);

  /*
   * Prints the current snake direction,
   * the direction if snake turn counterclockwise
   * and the direction if snake turn clockwise
   */
  gDisplay_print(
      PRINT_STRING("SNAKE COURSE:", FORWARD),
      POSITION(0, 0)
      );

  // Because of snake was been in verted displayed
  // we have invert the arrows directions
  uint8_t arrow_next_counterclockwise,
          arrow_curr,
          arrow_next_clockwise;

  switch(SnakePiece_direction(Snake_piece(&snake, 0))){
    case UP:
      arrow_curr = CHAR_ARROW_DOWN;
      arrow_next_counterclockwise = CHAR_ARROW_RIGHT;
      arrow_next_clockwise = CHAR_ARROW_LEFT;
      break;

    case RIGHT:
      arrow_curr = CHAR_ARROW_LEFT;
      arrow_next_counterclockwise = CHAR_ARROW_DOWN;
      arrow_next_clockwise = CHAR_ARROW_UP;
      break;

    case DOWN:
      arrow_curr = CHAR_ARROW_UP;
      arrow_next_counterclockwise = CHAR_ARROW_LEFT;
      arrow_next_clockwise = CHAR_ARROW_RIGHT;
      break;

    case LEFT:
      arrow_curr = CHAR_ARROW_RIGHT;
      arrow_next_counterclockwise = CHAR_ARROW_UP;
      arrow_next_clockwise = CHAR_ARROW_DOWN;
      break;

    default:
      break;
  }

  gDisplay_print(
      PRINT_CUSTOM_CHAR(arrow_curr, FORWARD),
      NO_POSITION
      );

  gDisplay_print(
      PRINT_CUSTOM_CHAR(arrow_next_counterclockwise, FORWARD),
      NO_POSITION
      );
  gDisplay_print(
      PRINT_CUSTOM_CHAR(arrow_next_clockwise, FORWARD),
      NO_POSITION
      );


  // Displays the current player score
  gDisplay_print(
      PRINT_STRING("SCORE: ", FORWARD),
      POSITION(0, 1)
      );
  gDisplay_print(
      PRINTF_INT(gplay_score, "%02u", FORWARD),
      NO_POSITION
      );

  printed_last_gplay_score = gplay_score;
  printed_last_snake_direction = 
    SnakePiece_direction(Snake_piece(&snake, 0))
    ;
}


void gplay_classic()
{
  if(gstate_swapped){
    gplay_init();
  }

  // Check if snake's heas is in the smae place of
  // the food, that is, if he ate the food!
  snake_catch_food = Food_Snake_catch(&snake_food, &snake);
  if(snake_catch_food){
    Snake_increase(&snake);
    Food_generate(&snake_food, &snake);

    ++gplay_score;
  }

  // Read the input and turn the snake
  gameInput_read();
  if(buttRight_val == HIGH && snake_can_turn){
    Snake_turn_clockwise(&snake);
  }
  else if(buttLeft_val == HIGH && snake_can_turn){
    Snake_turn_counterclockwise(&snake);
  }
  if(
      (buttRight_val == HIGH || buttLeft_val == HIGH)
      && snake_can_turn
      )
  {
    snake_turned_last_time = millis();
  }

  // Display the snake and food into the led matrix
  T_FIGURE f_snake[SNAKE_TABLE_LINES];
  T_FIGURE f_food[SNAKE_TABLE_LINES];

  Snake_LMatrix_figure(&snake, f_snake);
  Food_LMatrix_figure(&snake_food, f_food);
  size_t i;
  for(i=0; i < SNAKE_TABLE_LINES; ++i){
    f_snake[i] += f_food[i];
  }

  LMatrix_draw(&lm, f_snake, 25);
  if(
      !Snake_move_forward_with_delay(&snake, GAME_PLAY_DELAY)
      && gplay_hp
      ){
    --gplay_hp;
  }

  gplay_print_infos();
}



void gplay_ended_bad()
{
  gDisplay_clean(CLEAN_DISPLAY);
  gDisplay_print(
      PRINT_STRING("GAME OVER", CENTER),
      POSITION(GDISPLAY_CENTER_X, 0)
      );

  gDisplay_print(
      PRINT_STRING("SCORE: ", FORWARD),
      POSITION(0, 1)
      );
  gDisplay_print(
      PRINTF_INT(gplay_score, "%02u", FORWARD),
      NO_POSITION
      );
  delay(3000);
}
void gplay_ended_good()
{
  gDisplay_clean(CLEAN_DISPLAY);
  gDisplay_print(
      PRINT_STRING("CONGRATULATIONS!", CENTER),
      POSITION(GDISPLAY_CENTER_X, 0)
      );

  gDisplay_print(
      PRINT_STRING("SCORE: ", FORWARD),
      POSITION(0, 1)
      );
  gDisplay_print(
      PRINTF_INT(gplay_score, "%02u", FORWARD),
      NO_POSITION
      );
  delay(3000);
}

// game level
void glevel_next()
{
  if(glevel == GLEVEL_END){
    glevel = GLEVEL_INIT;
    return;
  }

  glevel = (GLevel)(glevel + 1);
}

char* glevel_name()
{
  switch(glevel){
    case GLEVEL_CLASSIC:
      return "CLASSIC";
      break;
      
    default:
      return "";
      break;
  }
}

// game menu
void gmenu_update()
{
  if(gstate_swapped){
    gmenu = GMENU_PLAY;
    return;
  }

  gmenu_last = gmenu;
  switch(gmenu){
    case GMENU_PLAY:
      if(buttLeft_val == HIGH){
        gmenu_next();
      }
      else if(buttRight_val == HIGH){
      }
      break;

    case GMENU_SCORE:
      if(buttLeft_val == HIGH){
        gmenu_next();
      }
      break;

    case GMENU_LEVEL:
      if(buttLeft_val == HIGH){
        gmenu_next();
      }
      break;

    default:
      break;
  }
}

void gmenu_play()
{
  if(!gmenu_swapped && !gstate_swapped){
    return;
  }

  gDisplay_clean(CLEAN_DISPLAY);
  gDisplay_print(
      PRINT_STRING("MENU PLAY", CENTER),
      POSITION(GDISPLAY_CENTER_X, 0)
      );
}

void gmenu_score()
{
  if(gmenu_swapped || gstate_swapped){
    gDisplay_clean(CLEAN_DISPLAY);
    gDisplay_print(
        PRINT_STRING("MENU SCORE", FORWARD),
        POSITION(0, 0)
        );
    gscore_i_reset();
  }


  if(buttRight_val == HIGH){
    gscore_next();
  }

  if(
      buttRight_val == HIGH
      || gmenu_swapped
      || gstate_swapped
      ){
    gDisplay_print(
        PRINTF_INT(gscore_i() + 1, "SCORE %02u#: ", FORWARD),
        POSITION(0, 1)
        );
    gDisplay_print(
        PRINTF_INT(gscore_curr(), "%02u", BACKWARD),
        POSITION(GDISPLAY_COLMS, 1)
        );
  }
}

void gmenu_level()
{
  if(gmenu_swapped || gstate_swapped){
    gDisplay_clean(CLEAN_DISPLAY);
    gDisplay_print(
        PRINT_STRING("MENU LEVEL", FORWARD),
        POSITION(0, 0)
        );
  }

  if(buttRight_val == HIGH){
    glevel_next();
  }

  if(
      buttRight_val == HIGH
      || gmenu_swapped
      || gstate_swapped
    ){
    gDisplay_print(
        PRINT_STRING(glevel_name(), FORWARD),
        POSITION(0, 1)
        );
  }
}

// game play modes
T_HP glevel_hp()
{
  switch(glevel){
    case GLEVEL_CLASSIC:
      return GLEVEL_CLASSIC_HP;
      break;

    default:
      return 1;
      break;
  }
}

// main functions
void game_boot()
{
  gDisplay_print(PRINT_STRING("SSSNAKE GAMEEE", CENTER), POSITION(8, 0));
  gDisplay_print(PRINT_STRING("WELCOME!", CENTER), POSITION(8, 1));

  int i;
  for(i=0; i < 2; ++i){
    AnimationLCD_print(
        &game_boot_animation,
        GAME_BOOT_DELAY / (8 * 2)
        );
  }
}

void game_menu()
{
  gameInput_read();

  switch(gmenu){
    case GMENU_PLAY:
      gmenu_play();
      break;

    case GMENU_SCORE:
      gmenu_score();
      break;

    case GMENU_LEVEL:
      gmenu_level();
      break;

    default:
      break;
  }

  gmenu_update();
  delay(GAME_MENU_DELAY);
}

void game_play()
{
  switch(glevel){
    case GLEVEL_CLASSIC:
      gplay_classic();
      break;

    default:
      break;
  }

  gplay_update();
}

// Display functions
void gDisplay_print(
  int print_val_int,
  char print_val_char,
  float print_val_float,
  char print_val_string[],
  uint8_t print_val_customChar,
  
  VALUE_TYPE value_type,
  char format[],
  PRINT_ORIENTATION print_order,
  
  T_BOOL passed_position,
  int8_t x,
  int8_t y
  )
{
  char value[PRINT_VALUE_SIZE_MAX];
  
  switch(value_type){
    case VALUE_TYPE_INT:
      sprintf(value, format, print_val_int);
      break;
    
    case VALUE_TYPE_CHAR:
      sprintf(value, format, print_val_char);
      break;
    
    case VALUE_TYPE_FLOAT:
      sprintf(value, format, print_val_float);
      break;
    
    case VALUE_TYPE_STRING:
      sprintf(value, format, print_val_string);
      break;

    case VALUE_TYPE_CUSTOM_CHAR:
      break;
    
    default:
      value[0] = '\0';
      break;
  }
  
  T_CURSOR_X value_size = strlen(value);
  uint8_t value_chars_escapped;
  if(passed_position){
    cursor_x = x;
    cursor_y = y;
  }
  // Switch case for any value that is not a custom character
  switch(print_order){
    case CENTER:
      if(value_type == VALUE_TYPE_CUSTOM_CHAR){
        break;
      }
      value_chars_escapped = 
        (cursor_x >= value_size / 2)?0: value_size / 2 - cursor_x;
      cursor_x -= value_size / 2;
      
      if(value_chars_escapped <= value_size){
          gameDisplay.setCursor(
              (cursor_x >= 0)?cursor_x: 0,
              cursor_y
              );
          gameDisplay.print(value + value_chars_escapped);
      }
      cursor_x += value_size;
      break;
    
    case FORWARD:
      if(value_type == VALUE_TYPE_CUSTOM_CHAR){
        break;
      }
      value_chars_escapped = 
        (cursor_x >= 0)?0: -cursor_x;
      
      if(value_chars_escapped <= value_size){
          gameDisplay.setCursor(
              (cursor_x >= 0)? cursor_x: 0,
              cursor_y
              );
          gameDisplay.print(value + value_chars_escapped);
      }
      cursor_x += value_size;
      break;
    
    case BACKWARD:
      if(value_type == VALUE_TYPE_CUSTOM_CHAR){
        break;
      }
      value_chars_escapped = 
          (cursor_x >= value_size)? 0: value_size - cursor_x;
      cursor_x -= value_size;
    
      if(value_chars_escapped <= value_size){
          gameDisplay.setCursor(
              (cursor_x >= 0)?cursor_x: 0,
              cursor_y
              );
          gameDisplay.print(value + value_chars_escapped);
      }
      break;
    
    default:
      break;
  }

  // Switch case for any value that is a custom character
  switch(print_order){
    case CENTER:
    case FORWARD:
      if(value_type != VALUE_TYPE_CUSTOM_CHAR){
        break;
      }

      if(cursor_x >= 0){
        gameDisplay.setCursor(cursor_x, cursor_y);
        gameDisplay.write(byte(print_val_customChar));
      }

      ++cursor_x;
      break;

    case BACKWARD:
      if(value_type != VALUE_TYPE_CUSTOM_CHAR){
        break;
      }

      if((--cursor_x) >= 0){
        gameDisplay.setCursor(cursor_x, cursor_y);
        gameDisplay.write(byte(print_val_customChar));
      }
      break;

    default:
      break;
  }
}

void gDisplay_clean(
    CleanOrientation c,

    T_BOOL passed_position,
    T_CURSOR_X x,
    T_CURSOR_Y y
    )
{
  switch(c){
    case __CLEAN_LINE:
      for(x=0; x < GDISPLAY_COLMS; ++x){
        gameDisplay.setCursor(x, y);
        gameDisplay.print(" ");
      }
      break;

    case __CLEAN_COLM:
      for(y=0; y < GDISPLAY_LINES; ++y){
        gameDisplay.setCursor(x, y);
        gameDisplay.print(" ");
      }
      break;

    case __CLEAN_FORWARD:
      while((x++) < GDISPLAY_COLMS){
        gameDisplay.setCursor(x, y);
        gameDisplay.print(" ");
      }
      break;

    case __CLEAN_BACKWARD:
      while((x--) >= 0){
        gameDisplay.setCursor(x, y);
        gameDisplay.print(" ");
      }
      break;

    case __CLEAN_DISPLAY:
      gameDisplay.clear();
      break;

    default:
      break;
  }
}

void gDisplay_create_char(
    byte c[],
    uint8_t c_id
    )
{
  gameDisplay.createChar(c_id, c);
}

/*
 * Animation
 */
// Sprite
byte* Sprite_raw(Sprite*s)
{
  return s->_raw;
}

T_CURSOR_X Sprite_x(Sprite*s)
{
  return s->_x;
}

T_CURSOR_Y Sprite_y(Sprite*s)
{
  return s->_y;
}


void Sprite_raw_def(Sprite*s, byte*raw)
{
  size_t i;
  for(i=0; i < SPRITE_RAW_LINES; ++i){
    s->_raw[i] = raw[i];
  }
}

void Sprite_x_def(Sprite*s, T_CURSOR_X x)
{
  s->_x = x;
}

void Sprite_y_def(Sprite*s, T_CURSOR_Y y)
{
  s->_y = y;
}


void Sprite_copy(Sprite*to, Sprite*from)
{
  Sprite_raw_def(to, Sprite_raw(from));
  Sprite_x_def(to, Sprite_x(from));
  Sprite_y_def(to, Sprite_y(from));
}

void Sprite_print(Sprite*s, uint8_t char_slot)
{
  gDisplay_create_char(
      Sprite_raw(s),
      char_slot
      );
  gDisplay_print(
      PRINT_CUSTOM_CHAR(char_slot, FORWARD),
      POSITION(Sprite_x(s), Sprite_y(s))
      );
}

// AnimationLCD
size_t AnimationLCD_sprites_amt(
    AnimationLCD*a
    )
{
  return a->_sprites_amt;
}

void AnimationLCD_sprites_def(
    AnimationLCD*a,
    Sprite sprites[],
    size_t sprites_amt
    )
{
  size_t i;
  a->_sprites_amt = 0;

 for(i=0; i < sprites_amt
     && i < ANIMATIONLCD_SPRITE_MAX; ++i){
   Sprite_copy(&(a->_sprites[i]), &(sprites[i]));
   ++a->_sprites_amt;
 }
}

void AnimationLCD_print(
    AnimationLCD*a,
    T_TIME_DELAY time_delay
    )
{
  size_t i;

  for(i=0; i < AnimationLCD_sprites_amt(a); ++i){
    Sprite_print(&(a->_sprites[i]), i);
    delay(time_delay);
  }
}
