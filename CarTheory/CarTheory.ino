#include<math.h>

#define POT_VELOCITY_PIN A5
#define POT_DIRECTION_PIN A4

int potVelocity_val;
int potDirection_val;

//
typedef uint8_t T_LEFT_PIN;
typedef uint8_t T_RIGHT_PIN;
typedef uint8_t T_SPEED_PIN;
typedef int16_t T_SPEED;

typedef struct {
  T_LEFT_PIN leftPin;
  T_RIGHT_PIN rightPin;
  
  T_SPEED_PIN speedPin;
  T_SPEED speed;
} Motor;

T_LEFT_PIN Motor_leftPin(Motor*);
T_RIGHT_PIN Motor_rightPin(Motor*);
T_SPEED_PIN Motor_speedPin(Motor*);
T_SPEED Motor_speed(Motor*);

// /*
void Motor_leftPin_def(Motor*, T_LEFT_PIN);
void Motor_rightPin_def(Motor*, T_RIGHT_PIN);
void Motor_speedPin_def(Motor*, T_SPEED_PIN);
void Motor_speed_def(Motor*, T_SPEED);

void Motor_setup_pins(Motor*);

void Motor_stop(Motor*);
void Motor_forward(Motor*);
void Motor_backward(Motor*);

#define RAD (PI / 180)
typedef double T_COS;
typedef double T_DELTA;

T_SPEED _BiMotor_speed_m2_for_cos(Motor*, T_COS);
void BiMotor_direction_set(Motor*, Motor*, T_COS);
// */

Motor m1 = {
  3,
  4,
  5
};

Motor m2 = {
  8,
  7,
  6
};

//
void setup()
{
  Motor_setup_pins(&m1);
  Motor_setup_pins(&m2);
  
  Serial.begin(9600);
  
  
}

void loop()
{
  potVelocity_val = analogRead(POT_VELOCITY_PIN);
  potDirection_val = analogRead(POT_DIRECTION_PIN);
  
  int speed, cos;
  speed = map(potVelocity_val, 0, 1023, 0, 255);
  cos = map(potDirection_val, 0, 1023, 180, 0);
  
  Motor_speed_def(&m1, speed);
  Motor_speed_def(&m2, speed);
  BiMotor_direction_set(&m1, &m2, RAD * cos);
  delay(100);
}

//
T_LEFT_PIN Motor_leftPin(Motor*m)
{
  return m->leftPin;
}

T_RIGHT_PIN Motor_rightPin(Motor*m)
{
  return m->rightPin;
}

T_SPEED_PIN Motor_speedPin(Motor*m)
{
  return m->speedPin;
}

T_SPEED Motor_speed(Motor*m)
{
  return m->speed;
}


void Motor_leftPin_def(Motor*m, T_LEFT_PIN leftPin)
{
  m->leftPin = leftPin;
}

void Motor_rightPin_def(Motor*m, T_RIGHT_PIN rightPin)
{
  m->rightPin = rightPin;
}

void Motor_speedPin_def(Motor*m, T_SPEED_PIN speedPin)
{
  m->speedPin = speedPin;
}

void Motor_speed_def(Motor*m, T_SPEED speed)
{
  // /*
  int signal;
  if(speed < 0L){
    signal = -1;
    Motor_backward(m);
  }
  else{
    signal = 1;
    Motor_forward(m);
  }
  // */
  
  analogWrite(
    Motor_speedPin(m),
    speed * signal
    );
  m->speed = speed;
}


void Motor_setup_pins(Motor*m)
{
  pinMode(Motor_leftPin(m), OUTPUT);
  pinMode(Motor_rightPin(m), OUTPUT);
  pinMode(Motor_speedPin(m), OUTPUT);
}


void Motor_stop(Motor*m)
{
  digitalWrite(
    Motor_leftPin(m),
    LOW
    );
  
  digitalWrite(
    Motor_rightPin(m),
    LOW
    );
}

void Motor_forward(Motor*m)
{
  digitalWrite(
    Motor_leftPin(m),
    LOW
    );
  
  digitalWrite(
    Motor_rightPin(m),
    HIGH
    );
}

void Motor_backward(Motor*m)
{
  digitalWrite(
    Motor_leftPin(m),
    HIGH
    );
  
  digitalWrite(
    Motor_rightPin(m),
    LOW
    );
}


T_SPEED _BiMotor_speed_m2_for_cos(Motor*m1, T_COS cos_val)
{
  T_DELTA a, b;
  T_DELTA delta;
  
  a = cos(cos_val);
  b = Motor_speed(m1);
  
  // (4 - 16*a^(4) + 16*a^(2) - 4)
  delta = 
    (
    - (16 * pow(a, 4))
    + (16 * pow(a, 2))
    ) * pow(b, 2)
    ;
  
  T_DELTA result =
    round(( - (2 * b) + sqrt(delta)))
    /
    (4.0 * pow(a, 2) - 2.0)
    ;
  
  /*
  Serial.print("delta : ");
  Serial.println(delta);
  Serial.println();
  // */
  
  return result;
}

void BiMotor_direction_set(Motor*m1, Motor*m2, T_COS cos_val)
{
  T_SPEED speed_motor;
  speed_motor = _BiMotor_speed_m2_for_cos(m1, cos_val);
  
  // Serial.println(speed_motor);
  
  if(cos_val < RAD * 90){
    Motor_speed_def(m1, speed_motor);
  }
  else {
    Motor_speed_def(m2, speed_motor);
  }
}
