#include <Servo.h>
//Inicio variables para el servo
Servo servo;   // controlador servo
int eLDRPin = A1; // pines asignados a las fotoresistencias
int wLDRPin = A0; // pines asignados a las fotoresistencias
int eastLDR = 0; //variables para fotoresistencia
int westLDR = 0;//variables para fotoresistencia
int difference = 0; //variable para comparar ambas ldr
int error = 10;  // Variable para una diferencia notable entre las LDR
int servoSet = 130; //Variable para la posicion del servomotor
//Fin variables para el servo

//Inicio variables para el control de carga
int estadoPulsador = 0;  //LOW es 0 y HIGH es 1
//variable para guardar el estado anterior del pulsador
int estadoAnterior = 0;  //LOW es 0 y HIGH es 1
int pulsador=13;
const int led = 4;
//Fin variables para el control de carga

//Inicio variables para controlar el paso a paso
int pos = 2; 
int neg = 3;
int cambio = 1;
bool devolver=false;
//Fin variables para controlar el paso a paso

void setup()
{
  Serial.begin(9600);
  //Definiendo pines de entrada y salida
  servo.attach(9);   //asignacion de la linea de señal al pin 9 PWM
  pinMode(led, OUTPUT);
  pinMode(pulsador,OUTPUT);
  pinMode(A2,INPUT); 
  pinMode(pos, OUTPUT);
  pinMode(neg, OUTPUT);
}

//Inicio función para controlar el servo
 void controlServo(){
  //Un LDR es un resistor que varía su valor de resistencia 
  //eléctrica dependiendo de la cantidad de luz que incide 
  //sobre él.
  // entre mayor es la luz menor sera el valor de la resistencia
  // entre menor es la luz mayor es la resistencia
 eastLDR = analogRead(eLDRPin); //Leer los valores de la fotocelda
 westLDR = analogRead(wLDRPin);
 while (eastLDR < 400 && westLDR < 400) {  // verifica si la luz que persiben las ldr son bajas
   eastLDR = analogRead(eLDRPin);
    westLDR = analogRead(wLDRPin);
   while (servoSet <=140 && servoSet >=15) {     // si es asi lo vamos a activar el motor para cerrar la carpa
     servoSet ++;
     servo.write(servoSet);
     delay(100);
   }
 }
 difference = eastLDR - westLDR ; //comprueba la diferencia 
 if (difference > 10) {          //envia el panel hacia la fotocelda con una lentura alta
   if (servoSet <= 140) {
     servoSet ++;
     servo.write(servoSet);   
   }
 } else if (difference < -10) {
   if (servoSet >= 15) {
     servoSet --;
     servo.write(servoSet);  
    }
   }
  }
//Fin función para controlar el servo

//Inicio Función para cotrol de carga
void controlCarga(){
 //controlando suministro del panel a la bateria para no sobrecargarla
  int valorPot=analogRead(A2);
  //Serial.println(valorPot);
  delay(100);
  while(valorPot>950){
  	digitalWrite(led,LOW);
    valorPot=analogRead(A2);
    estadoPulsador=0;
     digitalWrite(pulsador,estadoPulsador);   
    break;
  }
  while(valorPot<950){
  	digitalWrite(led,HIGH);
    valorPot=analogRead(A2);
    estadoPulsador=1;
     digitalWrite(pulsador,estadoPulsador);
    break;
  }
}
//Fin Función para control de carga

void positivo()
{
 digitalWrite(pos, 0);
 digitalWrite(neg, 1);
 delay(8000);
 digitalWrite(pos,0);
 digitalWrite(pos,1);
}

void negativo()
{
 digitalWrite(pos, 1);
 digitalWrite(neg, 0);
 delay(8000);
 digitalWrite(pos,0);
 digitalWrite(pos,0);
}
void giroPositivo(){
  while(devolver==false){
  	eastLDR = analogRead(eLDRPin);
  	westLDR = analogRead(wLDRPin);  
  if(eastLDR>800 && westLDR>800){
    positivo();
    delay(100);
    devolver=true;
    }
    break;
  }
}
void giroNegativo(){
  while(devolver==false){
  	eastLDR = analogRead(eLDRPin);
  	westLDR = analogRead(wLDRPin);
   if(eastLDR<800 && westLDR<800 && devolver==true){
    negativo();
    delay(100);
    devolver=true;
    }
    break;
  }
}

void loop()
{
  giroPositivo();
  giroNegativo();
  controlServo();
  controlCarga();
}
