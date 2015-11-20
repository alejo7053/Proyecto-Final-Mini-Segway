int pinA1 = 6; // entrada de motor A1
int pinB1 = 9;// entrada motor B1
int pinEN1=11; // entrada ENABLE 1
int pinPot = A0; // lectura analogica del potenciometro
int valorpot =0;
int valorveloc =0;
void setup() {
  // inicializa los pines de salida:
pinMode(pinA1, OUTPUT);
pinMode(pinB1, OUTPUT);
pinMode(pinEN1, OUTPUT);
pinMode(pinPot, INPUT);
digitalWrite(pinEN1,HIGH);//lINEA ES LA CLAVE, RPA
Serial.begin(9600); 
}

void loop() {
  
valorpot = analogRead(pinPot); // lee el valor del potenciometro
Serial.println(valorpot);
if(valorpot>=0&&valorpot<=511)
{
digitalWrite(pinA1,HIGH); //valores  ALTO en A y BAJO  en B simultaneamente
digitalWrite(pinB1,LOW); // hacen girar el motor 1 hacia adelante
valorveloc=map(valorpot, 0, 511, 255, 90);// convierte un valor 0 y 1023 al rango 0-255
// valorveloc=valorpot/4; // segunda opcion
analogWrite(pinEN1,valorveloc); // y establece la velocidad del motor con ese valor
 
}
else if(valorpot>=512&&valorpot<=1023){
digitalWrite(pinA1,LOW);// valores ALTO en A y BAJO en B simultaneamente
digitalWrite(pinB1,HIGH); // hacen girar el motor 1 hacia adelante
valorveloc=map(valorpot, 512, 1023, 70, 255); // convierte un valor entre 0 y 1023 al rango 0-255
// valorVeloc=valorPot/4; // Segunda opcion
analogWrite(pinEN1,valorveloc); // y establece la velocidad del motor con ese valor
}
}
