// Nome: Leandro de Jesus Luna
// RM: 86492

/****************************************
 * Include Libraries
 ****************************************/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

/****************************************
 * Define Constants
 ****************************************/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int PLAYER_ONE_BUTTON = 27;
const int PLAYER_TWO_BUTTON = 14;

const int RED_LED_PIN = 12;
const int GREEN_LED_PIN = 13;

const int WIN_CONDITION = 19;
const int RESET_RACE_DELAY = 5000;
bool isResetting = false; 

volatile int player1Position = 0;
volatile int player2Position = 0;

int player1Score = 0;
int player2Score = 0;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
const long debounceDelay = 200;

/****************************************
 * Task Functions
 ****************************************/
void TaskPlayer1(void *pvParameters) {
  Serial.println("Task Player 1 created!");
  while(1) {
    if (!isResetting && digitalRead(PLAYER_ONE_BUTTON) == LOW) {
      unsigned long currentTime = millis();
      if ((currentTime - lastDebounceTime1) > debounceDelay) {
        lastDebounceTime1 = currentTime;
        player1Position++;
        checkForWinner();
      }
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void TaskPlayer2(void *pvParameters) {
  Serial.println("Task Player 2 created!");
  while(1) {
    if (!isResetting && digitalRead(PLAYER_TWO_BUTTON) == LOW) {
      unsigned long currentTime = millis();
      if ((currentTime - lastDebounceTime2) > debounceDelay) {
        lastDebounceTime2 = currentTime;
        player2Position++;
        checkForWinner();
      }
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void TaskUpdateDisplay(void *pvParameters) {
  Serial.println("Task Update Display created!");
  while(1) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    display.setCursor(6 * player1Position, 0);
    display.print("P1");
    display.setCursor(6 * player2Position, 10);
    display.print("P2");

    display.setCursor(0, 25);
    display.print("Score: P1=");
    display.print(player1Score);
    display.print(" | P2=");
    display.print(player2Score);
    
    display.display();
  }
  vTaskDelay(100 / portTICK_PERIOD_MS);
}

/****************************************
 * Auxiliar Functions
 ****************************************/
void resetGame() {
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  player1Position = 0;
  player2Position = 0;
  isResetting = false;
}

void checkForWinner() {
  if (player1Position >= WIN_CONDITION || player2Position >= WIN_CONDITION) {
    if (player1Position >= WIN_CONDITION) {
      player1Score++;
      digitalWrite(GREEN_LED_PIN, HIGH);
    }
    if (player2Position >= WIN_CONDITION) {
      player2Score++;
      digitalWrite(RED_LED_PIN, HIGH);
    }
    isResetting = true;
    delay(RESET_RACE_DELAY);
    resetGame();
  }
}

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(PLAYER_ONE_BUTTON, INPUT_PULLUP);
  pinMode(PLAYER_TWO_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(6 * player1Position, 0);
  display.print("P1");
  display.setCursor(6 * player2Position, 10);
  display.print("P2");
  display.display();

  BaseType_t task1Status = xTaskCreate(&TaskPlayer1, "TaskPlayer1", 2048, NULL, 1, NULL);
  BaseType_t task2Status = xTaskCreate(&TaskPlayer2, "TaskPlayer2", 2048, NULL, 1, NULL);
  BaseType_t task3Status = xTaskCreate(&TaskUpdateDisplay, "TaskUpdateDisplay", 4096, NULL, 2, NULL);

  if (task1Status != pdPASS || task2Status != pdPASS || task3Status != pdPASS) {
    Serial.println("Task creation failed!");
  }
}

void loop() {
  // Do nothing here, tasks are running
}
