#include <Wire.h>              // include Arduino wire library (required for I2C devices)
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_SSD1306.h>  // include Adafruit SSD1306 OLED display driver
#include <Keypad.h>

#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/   this link for font selection

#define UP       '2'
#define DOWN     '8'
#define OK       '5'
#define BACK     '4'
#define FORWARD  '6'
#define PAGE1     0
#define PAGE2     1
#define MICROWAVE 0
#define HEATER    1

#define CHICKEN   1
#define BEEF      2
#define ROASTBEEF 3
#define SALMON    4
#define TUNA      5
#define HAM       6
 
const byte ROWS = 4; /* four rows */
const byte COLS = 4; /* four columns */
/* define the symbols on the buttons of the keypads */
char hexaKeys[ROWS][COLS] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte rowPins[ROWS] = {23, 25, 27, 29}; /* connect to the row pinouts of the keypad */
byte colPins[COLS] = {31, 33, 35, 37}; /* connect to the column pinouts of the keypad */
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);           // initialize an instance of class NewKeypad 


bool Direction,MwForward_flag1,MwForward_flag2;
char customKey=UP;
uint8_t MicrowaveMenuList;

void BeginIntialization()
{
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);                    //initialize the SSD1306 OLED display with I2C address = 0x3C

}
void CompanyName()
{
    display.clearDisplay();
    display.setCursor(0,1);
    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.print("  Criador    Labs");
    display.display();                   // update the display
    delay(1000);
}

void HomeSection()
{   
    //FreeSerif12pt7b
    display.setFont(&FreeSans9pt7b);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(21,25);
    display.print("Microwave");
    display.setCursor(21,52);
    display.print("Heater");
    display.display();                   // update the display
    
}


void DirectionSymbol(uint8_t Xpixels,uint8_t Ypixels)
{
  //display.setFont(&FreeMono9pt7b);
  //display.clearDisplay();
  display.setCursor(Xpixels,Ypixels);
  display.print("->");
  //display.setTextSize(1);
  //display.write(16);
  //display.drawTriangle(10, 10, 55, 20, 5, 40, WHITE);
  //display.fillTriangle(10, 10, 55, 20, 5, 40, WHITE);
  display.display();  
}

void MicrowaveMenu(bool Page)
{
  display.setFont(&FreeSans9pt7b);
  display.clearDisplay();
  if(Page==PAGE1)
  {

      display.setCursor(21,15);             // move cursor to position (20, 0) pixel
      display.print("Chicken");
      display.setCursor(21,36);
      display.print("Beef");
      display.setCursor(21,60);
      display.print("Roast Beef");
  }
  else if(Page==PAGE2)
  {

      
      display.setCursor(21,15);             // move cursor to position (20, 0) pixel
      display.print("Salmon");
      display.setCursor(21,36);
      display.print("Tuna");
      display.setCursor(21,60);
      display.print("Ham");
    
  }
  display.display(); 
  
}



char Microwave()
{
  uint8_t options=1;
  bool check_flag=1;
  customKey=0;
  while(1)
  {
     customKey = customKeypad.getKey();
     if(customKey==UP&&options!=1)
     {
        check_flag=1;
        options--;
        customKey=0;
      
     }
     else if(customKey==DOWN&&options<=5)
     {
        check_flag=1;
        options++;
        customKey=0; 
     }
     else if(customKey==BACK)
     {
        if(options>=SALMON)
        {
          options=1;
          check_flag=1;
        }
        else
        {
          options=0;
          return UP;
        }
        
     }
     else if(customKey==FORWARD)
     {
        if(options<SALMON&&MwForward_flag2)
        {
          options=4;
          check_flag=1;
        }
     }
     
     if(check_flag)
     {
      check_flag=0;
      //display.clearDisplay();
      switch(options)
      {
        case 1: MicrowaveMenu(PAGE1);
                DirectionSymbol(0,13);break;
                
        case 2: MicrowaveMenu(PAGE1);
                DirectionSymbol(0,34);break;
                
        case 3: MicrowaveMenu(PAGE1);
                DirectionSymbol(0,58);break;
                
        case 4: MicrowaveMenu(PAGE2);
                DirectionSymbol(0,13);
                MwForward_flag2=1;break;
                
        case 5: MicrowaveMenu(PAGE2);
                DirectionSymbol(0,34);break;
                
        case 6: MicrowaveMenu(PAGE2);
                DirectionSymbol(0,58);break;
      }
      
     }
    
  }
  
}


void setup(void)
{

  BeginIntialization();
  CompanyName();
  
}

void loop()
{    
  
  if(customKey==UP)
  {
       customKey='\0';
       Direction=MICROWAVE;
       HomeSection();
       DirectionSymbol(0,23);
    
  }
  else if(customKey==DOWN)
  {
       customKey='\0';
       Direction=HEATER;
       HomeSection();
       DirectionSymbol(0,50);
    
  }
  customKey = customKeypad.getKey();
  if(customKey==OK||customKey==FORWARD)
  {
      if((Direction==MICROWAVE&&customKey==OK)||MwForward_flag1)
      {
            
            customKey=Microwave();
            MwForward_flag1=1;
            
      }
      else if(Direction==HEATER)
      {
          
          
      }
  }

    
  }
  
