#ifndef _COMMON_H_
#define _COMMON_H_
#include <Servo.h>
typedef struct
{
    /* data */
    float len;        //小车长度（长边
    float wide;       //小车宽度（短边
    float height;     //小车高度
    float weight;     //小车重量
    float d_of_voice; //超声波模块与小车边缘距离
    float d_of_trace; //循迹模块参数
} CarInfo;

typedef struct
{
    int TrigPin;
    int EchoPin;
} VoiceInfo; //超声波模块结构

//电工胶带只有18mm，也就是说中间两个探头起主要作用
typedef struct
{
    int d1;
    int d2;
    int d3;
    int d4;
} RaredInfo; //红外模块 1-4从左到右

typedef struct
{
    int pin1;
    int pin2;
    int pwm;
} TyreInfo; //小轮模块结构
extern Servo myServo; //舵机

extern CarInfo myCar;

extern VoiceInfo v_module; //定义超声波模块

extern RaredInfo s1, s2;

extern TyreInfo ty1, ty2, ty3, ty4; //定义四个轮

extern float dist[5];
extern int mode;   //0是循迹模式，1是超声波模式
extern int status; //用于描述小车姿态是否已调整，0为未调整，1为已调整
//
extern int rx;   //右摇杆x轴参数，-255~255，现在为之后自控到手控切换留的接口
extern int ry;   //右摇杆y轴参数，-255~255
extern int lx;   //左摇杆x轴参数，-255~255
extern int ly;   //左摇杆y轴参数，-255~255
extern int turn; //判断是启动还是正常前进
#endif