byte rojoPin = 9;  
byte verdePin = 10 ; 
byte azulPin = 11;  

unsigned long tiempoLed=0; 

int eeAddressModo=30 ;
byte modo ;                // Editable por Serial (0 - 5)  0

byte cambiaModo=0;

// todos modos
char *modosNombre[]={
  "apagado",
  "rojo",
  "verde",
  "azul",
  "rgb",
  "disco"
  };
byte luceModoLed=1;
int valorRGB=0;

// datos persistentes modos
int eeAddressModoDatosLed=30+sizeof(modo) ;
struct modosDatos {
  boolean fijo;         // Editable por Serial (fijo - variable) false
  byte intensidadMax;     // Editable por Serial (intensidadMin - 255) 155
  byte intensidadMin;      // Editable por Serial (0 - intensidadMax) 10
  byte pasos;
  byte delayLed;
   // Editable por Serial ( 2 - 100) 35
} modoDatosLed[6];

// modo 4
byte valF;
int eeAddressValRojo=30+sizeof(modo)+sizeof(modoDatosLed) ;
byte valRojo;             // Editable por Serial ( 0 - 255) 255

int eeAddressValVerde=30+sizeof(modo)+sizeof(modoDatosLed)+sizeof(valRojo) ;
byte valVerde;          // Editable por Serial ( 0 - 255) 255

int eeAddressValAzul=30+sizeof(modo)+sizeof(modoDatosLed)+sizeof(valRojo)+sizeof(valVerde) ;
byte valAzul;           // Editable por Serial ( 0 - 255) 255

byte valorR,valorG,valorB;


//modo 5
int delayR,delayG,delayB;
boolean onOffR,onOffG,onOffB;

int eeAddressMaxDelay=30+sizeof(modo)+sizeof(modoDatosLed)+sizeof(valRojo)+sizeof(valVerde)+sizeof(valAzul) ;
int maxDelay;            // Editable por Serial (500 -1000) 1000
int minDelay=200; 

