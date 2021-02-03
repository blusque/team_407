#ifndef _COMMON_H_
#define _COMMON_H_
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

extern CarInfo myCar;

extern RaredInfo s1, s2;

extern TyreInfo ty1, ty2, ty3, ty4; //定义四个轮
#endif