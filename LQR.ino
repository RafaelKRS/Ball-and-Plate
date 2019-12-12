#include <Servo.h>



Servo servo_x;  // create servo object to control a servo
Servo servo_y;

const int X1=A2,Y1=A3,X2=A4,Y2=A5;

boolean touch();
float x_cord=0,y_cord=0;   
float x_cord_o=550,y_cord_o=475;      
float alpha=0.3;//0.290
float alpha_y=0.3;
float s=0;
float p=0;

float s_old;
float p_old;
int delay1=15;
int in=2;/////////////////////////////////////////////////////////////////webadas/////////////////////////////////////
float in_x=92;
float in_y=85;

float Velx=0;
float Vely=0;
float sw_x=0;
float sw_y=0;
float sw_x1=90;
float sw_y1=90;
float sw_x_o=0;
float sw_y_o=0;

float spx;
float spy;
float c=100;
unsigned long tiempo_A = 0;
unsigned long tiempo_B = 0;
unsigned long tiempoSegundos = 0;

unsigned long timeold;

void setup()
{
Serial.begin(115200);
servo_x.attach(3);
servo_y.attach(2);
  servo_x.write(88);    
  servo_y.write(72);
  tiempo_A = millis();
}

void loop()
{
  while(touch()>0)
  { 
    s=(alpha*x_cord)+((1-alpha)*s);
    p=(alpha_y*y_cord)+((1-alpha_y)*p);


    tiempo_B = millis();
    if(tiempo_B > (tiempo_A+30)){  //Si ha pasado 2 segundos ejecuta el IF
        tiempo_A = millis(); //Actualiza el tiempo actual
        c=c-1;
    }
    if (c<0){c=100;}
    spx=550+210*cos(3.1415*2*c/100);
    spy=500+100*sin(3.1415*2*c/100);
   
    if (in==1){
        spx=500;
        spy=400;
      }else{
        spx=500+210*cos(3.1415*2*c/100);
        spy=350+140*sin(3.1415*2*c/100);}
///////////////////////////////////////////////////////        
       Serial.print((s*5)/1023);
        Serial.print(",");
        Serial.print((spx*5)/1023);//(550*5)/1023
        Serial.print(",");
        Serial.print((p*5)/1023);
        Serial.print(",");
        Serial.println((spy*5)/1023);//(600*5)/1023
                          ////
//////////////////////////////////////////////////////        
    //////VELOCIDAD/////
    Velx = ((s-s_old)/490)*(1/((2*delay1)/1000));
    Vely = ((p-p_old)/380)*(1/((2*delay1)/1000));
//   
    p_old=p;
    s_old=s;
    ////////////////LQR///////////////
    sw_x  =10*(-2.95*(((spx-s)/4900)) - 6.970*Velx);
    sw_y  =10*(-5*(((spy-p)/3800)) - 10*Vely);

   
    sw_x= 180/3.1415*asin((0.148*(sin(3.1415*(sw_x)/180)))/0.02);
    sw_y= 180/3.1415*asin((0.124*(sin(3.1415*(sw_y)/180)))/0.02);
    if(abs(sw_x-sw_x_o)>60){sw_x=sw_x_o;sw_x_o=sw_x;}
    if(abs(sw_y-sw_y_o)>60){sw_y=sw_y_o;sw_y_o=sw_y;}


    
    sw_x1=(0.3*(sw_x*100))+int((0.7)*sw_x1);
    sw_y1=(0.3*(sw_y*100))+int((0.7)*sw_y1);
    
    sw_x=97.2+sw_x1/100;
    sw_y=77.3+sw_y1/100;
 
    if (sw_x<=35){
      sw_x=38;}
    if (sw_y<=0){
      sw_y=0;
    }
    if (sw_y>=125){
      sw_y=125;
    }
    
    
    if (sw_x>=180){
      sw_x=180;
    }
    
  //Serial.println(sw_x);
    servo_x.write(sw_x);    
    servo_y.write(sw_y);
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
