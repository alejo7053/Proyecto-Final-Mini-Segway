#include <Wire.h>
//Direccion I2C de la MPU
#define MPU 0x68
#define GYRO_CONFIG 0x1B
//MPU-6050 da los valores en enteros de 16 bits
//valores en bruto
int16_t AX, AY, AZ, GX, GY, GZ,TEMP;


void setup() {
 Wire.begin();
 Wire.beginTransmission(MPU);
 Wire.write(0x6B);
 Wire.write(0);
 Wire.endTransmission(true);
 Wire.begin();
 Wire.beginTransmission(MPU);
 Wire.write(GYRO_CONFIG);
 Wire.write(19<<3);
 Wire.endTransmission(true);
 Serial.begin(9600);

}

void loop() {
  //miramos valores del acelerometro
Wire.beginTransmission(MPU);
Wire.write(0x43); //pedimos el registro 0x3B-corresponde a la aceleracion en X
Wire.endTransmission(false);
Wire.requestFrom(MPU,6,true);//apartir  del registro 0x43, pedimos el resto de registros
GX=Wire.read()<<8|Wire.read();
GY=Wire.read()<<8|Wire.read();
GZ=Wire.read()<<8|Wire.read();
Serial.print(" | GX = "); Serial.print(GX);
Serial.print(" | GY = "); Serial.println(GY);
Serial.print(" | GZ = "); Serial.println(GZ);

  delay(330);

}
