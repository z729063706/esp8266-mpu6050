#include<Wire.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
const int MPU6050_addr=0x68;
int16_t AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;
const char* ssid = "";//ssid
const char* password = "";//密码
const char* host = "";//电脑ip
const int httpsPort = 8000;
const String url = "/";
bool Debug = 0;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED)
  {
     delay(500);
     Serial.print(".");
  }//等待连接验证
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop(){
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  AccX=Wire.read()<<8|Wire.read();
  AccY=Wire.read()<<8|Wire.read();
  AccZ=Wire.read()<<8|Wire.read();
  Temp=Wire.read()<<8|Wire.read();
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();
  if (Debug)//调试信息
  {
    Serial.print("AccX = "); Serial.print(AccX);
    Serial.print(" || AccY = "); Serial.print(AccY);
    Serial.print(" || AccZ = "); Serial.print(AccZ);
    Serial.print(" || Temp = "); Serial.print(Temp/340.00+36.53);
    Serial.print(" || GyroX = "); Serial.print(GyroX);
    Serial.print(" || GyroY = "); Serial.print(GyroY);
    Serial.print(" || GyroZ = "); Serial.println(GyroZ);
    Serial.print("\n");
  }
  if (abs(GyroY)>500)//大于阈值，发送数据包，如果不灵敏改成300
  {
    Serial.print("Done\n");
    WiFiClient client;
    String postRequest =(String)("GET ") + url + "/ HTTP/1.1\r\n";
    client.connect(host, httpsPort);
  }
  delay(1000);//一秒之内关门，如果不明显改成500
}
