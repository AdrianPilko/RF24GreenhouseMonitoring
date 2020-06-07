/*
* Arduino Wireless greenhouse monitoring RX side
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 * radio = NULL;

const byte address[6] = "00001";
static int counter = 0;
char text[32];

void initRadio()
{
  if (radio != NULL) delete radio;
  
  radio = new RF24(7, 8); // CE, CSN

  radio->begin();
  radio->setPALevel(RF24_PA_HIGH);
  radio->setDataRate(RF24_250KBPS);
  //radio->setCRCLength(RF24_CRC_8);
  //radio->setAddressWidth(3);
  radio->openReadingPipe(0, address);
  radio->startListening();
}
void setup() 
{
  //printf_begin();
  initRadio();
  Serial.begin(9600);
}

void loop() 
{
  //radio->printDetails();
  
  if (radio->isChipConnected() == true)  
  {
    if (radio->available() == true)
    {
       radio->read(&text, sizeof(text));
       Serial.println(text);       
    }  
  }   
  else
  {
    Serial.println("RX not connected to board");    
  }             
}
