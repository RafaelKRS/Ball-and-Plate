#include <Servo.h>

//#include "DoubleEMAFilterLib.h"

Servo servo_x;  // create servo object to control a servo
Servo servo_y;

const int X1=A2,Y1=A3,X2=A4,Y2=A5,button=6;

boolean touch();

float x_cord=0,y_cord=0,val=0,count=-1,arr[11],k=0;      
float y=0;
float alpha=0.29;//0.290
float alpha_y=0.28;
float s=0;
float p=0;
float e_x=0;
float e_y;
int sp_x=350;
int sp_y=400;
float d_x;
float d_y;
float e_ant_x=0;
float e_ant_y=0;
float co_x;
float co_y;
float kp_x=0.05;
float kd_x=1.1;
float kp_y=0.06;
float kd_y=1.6;
float e;
float sw_x;
float sw_y;
float sw_x1;
float sw_y1;
//DoubleEMAFilter<float> doubleEMAFilter(0.6, 0.9);
void setup() 
{
Serial.begin(115200);
servo_x.attach(3);
servo_y.attach(2);
}

void loop() 
{

while(touch()>0)
   {

     s=(alpha*x_cord)+((1-alpha)*s);
     p=(alpha_y*y_cord)+((1-alpha_y)*p);

      

        Serial.print((s*5)/1023);
        Serial.print(",");
        Serial.print(2.33);//(550*5)/1023
        Serial.print(",");
        Serial.print((p*5)/1023);
        Serial.print(",");
        Serial.println(2.18);//600*5)/1023
       
        e_x=sp_x-s;
   co_x=kp_x*e_x+kd_x*d_x;
   d_x=e_x-e_ant_x;
   e_ant_x=e_x;
   
   sw_x=90+(co_x*(-1));
   if (sw_x<=35){
    sw_x=35;
   }
   if (sw_x>=180){
    sw_x=180;
   }
   sw_x1=(0.3*(sw_x*100))+int((0.7)*sw_x1);
 
   servo_x.write(sw_x1/100); 

   
   ////////////////////////////////////////////////////////////////////////////////////
    e_y=sp_y-p;
   co_y=kp_y*e_y+kd_y*d_y;
   d_y=e_y-e_ant_y;
   e_ant_y=e_y;
   co_y=co_y*(-1);
   sw_y=75+(co_y);
   if (sw_y<=0){
    sw_y=0;
   }
   if (sw_y>=125){
    sw_y=125;
   }
     
       sw_y1=(0.3*(sw_y*100))+int((0.7)*sw_y1);
   servo_y.write(sw_y1/100);
}
}

boolean touch()
      {
      boolean touch1=false; 
       
      pinMode(X1,OUTPUT);
      pinMode(X2,OUTPUT);
      pinMode(Y1,INPUT);
      pinMode(Y2,INPUT);
      digitalWrite(X1,LOW);
      digitalWrite(X2,HIGH);
      
      y_cord=analogRead(Y2);

     digitalWrite(X1,LOW);
      digitalWrite(X2,LOW);
       delay(15);
      
      pinMode(Y1,OUTPUT);
      pinMode(Y2,OUTPUT);
      pinMode(X1,INPUT);
      pinMode(X2,INPUT);
      
      digitalWrite(Y1,LOW);
      digitalWrite(Y2,HIGH);
      
      
      x_cord=analogRead(X2);

      digitalWrite(Y1,LOW);
      digitalWrite(Y2,LOW);
      delay(15);
      if(x_cord>0 && x_cord<1000 && y_cord>0 && y_cord<1000)
       touch1=true;
      
      return touch1;
      }
