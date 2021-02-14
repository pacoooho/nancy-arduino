byte pinPulsador = 2;

byte pulsacion=1;

unsigned long tiempoPulsacion=0;

byte estadoPulsacion = 0;


void leePulsacion (){
  unsigned long tiempoPulsacion2=0;
  if (pulsacion ==2 || pulsacion ==3 ||pulsacion ==4 || pulsacion ==8){
    tiempoPulsacion2 = millis()-tiempoPulsacion;
  }
  if ( pulsacion==1 ){
    if (digitalRead(pinPulsador)==HIGH){
      Serial.println("PULSADO");
      tiempoPulsacion = millis();
      pulsacion=2;
    }
  }
  else if ( pulsacion == 2 && digitalRead(pinPulsador) == LOW){
    Serial.print("FIN PULSACION :");
    if (tiempoPulsacion2 >= 1000){
      Serial.println("NO VALIDA");
      tiempoPulsacion = millis();
      pulsacion=8;
      return;
    }
    Serial.println(tiempoPulsacion2);
    tiempoPulsacion = millis();
    pulsacion=3;
  }
  else if ( pulsacion == 3 && digitalRead(pinPulsador) == LOW
  && tiempoPulsacion2 >= 200){
    Serial.println("pulsacion corta");
    cambiaModo=modo;
    cambiaModo=cambiaModo+1;
    modo=9;
    tiempoPulsacion = millis();
    pulsacion=8;
    return;
  }
  else if (pulsacion == 3 && digitalRead(pinPulsador)==HIGH){
     tiempoPulsacion = millis();
     pulsacion=4;
  }
  else if ( pulsacion == 4  && digitalRead(pinPulsador) == LOW 
  && tiempoPulsacion2 <= 200 && tiempoPulsacion2 >=50){
    Serial.print ("doble pulsacion "); Serial.println (tiempoPulsacion2);
    estadoMotor = !estadoMotor;
    motor=10;
    tiempoPulsacion = millis();
    pulsacion=8;
  }
  else if ( pulsacion == 4  && digitalRead(pinPulsador) == LOW 
  && tiempoPulsacion2 >= 200 ){
    Serial.println("NO VALIDA");
      tiempoPulsacion = millis();
      pulsacion=8;
      return;
  }
  else if ( pulsacion == 8 && tiempoPulsacion2 >=1000){
    Serial.println("LISTO");
    tiempoPulsacion = 0;
    pulsacion=1;
  }
  else if (tiempoPulsacion2 >4000){
    Serial.println("OUT");
    potenciometro=1;
    centrarMotor=1;
    tiempoPulsacion = millis();
    pulsacion=8;
  }
}
