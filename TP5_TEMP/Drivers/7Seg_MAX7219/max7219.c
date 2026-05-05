/*
*********************************************************************************************************
* Module     : MAX7219.C
* Author     : Randy Rasa modifié par Alain REBOUX pour STM32 
* Description: MAX7219 LED Display Driver Routines
*
*  The Maxim MAX7219 is an LED display driver thant can control up to 64 individual LEDs, or
*  eight 7-segment LED digits, or any combination of individual LEDs and digits.  It frees the
*  host from the chore of constantly multiplexing the 8 rows and 8 columns.  In addition, it
*  takes care of brightness control (16 steps), and implements display test and display blank
*  (shutdown) features.
*
*  The host communicates with the MAX7219 using three signals: DATA, CLK, and LOAD.  This
*  modules bit-bangs them, but Motorola's SPI interface (or similar interface from other
*  manufacturers) may also be used to simplify and speed up the data transfer.
*                   ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
*    DATA _________|D15|D14|D13|D12|D11|D10|D09|D08|D07|D06|D05|D04|D03|D02|D01|D00|______
*         ________    __    __    __    __    __    __    __    __    __    __    ________
*    CLK          |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|
*                __________________________________________________________________    
*    LOAD ______|                                                                  |__

/*
*********************************************************************************************************
* Include Header Files
*********************************************************************************************************
*/

/*
*********************************************************************************************************
* Include Header Files
*********************************************************************************************************
*/

#include "main.h"
#include "max7219.h"
extern SPI_HandleTypeDef hspi1;

/*defined in main.h
#define MAX7219_nCS_PORT       GPIOC 
#define MAX7219_nCS_PIN        GPIO_PIN_0  
*/

//Constantes

/*
*********************************************************************************************************
* LED Segments:         a
*                     ----
*                   f|    |b
*                    |  g |
*                     ----
*                   e|    |c
*                    |    |
*                     ----  o dp
*                       d
*   Register bits:
*      bit:  7  6  5  4  3  2  1  0
*           dp  a  b  c  d  e  f  g
*********************************************************************************************************
*/


char const conv_7seg[]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x1F,0x4E,0x3D,0x4F,0x47};


// define
#define REG_DECODE        0x09                        // "decode mode" register
#define REG_INTENSITY     0x0a                        // "intensity" register
#define REG_SCAN_LIMIT    0x0b                        // "scan limit" register
#define REG_SHUTDOWN      0x0c                        // "shutdown" register
#define REG_DISPLAY_TEST  0x0f                        // "display test" register

#define INTENSITY_MIN     0x00                        // minimum display intensity
#define INTENSITY_MAX     0x0f                        // maximum display intensity


/*
*********************************************************************************************************
* Private Function Prototypes
*********************************************************************************************************
*/
 void MAX7219_Write (unsigned char reg_number, unsigned char data);
static void MAX7219_SendByte (unsigned char data);



// ...................................... Public Functions ..............................................


/*
*********************************************************************************************************
* MAX7219_Init()
*
* Description: Initialize MAX7219 module; must be called before any other MAX7219 functions.
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_Init (void)
{
                               // configure "LOAD" as output

  MAX7219_Write(REG_SCAN_LIMIT, 7);                   // set up to scan all eight digits
  MAX7219_Write(REG_DECODE, 0x00);                    // set to "no decode" for all digits
  MAX7219_ShutdownStop();                             // select normal operation (i.e. not shutdown)
  MAX7219_DisplayTestStop();                          // select normal operation (i.e. not test mode)
  MAX7219_Clear();                                    // clear all digits
  MAX7219_SetBrightness(INTENSITY_MAX);               // set to maximum intensity
}

/*
*********************************************************************************************************
* MAX7219_ShutdownStart()
*
* Description: Shut down the display.
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_ShutdownStart (void)
{
  MAX7219_Write(REG_SHUTDOWN, 0);                     // put MAX7219 into "shutdown" mode
}


/*
*********************************************************************************************************
* MAX7219_ShutdownStop()
*
* Description: Take the display out of shutdown mode.
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_ShutdownStop (void)
{
  MAX7219_Write(REG_SHUTDOWN, 1);                     // put MAX7219 into "normal" mode
}
/*
*********************************************************************************************************
* MAX7219_DisplayTestStart()
*
* Description: Start a display test.
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_DisplayTestStart (void)
{
  MAX7219_Write(REG_DISPLAY_TEST, 1);                 // put MAX7219 into "display test" mode
}



/*
*********************************************************************************************************
* MAX7219_DisplayTestStop()
*
* Description: Stop a display test.
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_DisplayTestStop (void)
{
  MAX7219_Write(REG_DISPLAY_TEST, 0);                 // put MAX7219 into "normal" mode
}


/*
*********************************************************************************************************
* MAX7219_SetBrightness()
*
* Description: Set the LED display brightness
* Arguments  : brightness (0-15)
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_SetBrightness (char brightness)
{
  brightness &= 0x0f;                                 // mask off extra bits
  MAX7219_Write(REG_INTENSITY, brightness);           // set brightness
}


/*
*********************************************************************************************************
* MAX7219_Clear()
*
* Description: Clear the display (all digits blank)
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_Clear (void)
{
  char i;
  for (i=0; i < 8; i++)
    MAX7219_Write(i, 0x00);                           // turn all segments off
}


/*
*********************************************************************************************************
* MAX7219_DisplayChar() = MAX7219_DisplayCharPointOff(), MAX7219_DisplayCharPointON() 
*
* Description: Display a character on the specified digit.
* Arguments  : digit = digit number (0-7)
*              character = character to display (0-9, A-Z)
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_DisplayChar(char digit, char character)
{
  //MAX7219_Write(digit, MAX7219_LookupCode(character));
	MAX7219_Write(digit, conv_7seg[character]);
}

void MAX7219_DisplayCharPointOff (char digit, char character)
{
  //MAX7219_Write(digit, MAX7219_LookupCode(character));
	MAX7219_Write(digit, conv_7seg[character]);
}
void MAX7219_DisplayCharPointOn (char digit, char character)
{
  //MAX7219_Write(digit, MAX7219_LookupCode(character));
	MAX7219_Write(digit, conv_7seg[character]|128);
}



/*
*********************************************************************************************************
* MAX7219_Write()
*
* Description: Write to MAX7219
* Arguments  : reg_number = register to write to
*              dataout = data to write to MAX7219
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_Write (unsigned char reg_number, unsigned char dataout)
{
 MAX7219_nCS_PORT->BSRR = (uint32_t)MAX7219_nCS_PIN<<16;// nCS = 0                                          // take LOAD high to begin
  MAX7219_SendByte(reg_number);                       // write register number to MAX7219
  MAX7219_SendByte(dataout);                          // write data to MAX7219
  MAX7219_nCS_PORT->BSRR = (uint32_t)MAX7219_nCS_PIN;// nCS = 1                                       // take LOAD low to latch in data
 }


/*
*********************************************************************************************************
* MAX7219_SendByte()
*
* Description: Send one byte to the MAX7219
* Arguments  : dataout = data to send
* Returns    : none
*********************************************************************************************************
*/

static void MAX7219_SendByte (unsigned char dataout)
{

	HAL_SPI_Transmit(&hspi1, &dataout, 1, 1000);

}


