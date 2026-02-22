// C++ code
#define DICE_LINES 3
#define DICE_COLUMNS 2
#define DICE_MAX_NUM (DICE_LINES * DICE_COLUMNS)

#define BUTT_DECREASE_PIN 6
#define BUTT_INCREASE_PIN 7
#define BUTT_RANDOM_NUM_PIN 11
#define BUTT_CHANGE_DRAW_PIN 12

enum{
  DICE_DRAW_C,
  DICE_DRAW_L
};

int dice[DICE_LINES][DICE_COLUMNS] = {
  {2, 8}, 
  {3, 9}, 
  {4, 10}
};
int draw_order[] = {
  DICE_DRAW_C,
  DICE_DRAW_L
};
int n, draw_order_i;

#define SIZE_DRAW_ORDER \
	(sizeof(draw_order) / sizeof(draw_order[0]))

//
void setup()
{
  size_t i, j;
  for(i=0; i < DICE_LINES; ++i){
    for(j=0; j < DICE_COLUMNS; ++j){
    	pinMode(dice[i][j], OUTPUT);
    }
  }
  
  pinMode(BUTT_DECREASE_PIN, INPUT);
  pinMode(BUTT_INCREASE_PIN, INPUT);
  pinMode(BUTT_RANDOM_NUM_PIN, INPUT);
  pinMode(BUTT_CHANGE_DRAW_PIN, INPUT);
}

void loop()
{
  /*
  int i;
  for(i=0; i <= DICE_MAX_NUM; ++i){
  	dice_draw(i, DICE_DRAW_L);
  	delay(300);
  }
  
  delay(500);
  for(i=0; i <= DICE_MAX_NUM; ++i){
    dice_draw(i, DICE_DRAW_C);
    delay(300);
  }
  // */
  
  /*
  int i;
  for(i=0; i <= DICE_MAX_NUM; ++i){
    dice_draw(i, DICE_DRAW_L);
    delay(700);
    dice_draw(i, DICE_DRAW_C);
    delay(700);
  }
  // */
  
  // /*
  int butt_dec,
  butt_inc,
  butt_ran,
  butt_change_draw;
  
  butt_dec = digitalRead(BUTT_DECREASE_PIN);
  butt_inc = digitalRead(BUTT_INCREASE_PIN);
  butt_ran = digitalRead(BUTT_RANDOM_NUM_PIN);
  butt_change_draw = digitalRead(BUTT_CHANGE_DRAW_PIN);
  
  if(butt_inc == HIGH
     	&& n < DICE_MAX_NUM){
    ++n;
  }
  else if(butt_dec == HIGH
          && n > 0){
    --n;
  }
  else if(butt_ran == HIGH){
    n = rand() % 7;
  }
  
  if(butt_change_draw == HIGH){
    ++draw_order_i;
    draw_order_i %= SIZE_DRAW_ORDER;
  }
  
  dice_draw(n, draw_order[draw_order_i]);
  delay(100);
  // */
}

void dice_clean()
{
  size_t i, j;
  for(i=0; i < DICE_LINES; ++i){
    for(j=0; j < DICE_COLUMNS; ++j){
      digitalWrite(dice[i][j], LOW);
    }
  
  }
}

void dice_draw_num_by_line(int n)
{
  if(n > DICE_MAX_NUM)
    return;
  
  dice_clean();

  size_t i, j;
  int current_n;
  
  current_n = 0;
  for(i=0; current_n < n; ++i){
    for(j=0; j < DICE_COLUMNS
        && (current_n++) < n; ++j){
      digitalWrite(dice[i][j], HIGH);
    }
  }
}

void dice_draw_num_by_column(int n)
{
  if(n > DICE_MAX_NUM)
    return;
  
  dice_clean();
  
  size_t i, j;
  int current_n;
  
  current_n = 0;
  for(j=0; current_n < n; ++j){
    for(i=0; i < DICE_LINES
        && (current_n++) < n; ++i){
      digitalWrite(dice[i][j], HIGH);
    }
  }
}

void dice_draw(int n, int type)
{
  if(type == DICE_DRAW_C)
    dice_draw_num_by_column(n);
  else if(type == DICE_DRAW_L)
    dice_draw_num_by_line(n);
}
