#include "common.h"
 #include "move.h"
 #include "basic.h"

int Read(RaredInfo s)
{
  return (digitalRead(s.d1)*1000 + digitalRead(s.d2) * 100 + digitalRead(s.d3) * 10 + digitalRead(s.d4));
}//读取红外模块信号

void TurnRound_R(int flag)
{
    int a, b;                
    float w = M_PI / 6000;
    while (Read(s1)*10000+Read(s2)==0||Read(s1)*10000+Read(s2)==flag)//当状态发生变化且能找到黑线时停止
      {
          int speed1, speed2;
          speed1 = 120 + w * (a + b);
          speed2 = 120 - w * (a + b);
          analogWrite(ty1.pwm, speed2);
          analogWrite(ty2.pwm, speed1);
          analogWrite(ty3.pwm, speed2);
          analogWrite(ty4.pwm, speed1);
      }
}

void TurnRound_L(int flag)
{
    int a, b;                
    float w = M_PI / 6000; 
    while (Read(s1)*10000+Read(s2)==0||Read(s1)*10000+Read(s2)==flag)
      {
          int speed1, speed2;
          speed1 = 120 - w * (a + b);
          speed2 = 120 + w * (a + b);
          analogWrite(ty1.pwm, speed2);
          analogWrite(ty2.pwm, speed1);
          analogWrite(ty3.pwm, speed2);
          analogWrite(ty4.pwm, speed1);
      }
}

void TurnRight(int flag)
{
    Stop();
    digitalWrite(ty1.pin1, HIGH);
    digitalWrite(ty2.pin2, HIGH);
    digitalWrite(ty3.pin2, HIGH);
    digitalWrite(ty4.pin1, HIGH);
    digitalWrite(ty1.pin2, LOW);
    digitalWrite(ty2.pin1, LOW);
    digitalWrite(ty3.pin1, LOW);
    digitalWrite(ty4.pin2, LOW);
    int speed = 120;
    analogWrite(ty1.pwm, speed);
    analogWrite(ty2.pwm, speed);
    analogWrite(ty3.pwm, speed);
    analogWrite(ty4.pwm, speed);
    while (Read(s1)*10000+Read(s2)==flag);
    Stop;
}

void TurnLeft(int flag)
{
    Stop();
    digitalWrite(ty1.pin2, HIGH);
    digitalWrite(ty2.pin1, HIGH);
    digitalWrite(ty3.pin1, HIGH);
    digitalWrite(ty4.pin2, HIGH);
    digitalWrite(ty1.pin1, LOW);
    digitalWrite(ty2.pin2, LOW);
    digitalWrite(ty3.pin2, LOW);
    digitalWrite(ty4.pin1, LOW);
    int speed = 120;
    analogWrite(ty1.pwm, speed);
    analogWrite(ty2.pwm, speed);
    analogWrite(ty3.pwm, speed);
    analogWrite(ty4.pwm, speed);
    while (Read(s1)*10000+Read(s2)==flag);
    Stop();
}

void Trace()
{
    int flag;
    switch (flag = Read(s1) * 10000 + Read(s2))
    {
    case 0:
        TurnRound_R(flag); //原地转圈

    case 1100110: //理想情况
        MoveForw();
        break; //直行

    case 100010: //左边离开黑线，但仍与黑线平行
    case 10001:  //严重偏移，发生概率不大
    case 10000:
    case 1:
    case 100000:
    case 10:
        TurnRight(flag);
        delay(50);
        break; //右平移

    case 1000100: //右边离开黑线，但仍与黑线平行
    case 10001000:
    case 10000000:
    case 1000:
    case 1000000:
    case 100:
        TurnLeft(flag);
        delay(50);
        break; //左平移

    case 100110:
    case 1100100:
    case 100100:
    case 10110:
    case 110110:
    case 1110110:
        Stop();
        TurnRound_R(flag); //转动一定的角度,角度可在测试后确定
        break;             //原地顺时针转动

    case 1000110:
    case 1100010:
    case 1000010:
    case 10000110:
    case 11000110:
    case 11100110:
        Stop();
        TurnRound_L(flag);
        break; //逆时针转动

    case 1100000:
    case 110:
        int flag_s;
        TurnRound_R(flag);
        if (Read(s1) * 10000 + Read(s2) == 10000000)
        {
            flag_s = Read(s1) * 10000 + Read(s2);
            TurnRound_L(flag_s);
            TurnRound_L(flag);
        }
    }
}