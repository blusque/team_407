//本程序用于测试串口状态，若拷入程序启动之后小车一直处于前进状态，则说明串口数据会保持；若小车只有一瞬处于运动状态，则说明串口状态不保持
//注意：本测试只监视轮1

typedef struct
{
    int pin1;
    int pin2;
    int pwm;
} TyreInfo;

void MoveForw(); //前进

/*
小车模拟图：
ty1//  ------------------------ \\ty2
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
                ///////////
ty3\\ ----------------------- //ty4
*/

/*
{
    v1 = vty + vtx - w*(a + b)
    v2 = vty - vtx + w*(a + b)
    v3 = vty - vtx - w*(a + b)
    v4 = vty + vtx + w*(a + b)
    v1等是各轮的速度
    vty与vtx是底盘的速度
    y方向为前后，正前负后
    x方向为左右，正右负左
    w是底盘转动的角速度
    a和b是矢量臂
    可以反解方程组得到各轮速度
}
*/

TyreInfo ty1; //定义四个轮
int rx = 0;                  //右摇杆x轴参数，-255~255，现在为之后自控到手控切换留的接口
int ry = 0;                  //右摇杆y轴参数，-255~255
int lx = 0;                  //左摇杆x轴参数，-255~255
int ly = 0;                  //左摇杆y轴参数，-255~255
int turn = 0;                //判断是启动还是正常前进

void setup()
{
    Serial.begin(9600);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);
    ty1.pin1 = 18;
    ty1.pin2 = 19;
}

void loop()
{
    if ((rx + ry) != 510 && (lx + ly) != 510)
    {
        if (!turn)
        {
            MoveForw();
            turn++;
        }
    }
}

void MoveForw()
{
    digitalWrite(ty1.pin1, HIGH); //轮1正转
    digitalWrite(ty1.pin2, LOW);
    int speed = 200;
    analogWrite(ty1.pwm, speed);
    //以每50ms20个byte的速度上升
}
