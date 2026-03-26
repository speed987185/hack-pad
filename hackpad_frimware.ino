const unsigned char batmanBitmap [] PROGMEM = {
0x00,0x3C,0x00,
0x00,0x7E,0x00,
0x00,0xFF,0x00,
0x01,0xFF,0x80,
0x03,0xC3,0xC0,
0x07,0x81,0xE0,
0x0F,0x00,0xF0,
0x1E,0x00,0x78,
0x3C,0x00,0x3C,
0x7F,0xFF,0xFE,
0x7F,0xFF,0xFE,
0x3C,0x00,0x3C,
0x18,0x00,0x18
};

#include <Keyboard.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// buttons
#define BTN1 10
#define BTN2 9
#define BTN3 8

unsigned long showTimeUntil = 0;

void setup() {
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

  Keyboard.begin();

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {

  if (!digitalRead(BTN1)) {
    screenshot();
    showTimeUntil = millis() + 5000;
    delay(300);
  }

  if (!digitalRead(BTN2)) {
    openOBS();
    showTimeUntil = millis() + 5000;
    delay(300);
  }

  if (!digitalRead(BTN3)) {
    openWebsite();
    showTimeUntil = millis() + 5000;
    delay(300);
  }

  if (millis() < showTimeUntil) {
    showClock();
  } else {
    showBatman();
  }

  delay(50);
}



void screenshot() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('S');
  delay(100);
  Keyboard.releaseAll();
}

void openOBS() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  delay(300);

  Keyboard.print("obs");
  delay(100);
  Keyboard.write(KEY_RETURN);
}

void openWebsite() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  delay(300);

  Keyboard.print("https://hackclub.com/ysws");
  delay(100);
  Keyboard.write(KEY_RETURN);
}


void showClock() {
  display.clearDisplay();

  int seconds = millis() / 1000;
  int mins = seconds / 60;
  int hrs = mins / 60;

  seconds %= 60;
  mins %= 60;

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,20);

  if (hrs < 10) display.print("0");
  display.print(hrs);
  display.print(":");

  if (mins < 10) display.print("0");
  display.print(mins);
  display.print(":");

  if (seconds < 10) display.print("0");
  display.print(seconds);

  display.display();
}


void showBatman() {
  display.clearDisplay();

  display.drawBitmap(32, 10, batmanBitmap, 24, 13, WHITE);

  display.setTextSize(1);
  display.setCursor(30, 40);
  display.print("ABI PAD");

  display.display();
}