void MAX7219_Init(void);
void MAX7219_ShutdownStart(void);
void MAX7219_ShutdownStop(void);
void MAX7219_DisplayTestStart(void);
void MAX7219_DisplayTestStop(void);
void MAX7219_SetBrightness(char brightness);
void MAX7219_Clear(void);
void MAX7219_DisplayChar(char digit, char character);
void MAX7219_DisplayCharPointOff(char digit, char character);
void MAX7219_DisplayCharPointOn(char digit, char character);

// ST7735 CS (Chip Select) pin
#define MAX7219_nCS_PORT       GPIOC //A
#define MAX7219_nCS_PIN        GPIO_PIN_0  //8

