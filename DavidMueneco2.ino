/*
KY016 RGB LED module
https://descubrearduino.com
PWM LED Color Generation
*/


void(* resetFunc) (void) = 0;//declare reset function at address 0


const int pinMicrophone = A1;
long long int last_states = 0;
unsigned long timer;

#include <SoftwareSerial.h>
SoftwareSerial BT(7, 8); // RX | TX
#include <EEPROM.h>

byte color = 0;

int val;
#include "help.h"
  #include "motor.h"
  #include "led.h"

  #include "pulsador.h"
  #include "serial.h"

 

void setup () {
  Serial.begin(9600);
   BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2)

  
  pinMode (rojoPin, OUTPUT);
  pinMode (azulPin, OUTPUT);
  pinMode (verdePin, OUTPUT);

  pinMode (motorPin, OUTPUT);
  
   pinMode(centroPin,INPUT);
   Serial.println(F("Iniciando"));
    Serial.println(F("Para configuración por Serial : -ayuda led- ó -ayuda motor-"));
   
  Serial.println(sizeof(modosNombre)/sizeof(modosNombre[0]));
Serial.println(sizeof(modoDatosLed[1]));
 
 /*
  *    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  */
 
 
  

  ActualizaEEPROM_Motor();
  ActualizaEEPROM_Led();
 
}
void loop ()
{
 /*
  *   if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    Serial.write(BT.read());
  }
  
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read());
  }
  */
   /*
    * 
 float valRed = 255.0;
 float valGreen= 255.0;
 float valBlue = 255.0;
 Serial.println("---------------------");
  for (float valF = 10.0; valF <=100.0; valF  =valF +5.0)
  {
   float valR= (valRed*valF)/100.0;
   float valG= (valGreen*valF)/100.0;
   float valB= (valBlue*valF)/100.0;

    analogWrite (rojoPin, valR);
       analogWrite (verdePin, valG);
   analogWrite (azulPin, valB);
  Serial.print(valF);Serial.print(" ");Serial.print(valR);
  Serial.print(" ");Serial.print(valG);
  Serial.print(" ");Serial.println(valB);
    delay (35);
  }
  delay(2000);
 Serial.println("---------------------");
      for (float valF = 100.0; valF>= 10.0; valF =valF -5.0)
  {
      float valR= (valRed*valF)/100.0;
float valG= (valGreen*valF)/100.0;
   float valB= (valBlue*valF)/100.0;
  analogWrite (rojoPin, valR);
    analogWrite (verdePin, valG);
   analogWrite (azulPin, valB);
 Serial.print(valF);Serial.print(" ");Serial.print(valR);
  Serial.print(" ");Serial.print(valG);
  Serial.print(" ");Serial.println(valB);

    delay (35);
  }  

  delay(1000);
 
 
    */
  
/*
 * 
    unsigned long milli=millis()/1000;

if (milli>=timer){ 
  Serial.println(timer);
  timer =milli+1;
}
 
 */
   
  if (Serial.available()>0){
 // Serial.println(Serial.read());
  leeSerial();
} 
  
//  Serial.println( analogRead(centroPin)); 
//delay(20);
   luceLed ( modoDatosLed[modo], modo);
  giraNancy();
leePulsacion();
 leePotenciometro();
  
}
