#include <SPI.h> // needed in Arduino 0019 or later
#include <Ethernet.h>
#include <Twitter.h>
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0x9E, 0x63 };
byte ip[] = { 192, 168, 0, 10 };
Twitter twitter("1437507451-p1Ki9ssaeVFDmh4rB2cw3ALsg0YvxQ3IKseObS4");
int LDRpin = 3;
int last_val = 200;

void setup()
{
  delay(1000);
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  Serial.println("connecting ...");
}

void loop()
{
  int LDRValue = analogRead(LDRpin);
  String buff= tweetMessage(LDRValue);
  char msg[140];
  buff.toCharArray(msg, 140);
  if (twitter.post(msg)) {
    int status = twitter.wait(&Serial);
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
  delay(120000);
}

String tweetMessage(int ldrvalue){
  String str;
  if (ldrvalue-100 > last_val ){
    str="Its getting darker! LDR Value: ";
    str+=ldrvalue;
    last_val = ldrvalue;
  }
  else
  {
    if(ldrvalue+100<last_val){
    str="Its getting brighter! LDR Value: ";
     str+=ldrvalue;
    last_val = ldrvalue;
    }
  }
  return str;
}