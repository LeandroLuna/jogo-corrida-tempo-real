/****************************************
 * Include Libraries
 ****************************************/
 
#include "ThreadHandler.h"

/****************************************
 * Define Constants
 ****************************************/
const uint8_t PLAYER_ONE_PRIORITY = 0;
const uint8_t PLAYER_TWO_PRIORITY = 1;
const uint32_t PERIOD = 6000; // Tempo do processo
const uint32_t START_OFF_SET = 1000 * (2/10); // Tempo de execução/foco do processo

// Sensors
//// LEDs
const uint8_t RED_LED_PIN = 5;
const uint8_t GREEN_LED_PIN = 6;

//// THREAD 
SET_THREAD_HANDLER_TICK(1000) // Intervalo de execução do processador 1ms
THREAD_HANDLER(InterruptTimer::getInstance()) // Define que será utilizado threads

/****************************************
 * Auxiliar Functions
 ****************************************/

void player1(){
  digitalWrite(RED_LED_PIN, HIGH);
  Serial.println("RED Led ON");
  delay(1000);
  digitalWrite(RED_LED_PIN, LOW);
  Serial.println("RED Led OFF");
  delay(1000);
}

void player2(){
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
  Serial.begin(9600);
  ThreadHandler::getInstance()->enableThreadExecution(); // Habilita a execução das threads
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}