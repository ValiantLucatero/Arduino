#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// 0x27 is the I2C bus address for an unmodified module
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);
//global variables
int state=0;
int i=100;
int inputPin=2;

void setup()
{
    lcd.setBacklightPin(3,POSITIVE);
    // You can turn the backlight off by setting it to LOW instead of HIGH
    lcd.setBacklight(HIGH);
    lcd.begin(16, 2); //initiate LCD screen
    lcd.clear(); //clear LCD screen
    pinMode(2,INPUT); //Pin where recieves signal of the phototransistor
}

void loop()
{
    lcd.setCursor(0,0);
    lcd.print("Cupo disponible:");
    state = digitalRead(inputPin); //reads for input
    if(state == HIGH) //if circuit is open (no base current)
      i--; //counter goes down
    while(state == HIGH) //while the circuit is open
      state = digitalRead(inputPin); //keeps the same state
      //this is to prevent counter from keep going on if circuit keeps open
    lcd.clear();
    lcd.setCursor(7,1);
    lcd.print(i); //print counter value
    if(i<0){ //place counter limit at 0, then reset it
      i=100;
      lcd.clear();
    }
}
