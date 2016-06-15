/* INCLUDE */
#include <SPI.h>


/* DEFINE */
#define PIN_SS1 10
#define PIN_SS2 9

void setup() {
	initMAX7219();
}

void loop() {
  displaySegment1(1234);
  _delay_ms(100);
}


/* FUNCTION */
void initMAX7219(){
  SPI.begin();
  pinMode(PIN_SS1, OUTPUT);
  
  sendCommand (0xF,0x1);  // Enable Testing Mode
  _delay_ms(250);
  sendCommand (0xF,0x0);  // Disable Testing Mode
  sendCommand (0xC,0x1);  // Go normal operation

  sendCommand (0xB,0x7);  // Set Scan Limit
  sendCommand (0x9,0xFF); // Decode mode that you shall be send the number charecter.
  sendCommand (0xA, 0x6); // Set intensity
  
  displaySegment1(0);
  displaySegment2(0);
}

void sendCommand(int command, int value)
{
  digitalWrite(PIN_SS1, LOW); //chip select is active low
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(PIN_SS1,HIGH);
}

void spiSend(unsigned char ss_pin, int cmd, int val){
  digitalWrite(ss_pin, LOW); //chip select is active low
  SPI.transfer(cmd);
  SPI.transfer(val);
  digitalWrite(ss_pin,HIGH);
}



void displaySegment1 (int number)
  {
    for (int i=0; i <= 3; i++)
    {
      byte character= number % 10; //get the value of the rightmost digit
      if (number == 0 && i > 0)
      character = 0xf;
      sendCommand(4-i, character);
      number= number/10;
    }
}
void displaySegment2 (int number)
  {
    for (int i = 0; i <= 3; i++)
    {
      byte character= number % 10; //get the value of the rightmost digit
      if (number == 0 && i > 0)
      character = 0xf;
      sendCommand(8-i, character);
      number= number/10;
    }
}
