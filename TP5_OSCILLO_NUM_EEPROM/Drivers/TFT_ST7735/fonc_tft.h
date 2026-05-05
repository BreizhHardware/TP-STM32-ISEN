/************************************************************************
* TITLE: fonc_tft.h               
* AUTHOR:               
* DESCRIPTION: include pour afficheur graphique TFT          
* VERSION : 1.1 ajout dimension ecran et caractere
*	    1.2 suppression redefinition uint8_t et uint16_t	
*           
************************************************************************/


	
/* DEFINE **************************************************************/


// Color definitions
#define ST7735_BLACK   0x0000
#define ST7735_BLUE    0x001F
#define ST7735_RED     0xF800
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0  
#define ST7735_WHITE   0xFFFF

// size TFT display  
#define ST7735_TFTWIDTH      128	// Width TFT display 
#define ST7735_TFTHEIGHT_18  160	// Heigt TFT 1.8" display

// size character on screen
#define DIM_CHAR_X_TFT   6		// H character dimension (5 pixel + intercaracter 1 pixel) when size=1  	
#define DIM_CHAR_Y_TFT   8		// V character dimension (7 pixel + intercaracter 1 pixel) when size=1  	


// ST7735 RST (Reset) pin
#define ST7735_RST_PORT      GPIOD
#define ST7735_RST_PIN       GPIO_PIN_2

// ST7735 (Data/Command select) pin
#define ST7735_D_nC_PORT       GPIOC
#define ST7735_D_nC_PIN        GPIO_PIN_2

// ST7735 CS (Chip Select) pin
#define ST7735_nCS_PORT       GPIOC
#define ST7735_nCS_PIN        GPIO_PIN_1


/* PROTOTYPE *************************************************************/

// init screen
void init_TFT( void);

// draw pixel
void drawPixel_TFT(uint16_t x, uint16_t y, uint16_t color);

// fill a rectangle
void fillRect_TFT(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

// fill screen
void fillScreen_TFT(uint16_t color);

// Draw a character
void displayChar_TFT(uint16_t x, uint16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);

// Draw a vertical line
void drawVLine_TFT(uint16_t x, uint16_t y, uint16_t h, uint16_t color);
