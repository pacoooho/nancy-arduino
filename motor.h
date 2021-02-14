 byte motorPin = 6;
 byte centroPin = A0;
 
int eeAddressRetardoMotor=10 ;
byte retardoMotor;                    // Editable por Serial (10-100)

int eeAddressVoltajeMotor=10+sizeof(retardoMotor);
byte voltajeMotor;               // Editable por Serial(100-200)

int eeAddressMotor=10+sizeof(retardoMotor)+sizeof(voltajeMotor);
byte motor;                           // Editable por Serial ( apagado - encendido)

void ActualizaEEPROM_Motor(){
   EEPROM.get(eeAddressRetardoMotor, retardoMotor);
   EEPROM.get(eeAddressVoltajeMotor, voltajeMotor);
   EEPROM.get(eeAddressMotor, motor);
   if ( retardoMotor==0 || voltajeMotor==0 ){
     voltajeMotor= 100;
     retardoMotor=10;
     motor=1;
     EEPROM.put(eeAddressRetardoMotor, retardoMotor);
     EEPROM.put(eeAddressVoltajeMotor, voltajeMotor);
     EEPROM.put(eeAddressMotor, motor);
     Serial.println("Guardado Motor");
   }
   Serial.print(F("retardoMotor "));Serial.println(retardoMotor);
   Serial.print(F("voltajeMotor "));Serial.println(voltajeMotor);
   Serial.print(F("motor "));Serial.println(motor);

}

boolean centrarMotor=0; 


unsigned long tiempoMotor = 0;

boolean estadoMotor=1;

byte potenciometro=0;
unsigned long tiempoPotenciometro=0;


void giraNancy(){
  if (motor==0){
    return;
  }
  else if (motor==1){
    analogWrite (motorPin, voltajeMotor);
    tiempoMotor = millis();
    motor = 2;
  }
  else if ( motor==2){
    if ( millis()-tiempoMotor >= retardoMotor){
      tiempoMotor = 0;
      motor = 3;
    }
  }
  else if ( motor==3){
    analogWrite (motorPin, 0);
    tiempoMotor = millis();
    motor = 4;
  }
  else if ( motor==4){
    if ( millis()-tiempoMotor >= retardoMotor){
      tiempoMotor = 0;
      motor = 1;
    }
  }
  else if (motor == 9){
       analogWrite (motorPin, 0);
       motor=0;
  }
   else if (motor == 10){
     if (estadoMotor){
      motor=1;
     } else {motor=9;}
   }
}

void leePotenciometro(){
  if ( potenciometro == 0){
  return;
  }
  else if (potenciometro == 1){
    potenciometro=2;
    tiempoPotenciometro=millis();
    return;
  }
  else if (potenciometro == 2 ){
    unsigned long tiempo=millis()-tiempoPotenciometro;
    if (tiempo >=5){
        //   int val =analogRead(centroPin); val >=410 && val <=420
       byte val =digitalRead(centroPin);
      Serial.println(val);
     // Serial.println(centrarMotor);
      if (centrarMotor && digitalRead(centroPin)== HIGH){
        Serial.println("sdffffsfdsfdsfdfdsfdsfsf");
      estadoMotor=0;
      motor =10;
      centrarMotor=!centrarMotor;
      potenciometro =0;
      return;
      }
       
      tiempoPotenciometro=0;
      potenciometro=1;
    }
  }
}
