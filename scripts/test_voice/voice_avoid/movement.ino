//第一版基本运动代码，作者梅济东，王钰源，于2020/1/19
//功能：实现小车前进，后退，左右平移，定度转圈，减速以及停止功能
//缺陷：未知

/*
#include "struct.h"
void MoveForw();//前进

void SpeedUp(int max);//加速到某值

void MoveBack();//后退

void TurnRight();//向左平移

void TurnLeft();//向右平移

void TurnRound(int deg);//原地转圈deg度,需测试得出

void SlowDown();//减速到0

void Stop();//停止
*/

/*
小车模拟图：
ty1//  ------------------------ \\ty2
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
ty3\\ ----------------------- //ty4
*/

/*
{
    v1 = vty + vtx - w*(a + b)
    v2 = vty - vtx + w*(a + b)
    v3 = vty - vtx - w*(a + b)
    v4 = vty + vtx + w*(a + b)
    v1等是各轮的速度
    vty与vtx是底盘的速度
    y方向为前后，正前负后
    x方向为左右，正右负左
    w是底盘转动的角速度
    a和b是矢量臂
    可以反解方程组得到各轮速度
}
*/
#include "common.h"
#include "basic.h"

void SpeedUp(int max)
{
    int speed = 80;
    for (speed; speed <= max; speed += 10)
    {
        analogWrite(ty1.pwm, speed);
        analogWrite(ty2.pwm, speed);
        analogWrite(ty3.pwm, speed);
        analogWrite(ty4.pwm, speed);
        //以每50ms8个byte的速度上升
        delay(50);
    }
}

void SlowDown()
{
    for (int speed = 200; speed >= 0; speed -= 10)
    {
        analogWrite(ty1.pwm, speed);
        analogWrite(ty2.pwm, speed);
        analogWrite(ty3.pwm, speed);
        analogWrite(ty4.pwm, speed);
        delay(50);
    }
}

void Stop()
{
    SlowDown();
    digitalWrite(ty1.pin1, LOW);
    digitalWrite(ty1.pin2, LOW);
    digitalWrite(ty2.pin1, LOW);
    digitalWrite(ty2.pin2, LOW);
    digitalWrite(ty3.pin1, LOW);
    digitalWrite(ty3.pin2, LOW);
    digitalWrite(ty4.pin1, LOW);
    digitalWrite(ty4.pin2, LOW);
}

void MoveForw()
{
    digitalWrite(ty1.pin1, HIGH); //轮1正转
    digitalWrite(ty2.pin1, HIGH); //轮2正转
    digitalWrite(ty3.pin1, HIGH); //轮3正转
    digitalWrite(ty4.pin1, HIGH); //轮4正转
    digitalWrite(ty1.pin2, LOW);
    digitalWrite(ty2.pin2, LOW);
    digitalWrite(ty3.pin2, LOW);
    digitalWrite(ty4.pin2, LOW);
    int speed = 200;
    analogWrite(ty1.pwm, speed);
    analogWrite(ty2.pwm, speed);
    analogWrite(ty3.pwm, speed);
    analogWrite(ty4.pwm, speed);
    //以每50ms20个byte的速度上升
}

void TurnRight()
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
}

void TurnLeft()
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
}

void TurnRound(int deg) //左转为正，右转为负
{
    int a, b;              //a,b未知，为底盘几何中心到轮轴的x方向距离和y方向距离
    float w = M_PI / 6000; //小车转动时的角速度，公式为：+(-)(v - vty)/(a + b)。其中，v为各轮速度，vty为底盘y轴方向速度
    if (deg > 0)
    {
        while (fabsf(w * millis()) < fabsf(deg))
        {
            int speed1, speed2;
            speed1 = 120 + w * (a + b); //此处还需将w*（a + b）换算，下同，记得修改
            speed2 = 120 - w * (a + b);
            analogWrite(ty1.pwm, speed2);
            analogWrite(ty2.pwm, speed1);
            analogWrite(ty3.pwm, speed2);
            analogWrite(ty4.pwm, speed1);
        }
    }
    else
    {
        while (fabsf(w * millis()) < fabsf(deg))
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
}

void MoveBack()
{
    Stop();
    digitalWrite(ty1.pin2, HIGH);
    digitalWrite(ty2.pin2, HIGH);
    digitalWrite(ty3.pin2, HIGH);
    digitalWrite(ty4.pin2, HIGH);
    digitalWrite(ty1.pin1, LOW);
    digitalWrite(ty2.pin1, LOW);
    digitalWrite(ty3.pin1, LOW);
    digitalWrite(ty4.pin1, LOW);
    int speed = 120;
    analogWrite(ty1.pwm, speed);
    analogWrite(ty2.pwm, speed);
    analogWrite(ty3.pwm, speed);
    analogWrite(ty4.pwm, speed);
}
