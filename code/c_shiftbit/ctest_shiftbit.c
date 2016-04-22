#include <stdio.h>


unsigned char i;

void shiftIO(unsigned char dIn){
	char i;
	for(i = 7;i >= 0; i--){
		if ( (dIn & (0b1<<i)) != 0){
			printf("[1]\n");
		}else{
			printf("[0]\n");
		}
	}	
}

int main(void) {
	printf("Helllo worlds\n");
	uint8_t tmp = 0b01100000;
	shiftIO(tmp);

	// Test Shift Bit
	printf("%d\n", (0xFF0A&0xFF));
	printf("%d\n", (0xFF0A>>8));
	return 0;
}
