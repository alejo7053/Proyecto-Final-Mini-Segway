/*-------------------- GIROSCOPIO -------------------*/
#include <Wire.h>
//Direccion I2C de la MPU
#define MPU 0x68
#define GYRO_CONFIG 0x1B //direccion registro de configuracion del giroscopio
//MPU-6050 da los valores en enteros de 16 bits
//valores en bruto
int16_t GY;
/*---------------------------------------------------*/

/*---------------------- PWM --------------------------*/
int pinA1 = 6; // entrada de motor A1
int pinB1 = 9;// entrada motor B1
int pinEN1=11; // entrada ENABLE 1
int valorveloc =0;
/*------------------------------------------------------*/

void setup() {
  
/*-------------------- GIROSCOPIO ------------------------*/
Wire.begin();
   Wire.beginTransmission(MPU);
   Wire.write(0x6B);
   Wire.write(0);
   Wire.endTransmission(true);
   Wire.begin();
   Wire.beginTransmission(MPU);
   Wire.write(GYRO_CONFIG); //configuracion del rango de las salidas del giroscopio
   Wire.write(3<<3);
   Wire.endTransmission(true);
/*-------------------------------------------------------*/

/*--------------------- PWM -----------------------------*/
// inicializa los pines de salida:
  pinMode(pinA1, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinEN1, OUTPUT);
  digitalWrite(pinEN1,HIGH);//lINEA ES LA CLAVE, RPA
/*-------------------------------------------------------*/

 Serial.begin(9600);
}

void loop() {
/*------------------------- GIROSCOPIO ------------------------*/
    //miramos valores del acelerometro
  Wire.beginTransmission(MPU);
  Wire.write(0x45); //pedimos el registro 0x45-corresponde al giroscopio en Y
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,2,true);//apartir  del registro 0x45, pedimos el resto de registros
  GY=Wire.read()<<8|Wire.read();
  Serial.print("GY = "); 
  Serial.println(GY);
/*-------------------------------------------------------------*/

/*------------------ CONTROL ----------------------------------*/

if(GY >= 255){
  GY =255;
}

if(GY<=-255){
  GY = -255;
}

/*-------------------------------------------------------------*/

/*--------------------------- PWM -----------------------------*/
if(GY>0)
{
digitalWrite(pinA1,HIGH); //valores  ALTO en A y BAJO  en B simultaneamente
digitalWrite(pinB1,LOW); // hacen girar el motor 1 hacia adelante
valorveloc=map(GY, 0, 255, 255, 30);// convierte un valor 0 y 1023 al rango 0-255
// valorveloc=valorpot/4; // segunda opcion
analogWrite(pinEN1,valorveloc); // y establece la velocidad del motor con ese valor
 
}
else if(GY<0){
digitalWrite(pinA1,LOW);// valores ALTO en A y BAJO en B simultaneamente
digitalWrite(pinB1,HIGH); // hacen girar el motor 1 hacia adelante
valorveloc=map(GY, 0, -255, 30, 255); // convierte un valor entre 0 y 1023 al rango 0-255
// valorVeloc=valorPot/4; // Segunda opcion
analogWrite(pinEN1,valorveloc); // y establece la velocidad del motor con ese valor
}
/*------------------------------------------------------------------------------------*/
 Serial.print("GY = "); Serial.println(GY);
delay(10);

}
