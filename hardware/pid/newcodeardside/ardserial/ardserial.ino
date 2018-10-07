#include <DCMotor.h>


dcm m3(8,22,23);
dcm m2(9,24,25);
dcm m1(10,26,27);
dcm d(11,28,29);

volatile long int oldtime1,c1=0,t1,rpm1,e1,eo1,es1,ed1,kp1=4,kd1=1,ki1=1,pid1,r1=-30,dir1,rpmo1;
volatile long int oldtime2,c2=0,t2,rpm2,e2,eo2,es2,ed2,kp2=4,kd2=1,ki2=1,pid2,r2=-30,dir2,rpmo2;
volatile long int oldtime3,c3=0,t3,rpm3,e3,eo3,es3,ed3,kp3=4,kd3=1,ki3=1,pid3,r3=-30,dir3,rpmo3;

volatile int k,ds;

void setup() 
{
  m3.minit();
  m2.minit();
  m1.minit();
  attachInterrupt(digitalPinToInterrupt(2), count1, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), count2, FALLING);
  attachInterrupt(digitalPinToInterrupt(18), count3, FALLING);
  d.minit();
  Serial.begin(9600);
  pinMode(7,OUTPUT);
}

void loop() 
{
    ser();
    getspeed();
    actuate1(r1);
    actuate3(r2);
    actuate2(r3);
    d.mspeed(ds);

    if(k==1){
      digitalWrite(7,HIGH);
    }
    else{
      digitalWrite(7,LOW);
    }
    
    /*if(rpmo1==rpm1) {rpm1=0;m1.mspeed(dir1*255);}
    if(rpmo2==rpm2) {rpm2=0;actuate2(dir2*255);}
    if(rpmo3==rpm3) {rpm3=0;actuate3(dir3*255);}
    rpmo1 = rpm1;
    rpmo2 = rpm2;
    rpmo3 = rpm3;*/
}

void printsp(){
    Serial.print(rpm1);
    Serial.print("  ");
    Serial.print(pid1);
    Serial.print("  ");
    Serial.print(rpm2);
    Serial.print("  ");
    Serial.print(pid2);
    Serial.print("  ");
    Serial.print(rpm3);
    Serial.print("  ");
    Serial.println(pid3);  
}

void getspeed(){
  if (t1!=0)
    {
      rpm1 = (60000)/(30*t1);
    }
    if (t2!=0)
    {
      rpm2 = (60000)/(30*t2);
    }
    if (t3!=0)
    {
      rpm3 = (60000)/(30*t3);
    }
}

void actuate1(int r){
    detachInterrupt(2);
    detachInterrupt(3);
    detachInterrupt(18);
    dir1 = r/abs(r);

    e1 = abs(r - dir1*rpm1);
    ed1 = (e1 - eo1);
    es1 += e1;

    pid1 = kp1*e1 + kd1*ed1 + ki1*es1;
    
    if(pid1>255) pid1 = 255;

    if(abs(r-rpm1)<5) es1=0;

    if(abs(rpm1)>abs(r)) m1.mspeed(0);
    else m1.mspeed(dir1*pid1);

    eo1 = e1;
    attachInterrupt(digitalPinToInterrupt(2), count1, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), count2, FALLING);
    attachInterrupt(digitalPinToInterrupt(18), count3, FALLING);
}

void actuate2(int r){
    detachInterrupt(2);
    detachInterrupt(3);
    detachInterrupt(18);
    dir2 = r/abs(r);

    e2 = abs(r - dir2*rpm2);
    ed2 = (e2 - eo2);
    es2 += e2;

    pid2 = kp2*e2 + kd2*ed2 + ki2*es2;
    
    if(pid2>255) pid2 = 255;

    if(abs(r-rpm2)<5) es2=0;

    if(abs(rpm2)>abs(r)) m2.mspeed(0);
    else m2.mspeed(dir2*pid2);

    eo2 = e2;
    attachInterrupt(digitalPinToInterrupt(2), count1, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), count2, FALLING);
    attachInterrupt(digitalPinToInterrupt(18), count3, FALLING);
}

void actuate3(int r){
    detachInterrupt(2);
    detachInterrupt(3);
    detachInterrupt(18);
    dir3 = r/abs(r);

    e3 = abs(r - dir3*rpm3);
    ed3 = (e3 - eo3);
    es3 += e3;

    pid3 = kp3*e3 + kd3*ed3 + ki3*es3;
    
    if(pid3>255) pid3 = 255;

    if(abs(r-rpm3)<5) es3=0;

    if(abs(rpm3)>abs(r)) m3.mspeed(0);
    else m3.mspeed(dir3*pid3);

    eo3 = e3;
    attachInterrupt(digitalPinToInterrupt(2), count1, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), count2, FALLING);
    attachInterrupt(digitalPinToInterrupt(18), count3, FALLING);
}

void count1(){
  c1++;
  t1 = millis() - oldtime1;
  oldtime1 = millis();
}

void count2(){
  c2++;
  t2 = millis() - oldtime2;
  oldtime2 = millis();
}

void count3(){
  c3++;
  t3 = millis() - oldtime3;
  oldtime3 = millis();
}

void ser()
{
  while(!Serial.available());
  r1=-Serial.readStringUntil('\t').toInt();
  r2=-Serial.readStringUntil('\t').toInt();
  r3=-Serial.readStringUntil('\t').toInt();
  ds=Serial.readStringUntil('\t').toInt();
  k = Serial.readStringUntil('\n').toInt(); 
}