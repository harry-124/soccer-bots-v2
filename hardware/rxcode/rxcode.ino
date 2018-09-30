#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();

Rx16Response rx16 = Rx16Response();

uint8_t option = 0;
uint8_t data;
SoftwareSerial mySerial(10, 11);
void setup() {
  mySerial.begin(115200);
  Serial.begin(115200);
  xbee.setSerial(mySerial);
  
  pinMode(13,OUTPUT);
}

void loop() {
    int flag=0;
    flag = 0;
    int i =0;
    digitalWrite(13,LOW);
    while(!(xbee.getResponse().isAvailable())){

      xbee.readPacket();
    }
    xbee.getResponse().getRx16Response(rx16);
    option = rx16.getOption();
    
   
    if(rx16.getData(0)){
      digitalWrite(13,HIGH);
      data  = rx16.getData(0);
      Serial.write(data);
    }
    else{
      digitalWrite(13,LOW);
    }
}
