#include <Arduino.h>
#line 1 "f:\\迅雷下载\\Mixly0.998_WIN(7.9)\\arduino-1.8.5\\libraries\\Stepper\\examples\\stepper_2wire_drive\\driver.ino"
#line 1 "f:\\迅雷下载\\Mixly0.998_WIN(7.9)\\arduino-1.8.5\\libraries\\Stepper\\examples\\stepper_2wire_drive\\driver.ino"
#include "Stepper.h"
#define STEP_PER_REV 6400
#define WIDTH 600
#define MM_PER_REV 40
Stepper left(STEP_PER_REV,2,3);
Stepper right(STEP_PER_REV,5,4);
#line 7 "f:\\迅雷下载\\Mixly0.998_WIN(7.9)\\arduino-1.8.5\\libraries\\Stepper\\examples\\stepper_2wire_drive\\driver.ino"
void setup();
#line 34 "f:\\迅雷下载\\Mixly0.998_WIN(7.9)\\arduino-1.8.5\\libraries\\Stepper\\examples\\stepper_2wire_drive\\driver.ino"
void resetCommand();
#line 43 "f:\\迅雷下载\\Mixly0.998_WIN(7.9)\\arduino-1.8.5\\libraries\\Stepper\\examples\\stepper_2wire_drive\\driver.ino"
void runCommand();
#line 66 "f:\\迅雷下载\\Mixly0.998_WIN(7.9)\\arduino-1.8.5\\libraries\\Stepper\\examples\\stepper_2wire_drive\\driver.ino"
void loop();
#line 7 "f:\\迅雷下载\\Mixly0.998_WIN(7.9)\\arduino-1.8.5\\libraries\\Stepper\\examples\\stepper_2wire_drive\\driver.ino"
void setup(){
    left.setSpeed(100);
    right.setSpeed(100);
    Serial.begin(9600);
    pinMode(9,OUTPUT);
    pinMode(11,OUTPUT);
}
/* Variable initialization */

// A pair of varibles to help parse serial commands (thanks Fergs)
int arg = 0;
int index = 0;

// Variable to hold an input character
char chr;

// Variable to hold the current single-character command
char cmd;

// Character arrays to hold the first and second arguments
char argv1[16];
char argv2[16];

// The arguments converted to integers
long arg1;
long arg2;
/* Clear the current command parameters */
void resetCommand() {
  cmd = NULL;
  memset(argv1, 0, sizeof(argv1));
  memset(argv2, 0, sizeof(argv2));
  arg1 = 0;
  arg2 = 0;
  arg = 0;
  index = 0;
}
void runCommand() {
    arg1 = atoi(argv1);
    arg2 = atoi(argv2);

    switch(cmd) {
        case 'm':
            left.step(arg1);
            right.step(arg2);
            break;
        case 'p':
            analogWrite(9,127);
            analogWrite(11,127);
            break;
        case 'b':
            digitalWrite(9,LOW);
            digitalWrite(11,LOW);
            break;
        case 'x':
            break;
        case 'y':
            break;
    }
}
void loop(){
    while (Serial.available() > 0) {
    
    // Read the next character
    chr = Serial.read();

    // Terminate a command with a CR
    if (chr == 13) {
      if (arg == 1) argv1[index] = NULL;
      else if (arg == 2) argv2[index] = NULL;
      runCommand();
      resetCommand();
    }
    // Use spaces to delimit parts of the command
    else if (chr == ' ') {
      // Step through the arguments
      if (arg == 0) arg = 1;
      else if (arg == 1)  {
        argv1[index] = NULL;
        arg = 2;
        index = 0;
      }
      continue;
    }
    else {
      if (arg == 0) {
        // The first arg is the single-letter command
        cmd = chr;
      }
      else if (arg == 1) {
        // Subsequent arguments can be more than one character
        argv1[index] = chr;
        index++;
      }
      else if (arg == 2) {
        argv2[index] = chr;
        index++;
      }
    }
  }
}


