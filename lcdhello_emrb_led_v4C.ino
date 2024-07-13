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
// VERSAO 4A  


#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>
#include <Adafruit_NeoPixel.h>
#define PINOUT 9
#define led4   4
#define led5   5
#define led6   6
#define led7   7
#define led8   8
#define led10  10
#define led13  13
#define InterruptPin 2


//#define PIN PA10   //https://www.stm32duino.com/viewtopic.php?t=617
#define NUMPIXELS 44 // numero de leds
  // put your setup code here, to run once:
unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval1 = 1000;  // interval at which to blink (milliseconds)
const long interval2 = 1000;  // interval at which to blink (milliseconds)
const long interval3 = 400;  // interval at which to blink (milliseconds)
//estado atual do led, o atributo volatile pois ele vai ser usado na função ISR

volatile bool estado = false;
bool ActiveInterrupt = true;
int delayval = 11;
int currentColor = 0;
int finalposition = NUMPIXELS;
int position = 1;
int Brightness = 105;
int timing = 1;
int contador = 4;
//int led4 =  4;      // led4 connected at pin 4
//int led5 =  5;       // led5 connected at pin 5
//int led6 =  6;      // led6 connected at pin 6
//int led7 =  7;       // led7 connected at pin 7
//int led13 =  13;       // led13 connected at pin 13
int ledState1 = HIGH;  // to determine the states of led1 and led2
int ledState2 = HIGH;  // to determine the states of led2 and led2
int ledState3 = HIGH;  // to determine the states of led3 and led2
int ledState4 = HIGH;  // to determine the states of led4 and led2
//int ledState1 = LOW;  // to determine the states of led1 and led2
//int ledState2 = LOW;  // to determine the states of led2 and led2
//int ledState3 = LOW;  // to determine the states of led3 and led2
//int ledState4 = LOW;  // to determine the states of led4 and led2


unsigned long previousMillis1 = 0;  //store last time LED1 was blinked
unsigned long previousMillis2 = 0;  //store last time LED2 was blinked


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
  pinMode(led4, OUTPUT);               // define pins as input or output
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led10, OUTPUT); 
  pinMode(led13, OUTPUT); 
  pinMode(InterruptPin, INPUT);
  lcd.begin();
  pixels.begin(); //This initializes the NeoPixel library.
  pixels.setBrightness(Brightness); // 100/255 brightness(about 40%)
  pixels.show();
  digitalWrite(led4, ledState1);    //set LED with ledState to blink again
  digitalWrite(led5, ledState2);    //set LED with ledState to blink again
  digitalWrite(led6, ledState3);    //set LED with ledState to blink again
  digitalWrite(led7, ledState4);    //set LED with ledState to blink again
  Logo_EMRB();
//configura interrupção por qualquer mudança no pino 2
  attachInterrupt(digitalPinToInterrupt(InterruptPin), inverte_led, RISING);  //RISING  CHANGE FALLING
}
  
void Logo_EMRB(){
  lcd.clear();
	lcd.setCursor(40, 1);
	lcd.draw(emrb, 50, 46);
	delay(2000);
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

void D_FONT_SIZE_MEDIUM(unsigned long contmillis){
  lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_MEDIUM);
	lcd.printLong(contmillis);
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


void loop()
{
	
//   unsigned long currentMillis = millis(); // store the current time
//  if (digitalRead(InterruptPin) == true)
//{
 digitalWrite(led8, true);// true apaga false acendeLedInterrupt = true; 
delay(200);
//}
//if (digitalRead(InterruptPin) == false)
//{
 digitalWrite(led8, false);// true apaga false acendeLedInterrupt = false; 
delay(200);
//}
   
 // D_FONT_SIZE_MEDIUM();
 // ahead();
  //backward();
	//ahead();
//  backward();
//	ahead();
  //backward();
	//ahead();
//  backward();
//	ahead();
  //backward();
	//ahead();
//  backward();
}

//ISR que inverte o valor de LedInterrupt
void inverte_led(){
digitalWrite(led13, true); // vai acender o led  
unsigned long currentMillis = millis();
//ActiveInterrupt = true;
 // if (estado == false) 
    //{
   // digitalWrite(led13, true); // vai acender o led
   // if (currentMillis - previousMillis >= interval1) {
    // save the last time you blinked the LED
   // previousMillis = currentMillis;
  //  estado = true;
  //  digitalWrite(led13, false); // vai apagar o led
  //  digitalWrite(led8, ActiveInterrupt);  //acende a lampada
    // if the LED is off turn it on and vice-versa:
   // } 
   // } 
    
  //  if (estado == true) {
  
  if(contador == 0){
  D_FONT_SIZE_MEDIUM(12345678);
  digitalWrite(led13, false); // vai acender o led   
  contador = 4;
  }          
   contador--; 
  //if (currentMillis - previousMillis >= interval2) {
    // save the last time you blinked the LED
  //  previousMillis = currentMillis;
  //  estado = false;
  //  digitalWrite(LedInterrupt, estado);
    // if the LED is off turn it on and vice-versa:
  //  } 
  //  }  
 
  
 //   digitalWrite(LedInterrupt, LOW);
 //   estado = false;
 // }else{
 //   digitalWrite(LedInterrupt, HIGH);
 //   estado = true;
  }

