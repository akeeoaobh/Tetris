//
// Smpl_LCD_Bmp : display bitmap on LCD
//
// Step 1. use Paint to draw 128x64 bitmap 
// Step 2. use bmp2asm to convert bitmap into hex
// Step 3. cut hex code paste into char array for LCD display
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Seven_Segment.h"
//#include "scankey.h"
#include <time.h> 
#include "NUC1xx.h"
#include "DrvSYS.h"
#include "NUC1xx-LB_002\LCD_Driver.h"


#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"
#include "Seven_Segment.h"

int color = 1;
unsigned char DisplayBuf [8*128];
int idk=0,i=0,j=64;
unsigned char Bitmap[128*8] = {
		0x00,0x18,0x3C,0x7E,0x72,0x70,0xF0,0xFE,0x3C,0x18,0x80,0x80,0xC0,0xE0,0xE0,0xC0,0xC0,0xC0,0xE0,0xE0,0x80,0x00,0x30,0xF8,0xFC,0xE4,0xE0,0xE0,0xFC,0x78,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xDF,0xFF,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0xFE,0xE7,0x83,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 	0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	};


void seg_display(int16_t value)
{
  int8_t digit;
		digit = value / 1000;
		close_seven_segment();
		show_seven_segment(3,digit);
		DrvSYS_Delay(5000);
			
		value = value - digit * 1000;
		digit = value / 100;
		close_seven_segment();
		show_seven_segment(2,digit);
		DrvSYS_Delay(5000);

		value = value - digit * 100;
		digit = value / 10;
		close_seven_segment();
		show_seven_segment(1,digit);
		DrvSYS_Delay(5000);

		value = value - digit * 10;
		digit = value;
		close_seven_segment();
		show_seven_segment(0,digit);
		DrvSYS_Delay(5000);
}

void GPABCallback(uint32_t u32GPAStatus, uint32_t u32GPBStatus)
{
		int8_t number,irow;
		uint8_t x, y,c=0;
    int a=1,b=1;
		// interrupt may be more than once due to key bouncing
		// (GPIOA->PIN & 0x3F): get GPIOA[5:0]
		// u32GPAStatus: Indicates GPIOx[n] generate an interrupt 
		// 


//----------------------------------------------------------------
// check key from keypad
//----------------------------------------------------------------
	number = 0;		
	for (irow=1; irow <4; irow++)
	{
		//GPIOA->DOUT &= ~(0x7);      //xxxx-x000
		//GPIOA->DOUT |= nrow[irow]; //
		GPIOA->DOUT |= (0x7);           //xxxx-x111
		GPIOA->DOUT &= ~(1<<(3-irow));  //011, 101, 110
		//scan row1 GPIOA[3] for 1,2,3
		if((GPIOA->PIN & (0x1<<3)) == 0)number = irow; 
		//scan row2 GPIOA[4] for 4,5,6
		if((GPIOA->PIN & (0x1<<4)) == 0)number = irow+3; 
		//scan row3 GPIOA[5] for 7,8,9
		if((GPIOA->PIN & (0x1<<5)) == 0)number = irow+6; 
	}
//----------------------------------------------------------------
// display number on 7-seg.
//----------------------------------------------------------------
if(number==4){
	  idk--;
}	
else if(number==6){
	idk++; 
}	
 for (y=0; y<64; y++) {
    for (x=0; x<4; x++) {
			if((y+idk)>0){
				DisplayBuf[(y+idk)*8+x+5] = Bitmap[y+x*128];
				//c++;
			}
			else{
				DisplayBuf[(y)*8+x+5] = Bitmap[y+x*128];
				//c++;
			}
				
		}
	}
	draw_LCD(DisplayBuf);
		/*if(number)show_seven_segment(0,number);//448 states
		//GPIOE->DOUT &= ~(0xFF);				 //clear 7 seg., GPIOE bit0-7=0000000
		//GPIOE->DOUT |= SEG_BUF[number];//show 7 seg.,GPIOE bit0-7=
		//GPIOC->DOUT |= (1<<(0+4)); 		 //display 1st 7 seg.,GPIOC bit 7=1
*/
		GPIOA->DOUT &= ~(0x7);         			//xxxx-x000
		NVIC_ClearPendingIRQ(GPAB_IRQn); 		//IRQ4
}

//=============================================================
// GPIO C, D, E interrupt routine
//=============================================================
void GPCDECallback(uint32_t u32GPCStatus, uint32_t u32GPDStatus, uint32_t u32GPEStatus)
{
	
}
int32_t main (void)
{
	uint8_t x, y,c=0;
	int32_t score=0;
	int prei=0;

	UNLOCKREG();
    DrvSYS_Open(48000000);
	LOCKREG();

	Initial_panel();  
	clr_all_panel();

	OpenKeyPad(); //(ScanKey.c)383 states
	DrvGPIO_EnableInt(E_GPA, 3, E_IO_FALLING, E_MODE_EDGE); //(DrvGPIO.c)
	DrvGPIO_EnableInt(E_GPA, 4, E_IO_FALLING, E_MODE_EDGE); //(DrvGPIO.c)
	DrvGPIO_EnableInt(E_GPA, 5, E_IO_FALLING, E_MODE_EDGE); //(DrvGPIO.c
    // copy Bitmap into Display Buffer
		
	srand(6);	//random 
	DrvGPIO_SetIntCallback(GPABCallback, GPCDECallback) ;
	GPIOA->DOUT &= ~(0x7);         			//xxxx-x000
	while(1){
		for (y=0; y<64; y++) {
			for (x=0; x<4; x++) {
				if((y+idk)>0){
					DisplayBuf[(y+idk)*8+x+5] = Bitmap[y+x*128]; //display the crab
				
				}	
			}
		}
	
		/*&
		if(i in the range){
			*/if( j>idk-10 &&j<idk+10 && prei!=i){
				score++;
				prei = i;
			}
			/*else {
				game over;
				reset sevensegment
			}
		}
		*/
		seg_display(score);
	if(i==58){//if the coco has drop to ground y
		j=(rand()%127)+1;//random the coco's x
		i=0;//reset coco's y
	}
	
	i++;//
	DrvSYS_Delay(48000);


	 // Draw all pixels onto LCD
	CircleBresenham(4+i,j,3,color);
	//if(crab cor == j)
	DrvSYS_Delay(48000000);

	draw_LCD(DisplayBuf);
	memset(&DisplayBuf[0],0,sizeof(DisplayBuf));

	}
}
