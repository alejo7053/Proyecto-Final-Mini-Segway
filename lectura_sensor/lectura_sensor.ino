#include <Wire.h>
//Direccion I2C de la MPU
#define MPU 0x68
#define GYRO_CONFIG 0x1B
//MPU-6050 da los valores en enteros de 16 bits
//valores en bruto
int16_t GY;


void setup() {
 Wire.begin();
 Wire.beginTransmission(MPU);
 Wire.write(0x6B);
 Wire.write(0);
 Wire.endTransmission(true);
 Wire.begin();
 Wire.beginTransmission(MPU);
 Wire.write(GYRO_CONFIG);
 Wire.write(3<<3);
 Wire.endTransmission(true);
 Serial.begin(9600);
}

void loop() {
  
Wire.beginTransmission(MPU);
Wire.write(0x45); //pedimos el registro 0x45-corresponde al giroscopio en Y
Wire.endTransmission(false);
Wire.requestFrom(MPU,0,true);//apartir  del registro 0x45, pedimos el resto de registros
GY=Wire.read()<<8|Wire.read();
Serial.print("GY = "); 
Serial.println(GY);

  delay(10);

}
