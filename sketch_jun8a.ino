//接收
#include <ESP8266WiFi.h>
#include <espnow.h>
#include<Servo.h>
//接收数据保存的结构体和发送方一致
typedef struct XYZ{
  float X;
  float Y;
  float Z;
//  int head;
}XYZ;
XYZ s;

Servo down,left,right,head;
int downnum=0,leftnum=0,rightnum=0;

//创建一个回调函数作为接收数据后的串口显示
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&s, incomingData, sizeof(s));
}

void setup() {
  //初始化窗口
  Serial.begin(9600);
  servoset();
  //设置ESP8266模式
  WiFi.mode(WIFI_STA);

  //初始化 ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //设置ESP8266角色：
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  //先前创建的功能 测试ESP-NOW通信
  esp_now_register_recv_cb(OnDataRecv);
}

void servoset(){
  head.attach(D3,500,5000);
  // roll
  down.attach(D4,500,5000);
  // pitch
  left.attach(D5,500,5000);
  right.attach(D6,500,5000);
//  left.write(130);
  down.write(90);
  right.write(45);
  left.write(130);
  head.write(90);
//  Serial.println(head.read());
}
void loop(){
  servomove();
//  headwork();
 Serial.println("angle");
 Serial.println(s.X);
 Serial.println(s.Y);
 Serial.println(s.Z);
  delay(100);
}

void servomove()
{
  if(s.X<-1.2){
    int temp=right.read();
    for(int i=0;i<10;++i){
      temp++;
      if(temp<180)
      right.write(temp);
     
      delay(25);
    }
  }


  if(s.X>1.2){
    int temp=right.read();
    for(int i=0;i<10;++i){
      temp--;
      if(temp>40);
      right.write(temp);
      
      delay(25);
    }
  }
  if(s.Y<-2){
    int temp=down.read();
    for(int i=0;i<10;++i){
      temp++;
      if(temp<180)
      down.write(temp);
      delay(25);
    }
  }
  if(s.Y>2){
    int temp=down.read();
    for(int i=0;i<10;++i){
      temp--;
      if(temp>0);
      down.write(temp);
      delay(25);
    }
  }
  if(s.Z<800){
      int temp=head.read();
    for(int i=temp;i>=60;--i){
      head.write(i);
      delay(25);
    }
  }
}
void leftwork(int rightservo){
    if(rightservo>120){
      int temp=left.read();
      for(int i=temp;i<=140;++i){
         left.write(i);
         delay(25);
      }
    }

    if(rightservo<90){
      int temp=left.read();
      for(int i=temp;i>=130;--i){
         left.write(i);
         delay(25);
      }
    }
  }
void downwork(){  
}