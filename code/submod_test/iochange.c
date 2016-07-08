#include <stdio.h>

unsigned char io_prv[12];
unsigned char io_now[12];
unsigned char i=0;
unsigned char j=0;
unsigned int tmp=0;
unsigned int tt[3];

void ioRelease(unsigned int io_in, unsigned char *io_prv, unsigned char *io_now){
	unsigned char i;
	unsigned char ion[12];
	for (i=0 ; i<12 ; i++)
	{
			ion[i] = (io_in >> i) & 0x1;
			printf("%d:%d, ",i, ion[i]);
			
			if ( (*(io_prv+i) == 1) && (ion[i] == 0) ){
				printf("<%d is released>", i);
				*(io_now+i) = 1;
			}else{
				*(io_now+i) = 0;
			}
			*(io_prv+i) = ion[i];
	}
}

int main(){
	// io_prv[5]=0;
	// io_now[5]=1;
	tt[0] = 0x0002;
	tt[1] = 0xFFF1;
	tt[2] = 0xFFF0;
	for (j=0;j<3;j++)
	{
		/**/
		tmp = tt[j];
		/**/
		ioRelease(tmp, io_prv, io_now);
		printf("<%d>", io_now[0]);
		printf("<%d>", io_now[1]);
		/**/
		// for (i=0;i<12;i++){
		// 	io_now[i] = (tmp >> i) & 0x1;
		// 	printf("%d:%d, ",i, io_now[i]);
		// 	if ((io_prv[i] == 1) && (io_now[i] == 0)){
		// 		printf("%d is released.", i);
		// 	}
		// 	io_prv[i] = io_now[i];
		// }
		printf("\n");
	}
	return 0;
}