const PROGMEM char ayudaMotor[]  = R"=====(
-------------------------------------------------------------------------------
Hola hola puedes cambiar algunos párametros desde el terminal
enviando algunos comandos.
Para el motor son: "motor" - "retardo" - "velocidad " - "OnOff" - "guarda". ejemplos:

"motor retardo 10"      - esto cambiará el retardo entre pulso y pulso 
                        aumentando o disminuyendo la velocidad (10-100).
"motor voltaje 100"     - esto cambiará el voltaje del pulso de salida al motor
                         yo no lo tocaría (100-200).
"motor OnOff encendido" - esto cambiará el estado del motor (apagado -encendido)
"motor guarda"          - esto guardará la configuración existente en la memoria 
                         persistente  
--------------------------------------------------------------------------------            
)=====";

const PROGMEM char ayudaLed[]  = R"=====(
-------------------------------------------------------------------------------
Hola hola puedes cambiar algunos párametros desde el terminal
enviando algunos comandos. Hay 5 modos de iluminación. El modo 0 es apagado.
Para el led son: "modo" - "fijo " - "variable " - "intensidadMax" - "intensidadMin" - 
"retardo " - "valRojo" -"valVerde " - "valAzul" - "maxDelay" - "guarda".
algunos comando solo valen para algunos modos ejemplos:

"led modo 1 fijo"         - el modo 1 es color rojo será fijo (fijo - variable)
                           sí es variable cambiará entre intensidadMin y intensidadMax
                           progresivamente. (válido modo 1,2,3,4)
"led modo 2 intensidadMax 155"- el modo 2 es verde configurará en una intensidad
                           máxima. (intensidadMin - 255) (válido modo 1,2,3)
"led modo 3 intensidadMin 10"- el modo 3 es color azul configurará en una intensidad
                           mínima. (0 - intensidadMax) (válido modo 1,2,3,4)
"led modo 4 retardo 35"  - el modo 4 se podrá configurar cualquier color. Mediante 
                           retardo se configura el tiempo en milisegundos que cambia 
                           la intensidad (2 - 100) (válido modo 1,2,3,4)
"led modo 4 valRojo 155" - en este caso configurará el valor rojo en el led RGB.
                           Configurando también valVerde y valAzul creará el color 
                           se desee. (0 - 255) (válido solo modo 4)
"led modo 5 maxDelay 1000"- el modo 5 es discoteca, alternará colores y tiempos de 
                           encendidos mediante maxDelay( 500 - 1000) (sólo modo 5)
"led modo 1 guarda"       - esto guardará la configuración existente del modo 1  en 
                           la memoria persistente.
--------------------------------------------------------------------------------            
)=====";
