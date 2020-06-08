/*
* Arduino Wireless greenhouse monitoring TX side
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include "DHT.h"

const byte address[6] = "00001";
RF24 * radio = NULL; 

static int sendCount = 0;
int MO_pin = A0;
int MO_output;
int dryValue = 0;
int wetValue = 1023;
int friendlyDryValue = 0;
int friendlyWetValue = 100;

#define DHT_PIN_DATA  2
#define DHTTYPE DHT11 
DHT dht(DHT_PIN_DATA,DHTTYPE);
char text[32];
char debugText[32];

void initRadio()
{
  if (radio != NULL) delete radio;
  
  radio = new RF24(7, 8); // CE, CSN

  radio->begin();
  radio->setPALevel(RF24_PA_MAX);
  radio->setDataRate(RF24_250KBPS);
  //radio->setCRCLength(RF24_CRC_8);
  //radio->setAddressWidth(3);
  radio->openWritingPipe(address);
  radio->stopListening(); 
}

void setup() 
{   
  //printf_begin();
  initRadio();
  Serial.begin(9600);  
  dht.begin();
  delay(1000);
}

void loop() {  
  char strTempC[6];
  char strHum[6];

  //radio->printDetails();
  if (radio->isChipConnected() == false)
  {
    Serial.println("TX not connected to board, calling initRadio()");
    initRadio();    
  }
  
  if (radio->isChipConnected() == true)
  {
    // read sensor data
    float dhtHumidity = dht.readHumidity();
    float dhtTempC = dht.readTemperature();
  
    // format the output string     
    dtostrf(dhtTempC, 4, 2, strTempC);
    dtostrf(dhtHumidity, 4, 2, strHum);          
    
    // soild moisture sensor value
    MO_output = analogRead(MO_pin);
    MO_output = map(MO_output, dryValue, wetValue, friendlyDryValue, friendlyWetValue);
          
    sprintf(text,"T=%s,H=%s,MO=%d,%d",strTempC,strHum, MO_output, sendCount);    
    // write the data to the rf24
    radio->write(text, sizeof(text));          

    // output some basic debug to serial
    sprintf(debugText,"TX'ing %d",sendCount);    
    Serial.println(debugText);
    Serial.println(text);
    
    if (++sendCount >=9999 ) sendCount = 0;
  }  
  // only output every 30seconds to save power
  delay(30000);
}
