#include <DCMotor.h>

#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();

Rx16Response rx16 = Rx16Response();


uint8_t option = 0;
uint8_t data;


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
  attachInterrupt(digitalPinToInterrupt(19), count1, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), count2, FALLING);
  attachInterrupt(digitalPinToInterrupt(18), count3, FALLING);
  d.minit();
  Serial3.begin(115200);
  Serial.begin(9600);
  xbee.setSerial(Serial3);
  pinMode(7,OUTPUT);
}

void loop() 
{
    xbee.readPacket();
    getspeed();
    
    if (xbee.getResponse().isAvailable()) {
      
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
        
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
                xbee.getResponse().getRx16Response(rx16);
          option = rx16.getOption();
          //Serial.print(j++);
            //Serial.print(" ");

          String s;
          int count = 1;
          for (int i = 0; i <  rx16.getDataLength(); i++) {
            if(rx16.getData(i)!=58){
              s += (rx16.getData(i)-48);
              //Serial.print(s);
              }
            else
            {
              //s += '\n';
              switch(count)
              {
                case 1:
                  
                  ::r1 = s.toInt();
                  ::r1=rerange(r1);
                  actuate1(r1);
                  /*Serial.print("Wheel 1: ");*/
                  //Serial.print(r1);
                  break;
                case 2:
                  
                  ::r2 = s.toInt();
                  ::r2 = rerange(r2);
                  actuate2(r2);
                  //Serial.print("Wheel 2: ");
                  //Serial.print(r2);
                  break;
                case 3:
                  ::r3 = s.toInt();
                  ::r3 = rerange(r3);
                  actuate3(r3);
                  //Serial.print("Wheel 3: ");
                  //Serial.print(r3);
                  break;
                case 4:
                  
                  ::ds = s.toInt();
                  d.mspeed(ds);
                  //Serial.print("dribbler: ");
                  //Serial.print(ds);
                  break;
                case 5:
                  
                  ::k = s.toInt();
                  
                  /*Serial.print("Kicker: ");
                  Serial.println(k);*/
                  break;              
              }
              
              count++;
              s = "";
            }
           }
        }
      }
    }
    //printsp();
    //Serial.println(r1);
}

void sanitycheck(){
  if(rpmo1==rpm1) {rpm1=0;m1.mspeed(dir1*255);}
    if(rpmo2==rpm2) {rpm2=0;actuate2(dir2*255);}
    if(rpmo3==rpm3) {rpm3=0;actuate3(dir3*255);}
    rpmo1 = rpm1;
    rpmo2 = rpm2;
    rpmo3 = rpm3;
}

void printsp(){
    Serial.print(r1);
    Serial.print("  ");
    Serial.print(pid1);
    Serial.print("  ");
    Serial.print(r2);
    Serial.print("  ");
    Serial.print(pid2);
    Serial.print("  ");
    Serial.print(r3);
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

int rerange(int x){
  if(x > -40 && x < -30){
    x += 30;
  }
  else if(x > -400 && x< -309){
    x+= 300;
  }
  else if(x > -500 && x< -409){
    x+= 400;
  }
  else if(x > 4000 && x < -3099){
    x += 3000;
  }
  return x;
}

void actuate1(int r){
    detachInterrupt(19);
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
    attachInterrupt(digitalPinToInterrupt(19), count1, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), count2, FALLING);
    attachInterrupt(digitalPinToInterrupt(18), count3, FALLING);
}

void actuate2(int r){
    detachInterrupt(19);
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
    attachInterrupt(digitalPinToInterrupt(19), count1, FALLING);
volatile int k,ds;
    attachInterrupt(digitalPinToInterrupt(3), count2, FALLING);
    attachInterrupt(digitalPinToInterrupt(18), count3, FALLING);
}

void actuate3(int r){
    detachInterrupt(19);
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
    attachInterrupt(digitalPinToInterrupt(19), count1, FALLING);
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

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}



void ser()
{
    char rawdata[30];
    String w1,w2,w3,dss,ks;
    while(!(xbee.getResponse().isAvailable())){
      xbee.readPacket();
    }
    xbee.getResponse().getRx16Response(rx16);
    option = rx16.getOption();
    int j=0;
    /*while(rx16.getData(j)){
      rawdata[j] = rx16.getData(j);
      j++;
    }
    String data(rawdata);*/
    String data(rawdata);
    Serial.write(rx16.getData(0));
    
    w1 = getValue(data,'\t',0);
    w2 = getValue(data,'\t',1);
    w3 = getValue(data,'\t',2);
    dss = getValue(data,'\t',3);
    ks = getValue(data,'\t',4);
    
    r1 = w1.toInt();
    r2 = w2.toInt();
    r3 = w3.toInt();
    ds = dss.toInt();
    k = ks.toInt();
  /*while(!Serial.available());
  r1=-Serial.readStringUntil('\t').toInt();
  r2=-Serial.readStringUntil('\t').toInt();
  r3=-Serial.readStringUntil('\t').toInt();
  ds=Serial.readStringUntil('\t').toInt();
  k = Serial.readStringUntil('\n').toInt();*/ 
}

