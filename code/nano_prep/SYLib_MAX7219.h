/*
	SYLib_MAX7219.h
	Support 2 7Segment 4 Digits.
	Use 2 SPI Bus.
*/

#include <SPI.h>

#define SPI_SS1 10
#define SPI_SS2 9

void spiSend(uint8_t pin_ss, uint8_t command, unsigned short value)
{
	digitalWrite(pin_ss, LOW);
	SPI.transfer(command);
	SPI.transfer(value);
	digitalWrite(pin_ss, HIGH);
	_delay_ms(2);
}  

void printSeg(uint8_t seg_no, unsigned short num){
	for (int8_t i=0; i <= 3; i++)
	{
		byte character = num % 10; //get the value of the rightmost digit
		if (num == 0 && i > 0)
		character = 0xf;
		switch(seg_no){
			case 1: spiSend(SPI_SS1, 4-i, character);
			break;
			case 2: spiSend(SPI_SS1, 8-i, character);
			break;
			case 3: spiSend(SPI_SS2, 4-i, character);
			break;
			case 4: spiSend(SPI_SS2, 8-i, character);
			break;
		}
		num = num/10;
	}
}

void printSegChar(uint8_t seg_no, uint8_t i, uint8_t chr){
	switch(seg_no){
		case 1: spiSend(SPI_SS1, 4-i, chr);
		break;
		case 2: spiSend(SPI_SS1, 8-i, chr);
		break;
		case 3: spiSend(SPI_SS2, 4-i, chr);
		break;
		case 4: spiSend(SPI_SS2, 8-i, chr);
		break;
	}
}


void initSingleChip(uint8_t ss){
	spiSend(ss, 0xF,0x1);  // Enable Testing Mode
	_delay_ms(250);
	spiSend(ss, 0xF,0x0);  // Disable Testing Mode
	// spiSend(ss, 0xC,0x0);
	spiSend(ss, 0xC,0x1);  // Go normal operation

	spiSend(ss, 0xB,0x7);  // Set Scan Limit
	spiSend(ss, 0x9,0xFF); // Decode mode that you shall be send the number charecter.
	spiSend(ss, 0xA, 0x1); // Set intensity
	
	for (unsigned char i=1; i <=8; i++){
		spiSend(ss, i, 0x9);
		_delay_ms(20);
	}
}


/*
 * @brief: User config
 */
void setupMAX7219(){
	SPI.begin();

	pinMode(SPI_SS1, OUTPUT);
	digitalWrite(SPI_SS1, HIGH);
	initSingleChip(SPI_SS1);

	pinMode(SPI_SS2, OUTPUT);
	digitalWrite(SPI_SS2, HIGH);
	initSingleChip(SPI_SS2);

}
