/****************************************
 * Include Libraries
 ****************************************/
 
#include "ThreadHandler.h"
// #include <LiquidCrystal.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/****************************************
 * Define Constants
 ****************************************/

const uint8_t PLAYER_ONE_PRIORITY = 0;
const uint8_t PLAYER_TWO_PRIORITY = 1;
const uint32_t PERIOD = 1000; // Tempo do processo
const uint32_t START_OFF_SET = 1000 * (2/10); // Tempo de execução/foco do processo

// Sensors
//// Botões
const uint8_t PUSH_BUTTON_PLAYER_ONE = 4;
const uint8_t PUSH_BUTTON_PLAYER_TWO = 3;

//// LEDs
const uint8_t RED_LED_PIN = 5;
const uint8_t GREEN_LED_PIN = 6;

//// LCD 16X2
// const uint8_t RS = 13, EN = 12, D4 = 11, D5 = 10, D6 = 9, D7 = 8; 
// LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);              

//// OLED 128X32
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C 

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//// THREAD 
SET_THREAD_HANDLER_TICK(100000) // Intervalo de execução do processador 1ms
THREAD_HANDLER(InterruptTimer::getInstance()) // Define que será utilizado threads

/****************************************
 * Auxiliar Functions
 ****************************************/

// void racingDisplay(){
//   lcd.clear();
//   lcd.setCursor(0, 0);            
//   lcd.print("Leandro");   
//   lcd.setCursor(0, 1);            
//   lcd.print("Luna");
//   delay(1000);       
// }

void scoreDisplay(){
  oled.clearDisplay();
  oled.setTextSize(1); 
  oled.setTextColor(1); 
  oled.setCursor(2, 8); 
  oled.print("Leandro Luna");
  oled.display();
}

void readButton(){
  if (digitalRead(PUSH_BUTTON_PLAYER_ONE) == LOW){
    Serial.println("Player one clicked");
  }

  if (digitalRead(PUSH_BUTTON_PLAYER_TWO) == LOW){
    Serial.println("Player two clicked");
  }
}

void player1(){
  scoreDisplay();
  digitalWrite(RED_LED_PIN, HIGH);
  Serial.println("RED Led ON");
  delay(1000);
  digitalWrite(RED_LED_PIN, LOW);
  Serial.println("RED Led OFF");
  delay(1000);
}

void player2(){
  readButton();
  digitalWrite(GREEN_LED_PIN, HIGH);
  Serial.println("Green Led ON");
  delay(1000);
  digitalWrite(GREEN_LED_PIN, LOW);
  Serial.println("Green Led OFF");
  delay(1000);
}

Thread* thread1 = createThread(PLAYER_ONE_PRIORITY, PERIOD, START_OFF_SET, player1);
Thread* thread2 = createThread(PLAYER_TWO_PRIORITY, PERIOD, START_OFF_SET, player2);

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  ThreadHandler::getInstance()->enableThreadExecution(); // Habilita a execução das threads
  Serial.begin(115200);
  
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(PUSH_BUTTON_PLAYER_ONE, INPUT_PULLUP); 
  pinMode(PUSH_BUTTON_PLAYER_TWO, INPUT_PULLUP);
  
  // lcd.begin(16, 2);

  if(!oled.begin(SSD1306_SWITCHCAPVCC)) {
    for(;;);
  }

  oled.display();
  delay(2000);
}

void loop() {
}