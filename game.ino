#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_6s;
AsyncDelay delay_12s;
AsyncDelay delay_30s;
volatile bool leftFlag = false;
volatile bool rightFlag = false;
volatile bool switchFlag = false;
bool soundOn;
int position = 0;
int leftWin = -90;
int rightWin = 90;
int color = 90;
float lightPos = 4.5;
float prevLightPos;
int factor = 1;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(4),left,FALLING); // interrupts for later use
  attachInterrupt(digitalPinToInterrupt(5),right,FALLING);
  attachInterrupt(digitalPinToInterrupt(7),onoff,CHANGE);
  countdown(); // play countdown animation
  soundOn = CircuitPlayground.slideSwitch(); //sound check
  delay_6s.start(6000, AsyncDelay::MILLIS); //start timers for diffculty
  delay_12s.start(12000, AsyncDelay::MILLIS);
  delay_30s.start(30000, AsyncDelay::MILLIS);
}

void loop() {
  prevLightPos = lightPos; //store light position to use later and decide whether to play tone
  if (delay_6s.isExpired()){ //these timers increment the input scaling/difficulty
    factor = 2;
    color = 50;
  }
  if (delay_12s.isExpired()){
    factor = 3;
    color = 20;
  }
  if (delay_30s.isExpired()){
    factor = 10;
    color = 0;
  }

  if(switchFlag){ //gets switch position for volume toggle
    soundOn = CircuitPlayground.slideSwitch(); 
  }

  if(leftFlag){ //decrements position variable (not light pos)
    leftFlag = 0;
    delay(30);
    position = position - factor;
  }
  if(rightFlag){ //increments position variable (not light pos)
    rightFlag = 0;
    delay(30);
    position = position + factor;
  }

  decidePos(); //decides light position based on position variable
  
  if(lightPos != 4.5){ //for all positions except for the middle, set the light to its determined position and color
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(lightPos, CircuitPlayground.colorWheel(color));
  }

  if(prevLightPos < lightPos && soundOn){ //logic for playing tones, checks if sound switch is on and if light position has moved
    CircuitPlayground.playTone(300, 25);
  }
  else if(prevLightPos > lightPos && soundOn){
    CircuitPlayground.playTone(600, 25);
  }
  
  if(position >= rightWin){ //logic for win animations
    rightAnimation();
    while(1);
  }

  if(position <= leftWin){
    leftAnimation();
    while(1);
  }

}

void decidePos(){ //thresholds set light position based on 
  if(position >= 90){
    lightPos = 9;
  }
  else if(position >= 70){
    lightPos = 8;
  }
  else if(position >= 50){
    lightPos = 7;
  }
  else if(position >= 30){
    lightPos = 6;
  }
  else if(position >= 10){
    lightPos = 5;
  }
  else if(position > -10 && position < 10){ //special exception made for "center" position given the even number of LEDs
    lightPos = 4.5;
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(4, CircuitPlayground.colorWheel(color));
    CircuitPlayground.setPixelColor(5, CircuitPlayground.colorWheel(color));
  }
  else if(position <= -90){
    lightPos = 0;
  }
  else if(position <= -70){
    lightPos = 1;
  }
  else if(position <= -50){
    lightPos = 2;
  }
  else if(position <= -30){
    lightPos = 3;
  }
  else if(position <= -10){
    lightPos = 4;
  }
}

void left(){ //ISR functions
  leftFlag = 1;
}

void right(){
  rightFlag = 1;
}

void onoff(){
  switchFlag = 1;
}

void countdown(){ //countdown animation to play before the game starts
  for(int c=10; c>=0; c--) {
    CircuitPlayground.setPixelColor(c, 255, 0, 0);
    delay(35);
  }
  delay(200);
  CircuitPlayground.clearPixels();
  delay(50);
  for(int c=10; c>=0; c--) {
    CircuitPlayground.setPixelColor(c, 255, 0, 0);
    delay(35);
  }
  delay(200);
  CircuitPlayground.clearPixels();
  delay(50);
  for(int c=10; c>=0; c--) {
    CircuitPlayground.setPixelColor(c, 0, 255, 0);
    delay(35);
  }
  delay(200);
}

void leftAnimation(){ //left win animation
  CircuitPlayground.setPixelColor(0, CircuitPlayground.colorWheel(color));
  CircuitPlayground.playTone(600, 50);
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  CircuitPlayground.setPixelColor(0, CircuitPlayground.colorWheel(color));
  CircuitPlayground.playTone(600, 50);
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  CircuitPlayground.setPixelColor(0, CircuitPlayground.colorWheel(color));
  CircuitPlayground.playTone(600, 50);
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  for(int i = 0; i<=4; i++){
    CircuitPlayground.setPixelColor(i,0,255,0);
  }
}

void rightAnimation(){ //right win animation
  CircuitPlayground.setPixelColor(9, CircuitPlayground.colorWheel(color));
  CircuitPlayground.playTone(300, 50);
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  CircuitPlayground.setPixelColor(9, CircuitPlayground.colorWheel(color));
  CircuitPlayground.playTone(300, 50);
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  CircuitPlayground.setPixelColor(9, CircuitPlayground.colorWheel(color));
  CircuitPlayground.playTone(300, 50);
  delay(200);
  CircuitPlayground.clearPixels();
  delay(200);
  for(int i = 9; i>=5; i--){
    CircuitPlayground.setPixelColor(i,0,255,0);
  }
}
