#ifndef _TRACE_H_
#define _TRACE_H_
#include "common.h"
/*=========================红外循迹函数========================*/
int Read(RaredInfo s);

void TurnRound_R(int flag);

void TurnRound_L(int flag);

void TurnRight(int flag);

void TurnLeft(int flag);

void Trace();
/*=========================================================*/
#endif