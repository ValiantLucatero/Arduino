#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// 0x27 is the I2C bus address for an unmodified module
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);
//global variables
int i,state=0;
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
    lcd.print("Numero de autos:");
    lcd.setCursor(7,1);
    state = digitalRead(inputPin); //reads for input
    if(state == HIGH) //if circuit is open (no base current)
      i++; //counter goes up
    while(state == HIGH) //while the circuit is open
      state = digitalRead(inputPin); //keeps the same state
      //this is to prevent counter from keep going on if circuit keeps open
    lcd.print(i); //print counter value
    if(i>100){ //place counter limit at 100, then reset it
      i=0;
      lcd.clear();
    }
}
