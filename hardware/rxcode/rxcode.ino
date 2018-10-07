#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();

Rx16Response rx16 = Rx16Response();

volatile long int oldtime1,c1=0,t1,rpm1,e1,eo1,es1,ed1,kp1=4,kd1=1,ki1=1,pid1,dir1,rpmo1;
volatile long int oldtime2,c2=0,t2,rpm2,e2,eo2,es2,ed2,kp2=4,kd2=1,ki2=1,pid2,dir2,rpmo2;
volatile long int oldtime3,c3=0,t3,rpm3,e3,eo3,es3,ed3,kp3=4,kd3=1,ki3=1,pid3,dir3,rpmo3;

int r1,r2,r3;

volatile int k,ds;

int j=0;
uint8_t option = 0;
char data[30];
SoftwareSerial mySerial(10, 11);
void setup() {
  mySerial.begin(115200);
  Serial.begin(115200);
  xbee.setSerial(mySerial);
  
  pinMode(13,OUTPUT);
}

void loop() {
  xbee.readPacket();
    
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
                  /*Serial.print("Wheel 1: ");*/
                  //Serial.print(r1);
                  break;
                case 2:
                  
                  ::r2 = s.toInt();
                  ::r2 = rerange(r2);
                  //Serial.print("Wheel 2: ");
                  //Serial.print(r2);
                  break;
                case 3:
                  ::r3 = s.toInt();
                  ::r3 = rerange(r3);
                  //Serial.print("Wheel 3: ");
                  //Serial.print(r3);
                  break;
                case 4:
                  
                  ::ds = s.toInt();
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

void printsp(){
    Serial.print(r1);
    Serial.print("  ");
    //Serial.print(pid1);
    Serial.print("  ");
    Serial.print(r2);
    Serial.print("  ");
    //Serial.print(pid2);
    Serial.print("  ");
    Serial.print(r3);
    Serial.print("  ");
    Serial.println(ds);  
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

void ser2(){
  xbee.readPacket();
    
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
              s += '\n';
              switch(count)
              {
                case 1:
                  
                  r1 = s.toInt();
                  r1=rerange(r1);
                  /*Serial.print("Wheel 1: ");
                  Serial.print(r1);*/
                  break;
                case 2:
                  
                  r2 = s.toInt();
                  r2 = rerange(r2);
                  /*Serial.print("Wheel 2: ");
                  Serial.print(r2);*/
                  break;
                case 3:
                  r3 = s.toInt();
                  r3 = rerange(r3);
                  /*Serial.print("Wheel 3: ");
                  Serial.print(r3);*/
                  break;
                case 4:
                  
                  ds = s.toInt();
                  /*Serial.print("dribbler: ");
                  Serial.print(ds);*/
                  break;
                case 5:
                  
                  k = s.toInt();
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
  }
