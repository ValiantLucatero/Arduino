long tiempo = 0; 
int triger = 7;   // triger
int echo = 8;      // echo
int led = 13;
float distancia = 0; 


void setup()
{
  for (int i=0;i<2;i++){
  pinMode(triger, OUTPUT);
  pinMode(echo, INPUT);
  }
  
  Serial.begin(9600);
}


void loop( )
{
  
 for(int j=0;j<2;j++){ // lanzamos un pequeño pulso para activar el sensor
  digitalWrite(triger, HIGH);
  delayMicroseconds(10);
  digitalWrite(triger, LOW);
  
  // medimos el pulso de respuesta
  tiempo = (pulseIn(echo, HIGH)/2); // dividido por 2 por que es el 
                                       // tiempo que el sonido tarda
                                       // en ir y en volver
  // ahora calcularemos la distancia en cm
  // sabiendo que el espacio es igual a la velocidad por el tiempo
  // y que la velocidad del sonido es de 343m/s y que el tiempo lo 
  // tenemos en millonesimas de segundo
  distancia = float(tiempo * 0.0343);
 }


 float a = distancia; 
 Serial.println(a);
}
