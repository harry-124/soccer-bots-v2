
const int analogInPin = A0;
volatile int c2,c3,c4;
int sensorValue = 0;
volatile long int t2=0,t3 =0,t4 = 0,oldtime2 = 0,oldtime3=0,oldtime4=0;
#include <DCMotor.h>
dcm a(8,22,23);
dcm b(9,24,25);
dcm c(10,26,27);
dcm d(11,28,29);

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(18), count4, FALLING);
  attachInterrupt(digitalPinToInterrupt(2), count2, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), count3, FALLING);
  a.minit();
  b.minit();
  c2 =0;  
}

void loop() {
  float rpm2=0,rpm3,rpm4,kp=5.0,pid2,e2[20],e3[20],e4[20],r=30,s2 = 0,ki =1,  kd =2, d2=0,s3 = 0,d3 =0,s4 = 0,d4 = 0,pid3,pid4;
  int i=0;
  if (t2!=0){
    rpm2 = (60000.0)/(30*t2);
  }
  for(i = 0;i<19;i++){
    e2[i+1] = e2[i];
  }
  e2[0] = abs(r - rpm2);
  s2 = 0;
  for(i=0; i<20 ; i++){
    s2 += e2[i];
  }
  d2 = e2[0] - e2[1];
  if(r -rpm2< 0) e2[0] =0;
  pid2 = kp*e2[0] + ki*s2 + kd*d2;
  if(pid2> 255) pid2 =255;

  i=0;
  if (t3!=0){
    rpm3 = (60000.0)/(30*t3);
  }
  for(i = 0;i<19;i++){
    e3[i+1] = e3[i];
  }
  e3[0] = abs(r - rpm3);
  s3 = 0;
  for(i=0; i<20 ; i++){
    s3 += e3[i];
  }
  d3 = e3[0] - e3[1];
  if(r -rpm3< 0) e3[0] =0;
  pid3 = kp*e3[0] + ki*s3 + kd*d3;
  if(pid3> 255) pid3 =255;

  i=0;
  if (t4!=0){
    rpm4 = (60000.0)/(30*t4);
  }
  for(i = 0;i<19;i++){
    e4[i+1] = e4[i];
  }
  e4[0] = abs(r - rpm4);
  s4 = 0;
  for(i=0; i<20 ; i++){
    s4 += e4[i];
  }
  d4 = e4[0] - e4[1];
  if(r -rpm4< 0) e4[0] =0;
  pid4 = kp*e4[0] + ki*s4 + kd*d4;
  if(pid4> 255) pid4 =255;
  
  //Serial.print(rpm2);
  //Serial.print("  ");
  //Serial.print(rpm3);
  //S0erial.print("  ");
  Serial.println(c3);
  a.mspeed(pid2);
  b.mspeed(0);
  c.mspeed(pid4);
  d.mspeed(-255);
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

void count4(){
  c4++;
  t4 = millis() - oldtime4;
  oldtime4 = millis();
}
