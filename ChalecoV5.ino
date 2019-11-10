/* Programa ChalecoV5.ino
   Realiza el control de encendido de los leds del chaleco
   de seguridad para ciclistas                           */
// Variables
int bot[ ] = {1,2,3};
int led[ ] = {4,5,6,7,8,9,10,11,12,13};
int numLeds = 10;
int numBots = 3;
int tiempoRet = 300;
int tiempoStop = 400;
int tiempoRetOciosa = 100;
int estePin;
int cuenta_der = 0;
int cuenta_alto = 0;
int cuenta_izq = 0;
int cuenta_ocio = 0;
bool bot_derecha = LOW;
bool bot_alto = LOW;
bool bot_izquierda = LOW;
// Función setup
void setup ()
{ 
  for (estePin = 0; estePin < numBots; estePin++)
  {
    pinMode (bot[estePin],INPUT);
  }
  for (estePin = 0; estePin < numLeds; estePin++)
  {
    pinMode (led[estePin],OUTPUT);
  }
}
// Función loop
void loop ()
{
  for (estePin = 0; estePin < numLeds; estePin++)
  {
    digitalWrite (led[estePin], LOW);
  }
  
  bot_derecha = digitalRead (bot[0]);
  bot_izquierda = digitalRead (bot[1]);
  bot_alto = digitalRead (bot[2]);
  if (bot_alto==HIGH)
  {
    Alto(); 
  }
  else if (bot_derecha==HIGH)
  {
    Derecha ();
  }
  else if (bot_izquierda==HIGH)
  {
    Izquierda ();
  }
  else
  {
    Ociosa();
  }
}
// Función Derecha
void Derecha ()
{
  switch (cuenta_der)
  {
    case 0:
      digitalWrite (led[0],HIGH);
      digitalWrite (led[8],HIGH);
      digitalWrite (led[6],HIGH);
      break;
    case 1:
      digitalWrite (led[1],HIGH);
      digitalWrite (led[9],HIGH);
      digitalWrite (led[5],HIGH);
      break;
    case 2:
      digitalWrite (led[2],HIGH);
      digitalWrite (led[3],HIGH);
      digitalWrite (led[4],HIGH);
      break;
    default: 
      ;
  }
  delay (tiempoRet);
  cuenta_der++;
  if (cuenta_der > 3)
  {
    cuenta_der = 0;
  }
}
// Función Alto
void Alto () {
  if (cuenta_alto == 1)
  {
    for (estePin = 0; estePin < numLeds; estePin++)
    {
      digitalWrite (led[estePin],HIGH);
    }
  }
  else
  {
    for (estePin = 0; estePin < numLeds; estePin++)
    {
      digitalWrite (led[estePin],LOW);
    } 
  }
  delay (tiempoStop);
  cuenta_alto++;
  if (cuenta_alto > 1)
  {
    cuenta_alto = 0;
  }
}
// Función Izquierda
void Izquierda ()
{
  switch (cuenta_izq)
  {
    case 0:
      digitalWrite (led[2],HIGH);
      digitalWrite (led[9],HIGH);
      digitalWrite (led[4],HIGH);
      break;
    case 1:
      digitalWrite (led[1],HIGH);
      digitalWrite (led[8],HIGH);
      digitalWrite (led[5],HIGH);
      break;
    case 2:
      digitalWrite (led[0],HIGH);
      digitalWrite (led[7],HIGH);
      digitalWrite (led[6],HIGH);
      break;
    default:
      ;
  }
  delay (tiempoRet);
  cuenta_izq++;
  if (cuenta_izq > 3)
  {
    cuenta_izq = 0;
  }
}
// Función Ociosa
void Ociosa ()
{
  digitalWrite (led[cuenta_ocio],HIGH);
  digitalWrite (led[cuenta_ocio+4],HIGH);
  delay (tiempoRetOciosa);
  cuenta_ocio++;
  if (cuenta_ocio > 3)
  {
    cuenta_ocio = 0;
  }
}

