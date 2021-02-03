#include "common.h"
#include "trace.h"

TyreInfo ty1, ty2, ty3, ty4;

RaredInfo s1, s2;

int time = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    //==========================================================
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(24, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(28, OUTPUT);
    pinMode(29, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    //==========================================================
    ty1.pin1 = 22; //轮1引脚1
    ty1.pin2 = 23; //轮1引脚2
    ty1.pwm = 2;   //轮1pwm引脚
    ty2.pin1 = 24;
    ty2.pin2 = 25;
    ty2.pwm = 3;
    ty3.pin1 = 26;
    ty3.pin2 = 27;
    ty3.pwm = 4;
    ty4.pin1 = 28;
    ty4.pin2 = 29;
    ty4.pwm = 5;
    //数字引脚不用17，18，19，20，21，22（这些引脚用于测试）
    //pwm引脚从2开始
    //以下为红外循迹接口
    s1.d1 = 1;
    s1.d2 = 2;
    s1.d3 = 3;
    s1.d4 = 4;
    s2.d1 = 5;
    s2.d2 = 6;
    s2.d3 = 7;
    s2.d4 = 8;
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    //这个是乱写的，可根据接线修改
}

void loop()
{
    if (Serial.available())
    {
        if (Serial.read() == 's')
        {
            time = 1;
            delay(100);
        }
        if (time)
        {
            Trace();
            delay(50);
        }
    }
}