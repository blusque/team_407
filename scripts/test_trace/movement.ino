#include "common.h"

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