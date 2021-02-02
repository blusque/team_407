#ifndef _AVOIDANCE_H_
#define _AVOIDANCE_H_
#include "common.h"
/*=========================超声避障函数========================*/
float get_distance(const VoiceInfo &v_module); //测量距离

void avoidance(const VoiceInfo &v_module);
/*=========================================================*/
#endif