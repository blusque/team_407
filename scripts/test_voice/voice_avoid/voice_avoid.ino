/*
 * 请先阅读README！
 * 请先阅读README！
 * 请先阅读README！
 * 请先完成voice_dist的测试！
 * 请先完成voice_dist的测试！
 * 请先完成voice_dist的测试！
 */

#include <Servo.h>
#include "common.h"
#include "basic.h"
#include "move.h"

CarInfo myCar;

VoiceInfo v_module;

Servo myServo; //舵机

TyreInfo ty1, ty2, ty3, ty4; //定义四个轮

float dist[5];

int flag = 0;//0表示程序处于中断状态

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

float get_distance(const VoiceInfo &v_module) //测量距离
{
    double time = 0.;
    double distance = 0.;
    digitalWrite(v_module.TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(v_module.EchoPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(v_module.TrigPin, LOW);
    time = pulseIn(v_module.EchoPin, HIGH);
    distance = time / 58.;
    Serial.println(distance);
    return distance;
}

void avoidance(const VoiceInfo &v_module)
{
    Serial.print("front dist: ");
    dist[front] = get_distance(v_module);
    if (dist[front] > 20)
        return;
    else
    {
        Stop(); //小车停止
        myServo.write(0);
        delay(500);
        Serial.print("left dist: ");
        dist[left] = get_distance(v_module);
        myServo.write(45);
        delay(500);
        Serial.print("left_middle dist: ");
        dist[lfront] = get_distance(v_module);
        myServo.write(135);
        delay(500);
        Serial.print("right_middle dist: ");
        dist[rfront] = get_distance(v_module);
        myServo.write(180);
        delay(500);
        Serial.print("right dist: ");
        dist[right] = get_distance(v_module);
        if ((dist[right] < dist[left]) || (dist[rfront] < dist[lfront]))
            TurnRound(90);
        else
            TurnRound(-90);
    }
    myServo.write(90);
    delay(500);
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
    int pos = 90;
    myServo.write(pos);

    car_initialize();
}

void loop()
{
    if (Serial.available())
    {
        if (Serial.read() == 's')//如果输入's'，表示开始程序
        {
            flag = 1;
        }
        if (flag)
        {
            avoidance(v_module);
            delay(100);
        }
    }
}
