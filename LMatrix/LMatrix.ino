/*
 * Led Matrix struct
 */
#define LMATRIX_LINES_MAX 10
#define LMATRIX_COLMS_MAX 10

typedef uint8_t T_LINE_PIN;
typedef uint8_t T_COLM_PIN;
typedef uint8_t T_LINE;
typedef uint8_t T_COLM;

typedef uint16_t T_FIGURE;

typedef struct {
  T_LINE_PIN _lines_pin[LMATRIX_LINES_MAX];
  T_COLM_PIN _colms_pin[LMATRIX_COLMS_MAX];
  
  T_LINE _lines_amt;
  T_COLM _colms_amt;
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

// methods
void LMatrix_reset(LMatrix*lm);
void LMatrix_setup(LMatrix*lm);
void LMatrix_led_up(
  LMatrix*lm,
  const T_LINE x,
  const T_COLM y
  );
void LMatrix_led_down(
  LMatrix*lm,
  const T_LINE x,
  const T_COLM y
  );

#define LMATRIX_DRAW_DELAY 25
void LMatrix_draw(
  LMatrix*lm,
  const T_FIGURE figure[]
  );

//
#define LINES_AMT 4
#define LINE_1_PIN 11
#define LINE_2_PIN 10
#define LINE_3_PIN 9
#define LINE_4_PIN 8

#define COLMS_AMT 4
#define COLM_1_PIN 5
#define COLM_2_PIN 4
#define COLM_3_PIN 3
#define COLM_4_PIN 2

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
  COLM_4_PIN
};

const T_FIGURE circle[] = {
  0x0110,
  0x1001,
  0x1001,
  0x0110
};

//
void setup()
{
  LMatrix_lines_def(&lm, lines_pin, LINES_AMT);
  LMatrix_colms_def(&lm, colms_pin, COLMS_AMT);
  LMatrix_setup(&lm);
}

void loop()
{
  LMatrix_draw(&lm, circle);
}

/* */
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

//
void LMatrix_reset(LMatrix*lm)
{
  T_LINE l;
  T_COLM c;
  
  for(l=0; l < LMatrix_lines_amt(lm); ++l){
    for(c=0; c < LMatrix_colms_amt(lm); ++c){
      LMatrix_led_down(lm, l, c);
    }
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
  
  LMatrix_reset(lm);
}


void LMatrix_led_up(
  LMatrix*lm,
  const T_LINE x,
  const T_COLM y
  )
{
  digitalWrite(
    LMatrix_line_pin(lm, y),
    HIGH
    );
  digitalWrite(
    LMatrix_colm_pin(lm, x),
    LOW
    );
}

void LMatrix_led_down(
  LMatrix*lm,
  const T_LINE x,
  const T_COLM y
  )
{
  digitalWrite(
    LMatrix_line_pin(lm, y),
    LOW
    );
  
  digitalWrite(
    LMatrix_colm_pin(lm, x),
    HIGH
    );
}

void LMatrix_draw(
  LMatrix*lm,
  const T_FIGURE figure[]
  )
{
  T_LINE l;
  T_COLM c;
  T_COLM colms_amt;
  
  /*
   * A row of the figure is set by a hex address.
   * By bitwise ( figure[y] >> ( 4 * x) ) & 1 
   * we can find out if the position x,y must be light.
   *
   * However, just make 4 * column mirror the image.
   * So, for fix it, we do 4 * ( LMatrix_colms_amt(lm) - c - 1).
   */
  colms_amt = LMatrix_colms_amt(lm) - 1;
  for(l=0; l < LMatrix_lines_amt(lm); ++l){
    for(c=0; c < LMatrix_colms_amt(lm); ++c){
      if(
        !((figure[l] >> ( 4 * ( colms_amt - c)) & 1))
      ){
        continue;
      }
      LMatrix_led_up(lm, c, l);
    }
    delay(LMATRIX_DRAW_DELAY);
    LMatrix_reset(lm);
  }
}

