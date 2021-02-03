#ifndef _MOVE_H_
#define _MOVE_H_
/*=========================基本运动函数========================*/
void MoveForw(); //前进

void SpeedUp(int max); //加速到某值

void MoveBack(); //后退

void TurnRight(); //向左平移

void TurnLeft(); //向右平移

void TurnRound(int deg); //原地转圈deg度,需测试得出

void SlowDown(); //减速到0

void Stop(); //停止
/*==========================================================*/
#endif