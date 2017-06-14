void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int tempCrud = analogRead(A0);
  int humCrud = analogRead(A1);
  
  //int temp = (tempCrud * 0.22222) - 61.11;
  int temp = map(tempCrud, 0, 1000, -30, 80);
  
  int hum = (humCrud * 0.1906) - 40.2;
  //int hum = map(humCrud, 0, 1000, 10, 95);

  Serial.print(temp);
  Serial.print("C ");
  Serial.print(hum);
  Serial.println("%");
}
