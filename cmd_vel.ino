#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

//#define LEFT_EN A1
#define LEFT_FR 7
#define LEFT_PG 6
#define LEFT_SV 5
//#define RIGHT_EN 12
#define RIGHT_FR 4
#define RIGHT_PG 3
#define RIGHT_SV 2
#define ROBOT_WIDTH 300
#define LEFT 0
#define RIGHT 1
unsigned char channel;
unsigned char dir;
unsigned char spd;
unsigned char leftSpd;
unsigned char leftDir;
unsigned char rightSpd;
unsigned char rightDir;
unsigned char recBuf;
double left_vel;
double right_vel;
long lasttim;
long tim;
ros::NodeHandle nh;
void setSpeed (char channel, double vel);

void messageCb(const geometry_msgs::Twist& cmd_vel)
{
    lasttim=millis();
    Serial.println("recevied");
    double vel_x=cmd_vel.linear.x;
    double vel_th=cmd_vel.angular.z;
    left_vel=vel_x-vel_th*ROBOT_WIDTH/2000;
    right_vel=vel_x+vel_th*ROBOT_WIDTH/2000;
    setSpeed(LEFT,left_vel);
    setSpeed(RIGHT,right_vel);
}

void setSpeed(char channel,double vel)
{
    vel= vel*255;
    if(vel>255)
    {
        dir=1;
        spd=255;
    }else if(vel>10)
    {
        dir=1;
        spd=(unsigned char)vel;
    }else if(vel>-10)
    {
        spd=0;
    }else if(vel>-255)
    {
        spd=(unsigned char)(-vel);
        dir=0;
    }
    else
    {
        dir=0;
        spd=255;
    }
    if(channel== LEFT)
    {
        digitalWrite(LEFT_FR, dir);
        analogWrite (LEFT_SV,spd);
    }else if(channel== RIGHT)
    {
        digitalWrite(RIGHT_FR, dir);
        analogWrite (RIGHT_SV,spd);
    }
}


ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", messageCb);

void setup()
{
//    pinMode(LED_BUILTIN, OUTPUT);
//    pinMode(LEFT_EN, OUTPUT);
    pinMode(LEFT_FR, OUTPUT);
    pinMode(LEFT_SV, OUTPUT);
//    pinMode(RIGHT_EN, OUTPUT);
    pinMode(RIGHT_FR, OUTPUT);
    pinMode(RIGHT_SV, OUTPUT);
    Serial.begin(57600);
    nh.initNode();
    nh.subscribe(sub);
    leftSpd=0;
    leftDir=0;
    rightSpd=0;
    rightDir=0;
//    digitalWrite(LEFT_EN, LOW);
    digitalWrite(LEFT_FR, leftDir);
//    digitalWrite(RIGHT_EN, LOW);
    digitalWrite(RIGHT_FR, rightDir);
    digitalWrite (LEFT_SV,leftSpd);
    digitalWrite (RIGHT_SV,rightSpd);
}
void loop()
{
//    Serial.println(sub.data);
    tim = millis();
    if((tim-lasttim)>1000)
    {
        setSpeed(LEFT,0);
        setSpeed(RIGHT,0);
    }
    nh.spinOnce();
    delay(1);
}
