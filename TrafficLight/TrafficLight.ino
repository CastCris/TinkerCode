#define BUTT_RESET_PIN 5

#define TRFC_LIGHT_GREEN_PIN 4
#define TRFC_LIGHT_YELLOW_PIN 3
#define TRFC_LIGHT_RED_PIN 2

#define TRFC_LIGHT_GREEN_DELAY 1000 // 5000
#define TRFC_LIGHT_YELLOW_DELAY 1000
#define TRFC_LIGHT_RED_DELAY 1000 // 5000

#define TRFC_LIGHT_RESET_DELAY 10000

enum {
  TRFC_LIGHT_GREEN,
  TRFC_LIGHT_YELLOW,
  TRFC_LIGHT_RED
};

#define TRFC_LIGHT_PINS { \
  TRFC_LIGHT_GREEN_PIN, \
  TRFC_LIGHT_YELLOW_PIN, \
  TRFC_LIGHT_RED_PIN \
}

#define TRFC_LIGHT_DELAYS { \
  TRFC_LIGHT_GREEN_DELAY, \
  TRFC_LIGHT_YELLOW_DELAY, \
  TRFC_LIGHT_RED_DELAY \
}

//
const int trfcLight[] = TRFC_LIGHT_PINS;
const int trfcLight_delays[] = TRFC_LIGHT_DELAYS;

uint32_t trfcLight_reset_last_time;
uint32_t trfcLight_change_last_time;

size_t trfcLight_size = sizeof(trfcLight) / sizeof(trfcLight[0]);

// /*
size_t trfcLight_i;
size_t trfcLight_i_delay;
// */

//
void TrfcLight_next();
void TrfcLight_reset();

void TrfcLight_shut_down();

//
void setup()
{
  Serial.begin(9600);
  size_t i;

  for(i=0; i < trfcLight_size; ++i){
    pinMode(trfcLight[i], OUTPUT);
  }

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTT_RESET_PIN, INPUT);

  digitalWrite(trfcLight[0], HIGH);
}

void loop()
{
  // /*
  TrfcLight_reset();
  TrfcLight_next();
  // */
}

//
void TrctLight_show()
{
  digitalWrite(trfcLight[trfcLight_i], HIGH);
}

void TrfcLight_next()
{
  uint32_t time_changed = millis() - trfcLight_change_last_time;
  
  if(time_changed < trfcLight_delays[trfcLight_i_delay]){
    return;
  }
  
  digitalWrite(trfcLight[trfcLight_i], LOW);
      
  ++trfcLight_i_delay;
  ++trfcLight_i;
  trfcLight_change_last_time = millis();

  trfcLight_i %= trfcLight_size;
  trfcLight_i_delay %= trfcLight_size;

  digitalWrite(trfcLight[trfcLight_i], HIGH);
}

void TrfcLight_reset()
{
  uint32_t reset_val;
  uint32_t reset_time;

  reset_val = digitalRead(BUTT_RESET_PIN);
  reset_time = millis() - trfcLight_reset_last_time;

  Serial.println(reset_time);

  if(reset_time <= TRFC_LIGHT_RESET_DELAY 
    || reset_val == LOW
    || trfcLight_i == TRFC_LIGHT_RED
   ){
    return;
  }

  trfcLight_i = TRFC_LIGHT_YELLOW;
  trfcLight_i_delay = TRFC_LIGHT_YELLOW;
  trfcLight_reset_last_time = millis();
  trfcLight_change_last_time = millis();

  TrfcLight_shut_down();
  digitalWrite(trfcLight[TRFC_LIGHT_YELLOW], HIGH);
}

void TrfcLight_shut_down()
{
  size_t i;
  for(i=0; i < trfcLight_size; ++i){
    digitalWrite(trfcLight[i], LOW);
  }
}
