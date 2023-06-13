#include <Servo.h>

Servo myservo; // 创建一个舵机实例

int angle=0; // 存储舵机的目标位置
int currentAngle; // 存储舵机的当前位置

void setup() {
  myservo.attach(D2,500,2500); // 将舵机连接到9号引脚
  Serial.begin(9600); // 启动串口通信
}

void loop() {
  if(Serial.available() > 0) { // 当串口有输入时
    angle = Serial.parseInt(); // 读取输入的角度值
    myservo.write(angle); // 将目标位置作为舵机的位置
    Serial.println(angle);
    delay(100);
    }
  }
  
