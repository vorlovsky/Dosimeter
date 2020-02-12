//#include <PinChangeInterrupt.h>
//#include <analogComp.h>

// defines for setting and clearing register bits
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

// #define SENSOR_PIN 2
// #define SENSOR_PIN2 3

#define MEASUREMENT_SECS 40

volatile unsigned int newTicks = 0;

unsigned long ticks[MEASUREMENT_SECS];
unsigned long tickCounts[MEASUREMENT_SECS];
int tickIndex = -1;
unsigned long ticksCount = 0;
unsigned long tickCountsSum = 0;
volatile unsigned int interruptionsCount = 0;

//volatile boolean pinState = 1;
//volatile unsigned long lastTickTime = 0;
//volatile unsigned long lastTickDelay = 0;

void setup() {
  Serial.begin(115200);

  pinMode(2, INPUT);

//  ACSR = 0;
//
//  sbi(ACSR, ACD); //set comparator off
//
//  ADCSRA = 0;
//  ADCSRB = 0;
//  ADMUX = 0;
//  
//  sbi(ADMUX, REFS0);
//  sbi(ADMUX, ADLAR);
//  sbi(ADMUX, MUX0);
//
//  sbi(ADCSRB, ACME);    
//  sbi(ADCSRA, ADEN);
//  
//  cbi(ADCSRA, ADPS2);
//  sbi(ADCSRA, ADPS1);
//  sbi(ADCSRA, ADPS0);
//  
//  sbi(ADCSRB, ADTS0);
  
  attachInterrupt(digitalPinToInterrupt(2), sensorISRPC, FALLING);
}

void sensorISRPC()
{
//  Serial.print(analogRead(A1));
//  Serial.print(" ");
//  Serial.print(analogRead(A2));
//  Serial.println(" 1024 0");

//  interruptionsCount++;

//  if(analogRead(A2) <= 50) {
    newTicks++;
//    delayMicroseconds(170);
//   delay(2);
//  }
}

void loop() {
//  Serial.print(analogRead(A1));
//  Serial.print(" ");
//  Serial.print(analogRead(A2));
//  Serial.println(" 1024 0");
//  return;
  
//  Serial.print(millis()/1000);

  unsigned int _newTicks = newTicks;
  newTicks = 0;
  
  //boolean hasNewTicks = (newTicks > 0);

//  unsigned int _interruptionsCount = interruptionsCount;
//  interruptionsCount = 0;
  
//  Serial.print(_interruptionsCount);
//  Serial.print(" ");
  Serial.print(_newTicks);

  if(tickIndex < (MEASUREMENT_SECS - 1)) {
    tickIndex++;
  } else {
    ticksCount -= ticks[0];
    tickCountsSum -= tickCounts[0];
    
    for(byte i = 1; i <= tickIndex; i++) {
      ticks[i - 1] = ticks[i];
      tickCounts[i - 1] = tickCounts[i];
    }
  }
  ticks[tickIndex] = _newTicks;
  ticksCount += _newTicks;
  tickCounts[tickIndex] = ticksCount;
  tickCountsSum += ticksCount;

//  ticksAverage = (ticksAverage * (loopCount - 1) + ticksCount) / loopCount;
  double ticksAverage = tickCountsSum / (tickIndex + 1);
  
//  Serial.println();
//  for(byte i = 0; i <= tickIndex; i++) {    
//    Serial.print(ticks[i]);
//    Serial.print(",");
//  }
//  Serial.println();
  Serial.print(" ");
  Serial.print(ticksCount);
  Serial.print(" ");
  Serial.print(ticksAverage);
  Serial.print(" ");
  Serial.println(((millis()/1000) % MEASUREMENT_SECS) ? 0 : 30);

  delay(1000);
}
