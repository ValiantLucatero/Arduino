#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 es la dirección del bus del I2C

//variables
int pot = A0; //potenciometro
int push = 2; //pushbutton
int act1 = 4; //actividad 1
int act2 = 7; //actividad 2
int salir = 8; //despedida

//variables para los cálculos
int valor;
int voltaje;
int sum1;
int sum2;
int res;

//booleanas para las funciones
bool actividad1 = LOW;
bool actividad2 = LOW;
bool despedida = LOW;
bool continuar = LOW;

void setup()
{
  //Setup del LCD
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH); //Se puede apagar la luz de fondo si se pone LOW
  lcd.begin(16, 2);
  lcd.clear();

  //Setup de los pushbuttons
  pinMode(push, INPUT);
  pinMode(act1, INPUT);
  pinMode(act2, INPUT);
  pinMode(salir, INPUT);
}

void loop()
{
  //Ponemos pantalla
  lcd.setCursor(0,0);
  lcd.print("Selecciona activ");
  lcd.setCursor(0,1);
  lcd.print("1)     2)     3)");

  //Preparamos botones
  actividad1 = digitalRead(act1);
  actividad2 = digitalRead(act2);
  despedida = digitalRead(salir);
  continuar = digitalRead(push);

  //Voltimetro 0-5V
  if (actividad1 == HIGH)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Voltimetro 0-5V");
    while (continuar == LOW)
      {
        valor = analogRead(pot);
        voltaje = map(valor, 0, 1023, 0, 6);
        lcd.setCursor(0,1);
        lcd.print(voltaje);
        continuar = digitalRead(push);
      }
  }

  //Sumadora
  if (actividad2 == HIGH)
  {
    delay (500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sumadora");
    lcd.setCursor(0,1);
    lcd.print("Ingresa un #:");
    continuar = LOW;
    delay(500);
    while (continuar == LOW)
    {
        valor = analogRead(pot);
        sum1 = map(valor, 0, 1023, 0, 9);
        lcd.setCursor(13,1);
        lcd.print(sum1);
        continuar = digitalRead(push);
    }
    lcd.setCursor(0,1);
    lcd.print("Ingresa otro:");
    continuar = LOW;
    delay(500);
    while (continuar == LOW)
    {
        valor = analogRead(pot);
        sum2 = map(valor, 0, 1023, 0, 9);
        lcd.setCursor(13,1);
        lcd.print(sum2);
        continuar = digitalRead(push);
    }
    res = sum1 + sum2;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sumadora");
    lcd.setCursor(0,1);
    lcd.print(sum1);
    lcd.print(" + ");
    lcd.print(sum2);
    lcd.print(" = ");
    lcd.print(res);
    continuar = LOW;
    delay(500);
    while (continuar == LOW)
    {
      continuar = digitalRead(push);
    }
  }

  //Despedida
  if (despedida == HIGH)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Despedida");
    lcd.setCursor(0,1);
    lcd.print("Hasta la Proxima");
    while (continuar == LOW)
    {
      continuar = digitalRead(push);
    }
  }
}
