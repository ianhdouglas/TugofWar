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
  attachInterrupt(digitalPinToInterrupt(4),left,FALLING);
  attachInterrupt(digitalPinToInterrupt(5),right,FALLING);
  attachInterrupt(digitalPinToInterrupt(7),onoff,CHANGE);
  countdown();
  soundOn = CircuitPlayground.slideSwitch();
  delay_6s.start(6000, AsyncDelay::MILLIS);
  delay_12s.start(12000, AsyncDelay::MILLIS);
  delay_30s.start(30000, AsyncDelay::MILLIS);
}

void loop() {
  prevLightPos = lightPos;
  if (delay_6s.isExpired()){
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

  if(switchFlag){
    soundOn = CircuitPlayground.slideSwitch();
  }

  if(leftFlag){
    leftFlag = 0;
    delay(30);
    position = position - factor;
  }
  if(rightFlag){
    rightFlag = 0;
    delay(30);
    position = position + factor;
  }

  decidePos();
  
  if(lightPos != 4.5){
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(lightPos, CircuitPlayground.colorWheel(color));
  }

  if(prevLightPos < lightPos && soundOn){
    CircuitPlayground.playTone(300, 25);
  }
  else if(prevLightPos > lightPos && soundOn){
    CircuitPlayground.playTone(600, 25);
  }
  
  if(position >= rightWin){
    rightAnimation();
    while(1);
  }

  if(position <= leftWin){
    leftAnimation();
    while(1);
  }

}

void decidePos(){
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
  else if(position > -10 && position < 10){
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

void left(){
  leftFlag = 1;
}

void right(){
  rightFlag = 1;
}

void onoff(){
  switchFlag = 1;
}

void countdown(){
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

void leftAnimation(){
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

void rightAnimation(){
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