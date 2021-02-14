
char *leeSerial() {
 // Serial.println("S");
 // Serial.println(Serial.available() );

  
  char byteserial;  char lectura[50]; *lectura = '\0'; char *_lectura = lectura;
  byte r = 1; char f;
  while (r) {
    while (Serial.available() > 0) {
      *_lectura = Serial.read();
    //  Serial.print("L ");Serial.println(*_lectura);
      delayMicroseconds(50);  f =  *_lectura;
      if (f == '\n' || f == '\r' || f == '\0' || f == '*') {
        r = 0;
        break;
      }
      *_lectura++;
    }
    if (f == '\n' || f == '\r' || f == '*') {
      r = 0;
      break;
    }
    delayMicroseconds(1000);
  }

  *_lectura = '\0';
 // Serial.print("Lectura bt "); Serial.println(lectura);

 
  char _datos[100]; *_datos = '\0'; strcpy(_datos, lectura); strcat(_datos, "\0");
  char *pch ;
  pch = strtok(_datos, " " );
  while (pch != '\0') {

//Serial.println(pch);
    ///////////////////////  AYUDA  //////////////////////////////////////////////////////////
  if (strcmp(pch, "ayuda") == 0) {
    pch = strtok('\0', " ");
    if (strcmp(pch, "led") == 0) {
      Serial.println(F("Led"));
      char myChar;
      for (unsigned long  k = 0; k < strlen_P(ayudaLed); k++) {
        myChar = pgm_read_byte_near(ayudaLed + k);
        Serial.print(myChar);
      }
    }
    else if (strcmp(pch, "motor") == 0) {
      Serial.println(F("motor"));
      char myChar;
      for (unsigned long  k = 0; k < strlen_P(ayudaMotor); k++) {
        myChar = pgm_read_byte_near(ayudaMotor + k);
        Serial.print(myChar);
      }
    }
  }
   ///////////////////////  MOTOR //////////////////////////////////////////////////////////
  else if (strcmp(pch, "motor") == 0){
    pch = strtok('\0', " ");
    if (strcmp(pch, "retardo") == 0) {
      Serial.println(F("retardo"));
      pch=strtok('\0'," ");
      int delayM = atoi(pch);
      if ( delayM <=9 || delayM >100){
        Serial.println(F("retardo no aceptable (10-100)"));  
         return;
       }
     retardoMotor=delayM;
     Serial.print(F("retardo motor")); 
     Serial.println(retardoMotor);
   }
   else if (strcmp(pch, "voltaje") == 0) {
     Serial.println(F("voltaje"));
     pch=strtok('\0'," ");
     int voltaje = atoi(pch);
     if ( voltaje <=99 || voltaje >200){
       Serial.println(F("voltaje no aceptable (100-200)"));  
       return;
     }
     voltajeMotor=voltaje;
     Serial.print(F("voltaje  motor")); 
     Serial.println(voltaje);
   }
   else   if (strcmp(pch, "OnOff") == 0) {
     pch=strtok('\0'," ");
     if (strcmp(pch, "apagado") == 0) {
       motor=9;
     }
     else if (strcmp(pch, "encendido") == 0) {
       motor=1;
     }
     Serial.print(F("motor ")); 
     Serial.println(pch);
   }
   else if (strcmp(pch, "guarda") == 0) {
     EEPROM.put(eeAddressRetardoMotor, retardoMotor);
     EEPROM.put(eeAddressVoltajeMotor, voltajeMotor);
     EEPROM.put(eeAddressMotor, motor);
     Serial.println(F("GUARDADO"));
   }
  }
      ///////////////////////  LED  //////////////////////////////////////////////////////////
  else if (strcmp(pch, "led") == 0){
     pch=strtok('\0'," ");
     if (strcmp(pch, "modo") == 0){
       pch=strtok('\0'," ");int modoInt = atoi(pch);
       char *comando;comando=strtok('\0'," ");
       boolean ok =0;
   
          pch=strtok('\0'," "); 
         int valor= atoi(pch);
         // Serial.print(" valor ");Serial.print(valor);Serial.println(); 
         if ( modoInt >=1 && modoInt<=3){
          if (strcmp(comando, "fijo") == 0) {
            modoDatosLed[modoInt].fijo = true;ok =1;
          }
          else if (strcmp(comando, "variable") == 0) {
            modoDatosLed[modoInt].fijo = false;ok =1;
          }
          else if (strcmp(comando, "intensidadMax") == 0) {
            if (valor >= modoDatosLed[modoInt].intensidadMin && valor <=255){
              modoDatosLed[modoInt].intensidadMax = valor ;ok =1;
            }else {Serial.print(F("valor erroneo "));Serial.print(modoDatosLed[modoInt].intensidadMin);Serial.println("-255");}
          }
          else if (strcmp(comando, "intensidadMin") == 0) {
            if (valor <= modoDatosLed[modoInt].intensidadMax  && valor >=0) {
              modoDatosLed[modoInt].intensidadMin = valor ;ok =1;
            }else {Serial.print(F("valor erroneo "));Serial.print(modoDatosLed[modoInt].intensidadMin);Serial.print("-");Serial.println(modoDatosLed[modoInt].intensidadMax);}
          }
          else if (strcmp(comando, "retardo") == 0) {
            if (valor >= 2 && valor <=100){
              modoDatosLed[modoInt].delayLed = valor ;ok =1;
            }else {Serial.print(F("valor erroneo 2-100"));}
          }
          else if (strcmp(comando, "guarda") == 0) {
            Serial.println(F("GUARDADO"));            
            EEPROM.put(eeAddressModoDatosLed+(modoInt*5), modoDatosLed[modoInt]);

          }
         }
         else if ( modoInt == 4){
          if (strcmp(comando, "fijo") == 0) {
            modoDatosLed[modoInt].fijo = true;ok =1;
          }
          else if (strcmp(comando, "variable") == 0) {
            modoDatosLed[modoInt].fijo = false;ok =1;
          }
          else if (strcmp(comando, "intensidadMin") == 0) {
            if (valor <= 80 && valor >=0) {
              modoDatosLed[modoInt].intensidadMin = valor ;ok =1;
            }else {Serial.println(F("valor erroneo 0 - 80 "));}
          }
          else if (strcmp(comando, "retardo") == 0) {
            if (valor >= 2 && valor <=100){
              modoDatosLed[modoInt].delayLed = valor ;ok =1;
            }else {Serial.println(F("valor erroneo 2-100"));}
          }
          else if (strcmp(comando, "valRojo") == 0) { 
             if (valor >= 0 && valor <=255){
              valRojo=valor;ok =1;
             }else { Serial.println(F("valor erroneo 0 255"));}
          }
          else if (strcmp(comando, "valVerde") == 0) { 
             if (valor >= 0 && valor <=255){
              valVerde=valor;ok =1;        
             }else { Serial.println(F("valor erroneo 0 255"));}
          }
          else if (strcmp(comando, "valAzul") == 0) { 
             if (valor >= 0 && valor <=255){ 
              valAzul=valor;luceModoLed=1;ok =1;       
             }else { Serial.println(F("valor erroneo 0 255"));}
          }
          else if (strcmp(comando, "guarda") == 0) {
            Serial.println(F("GUARDADO"));
            EEPROM.put(eeAddressModoDatosLed+(modoInt*5), modoDatosLed[modoInt]);
            EEPROM.put(eeAddressValRojo, valRojo);
            EEPROM.put(eeAddressValVerde, valVerde);
            EEPROM.put(eeAddressValAzul, valAzul);
          }
          
         }
         else if ( modoInt==5){
            if (strcmp(comando, "maxDelay") == 0) {
            if ( maxDelay <=1000 && maxDelay >=500){
              maxDelay = valor;ok = 1;
            }else {Serial.println(F("valor erroneo 500 -1000 milisegundos"));}
          }
          else if (strcmp(comando, "intensidadMax") == 0) {
            if (valor >= modoDatosLed[modoInt].intensidadMin && valor <=255){
              modoDatosLed[modoInt].intensidadMax = valor ;ok =1;
            }else {Serial.print(F("valor erroneo "));Serial.print(modoDatosLed[modoInt].intensidadMin);Serial.println(F("-255"));}
          }
          else if (strcmp(comando, "intensidadMin") == 0) {
            if (valor <= modoDatosLed[modoInt].intensidadMax && valor >=0) {
              modoDatosLed[modoInt].intensidadMin = valor ;ok =1;
            }else {Serial.print(F("valor erroneo "));Serial.print(modoDatosLed[modoInt].intensidadMin);Serial.print(F("-"));Serial.println(modoDatosLed[modoInt].intensidadMax);}
          }
          else if (strcmp(comando, "guarda") == 0) {
            Serial.println(F("GUARDADO"));
            EEPROM.put(eeAddressModoDatosLed+(modoInt*5), modoDatosLed[modoInt]);
            EEPROM.put(eeAddressMaxDelay, maxDelay);

          }
          
         }
      if ( ok ==1 ){
        Serial.print(F("OK cambiado "));Serial.println(comando );
        cambiaModo = modo;modo = 9;luceModoLed=1;
      }
      else if (ok == 2){
    
      }
     }
  }
  
  else if (strcmp(pch, "modo")==0){
           pch=strtok('\0'," ");int modoInt = atoi(pch);
           pch=strtok('\0'," ");
           if ( strcmp(pch, "?")==0){
             Serial.println(F("-------------------------------------"));
             if ( modoInt >=1 && modoInt<=4){
               Serial.println( modoDatosLed[modoInt].fijo == true ? "fijo" : "variable");
               Serial.print(F("intensidadMax "));Serial.println( modoDatosLed[modoInt].intensidadMax);
               if (modoInt!=4){Serial.print(F("intensidadMin "));Serial.println( modoDatosLed[modoInt].intensidadMin );}
               Serial.print(F("retardo "));Serial.println( modoDatosLed[modoInt].delayLed);           
             }
             if ( modoInt == 4 ){
               Serial.print(F("valRojo "));Serial.println(valRojo  );           
               Serial.print(F("valVerde "));Serial.println(valVerde );           
               Serial.print(F("valAzul "));Serial.println( valAzul );           
             }
             if ( modoInt == 5 ){
               Serial.print(F("maxDelay "));Serial.println( maxDelay );
               Serial.print(F("intensidadMax "));Serial.println( modoDatosLed[modoInt].intensidadMax);
               Serial.print(F("intensidadMin "));Serial.println( modoDatosLed[modoInt].intensidadMin );
             }
             Serial.println(F("-------------------------------------"));

             return;
           }
            else if ( strcmp(pch, "guarda")==0){
              EEPROM.put(eeAddressModo, modoInt);
              Serial.println(F("GUARDADO"));
            }
           if ( modoInt >=sizeof(modosNombre)/sizeof(modosNombre[0])){
            return;
           }
           cambiaModo = modoInt;modo = 9;luceModoLed=1;
  }
    else if (strcmp(pch, "reset")==0){
      analogWrite (rojoPin, 0);
      analogWrite (verdePin, 0);
      analogWrite (azulPin, 0);
      analogWrite (motorPin, 0);
      for (int i = 0 ; i < EEPROM.length() ; i++) {
        EEPROM.write(i, 0);
      }
      resetFunc();
    }
          pch = strtok('\0', " ");

   }
}
