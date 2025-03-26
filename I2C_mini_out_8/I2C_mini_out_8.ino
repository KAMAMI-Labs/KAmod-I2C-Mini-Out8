#include <Wire.h>
//#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23X08.h>

//LED
#define LED_PIN         2 
#define MY_DELAY        2000
#define TEST_LED_ON     1
#define TEST_LED_OFF    0

//I2C
#define I2C_SDA         33
#define I2C_SCL         32
#define I2C_FREQ        100000
#define MCP23008_ARD    0x20

TwoWire I2Cbus = TwoWire(0);
Adafruit_MCP23X08 MCPIO;
int i;

//-----------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Hello. KAmod I2C Mini Out 8 test");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  delay(500);
  while(!I2Cbus.begin(I2C_SDA, I2C_SCL, I2C_FREQ)){
    Serial.println("I2C init failed...");
    delay(500);
  }
  while (!MCPIO.begin_I2C(MCP23008_ARD, &I2Cbus)) {
    Serial.println("MCP init failed...");
    delay(500);
  }

  Serial.println("I2C init OK");
  delay(100);
}

//-----------------------------------------------------------------
void loop() {
  if (i & 1){
    digitalWrite(LED_PIN, TEST_LED_ON);
  } else {
    digitalWrite(LED_PIN, TEST_LED_OFF);
  }
  
  Serial.print("Out: ");
  Serial.println(i);

  MCPIO.pinMode(i, OUTPUT);
  MCPIO.digitalWrite(i, TEST_LED_ON);
  delay(100);
  MCPIO.pinMode(i, OUTPUT);
  MCPIO.digitalWrite(i, TEST_LED_OFF);
  delay(100);
  
  i++;
  if (i  >= 8){
    i = 0;
  }
}
