//本代码摘自网络，网址：https://blog.csdn.net/qq_16775293/article/details/77744682，有改动
//请注意串口连接，与小组内写的不同
//请在测试完成之后将图片截图发在群里

int leftCounter = 0, rightCounter = 0;
unsigned long time = 0, old_time = 0; // 时间标记
unsigned long time1 = 0;              // 时间标记
float lv, rv;                         //左、右轮速度
int turn = 0;
//轮半径，需要修改（8是我乱填的^_^)
const int r = 8*2*M_PI;//单位cm

//注意这个地方，有宏定义
#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define TURNLEFT 3
#define TURNRIGHT 4
#define CHANGESPEED 5

int leftMotor1 = 16;
int leftMotor2 = 17;
int rightMotor1 = 18;
int rightMotor2 = 19;
bool speedLevel = 0;

int leftPWM = 2;
int rightPWM = 3;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    attachInterrupt(0, RightCount_CallBack, FALLING);
    attachInterrupt(1, LeftCount_CallBack, FALLING);

    pinMode(leftMotor1, OUTPUT);
    pinMode(leftMotor2, OUTPUT);
    pinMode(rightMotor1, OUTPUT);
    pinMode(rightMotor2, OUTPUT);
    pinMode(leftPWM, OUTPUT);
    pinMode(rightPWM, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    SpeedDetection();

    if (!turn)
    {
        turn++;
        Serial.println("Speed(cm/s)");
    }
    else
    {
        if (Serial.available() > 0)
        {
            char cmd = Serial.read();

            Serial.print(cmd);
            motorRun(cmd);
            if (speedLevel) //根据不通的档位输出不同速度
            {
                analogWrite(leftPWM, 120);
                analogWrite(rightPWM, 120);
            }
            else
            {
                analogWrite(leftPWM, 200);
                analogWrite(rightPWM, 200);
            }
        }
    }
}
/*
 * *速度计算
 */
bool SpeedDetection()
{
    time = millis();                  //以毫秒为单位，计算当前时间
    if (abs(time - old_time) >= 1000) // 如果计时时间已达1秒
    {
        detachInterrupt(0); // 关闭外部中断0
        detachInterrupt(1); // 关闭外部中断1
        //把每一秒钟编码器码盘计得的脉冲数，换算为当前转速值
        //转速单位是每分钟多少转，即r/min。这个编码器码盘为20个空洞。
        //Serial.print("left:");
        lv = (float)leftCounter * 60 / 20;  //小车车轮电机转速
        rv = (float)rightCounter * 60 / 20; //小车车轮电机转速
        Serial.print("left speed:");
        Serial.print(lv*r); //向上位计算机上传左车轮电机当前转速的高、低字节
        Serial.print("     right speed:");
        Serial.println(rv*r); //向上位计算机上传左车轮电机当前转速的高、低字节
        //恢复到编码器测速的初始状态
        leftCounter = 0; //把脉冲计数值清零，以便计算下一秒的脉冲计数
        rightCounter = 0;
        old_time = millis();                              // 记录每秒测速时的时间节点
        attachInterrupt(0, RightCount_CallBack, FALLING); // 重新开放外部中断0
        attachInterrupt(1, LeftCount_CallBack, FALLING);  // 重新开放外部中断0
        return 1;
    }
    else
        return 0;
}
/*
 * *右轮编码器中断服务函数
 */
void RightCount_CallBack()
{
    rightCounter++;
}
/*
 * *左轮编码器中断服务函数
 */
void LeftCount_CallBack()
{
    leftCounter++;
}
/*
 * *小车运动控制函数
 */
void motorRun(int cmd)
{
    switch (cmd)
    {
    case FORWARD:
        Serial.println("FORWARD"); //输出状态
        digitalWrite(leftMotor1, HIGH);
        digitalWrite(leftMotor2, LOW);
        digitalWrite(rightMotor1, HIGH);
        digitalWrite(rightMotor2, LOW);
        break;
    case BACKWARD:
        Serial.println("BACKWARD"); //输出状态
        digitalWrite(leftMotor1, LOW);
        digitalWrite(leftMotor2, HIGH);
        digitalWrite(rightMotor1, LOW);
        digitalWrite(rightMotor2, HIGH);
        break;
    case TURNLEFT:
        Serial.println("TURN  LEFT"); //输出状态
        digitalWrite(leftMotor1, HIGH);
        digitalWrite(leftMotor2, LOW);
        digitalWrite(rightMotor1, LOW);
        digitalWrite(rightMotor2, HIGH);
        break;
    case TURNRIGHT:
        Serial.println("TURN  RIGHT"); //输出状态
        digitalWrite(leftMotor1, LOW);
        digitalWrite(leftMotor2, HIGH);
        digitalWrite(rightMotor1, HIGH);
        digitalWrite(rightMotor2, LOW);
        break;
    case CHANGESPEED:
        Serial.println("CHANGE SPEED"); //输出状态
        if (speedLevel)                 //接收到换挡命令的时候切换档位
            speedLevel = 0;
        else
            speedLevel = 1;
        break;
    case 'q':
    default:
        Serial.println("STOP"); //输出状态
        digitalWrite(leftMotor1, LOW);
        digitalWrite(leftMotor2, LOW);
        digitalWrite(rightMotor1, LOW);
        digitalWrite(rightMotor2, LOW);
    }
}