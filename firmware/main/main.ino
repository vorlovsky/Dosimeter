/* 
 * 
 * SCL - A5
 * SDA - A4
 * Voltmeter - A3 
 * Input - D2
 * Button - D3
 * Buzzer - D7
 * 
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MAX_UINT 65535

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 32, &Wire, OLED_RESET);

#define DEBUG 0

static const unsigned char PROGMEM radiation_sign_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7F, 0xE0, 0x00,
0x00, 0x01, 0x80, 0x1C, 0x00,
0x00, 0x07, 0x00, 0x0E, 0x00,
0x00, 0x0F, 0x80, 0x1F, 0x00,
0x00, 0x1F, 0x80, 0x1F, 0x80,
0x00, 0x3F, 0x80, 0x1F, 0xC0,
0x00, 0x7F, 0xC0, 0x3F, 0xE0,
0x00, 0xFF, 0xC0, 0x3F, 0xF0,
0x00, 0xFF, 0xC0, 0x3F, 0xF0,
0x00, 0xFF, 0xE0, 0x7F, 0xF8,
0x01, 0xFF, 0xE0, 0x7F, 0xF8,
0x01, 0xFF, 0xFF, 0xFF, 0xF8,
0x01, 0xFF, 0xF0, 0x7F, 0xF8,
0x01, 0xFF, 0xE0, 0x7F, 0xF8,
0x01, 0xFF, 0xC0, 0x3F, 0xF8,
0x01, 0xF8, 0x00, 0x03, 0xF8,
0x01, 0x00, 0x20, 0x40, 0x38,
0x01, 0x00, 0x10, 0x80, 0x08,
0x01, 0x00, 0x09, 0x00, 0x08,
0x01, 0x00, 0x0F, 0x00, 0x08,
0x00, 0x80, 0x1F, 0x80, 0x18,
0x00, 0x80, 0x3F, 0xC0, 0x10,
0x00, 0xC0, 0x7F, 0xC0, 0x30,
0x00, 0x40, 0xFF, 0xE0, 0x20,
0x00, 0x20, 0xFF, 0xF0, 0x40,
0x00, 0x11, 0xFF, 0xF8, 0xC0,
0x00, 0x0F, 0xFF, 0xF9, 0x80,
0x00, 0x07, 0xFF, 0xFE, 0x00,
0x00, 0x03, 0xFF, 0xFC, 0x00,
0x00, 0x00, 0x7F, 0xE0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00};

//static const unsigned char PROGMEM logo[] =
//{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xE0, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x1C, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x0E, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x1F, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x1F, 0x80,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x1F, 0xC0,
//0x07, 0x9E, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x7F, 0xC0, 0x3F, 0xE0,
//0x07, 0x9E, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0xFF, 0xC0, 0x3F, 0xF0,
//0x07, 0x9E, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x00, 0x3F, 0xE0, 0x00, 0x00, 0xFF, 0xC0, 0x3F, 0xF0,
//0x07, 0x9E, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x00, 0x3F, 0xF0, 0x00, 0x00, 0xFF, 0xE0, 0x7F, 0xF8,
//0x07, 0x9E, 0x3E, 0x73, 0x9C, 0x00, 0x78, 0x3E, 0x3E, 0xF0, 0xF0, 0x01, 0xFF, 0xE0, 0x7F, 0xF8,
//0x07, 0x9E, 0x7F, 0x33, 0x98, 0x00, 0x78, 0x7F, 0x3E, 0xF1, 0xF8, 0x01, 0xFF, 0xFF, 0xFF, 0xF8,
//0x07, 0x9E, 0x7F, 0x33, 0xB8, 0x00, 0x78, 0x7F, 0x3E, 0xF3, 0xFC, 0x01, 0xFF, 0xF0, 0x7F, 0xF8,
//0x07, 0xFE, 0xE7, 0x33, 0xB8, 0x00, 0x78, 0x73, 0xBE, 0xF3, 0x9C, 0x01, 0xFF, 0xE0, 0x7F, 0xF8,
//0x07, 0xFE, 0xE7, 0x3F, 0xF9, 0xF0, 0x78, 0x73, 0xBE, 0xF3, 0x9C, 0x01, 0xFF, 0xC0, 0x3F, 0xF8,
//0x07, 0xFE, 0xE7, 0x3F, 0xF9, 0xF0, 0x78, 0x73, 0xBE, 0xF3, 0x9C, 0x01, 0xF8, 0x00, 0x03, 0xF8,
//0x07, 0xFE, 0xE7, 0x3F, 0xF8, 0x00, 0x78, 0x73, 0xBE, 0xF3, 0x9C, 0x01, 0x00, 0x20, 0x40, 0x38,
//0x07, 0x9E, 0xE7, 0x3F, 0xF0, 0x00, 0x78, 0x73, 0xBE, 0xF3, 0x9C, 0x01, 0x00, 0x10, 0x80, 0x08,
//0x07, 0x9E, 0xE7, 0x1F, 0xF0, 0x00, 0x78, 0x73, 0xBE, 0xF3, 0x9C, 0x01, 0x00, 0x09, 0x00, 0x08,
//0x07, 0x9E, 0xE7, 0x1E, 0xF0, 0x00, 0x78, 0x73, 0xBF, 0xF3, 0x9C, 0x01, 0x00, 0x0F, 0x00, 0x08,
//0x07, 0x9E, 0xE7, 0x1E, 0xF0, 0x00, 0x78, 0x73, 0xBF, 0xF3, 0x9C, 0x00, 0x80, 0x1F, 0x80, 0x18,
//0x07, 0x9E, 0x7F, 0x1E, 0xF0, 0x00, 0x78, 0x7F, 0x3F, 0xE3, 0xFC, 0x00, 0x80, 0x3F, 0xC0, 0x10,
//0x07, 0x9E, 0x7E, 0x1E, 0xF0, 0x00, 0x78, 0x3F, 0x3F, 0xC1, 0xF8, 0x00, 0xC0, 0x7F, 0xC0, 0x30,
//0x07, 0x9E, 0x1C, 0x1C, 0xE0, 0x00, 0x78, 0x1C, 0x3F, 0x00, 0xF0, 0x00, 0x40, 0xFF, 0xE0, 0x20,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xFF, 0xF0, 0x40,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xFF, 0xF8, 0xC0,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF9, 0x80,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFE, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFC, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xE0, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const unsigned char PROGMEM battery_frame_bmp[] =
{ 0x00,
 0x1E,
 0x1E,
 0x3F,
 0x21,
 0x21,
 0x21,
 0x21,
 0x21,
 0x21,
 0x21,
 0x21,
 0x21,
 0x21,
 0x3F,
 0x00 };

static const unsigned char PROGMEM battery_level_bmp[] =
{ 0x0C,
 0x0C,
 0x00 };

static const unsigned char PROGMEM mute_bmp[] = 
{0x04, 0x00, 
 0x0c, 0x00, 
 0x1c, 0x00, 
 0x3c, 0x00, 
 0xfd, 0x10, 
 0xfc, 0xa0, 
 0xfc, 0x40, 
 0xfc, 0xa0, 
 0x3d, 0x10, 
 0x1c, 0x00, 
 0x0c, 0x00, 
 0x04, 0x00
};

#define SENSOR_PIN 2
#define BUTTON_PIN 3
#define BUZZER_PIN 7
#define BATTERY_PIN A3

#define MEASUREMENT_SECS 36
#define MEASUREMENTS_LOG_SECS 60
#define DEBOUNCE_DELAY 100
#define BUTTON_HOLD_DELAY 2000
#define DISPLAY_MODES_COUNT 4

volatile unsigned int newTicks = 0;

unsigned int ticksLog[MEASUREMENT_SECS];
unsigned int tickCountsLog[MEASUREMENTS_LOG_SECS];
unsigned int tickCountsSortedLog[MEASUREMENTS_LOG_SECS];
int ticksLogIndex = -1;
int tickCountsLogIndex = -1;

unsigned int ticksCount = 0;
unsigned int ticksCountPerSec = 0;
unsigned long tickCountsLogSum = 0;
unsigned long tickCountsLogMax = 0;
unsigned long tickCountsOverallMax = 0;

unsigned long lastLogsUpdateTime = 0;
unsigned long lastVoltageReadTime = 0;

int buttonState;
unsigned long lastButtonStateChangeTime = 0;

unsigned int displayMode = 0;
boolean muted = false;
boolean  buttonHoldActionComplete = false;

float voltage = 0;

void setup() {
  Serial.begin(115200);
  
  delay(1000);// added due to a resistors misplaced on the display board
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    return;
  }

//  display.display();
  
//  display.clearDisplay();
  
  //display.drawBitmap(0, 0, logo, 128, 32, WHITE);
  //display.display();
  //delay(2000);
  //display.clearDisplay();
        
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  buttonState = digitalRead(BUTTON_PIN);

  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensorISR, FALLING);

#if DEBUG
  Serial.println("Setup complete");
#endif
}

void sensorISR() {
  newTicks++;
}

void loop() {
  unsigned long startMillis = millis();

  unsigned int _newTicks = newTicks;
  newTicks = 0;

  checkButtonState();
  updateTicks(_newTicks);
  
  updateLogs();
  readVoltage();

  boolean hasNewTicks = (_newTicks > 0);
     
  updateDisplay(hasNewTicks);
  activateBuzzer(hasNewTicks);

  Serial.println(millis() - startMillis);
}

void checkButtonState() {
  int newButtonState = digitalRead(BUTTON_PIN);

  if(newButtonState != buttonState) {
    unsigned long lastStateDuration = (millis() - lastButtonStateChangeTime);
    
    if(lastStateDuration < DEBOUNCE_DELAY) {
      return;
    }
    
    lastButtonStateChangeTime = millis();     
    buttonState = newButtonState;
    
    if(newButtonState == HIGH) {
      if(lastStateDuration < BUTTON_HOLD_DELAY) {
        changedisplayMode();
      }      
    } else {
       buttonHoldActionComplete = false;
    }
  } else if(newButtonState == LOW) {
    unsigned long lastStateDuration = (millis() - lastButtonStateChangeTime);

    if((lastStateDuration >= BUTTON_HOLD_DELAY) && ! buttonHoldActionComplete) {
      toggleMute();

       buttonHoldActionComplete = true;
    }    
  }
}

void toggleMute() {
  if(muted) {
    muted = false;
  } else {
    activateBuzzer(false);
  
    muted = true;
  }
}

void changedisplayMode() {
  displayMode++;

  if(displayMode >= DISPLAY_MODES_COUNT) {
    displayMode = 0;
  }
}

void readVoltage() {
  if(!isTimeOut(lastVoltageReadTime, 1000)) {
    return;
  }
  
  voltage = (analogRead(BATTERY_PIN) * 5.0) / 1024.0; 

//  Serial.println(voltage);
   
  if (voltage < 0.1) {
    voltage = 0.0;
  }
}

void updateTicks(unsigned int newValue) {
  ticksCountPerSec += newValue;
  ticksCount += newValue;

#if DEBUG
  if(newValue > 0) {
    Serial.print(millis());
    Serial.print(" ");
    Serial.print(newValue);
    Serial.print(" ");
    Serial.print(ticksCount);
    Serial.print(" ");
    Serial.print(ticksLogIndex);
    Serial.print(" ");
    Serial.print(tickCountsLogIndex);
    Serial.print(" ");
    Serial.println(tickCountsLogSum);
  }
#endif
}

void updateLogs() {
  if(!isTimeOut(lastLogsUpdateTime, 1000)) {
    return;
  }
      
  updateTicksLog();
  updateTickCountsLog();
}

void updateTicksLog() {      
  if(ticksLogIndex < (MEASUREMENT_SECS - 1)) {
    ticksLogIndex++;
  } else {
    ticksCount -= ticksLog[0];
    
    for(byte i = 1; i <= ticksLogIndex; i++) {
      ticksLog[i - 1] = ticksLog[i];
    }
  }

  ticksLog[ticksLogIndex] = ticksCountPerSec;
  ticksCountPerSec = 0;
}

void updateTickCountsLog() {
  byte i;
  
  if(tickCountsLogIndex < (MEASUREMENTS_LOG_SECS - 1)) {
    tickCountsLogIndex++;
  } else {    
    unsigned int tickCountsToRemove = tickCountsLog[0];
    
    tickCountsLogSum -= tickCountsToRemove;

    if(tickCountsLogMax == tickCountsToRemove) {
      tickCountsLogMax = 0;
      
      for(i = 1; i <= tickCountsLogIndex; i++) {
        if(tickCountsLogMax < tickCountsLog[i]) {
           tickCountsLogMax = tickCountsLog[i];
        }
      }
    }
    
    for(i = 0; i < tickCountsLogIndex; i++) {
      tickCountsLog[i] = tickCountsLog[i + 1];

      if(tickCountsSortedLog[i] >= tickCountsToRemove) {
        tickCountsSortedLog[i] = tickCountsSortedLog[i + 1];
      }
    }
    tickCountsSortedLog[tickCountsLogIndex] = MAX_UINT;        
  }
  
  tickCountsLog[tickCountsLogIndex] = ticksCount;

  tickCountsLogSum += ticksCount;

  if(tickCountsLogMax < ticksCount) {
    tickCountsLogMax = ticksCount;
  }

  if(tickCountsOverallMax < ticksCount) {
    tickCountsOverallMax = ticksCount;
  }

//  Serial.print("Add ");
//  Serial.print(ticksCount);

  for(i = 0; i < tickCountsLogIndex; i++) {
    if(tickCountsSortedLog[i] > ticksCount) {
      break;
    }
  }
  
//  Serial.print(" at index ");
//  Serial.print(i);
//  Serial.print(" of ");
//  Serial.println(tickCountsLogIndex);

  for(byte j = tickCountsLogIndex; j > i; j--) {
    tickCountsSortedLog[j] = tickCountsSortedLog[j - 1];
  }

  tickCountsSortedLog[i] = ticksCount;

//  for(i = 0; i <= tickCountsLogIndex; i++) {
//    Serial.print(tickCountsLog[i]);
//    Serial.print(",");
//  }
//  Serial.println();
//
//  for(i = 0; i <= tickCountsLogIndex; i++) {
//    Serial.print(tickCountsSortedLog[i]);
//    Serial.print(",");
//  }
//  Serial.println();
//  Serial.println();
}

void updateDisplay(boolean hasNewTicks) {
  display.clearDisplay(); 
  
  drawValues();  
  drawBatteryLevel();
  drawRadiationImage(hasNewTicks);
  drawMuteStatus();

  display.display();
}

void drawValues() {   
  display.setTextColor(WHITE);
  
  drawCurrentValue();

  switch(displayMode) {
    case 0:
      drawMedianValue();
      break;

    case 1:
      drawLogMaxValue();
      break;

    case 2:
      drawOverallMaxValue();
      break;

    case 3:
      drawAverageValue();
      break;
  }
}

void drawCurrentValue() {   
  display.setCursor(0,0);
  
  drawFormattedValue(ticksCount);
}

void drawMedianValue() {
  if(tickCountsLogIndex < 0) {
    return;
  }

  int medianIndex = tickCountsLogIndex / 2;
  unsigned long median = (tickCountsLogIndex % 2 == 0) ? tickCountsSortedLog[medianIndex] : (tickCountsSortedLog[medianIndex] + tickCountsSortedLog[medianIndex + 1]) / 2;
  
  drawSecondaryValue(median, "med");
}

void drawAverageValue() {
  if(tickCountsLogIndex < 0) {
    return;
  }

  unsigned int average = tickCountsLogSum / (tickCountsLogIndex + 1);

  drawSecondaryValue(average, "avg");
}

void drawLogMaxValue() {
  drawSecondaryValue(tickCountsLogMax, "max");
}

void drawOverallMaxValue() {
  drawSecondaryValue(tickCountsOverallMax, "Max");
}

void drawSecondaryValue(unsigned long value, const char* label) {  
  display.setCursor(0,18);

  drawFormattedValue(value);
  
  display.setTextSize(1);
  display.setCursor(60,24);  
  display.println(label);
}

void drawBatteryLevel() {
  display.drawBitmap(118, 0, battery_frame_bmp, 8, 16, WHITE);
  
  if (voltage > 3.6) {
    display.drawBitmap(118, 11, battery_level_bmp, 8, 3, WHITE);
    
    if (voltage > 3.7) {
      display.drawBitmap(118, 8, battery_level_bmp, 8, 3, WHITE);
      
      if (voltage > 3.85) {
        display.drawBitmap(118, 5, battery_level_bmp, 8, 3, WHITE);
      }
    }
  }
}

void drawRadiationImage(boolean hasNewTicks) {
  if (hasNewTicks) {
      display.drawBitmap(75, 0, radiation_sign_bmp, 40, 32, WHITE);
  }
}

void drawMuteStatus() {
  if(muted) {
    display.drawBitmap(116, 20, mute_bmp, 12, 12, WHITE);
  }
}

void activateBuzzer(boolean hasNewTicks) {
  if(muted) {
    return;
  }
  
  if (hasNewTicks) {
      digitalWrite(BUZZER_PIN, HIGH); // buzzer ON
  } else {
      digitalWrite(BUZZER_PIN, LOW); // buzzer OFF
  }
}

void drawFormattedValue(unsigned long value) {
  display.setTextSize(2);
  
  String units = "uR/h";
  
  if(value > 10000) {
    display.print((float)value / 1000.0, 2);

    units = "mR/h";
//  } else if(value > 1000000) {
//    display.print((float)value / 1000000.0, 2);
//    
//    units = "R/h";
  } else {
    display.print(value);
  }
  
  display.setTextSize(1);
  display.println(units);
}

boolean isTimeOut(unsigned long& lastTimestamp, unsigned long duration) {
  unsigned long currentTimestamp = millis();
  
  if((currentTimestamp - lastTimestamp) < duration) {
    return false;
  }
  
  lastTimestamp = currentTimestamp;

  return true;
}
