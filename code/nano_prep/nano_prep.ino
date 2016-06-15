/* INCLUDE */
#include <SPI.h>


/* DEFINE */
#define PIN_SS1       10
#define PIN_SS2       9


/* VARIABLE */
int i = 0;


void setup() {
    initMAX7219();
}


void loop() {
    printSeg(0, i);
    printSeg(1, 9999-i);
    _delay_ms(100);
    i++;
    if (i > 9999){
      i=0;
    }
}

/* FUNCTION **************************************************/
/*
 * @brief: Initial IC MAX7219 (7 Segment driver)
 */
void initMAX7219(){
  SPI.begin();
  pinMode(PIN_SS1, OUTPUT);
  pinMode(PIN_SS2, OUTPUT);
  
  /* Enable Testing Mode */
  spiSend (PIN_SS1, 0xF, 0x1);
  spiSend (PIN_SS2, 0xF, 0x1);
  _delay_ms(250);
  /* Disable Testing Mode */
  spiSend (PIN_SS1, 0xF,0x0);
  spiSend (PIN_SS2, 0xF,0x0);
  /* Go normal operation */
  spiSend (PIN_SS1, 0xC,0x1);
  spiSend (PIN_SS2, 0xC,0x1);
  /* Set Scan Limit */
  spiSend (PIN_SS1, 0xB,0x7);
  spiSend (PIN_SS2, 0xB,0x7);
  /* Decode mode that you shall be send the number charecter. */
  spiSend (PIN_SS1, 0x9,0xFF);
  spiSend (PIN_SS2, 0x9,0xFF);
  /* Set Intensity */
  spiSend (PIN_SS1, 0xA, 0x6);
  spiSend (PIN_SS2, 0xA, 0x6);

}


/*
 * @brief: Send data via SPI (Serial Peripheral Interface).
 */
void spiSend(uint8_t pin_ss, uint8_t command, unsigned short value)
{
  digitalWrite(pin_ss, LOW); //chip select is active low
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(pin_ss,HIGH);
}


/*
 * @brief: Print 7 Segment, support four 4DIGIT.
 */
void printSeg(uint8_t seg_no, unsigned short num){
    for (int8_t i=0; i <= 3; i++)
    {
        byte character = num % 10; //get the value of the rightmost digit
        if (num == 0 && i > 0)
        character = 0xf;
        switch(seg_no){
            case 0: spiSend(PIN_SS1, 4-i, character);
            break;
            case 1: spiSend(PIN_SS1, 8-i, character);
            break;
            case 2: spiSend(PIN_SS2, 4-i, character);
            break;
            case 3: spiSend(PIN_SS2, 8-i, character);
            break;
        }
      num = num/10;
    }
}
