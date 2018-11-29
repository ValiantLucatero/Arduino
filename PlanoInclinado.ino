#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Math.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 es la dirección del bus del I2C

//variables que utilizan los ultrasónicos
long tm1 = 0;
long tm2 = 0; 
int triger1 = 7; 
int echo1 = 8;
int triger2 = 10;
int echo2 = 11;  
int led = 13;
float bandera1 = 100;
float bandera2 = 100;

//variables para los cálculos
float S = 0.5;
float g = 9.78;
float theta;
float tiempoInicial;
float tiempoFinal;
float tiempoBajada;
float tiempoCalculado;
float mk;
float masaBloque = 10; //Ingresar datos
float masaCilindro = 20;
float altura;
float distancia;
int valor;
int val;
int angulo;

//potenciómetros
int poAng = A0; 
int poAlt = A1;

//pushbuttons
int Ex1 = 3;
int Ex2 = 4;
int Ex3 = 5;
int Continuar = 12;

bool Experimento1 = LOW;
bool Experimento2 = LOW;
bool Experimento3 = LOW;
bool Continue = LOW;

void setup()
{
  //Setup del LCD
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH); //Se puede apagar la luz de fondo si se pone LOW
  lcd.begin(16, 2);
  lcd.clear();

  //Setup de los ultrasónicos
  pinMode(triger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(triger2, OUTPUT);
  pinMode(echo2, INPUT);
  Serial.begin(9600);

  //Setup de los pushbuttons
  pinMode(Ex1, INPUT);
  pinMode(Ex2, INPUT);
  pinMode(Ex3, INPUT);
  pinMode(Continuar, INPUT);
}

void loop()
{
  //Ponemos pantalla
  lcd.setCursor(0,0);
  lcd.print("Selecciona exp");
  lcd.setCursor(0,1);
  lcd.print("1)     2)     3)");

  //Preparamos botones
  Experimento1 = digitalRead(Ex1);
  Experimento2 = digitalRead(Ex2);
  Experimento3 = digitalRead(Ex3);
  Continue = digitalRead(Continuar);
  
  //Experimento 1
    if (Experimento1 == HIGH)
    {
      //Pedimos el ángulo
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pon el angulo:");

      //mostramos el angulo que se esta ingresando
      while (Continue == LOW)
      {
        valor = analogRead(poAng);
        angulo = map(valor, 0, 1023, 45, 9);
        lcd.setCursor(0,1);
        lcd.print(angulo);
        Continue = digitalRead(Continuar);
      }

      //hacemos la conversión a radianes
      theta = angulo*(3.1416/180);
      
      //Esperamos el paso del objeto
      while(bandera1 > 20)
      {
        //manda señal
        digitalWrite(triger2, HIGH);
        delayMicroseconds(10);
        digitalWrite(triger2, LOW);

        //medimos el pulso de respuesta
        tm1 = (pulseIn(echo2, HIGH)/2);

        //obtenemos la distancia
        bandera1 = float(tm1 * 0.0343);
        Serial.println(bandera1);
      }

      //Comenzamos a contar el tiempo
      tiempoInicial = millis();

      //Esperar a que pase por el segundo sensor
      while(bandera2 > 20)
      {
        //manda señal
        digitalWrite(triger1, HIGH);
        delayMicroseconds(10);
        digitalWrite(triger1, LOW);

        //medimos el pulso de respuesta
        tm2 = (pulseIn(echo1, HIGH)/2);

        //obtenemos la distancia
        bandera2 = float(tm2 * 0.0343);
        Serial.println(bandera2);
      }

      //Cuando detecta al objeto toma el tiempo
      tiempoFinal = millis();

      //Restamos los tiempos para obtener el tiempo de bajada
      tiempoBajada = (tiempoFinal - tiempoInicial)/1000;

      //Fórmula para obtener el mk
      mk = ((2*S/g*tiempoBajada*tiempoBajada)+sin(theta))/cos(theta);

      //Imprimimos
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("T=");
      lcd.setCursor(2,0);
      lcd.print(tiempoBajada);
      lcd.setCursor(0,1);
      lcd.print("mk=");
      lcd.setCursor(2,1);
      lcd.print(mk);
      delay(5000);
    }
  //Experimento 2
    if (Experimento2 == HIGH)
    {
      //Pedimos el ángulo
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pon el angulo:");

      //mostramos el angulo que se esta ingresando
      while (Continue == LOW)
      {
        valor = analogRead(poAng);
        angulo = map(valor, 0, 1023, 45, 9);
        lcd.setCursor(0,1);
        lcd.print(angulo);
        Continue = digitalRead(Continuar);
      }

      //hacemos la conversión a radianes
      theta = angulo*(3.1416/180);

      //fórmula para calcular el tiempo de bajada
      tiempoCalculado = sqrt((2*S)/((mk*cos(theta)-sin(theta))*g));
      Serial.println(tiempoCalculado);

      //Imprimimos resultado
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tc=");
      lcd.setCursor(3,0);
      lcd.print(tiempoCalculado);

      //Esperamos el paso del objeto
      bandera1 = 100;
      bandera2 = 100;
      while(bandera1 > 20)
      {
        //manda señal
        digitalWrite(triger2, HIGH);
        delayMicroseconds(10);
        digitalWrite(triger2, LOW);

        //medimos el pulso de respuesta
        tm1 = (pulseIn(echo2, HIGH)/2);

        //obtenemos la distancia
        bandera1 = float(tm1 * 0.0343);
      }

      //Comenzamos a contar el tiempo
      tiempoInicial = millis();

      //Esperar a que pase por el segundo sensor
      while(bandera2 > 20)
      {
        //manda señal
        digitalWrite(triger1, HIGH);
        delayMicroseconds(10);
        digitalWrite(triger1, LOW);

        //medimos el pulso de respuesta
        tm2 = (pulseIn(echo1, HIGH)/2);

        //obtenemos la distancia
        bandera2 = float(tm2 * 0.0343);
      }

      //Cuando detecta al objeto toma el tiempo
      tiempoFinal = millis();

      //Restamos los tiempos para obtener el tiempo de bajada
      tiempoBajada = (tiempoFinal - tiempoInicial)/1000;

      //Imprimimos
      lcd.setCursor(0,1);
      lcd.print("Tr=");
      lcd.setCursor(3,1);
      lcd.print(tiempoBajada);
      delay(5000);
    }
  //Experimento 3
    if (Experimento3 == HIGH)
    {
      //Pedimos el ángulo y la altura
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pon el angulo:");
      lcd.setCursor(0,1);
      lcd.print("Pon la altura:");

      //mostramos el angulo y la altura que se estan ingresando
      while (Continue == LOW)
      {
        valor = analogRead(poAng);
        val = analogRead(poAlt);
        angulo = map(valor, 0, 1023, 45, 9);
        altura = map(val, 0, 1023, 44, 0);
        lcd.setCursor(14,0);
        lcd.print(angulo);
        lcd.setCursor(14,1);
        lcd.print(altura);
        Continue = digitalRead(Continuar);
      }

      //hacemos la conversión a radianes
      theta = angulo*(3.1416/180);

      //formula para obtener la distancia recorrida de subida
      distancia = altura/((masaCilindro*g)-(mk*cos(theta)));

      //Imprimimos
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dc=");
      lcd.setCursor(3,0);
      lcd.print(distancia);
      delay(5000);
    }
}

