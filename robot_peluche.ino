
#include <Wire.h>
#include <Adafruit_MotorShield.h>

const int PIN_JOYSTICK_H = A0;
const int PIN_JOYSTICK_V = A1;
const int PIN_JOYSTICK_SEL = 2;

int joystickHor, joystickVert;

const int PIN_BTN_LEFT = 6;
const int PIN_BTN_RIGHT = 4;
const int PIN_BTN_UP = 3;
const int PIN_BTN_DOWN = 5; 
const int PIN_BTN_E = 7;
const int PIN_BTN_F = 8;

bool btnLeft, btnRight, btnUp, btnDown;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

Adafruit_DCMotor *motorUpDown = AFMS.getMotor(1);
Adafruit_DCMotor *motorWrench = AFMS.getMotor(2);
Adafruit_DCMotor *motorHor    = AFMS.getMotor(3);
Adafruit_DCMotor *motorVert   = AFMS.getMotor(4);



/*
// Horizontal / Pince
const int EN_HOR = 46;
const int EN_PINCE = 44;

//HOR
const int IN1 = 36;
const int IN2 = 38;
//WRENCH
const int IN3 = 40;
const int IN4 = 42 ;

// Vertical / HB
 const int EN_VERT = 45;
//VERT
const int IN5 = 47;
const int IN6 = 49;
//HB
const int IN7 = 51;
const int IN8 = 53;
*/
void  initPins() {
  pinMode(PIN_JOYSTICK_SEL, INPUT);
  pinMode(PIN_BTN_LEFT, INPUT);
  pinMode(PIN_BTN_RIGHT, INPUT);
  pinMode(PIN_BTN_UP, INPUT);
  pinMode(PIN_BTN_DOWN, INPUT);
  pinMode(PIN_BTN_E, INPUT);
  pinMode(PIN_BTN_F, INPUT);

/*
  pinMode(EN_HOR, OUTPUT);
  pinMode(EN_PINCE, OUTPUT);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(EN_VERT,OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
*/
}

void readInput() {
  joystickHor = analogRead(PIN_JOYSTICK_H);
  joystickVert = analogRead(PIN_JOYSTICK_V);

  joystickHor = map(joystickHor, 0, 1023, -255, 255);
  joystickVert = map(joystickVert, 0, 1023, -255, 255);

  btnUp = digitalRead(PIN_BTN_UP);
  btnDown = digitalRead(PIN_BTN_DOWN);
  btnLeft = digitalRead(PIN_BTN_LEFT);
  btnRight = digitalRead(PIN_BTN_RIGHT);
}

/*
void moveHor(bool isLeft, int speed) {
  if (isLeft) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  analogWrite(EN_HOR, speed);
}

void moveVert(bool isUp, int speed) {
  if (isUp) {
    digitalWrite(IN5, HIGH);
    digitalWrite(IN6, LOW);
  } else {
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, HIGH);
  }
  analogWrite(EN_VERT, speed); 
}

void moveWrench(bool isOpened, int speed) {
  if (isOpened) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  analogWrite(EN_HOR, speed);
}

void moveUpDown(bool isUp) {
  if (isUp) {
    digitalWrite(IN7, HIGH);
    digitalWrite(IN8, LOW);
  } else {
    digitalWrite(IN7, LOW);
    digitalWrite(IN8, HIGH);
  }
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, LOW);  
}


void demoOne() {
  moveHor(false, 150);
  delay(1000);
  moveVert(false, 150);
  delay(1000);
  moveWrench(false, 150);
  delay(1000);
  moveUpDown(false);
  delay(1000);
  stopMoving();  
}
*/
void setup() {
  initPins();
  AFMS.begin();  // create with the default frequency 1.6KHz
  
  //Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  
}


void loop() {

  // put your main code here, to run repeatedly:
  readInput();
  //Serial.print("Joystick H: ");
  //Serial.print(joystickHor);
  //Serial.print(", V: ");
  //Serial.println(joystickVert);  
 
  if (btnUp) {
      //Serial.println("UP! ");
      motorUpDown->setSpeed(255);
      motorUpDown->run(FORWARD);
  } else if (btnDown) {
      //Serial.println("DOWN! ");
      motorUpDown->setSpeed(255);
      motorUpDown->run(BACKWARD);
      
  } else {
    motorUpDown->run(RELEASE);
  }
    
  if (btnLeft) {
      //Serial.println("LEFT! ");
      motorWrench->setSpeed(255);
      motorWrench->run(FORWARD);
  } else if (btnRight) {
      //Serial.println("RIGHT! ");
      motorWrench->setSpeed(255);
      motorWrench->run(BACKWARD);
  } else {
      motorWrench->run(RELEASE);
  }
 
  if (abs(joystickVert) > 10) {
    motorVert->setSpeed(abs(joystickVert));
    motorVert->run(joystickVert > 0 ? FORWARD : BACKWARD);
  } else {
    motorVert->run(RELEASE);
  }
  
  if (abs(joystickHor) > 10) {
    motorHor->setSpeed(abs(joystickHor));
    motorHor->run(joystickHor > 0 ? BACKWARD : FORWARD);
  } else {
    motorHor->run(RELEASE);
  }
 
  delay(100);
  
}
