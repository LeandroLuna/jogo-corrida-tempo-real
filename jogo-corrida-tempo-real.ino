#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <SPI.h>
// #include <Wire.h>

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 32
// #define OLED_RESET -1
// #define SCREEN_ADDRESS 0x3C
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int PLAYER_ONE_BUTTON = 4;
const int PLAYER_TWO_BUTTON = 3;

const int RED_LED_PIN = 5;
const int GREEN_LED_PIN = 6;

const int WIN_CONDITION = 10;

volatile int player1Position = 0;
volatile int player2Position = 0;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
const long debounceDelay = 100;

void TaskPlayer1(void *pvParameters) {
  Serial.println("Task Player 1 created!");
  while(1) {
    if (digitalRead(PLAYER_ONE_BUTTON) == LOW) {
      unsigned long currentTime = millis();
      if ((currentTime - lastDebounceTime1) > debounceDelay) {
        lastDebounceTime1 = currentTime;
        if (player1Position < WIN_CONDITION) {
          player1Position++;
          Serial.println(player1Position);
          // updateDisplay();
        } else {
          digitalWrite(GREEN_LED_PIN, HIGH);
        }
      }
    }
  vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void TaskPlayer2(void *pvParameters) {
  Serial.println("Task Player 2 created!");
  while(1) {
    if (digitalRead(PLAYER_TWO_BUTTON) == LOW) {
      unsigned long currentTime = millis();
      if ((currentTime - lastDebounceTime2) > debounceDelay) {
        lastDebounceTime2 = currentTime;
        if (player2Position < WIN_CONDITION) {
          player2Position++;
          Serial.println(player2Position);
          // updateDisplay();
        } else {
          digitalWrite(RED_LED_PIN, HIGH);
        }
      }
    }
  vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

// void TaskUpdateDisplay(void *pvParameters) {
//   Serial.println("Task Update Display created!");
//   while(1) {
//     display.clearDisplay();
//     display.setTextSize(1);
//     display.setTextColor(SSD1306_WHITE);
//     display.setCursor(6 * player1Position, 0);
//     display.print("P1");
//     display.setCursor(6 * player2Position, 10);
//     display.print("P2");
//     display.display();
//   }
//   vTaskDelay(10000 / portTICK_PERIOD_MS);
// }

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(PLAYER_ONE_BUTTON, INPUT_PULLUP);
  pinMode(PLAYER_TWO_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
  // if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for (;;);
  // }
  // display.clearDisplay();
  // display.display();
  // updateDisplay();

  BaseType_t task1Status = xTaskCreate(TaskPlayer1, "TaskPlayer1", 128, NULL, 1, NULL);
  BaseType_t task2Status = xTaskCreate(TaskPlayer2, "TaskPlayer2", 128, NULL, 1, NULL);
  // BaseType_t task3Status = xTaskCreate(TaskUpdateDisplay, "TaskUpdateDisplay", 128, NULL, 1, NULL);

  if (task1Status != pdPASS || task2Status != pdPASS) {
    Serial.println("Task creation failed!");
  }
}

void loop() {
  // Do nothing here, tasks are running
}