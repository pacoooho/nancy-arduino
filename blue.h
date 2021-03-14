char *leeBlue() {
  Serial.println("S");
 // Serial.println(Serial.available() );

  char *ok="OK";
  char byteserial;  char lectura[50]; *lectura = '\0'; char *_lectura = lectura;
  byte r = 1; char f;
  while (r) {
       while (BT.available() > 0) {
      *_lectura = BT.read();
    //  Serial.print("L ");Serial.println(*_lectura);
      delayMicroseconds(50);  f =  *_lectura;
      if ( f == '*') {
        r = 0;
        break;
      }
      *_lectura++;
    }
  
 if ( f == '*') {
      r = 0;
      break;
    }
    delayMicroseconds(1000);
  }

  *_lectura = '\0';
   Serial.print("Lectura bt "); Serial.println(lectura);

 
  char _datos[100]; *_datos = '\0'; strcpy(_datos, lectura); strcat(_datos, "\0");
  char *pch ;
  pch = strtok(_datos, " " );
  while (pch != '\0') {


    
if (strcmp(pch, "dModo") == 0) {
    Serial.println("dModo");
    String output;
    output += "{\"modo\":";
    output +=  modo;
    output += "";//FIN
    output += "}*";
    analogWrite (motorPin, 0);
    Serial.println(output);

    BT.println(output);
    }
  else if (strcmp(pch, "dMotor") == 0) {
    Serial.println("dMotor");
    String output;
    output += "{\"motor\":";
    output +=  motor;
    output += ",\"voltajeMotor\":";
    output +=  voltajeMotor;
    output += ",\"retardoMotor\":";
    output += retardoMotor;
    output += "";//FIN
    output += "}*";
    analogWrite (motorPin, 0);
    Serial.println(output);
    BT.println(output);
    
  }
  else if (strcmp(pch, "dLed") == 0) {
     String output="[";
  for (byte cnt = 1; cnt<=5; cnt=cnt +1 ) {
    if (cnt > 1) {
      output += ',';
    }
    if ( cnt >=1 && cnt<=4){
    output += "{\"tipo\":";
    output +=  modoDatosLed[cnt].fijo;
      if (cnt!=4){   output += ",\"intensidadMax\":";
    output +=  modoDatosLed[modo].intensidadMax;}
    output += ",\"intensidadMin\":";
    output += modoDatosLed[modo].intensidadMin ;
    output += ",\"delayLed\":";
    output += modoDatosLed[modo].delayLed;   
    } 
    if ( cnt == 4 ){
    output += ",\"valRojo\":";
    output += valRojo;
    output += ",\"valVerde\":";
    output += valVerde;    
    output += ",\"valAzul\":";
    output += valAzul;
    }
    if ( cnt == 5 ){
       output += "{\"intensidadMax\":";
    output +=  modoDatosLed[cnt].intensidadMax;
    output += ",\"intensidadMin\":";
    output +=  modoDatosLed[modo].intensidadMin;
    output += ",\"maxDelay\":";
    output +=  maxDelay;
    
    }

    output += "";//FIN
    output += "}";
    
  }
      output += "]*";
      analogWrite (motorPin, 0);
  Serial.println(output);

  BT.println(output);
  Serial.println("B-Led");
  }
  else if (strcmp(pch, "mo")==0){
      pch=strtok('\0'," ");int modoInt = atoi(pch);
      if ( modoInt >=sizeof(modosNombre)/sizeof(modosNombre[0])){
        return;
      }
      cambiaModo = modoInt;modo = 9;luceModoLed=1;
      delay(1);
      BT.print(ok);
  }
  else if (strcmp(pch, "l")==0){
     pch=strtok('\0'," ");int modoInt = atoi(pch); 
     pch=strtok('\0'," ");int fijo = atoi(pch); 
     pch=strtok('\0'," ");int intMax = atoi(pch);
     pch=strtok('\0'," ");int intMin = atoi(pch);
     pch=strtok('\0'," ");int delayLed = atoi(pch);
     modoDatosLed[modoInt].fijo=fijo;
     modoDatosLed[modoInt].intensidadMax=intMax;
     modoDatosLed[modoInt].intensidadMin=intMin;
     modoDatosLed[modoInt].delayLed=delayLed;
     Serial.println(modoDatosLed[modoInt].fijo);
     Serial.println(modoDatosLed[modoInt].intensidadMax);
     Serial.println(modoDatosLed[modoInt].intensidadMin);
     Serial.println(modoDatosLed[modoInt].delayLed);
      cambiaModo = modoInt;modo = 9;luceModoLed=1;
      BT.print(ok);
      Serial.println("l");

  }
    else if (strcmp(pch, "RGB")==0){
      pch=strtok('\0'," ");int modoInt = atoi(pch); 
     pch=strtok('\0'," ");int fijo = atoi(pch); 
     pch=strtok('\0'," ");int intMin = atoi(pch);
     pch=strtok('\0'," ");int delayLed = atoi(pch);
     pch=strtok('\0'," ");int rojo = atoi(pch);
     pch=strtok('\0'," ");int verde = atoi(pch);
     pch=strtok('\0'," ");int azul = atoi(pch);
     modoDatosLed[modoInt].fijo=fijo;
     modoDatosLed[modoInt].intensidadMin=intMin;
     modoDatosLed[modoInt].delayLed=delayLed;
     valRojo=rojo;
     valVerde=verde;
     valAzul=azul;
     cambiaModo = modoInt;modo = 9;luceModoLed=1;
     BT.print(ok);
     Serial.println("RGB");

    }

    else if (strcmp(pch, "Disco")==0){
      pch=strtok('\0'," ");int modoInt = atoi(pch); 
     pch=strtok('\0'," ");int intMax = atoi(pch); 
     pch=strtok('\0'," ");int intMin = atoi(pch);
     pch=strtok('\0'," ");int maxDelay = atoi(pch);
      modoDatosLed[modoInt].intensidadMax=intMax;
     modoDatosLed[modoInt].intensidadMin=intMin;
     maxDelay=maxDelay;
     cambiaModo = modoInt;modo = 9;luceModoLed=1;
     BT.print(ok);
     Serial.println("Disco");

    }
        pch = strtok('\0', " ");

   }

  }
