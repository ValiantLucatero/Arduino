void setup()
{
  // put your setup code here, to run once:
  pinMode(A0, INPUT); //Declaras pines, nombre y que hace. INPUT o OUTPUT
  //los pines que declares con el pinmode solo los puedes leer si son output y solo los puedes escribir si son input
  Serial.begin(9600); //para puerto serial
}

void loop()
{
  // put your main code here, to run repeatedly:
  int var = analogRead(A0); //Lee un puerto analogico que le digas
  analogWrite(A0,1); //Para mandar a un puerto analogico que le digas lo que tu quieras
  digitalRead(1); //Same
  digitalWrite(1,HIGH); //Puede ser HIGH o LOW
  Serial.print(var); //lo imprime en la misma linea
  Serial.println(var); //Va haciendo saltos de linea
  map(var, minEntr, maxEntr, minSal, maxSal); //dato, minimo de entrada, maximo de entrada, minimo de salida, maximo de salida. Traduce escalas
}