void ActualizaEEPROM_Led(){
   EEPROM.get(eeAddressModo, modo);
   EEPROM.get(eeAddressValRojo, valRojo);
   EEPROM.get(eeAddressValVerde, valVerde);
   EEPROM.get(eeAddressValAzul, valAzul);
   EEPROM.get(eeAddressMaxDelay, maxDelay);
   EEPROM.get(eeAddressModoDatosLed, modoDatosLed);
 
   if (modo == 0 ||  valRojo==0 || valVerde==0 || valAzul==0 || maxDelay==0){
     modo= 1;
     valRojo=255;
     valVerde=255;
     valAzul=255;
     maxDelay=1000;
     for (byte f = 1; f < 6; f++){
       modoDatosLed[f].fijo = false;
       modoDatosLed[f].intensidadMax = 155;
       modoDatosLed[f].intensidadMin = 10;
       modoDatosLed[f].pasos = 5;
       modoDatosLed[f].delayLed = 35;
     }
      
   EEPROM.put(eeAddressModo, modo);
   EEPROM.put(eeAddressModoDatosLed, modoDatosLed);
   EEPROM.put(eeAddressValRojo, valRojo);
   EEPROM.put(eeAddressValVerde, valVerde);
   EEPROM.put(eeAddressValAzul, valAzul);
   EEPROM.put(eeAddressMaxDelay, maxDelay);
   Serial.println("Guardado modos leds");
   }
   
   Serial.print(F("modo "));Serial.println(modo);
   Serial.print(F("valRojo "));Serial.println(valRojo);
   Serial.print(F("valVerde "));Serial.println(valVerde);
   Serial.print(F("valAvul "));Serial.println(valAzul);
   Serial.print(F("maxDelay "));Serial.println(maxDelay);
   Serial.print(F("modoDatosLed[1].fijo "));Serial.println(modoDatosLed[1].fijo);

   Serial.print("modoDatosLed[1].intensidadMax ");Serial.println(modoDatosLed[1].intensidadMax);
   Serial.print("modoDatosLed[1].intensidadMin ");Serial.println(modoDatosLed[1].intensidadMin);

}

  void luceLed ( modosDatos modoLed, byte &modo ) {
 //  Serial.println(modo);
   if (modo==0){
      return;
    }
    else if (modo==1 || modo == 2 || modo == 3){
      if (modoLed.fijo){
         if (luceModoLed==1){
          valorRGB=modoLed.intensidadMax;
          switch (modo) {
          case 1:
            analogWrite (rojoPin, valorRGB);
            break;
          case 2:
            analogWrite (verdePin, valorRGB);
            break;
          case 3:
            analogWrite (azulPin, valorRGB);
            break;  
          default:
           // statements
             break;
          }
          luceModoLed=2;
          return;
        }
        else if (luceModoLed==2){
          return;
        }
      }
      else {// variable
        if (luceModoLed==1){
          valorRGB=modoLed.intensidadMin;
          luceModoLed=2;
          return;
        }
        else if ( luceModoLed == 2){
          
          tiempoLed=millis();
          luceModoLed=3;
          valorRGB = valorRGB + modoLed.pasos;
          switch (modo) {
          case 1:
            analogWrite (rojoPin, valorRGB);
            break;
          case 2:
            analogWrite (verdePin, valorRGB);
            break;
          case 3:
            analogWrite (azulPin, valorRGB);
            break;  
          default:
           // statements
             break;
          }
        }
        else if ( luceModoLed == 3){
          if ( millis()-tiempoLed >= modoLed.delayLed){
            tiempoLed = 0;
            luceModoLed = 2;
            return;
          }
          if ( valorRGB>=modoLed.intensidadMax){
            luceModoLed=4;
            return;
          } 
        }
        else if ( luceModoLed == 4){
          tiempoLed=millis();
          luceModoLed=5;
          valorRGB = valorRGB - modoLed.pasos;
          switch (modo) {
          case 1:
            analogWrite (rojoPin, valorRGB);
            break;
          case 2:
            analogWrite (verdePin, valorRGB);
            break;
          case 3:
            analogWrite (azulPin, valorRGB);
            break;  
          default:
             // statements
              break;  
        }
      }
      else if ( luceModoLed == 5){
        if ( millis()-tiempoLed >= modoLed.delayLed){
          tiempoLed = 0;
          luceModoLed = 4;
          return;
        }
        if ( valorRGB<=modoLed.intensidadMin){
          luceModoLed=1;
          return;
        } 
      }
    }
  }
  else if (modo==4){
    if (modoLed.fijo){
      if (luceModoLed==1){
         analogWrite (rojoPin, valRojo);
         analogWrite (verdePin, valVerde);
         analogWrite (azulPin, valAzul);
         luceModoLed=2;
         return;
       }
       else if (luceModoLed==2){
         return;
       }
     }
      else {
        if (luceModoLed==1){
          valF=modoLed.intensidadMin;
          luceModoLed=2;
          return;
        }
        else if ( luceModoLed == 2){
          valF = valF+modoLed.pasos;
          tiempoLed=millis();
          luceModoLed=3;
          valorR= (valRojo*valF)/100;
          valorG= (valVerde*valF)/100;
          valorB= (valAzul*valF)/100;
          analogWrite (rojoPin, valorR);
          analogWrite (verdePin, valorG);
          analogWrite (azulPin, valorB);
        }
        else if ( luceModoLed == 3){
          if ( millis()-tiempoLed >= modoLed.delayLed){
            tiempoLed = 0;
            luceModoLed = 2;
            return;
          }
          if ( valF>=100){
            luceModoLed=4;
            return;
          } 
        }
        else if ( luceModoLed == 4){
          valF = valF-modoLed.pasos;
          tiempoLed=millis();
          luceModoLed=5;
          valorR= (valRojo*valF)/100;
          valorG= (valVerde*valF)/100;
          valorB= (valAzul*valF)/100;
          analogWrite (rojoPin, valorR);
          analogWrite (verdePin, valorG);
          analogWrite (azulPin, valorB);
      }
      else if ( luceModoLed == 5){
        if ( millis()-tiempoLed >= modoLed.delayLed){
          tiempoLed = 0;
          luceModoLed = 4;
          return;
        }
        if ( valF<=modoLed.intensidadMin){
          luceModoLed=2;
          return;
        } 
      }
    }
  }
  else if (modo == 5){
     byte mimL=modoLed.intensidadMin;
     byte maxL=modoLed.intensidadMax;
    if (luceModoLed==1){
      delayR=random(minDelay,maxDelay);delayG=random(minDelay,maxDelay);delayB=random(minDelay,maxDelay);
       onOffR=random(0,5);onOffG=random(0,5);onOffB=random(0,5); 
       valorR=random(mimL,maxL);valorG=random(mimL,maxL);valorB=random(mimL,maxL); 
       if ( onOffR){
          analogWrite (rojoPin, valorR); 
       } else {analogWrite(rojoPin, 0);}
       if ( onOffG){
         analogWrite (verdePin, valorG);
       } else {analogWrite(verdePin, 0);} 
       if ( onOffB){
         analogWrite (azulPin, valorB);
       }  else {analogWrite(azulPin, 0);}
      luceModoLed=2;
      return;
    }
    else if ( luceModoLed == 2){
      int tiempo = millis()%1000;
      if ( delayR - tiempo <= 0){
        delayR=random(minDelay,maxDelay); onOffR=random(0,5);valorR=random(mimL,maxL);
        if ( onOffR){
          analogWrite (rojoPin, valorR); 
        } else {analogWrite(rojoPin, 0);}
      }
       if ( delayG - tiempo <= 0){
        delayG=random(minDelay,maxDelay); onOffG=random(0,5);valorG=random(mimL,maxL);
        if ( onOffG){
          analogWrite (verdePin, valorG); 
        } else {analogWrite(verdePin, 0);}
      }
      if ( delayB - tiempo <= 0){
        delayB=random(minDelay,maxDelay); onOffB=random(0,5);valorB=random(mimL,maxL);
        if ( onOffB){
          analogWrite (azulPin, valorB); 
        } else {analogWrite(azulPin, 0);}
      }
    } 
  }
  else if ( modo == 9 ){
    analogWrite (rojoPin, 0);
    analogWrite (verdePin, 0);
    analogWrite (azulPin, 0);
    if (cambiaModo >=sizeof(modosNombre)/sizeof(modosNombre[0])){
      modo=0;cambiaModo=0;luceModoLed=1;
      return;
    }
    modo=cambiaModo;
    cambiaModo=0;
    luceModoLed=1;
  }
}
 
