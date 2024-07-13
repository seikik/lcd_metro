/*************************************************************************
* Demo sketch for MicroLCD library
* Distributed under GPL v2.0
* Copyright (c) 2013-2014 Stanley Huang <stanleyhuangyc@gmail.com>
* All rights reserved.
* For more information, please visit http://arduinodev.com
*************************************************************************/
//   imagem  LOGO_EMRB_50X46pb.bmp
//   LCD Assistant  LOGO_EMRB_50X46pb.txt
//  inclusão dos lampadas 
// inclusao da interrupção 


#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>
#include <Adafruit_NeoPixel.h>
#define PINOUT 9
//#define ledPin4   4      // led4 connected at pin 4
//#define ledPin5   5       // led5 connected at pin 5
//#define ledPin6   6      // led6 connected at pin 6
//#define ledPin7   7       // led7 connected at pin 7


//#define PIN PA10   //https://www.stm32duino.com/viewtopic.php?t=617
#define NUMPIXELS 44 // numero de leds
#define LedInterrupt 13
//#define ledPin 5
//#define ledPin2 6
#define InterruptPin 2

  // put your setup code here, to run once:
int delayval = 11;
int currentColor = 0;
int finalposition = NUMPIXELS;
int position = 1;
int Brightness = 105;
int timing = 1;
int ledPin4 =  4;      // led4 connected at pin 4
int ledPin5 =  5;       // led5 connected at pin 5
int ledPin6 =  6;      // led6 connected at pin 6
int ledPin7 =  7;       // led7 connected at pin 7
int led13 =  13;       // led13 connected at pin 13

unsigned long previousMillis1 = 0;  //store last time LED1 was blinked
unsigned long previousMillis2 = 0;  //store last time LED2 was blinked
//unsigned long currentMillis = millis(); // store the current time
int ledState1 = HIGH;  // to determine the states of led1 and led2
int ledState2 = HIGH;  // to determine the states of led2 and led2
int ledState3 = HIGH;  // to determine the states of led3 and led2
int ledState4 = HIGH;  // to determine the states of led4 and led2



Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINOUT, NEO_RGB + NEO_KHZ800);

void publica(){
  pixels.setPixelColor(position, pixels.Color(102,255,0));
  pixels.show();
}

void ahead(){
for (position = 0; position <= finalposition; position++) {
    publica();
    delay(timing);
  pixels.setPixelColor(position, pixels.Color(0,0,0));
  pixels.show();
  }
}

void backward(){
for (position = (position -1) ; position >= 0; position--) {
    publica();
    delay(timing);
  pixels.setPixelColor(position, pixels.Color(0,0,0));
  pixels.show();
  }

}




//LCD_SH1106 lcd; /* for SH1106 OLED module */
LCD_SSD1306 lcd; /* for SSD1306 OLED module */

const PROGMEM uint8_t emrb[50 * 46 / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0xFE, 0xCF, 0xC1, 0xC0, 0x80, 0x80, 0x80, 0x00,
0x00, 0xE0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x00, 0x01, 0x01, 0xC3, 0xF7, 0xFF, 0xFF, 0xFF,
0xFF, 0xC7, 0xF0, 0x9F, 0xE7, 0xF7, 0xF7, 0x67, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xC0, 0x40, 0x60, 0x70, 0x70, 0x78, 0x79, 0x7F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xBF, 0x3F, 0x3F, 0x7B, 0xF1, 0xF0, 0xF0, 0x30, 0x10, 0x30, 0x30, 0x30, 0x30,
0x30, 0x30, 0x30, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x18, 0x18, 0x18, 0x38,
0x70, 0x60, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xF8, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F,
0x1F, 0x1F, 0x1F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0x3E, 0x7E, 0x7C, 0x78, 0x78, 0xF0, 0xF0, 0xE0,
0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0x41, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x43, 0x01, 0x00, 0x00,
0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
};

const PROGMEM uint8_t tick[16 * 16 / 8] =
{0x00,0x80,0xC0,0xE0,0xC0,0x80,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0x78,0x30,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x1F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00};

const PROGMEM uint8_t cross[16 * 16 / 8] =
{0x00,0x0C,0x1C,0x3C,0x78,0xF0,0xE0,0xC0,0xE0,0xF0,0x78,0x3C,0x1C,0x0C,0x00,0x00,0x00,0x30,0x38,0x3C,0x1E,0x0F,0x07,0x03,0x07,0x0F,0x1E,0x3C,0x38,0x30,0x00,0x00};

void setup()
{
  pinMode(ledPin4, OUTPUT);               // define pins as input or output
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  


  lcd.begin();
  pixels.begin(); //This initializes the NeoPixel library.
  pixels.setBrightness(Brightness); // 100/255 brightness(about 40%)
  pixels.show();
  digitalWrite(ledPin4, ledState1);    //set LED with ledState to blink again
  digitalWrite(ledPin5, ledState2);    //set LED with ledState to blink again
  digitalWrite(ledPin6, ledState3);    //set LED with ledState to blink again
  digitalWrite(ledPin7, ledState4);    //set LED with ledState to blink again
  pinMode(LedInterrupt, OUTPUT);
  //pinMode(ledPin, OUTPUT);
  //pinMode(ledPin2, OUTPUT);
 //digitalRead(ledPin2, ActiveInterrupt);// true apaga false acende
  //logoEMRB():
  delay(2000);
}

void loop()
{
	
   unsigned long currentMillis = millis(); // store the current time
  if (digitalRead(InterruptPin) == true)
  {
  digitalWrite(LedInterrupt, true);// true apaga false acendeLedInterrupt = true; 
  }
  if (digitalRead(InterruptPin) == false)
  {
  digitalWrite(LedInterrupt, false);// true apaga false acendeLedInterrupt = false; 
  }

  ahead();
  //backward();
 
	//ahead();
  backward();
 	ahead();
  //backward();

	//ahead();
  backward();
	ahead();
  //backward();
  
	//ahead();
  backward();
  

  
}

void logoEMRB(){
  lcd.clear();
	lcd.setCursor(40, 1);
	lcd.draw(emrb, 50, 46);
	delay(2000);
  }

void D_FONT_SIZE_MEDIUM(){
  lcd.clear();
	lcd.setFontSize(FONT_SIZE_LARGE);//(FONT_SIZE_SMALL);
	lcd.println("Hello, world!");
	lcd.setFontSize(FONT_SIZE_MEDIUM);
	lcd.println("  SSMD  ");
	//delay(200);
}

void D_cross(){
  lcd.setCursor(40, 6);
	lcd.draw(tick, 16, 16);
	lcd.setCursor(72, 6);
	lcd.draw(cross, 16, 16);
	//delay(200);
}


void D_FONT_SIZE_SMALL(){
  lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_SMALL);
	lcd.printLong(12345678);  //currentMillis
	//delay(200);
}
  

void D_FONT_SIZE_MEDIUM2(){
  lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_MEDIUM);
	lcd.printLong(12345678);
	//delay(200);
}

void D_FONT_SIZE_LARGE(){
  lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_LARGE);
	lcd.printLong(12345678);
	//delay(200);
}



void D_FONT_SIZE_XLARGE(){
  lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_XLARGE);
	lcd.printLong(12345678);
	//delay(200);
  }
