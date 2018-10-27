//anadir la libreria
#include <servo.h>

//Sirven para el servo
Servo motorcito;
//Sirve para el LED RGB
int patitaRoja = 12;
int patitaVerde = 4;
int patitaAzul = 5;
//Sirven para Ultrasonico
double distancia;
double tiempo;
int echo = 8;
int trigger = 9;
//Sirven para puenteZitoZurdo
int in1 = 10;
int in2 = 7;
//Sirven para puenteZitoDerecho
int in3 = 11;
int in4 = 3;

void ultrasonico(){
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  tiempo=pulseIn(echo, HIGH);
  //regresa centimetros.
  distancia = (.017 * tiempo)/2;
  Serial.println(distancia);
  delay(10);
}

void puenteZitoAvanza(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void puenteZitoReverZa(){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void puenteZitoZtop(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

//Girar el Carro a la derecha
void puenteZitoDerecha(){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void puenteZitoZurdo(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void giro(){
  double d1, d2;
  // gira a la izquierda el Ultrasonico
  motorcito.write(-90);
  ultrasonico();
  d1 = distancia;
  // gira a la derecha el Ultrasonico
  motorcito.write(180);
  ultrasonico();
  d2 = distancia;

  //decide la distancia
  motorcito.write(-90);
  if(d1 > d2){
    puenteZitoDerecha();
  }
  else{
    puenteZitoZurdo();
  }
}

void estatus(int color){
  if (color  == 1){
    digitalWrite(patitaRoja, HIGH);
    digitalWrite(patitaVerde, LOW);
    digitalWrite(patitaAzul, LOW);
  }
  else{
    digitalWrite(patitaRoja, LOW);
    digitalWrite(patitaVerde, HIGH);
    digitalWrite(patitaAzul, LOW);
  }
}

void arcoiriZ(){
  //Hacer arcoiris con los leds;
  digitalWrite(patitaRoja, HIGH);
  delay(100);
  digitalWrite(patitaRoja, LOW);
  digitalWrite(patitaVerde, HIGH);
  delay(100);
  digitalWrite(patitaVerde, LOW);
  digitalWrite(patitaAzul, HIGH);
  delay(100);
  digitalWrite(patitaAzul, LOW);
  
}

void setup() {
  // declarar el servo
  motorcito.attach(6);
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  // puenteZito
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ultrasonico();
  if(distancia < 7){
    puenteZitoZtop();
    giro();
  }
  else{
    puenteZitoAvanza();
  }  
}
