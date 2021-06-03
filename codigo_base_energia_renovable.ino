#include <Servo.h>
Servo servo;   // controlador servo
int eLDRPin = A1; // pines asignados a las fotoresistencias
int wLDRPin = A0; // pines asignados a las fotoresistencias
int eastLDR = 0; //variables para fotoresistencia
int westLDR = 0;//variables para fotoresistencia
int difference = 0; //variable para comparar ambas ldr
int error = 10;  // Variable para una diferencia notable entre las LDR
int servoSet = 130; //Variable para la posicion del servomotor

int estadoPulsador = 0;  //LOW es 0 y HIGH es 1
//variable para guardar el estado anterior del pulsador
int estadoAnterior = 0;  //LOW es 0 y HIGH es 1
int pulsador=13;
//variable para manipular el servo


//Asignando led rojo a pin 2, estos led se usaran para el 
//control de la carga de la bateria, rojo = necesita cargar
//y verde= carga completa  (esto para no sobrecargar la bateria)
//Asignando led verde a pin 3
const int led = 2;

void setup()
{
  Serial.begin(9600);
  //Definiendo pines de entrada y salida
  servo.attach(9);   //asignacion de la linea de señal al pin 9 PWM
  pinMode(led, OUTPUT);
  pinMode(pulsador,OUTPUT);
  pinMode(A2,INPUT); 
  // Iniciamos el servo para que empiece a trabajar con el pin asignado
  

}
void loop()
{ 
   //Un LDR es un resistor que varía su valor de resistencia 
  //eléctrica dependiendo de la cantidad de luz que incide 
  //sobre él.
  // entre mayor es la luz menor sera el valor de la resistencia
  // entre menor es la luz mayor es la resistencia
 eastLDR = analogRead(eLDRPin); //Leer los valores de la fotocelda
 westLDR = analogRead(wLDRPin);

 if (eastLDR < 400 && westLDR < 400) {  // verifica si la luz que persiben las ldr son bajas
   while (servoSet <=140 && servoSet >=15) {     // si es asi lo vamos a activar el motor para cerrar la carpa
     servoSet ++;
     servo.write(servoSet);
     delay(100);
     // aca ingresaremos el codigo para mover el servomotor
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
  /*
   //controlando suministro del panel a la bateria para no sobrecargarla
  int valorPot=analogRead(A2);
  Serial.println(valorPot);
  delay(100);
  while(valorPot>950){
    digitalWrite(2,LOW);
    valorPot=analogRead(A2);
    estadoPulsador=0;
     digitalWrite(pulsador,estadoPulsador);   
  }
  while(valorPot<950){
    digitalWrite(2,HIGH);
    valorPot=analogRead(A2);
    estadoPulsador=1;
     digitalWrite(pulsador,estadoPulsador);
  } 
*/

}
