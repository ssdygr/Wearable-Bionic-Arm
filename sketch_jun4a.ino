#include<Wire.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

//接收方MAC地址 根据自己的板子修改
uint8_t broadcastAddress[] = {0x24,0xD7,0xEB,0xC8,0xE5,0xA5};

// 0x24, 0xD7, 0xEB, 0xC8, 0xE5, 0xA5  me

typedef struct XYZ{
  float X;
  float Y;
  float Z;
//  int head;
}XYZ;
XYZ ss;
XYZ s;
int fsrpin=0;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
//  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
//    Serial.println("Delivery success");
  }
  else{
//    Serial.println("Delivery fail");
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

//mpu初始化
if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
Serial.print("Accelerometer range set to: ");
mpu.getAccelerometerRange();
mpu.setGyroRange(MPU6050_RANGE_500_DEG);
Serial.print("Gyro range set to: ");
mpu.getGyroRange();
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
Serial.print("Filter bandwidth set to: ");
mpu.getFilterBandwidth();

  WiFi.mode(WIFI_STA);

  //立即初始化ESP
  if (esp_now_init() != 0) {
//    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //设置ESP8266角色  ESP_NOW_ROLE_CONTROLLER， ESP_NOW_ROLE_SLAVE， 
  //ESP_NOW_ROLE_COMBO， ESP_NOW_ROLE_MAX。
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  //先前创建的功能。
  esp_now_register_send_cb(OnDataSent);
  
  //与另一个ESP-NOW设备配对以发送数据
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  
  answer2();
  Serial.print("X:");
  Serial.println(s.X);
  Serial.println(s.Y);
  Serial.println(s.Z);
  esp_now_send(broadcastAddress, (uint8_t *) &s, sizeof(s));
  delay(100);
}

void getdata1(){
  byte b[sizeof(ss)];
  if(Serial.available()){
    for(int i=0;i<sizeof(ss);++i)
    {
        b[i]=Serial.read();   
        }
     memcpy(&s,b,sizeof(ss));
  }
}

void getdata2(){
  Serial.println("a");
  s.X=(int)Serial.read();
  Serial.println("b");
  s.Y=(int)Serial.read();
  Serial.println("c");
  s.Z=(int)Serial.read();
  delay(20);
}
void answer2(){
  float fsrReading = analogRead(fsrpin);
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  s.X=a.acceleration.x;
  s.Y=a.acceleration.y;
  s.Z=fsrReading;
  //  s.head=0;
  s.Z = a.acceleration.z;
//  Serial.println(s.X);
}


  