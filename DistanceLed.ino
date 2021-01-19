int trigPin=15;
int echoPin=16;
int led1 = 26;
int led2 = 27;
int led3 = 28;
int led4 = 29;
int led5 = 30;

int delayTime = 500;

unsigned int distance;

int ping() { //functie care inregistreaza distanta de pe senzorul ultrasonic
  long duration, distance; 
  digitalWrite(trigPin, LOW); //trecem pinul TRIGGER in starea low
  delayMicroseconds(2); // delay de 2 microsecunde pentru o citire corecta
  digitalWrite(trigPin, HIGH); //trecem pinul TRIGGER in starea HIGH

  delayMicroseconds(10); //delay la feld eimportant ca si primul pentru o citire corecta
  digitalWrite(trigPin, LOW); //trecem pinul trigger din nou pe LOW pentru a pregati urmatoarea citire
  duration = pulseIn(echoPin, HIGH); //durata actiunii de emitere a pulsului si intoarcerea acestuia inapoi la senzor se calculeaza cu functia integrata in arduino pulseIn
  distance = (duration / 2) / 29.1; // functie de convertire a duratei in centimetri, impartirea la 2 se face deoarece unda parcurge de 2 ori distanta de la senzor la obiect, iar impartirea cu constanta 29.1
                                    // este extrasa din viteza sunetului prin aer la o temperatura normala
  return distance;
}

int precisePing(int count) { //functie cu rolul de a mari precizia datelor inregistrate de senzor
                             // se vor face count inregistrari care se vor suma, mai apoi acea valoare urmand a fi impartita prin count
  int suma = 0;
  for (int i = 0; i < count; i++)
    suma += ping();
  suma /= count;
  return suma;
}


void setup() {
  Serial.begin(9600); //deschidem comunicarea prin serial pentru "enable-ul" sistemului
  pinMode(trigPin, OUTPUT); //setam pinii si tipul acestora
  pinMode(echoPin, INPUT);
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   pinMode(led3, OUTPUT);
   pinMode(led4, OUTPUT);
   pinMode(led5, OUTPUT);
}
void loop() {
  Serial.println(precisePing(10));
  delay(500);
  distance=precisePing(10); //luam distanta medie de pe 10 inregistrari
  while(distance>100) //in ciuda masurilor de precautie luate prin intermediul functiei precisePing, unele inregistrari pot fi eronate, iar prin intermediul acestui while se incearca o corectie
  {
     distance=precisePing(10);
  }
  Serial.print("Distanta este: ");
  Serial.println(distance);
  if(distance>30)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  if(distance>20 && distance<=30)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
  }
  if(distance>10 && distance <=20)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  if(distance>5 && distance<=10)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  if(distance>0 && distance<=5)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
}
