#include <Arduino.h>
#include "Keyboard.h"

#define BTN_LEFT 2
#define BTN_RIGHT 3
#define BAUDRATE 115200
#define DEBOUNCE_TIME 5
#define PULL_UP true
#define LEFT 'q'
#define RIGHT 'w'

//globals
bool isLeftPressed = false;
bool isRightPressed = false;
uint32_t currentLeftTime = 0;
uint32_t currentRightTime = 0;

void setup() {
  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);
  Keyboard.begin();

  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  //attachInterrupt(digitalPinToInterrupt(BTN_LEFT), leftPressed, LOW);
  //attachInterrupt(digitalPinToInterrupt(BTN_RIGHT), rightPressed, LOW);
  
  Serial.println("Setup Complete!");
}

void leftPressed() {
  if(digitalRead(BTN_LEFT) == 0) {
    Keyboard.press(LEFT);
    currentLeftTime = millis() + DEBOUNCE_TIME;
    isLeftPressed = true;
  }
}

void rightPressed() {
  if(digitalRead(BTN_RIGHT) == 0) {
    Keyboard.press(RIGHT);
    currentRightTime = millis() + DEBOUNCE_TIME;
    isRightPressed = true;
  }
}

void loop() {

  leftPressed();
  rightPressed();
  
  if(digitalRead(BTN_LEFT) != 0 && isLeftPressed && currentLeftTime < millis()) {
    Keyboard.release(LEFT);
    isLeftPressed = false;
  }
  
  if(digitalRead(BTN_RIGHT) != 0 && isRightPressed && currentRightTime < millis()) {
    Keyboard.release(RIGHT);
    isRightPressed = false;
  }
  
}
