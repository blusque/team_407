/*
 * 请一定先阅读README！
 * 请一定先阅读README！
 * 请一定先阅读README！
 */

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
typedef struct
{
    int TrigPin;
    int EchoPin;
} VoiceInfo; //超声波模块结构

VoiceInfo v_module;

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

void setup()
{
    Serial.begin(9600);
    v_module.TrigPin = 8;
    v_module.EchoPin = 9;
}

void loop()
{
    if (Serial.available())
    {
        Serial.print("distance is: ");
        float distance = get_distance(v_module);
        delay(100);
    }
}
