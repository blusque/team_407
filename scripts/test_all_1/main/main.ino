/*
作者：梅济东
时间：2021/1/29
功能：小车在超声波模式下的运动
            解决的问题主要有
            1.如何切入超声波模式；
            2.如何在超声波模式下避障；
            3.如何在超声波模式下转弯。
缺陷：未知
版本号：0.1.0
*/
#include <Servo.h>
#include "common.h"
#include "basic.h"
#include "move.h"
#include "trace.h"
#include "avoidance.h"

//定义与声明

Servo myServo; //舵机

CarInfo myCar;

VoiceInfo v_module; //定义超声波模块

RaredInfo s1, s2;

TyreInfo ty1, ty2, ty3, ty4; //定义四个轮

float dist[5] = {0.};
int mode = -1;   //-1是准备模式，0是循迹模式，1是超声波模式
int status = 1; //用于描述小车姿态是否已调整，0为未调整，1为已调整
//
int rx = 0;                  //右摇杆x轴参数，-255~255，现在为之后自控到手控切换留的接口
int ry = 0;                  //右摇杆y轴参数，-255~255
int lx = 0;                  //左摇杆x轴参数，-255~255
int ly = 0;                  //左摇杆y轴参数，-255~255
int turn = 0;                //判断是启动还是正常前进
int time = 0;

void car_initialize()
{
    /*
    小车各项参数（待测量）：
    myCar.len = ;
    myCar.wide = ;
    myCar.weight = ;
    myCar.d_of_voice = ;
    myCar.d_of_trace = ;
    */
    return;
}

int check_status()
{
    float dist_l = 0., dist_r = 0.;
    int status = 0;
    myServo.write(0);
    dist_l = get_distance(v_module);
    myServo.write(180);
    dist_r = get_distance(v_module);
    if (fabsf(dist_l - dist_r) < 3.)
    {
        status = 1;
        return status;
    }
    else
    {
        if (dist_l > dist_r)
        {
            TurnLeft();
            delay(50);
            Stop();
        }
        else
        {
            TurnRight();
            delay(50);
            Stop();
        }
        status = check_status();
    }
    return status;
}

void setup()
{
    v_module.TrigPin = 3;
    //超声波模块触发接口，可根据实际情况修改
    v_module.EchoPin = 4;
    //超声波模块接收接口，可根据实际情况修改
    myServo.attach(9);
    //舵机引脚，可根据实际情况修改

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
    int pos = 90;
    myServo.write(pos);

    car_initialize();
}

void loop()
{
    if (Serial.available())
    {
        if ((rx + ry) != 510 && (lx + ly) != 510)
        {
            if (mode == -1 && (Read(s1) == 0 && Read(s2) == 0))
            {
                mode = 0;
            }
            else if (mode == 0 && status == 1) //如果处于循迹模式下
            {
                Trace();
                if (Read(s1) == 0 && Read(s2) == 110)
                {
                    mode = 1;
                    status = 0;
                    status = check_status();
                }
            }
            else if (mode == 1) //如果处于超声波模式下
            {
                status = 0;
                avoidance(v_module);
                MoveForw();
                delayMicroseconds(100);
                if (Read(s1) == 0 && Read(s2) != 0)
                {
                    mode = 0;
                    status = 0;
                    status = check_status();
                }
            }
        }
    }
}
