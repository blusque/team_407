#include "common.h"
#include "move.h"
#include "basic.h"

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
    dist[front] = get_distance(v_module);
    if (dist[front] > 20)
        return;
    else
    {
        Stop(); //小车停止
        myServo.write(0);
        delay(500);
        dist[left] = get_distance(v_module);
        myServo.write(45);
        delay(500);
        dist[lfront] = get_distance(v_module);
        myServo.write(135);
        delay(500);
        dist[rfront] = get_distance(v_module);
        myServo.write(180);
        delay(500);
        dist[right] = get_distance(v_module);
        if ((dist[right] < dist[left]) || (dist[rfront] < dist[lfront]))
            TurnRound(90);
        else
            TurnRound(-90);
    }
    myServo.write(90);
    delay(500);
}
