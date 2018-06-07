/*
kyriakou xbee V1.1
  
  TRANSMITER
  Coordinator
  Series 2 XBee, Mode AP=2, API Options (AO)=0, MAC=13A20040E98ACE, 
  Sends a ZB TX request with the value of analogRead(5)

  RECEIVER
  Router
  Series 2 XBee, Mode AP=2,API Options (AO)=0, MAC=0013A20040E98ACD 

*/

#include <XBee.h>

XBee xbee = XBee();

int pin5=0;
uint8_t payload[] = { 0, 0 };//Byte
uint8_t data[] = {'H','E','L','L','O','O','O'};

void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial);
}
void loop() {
  XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40E98ACD);
  ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));//API ID 0x10
  xbee.send(zbTx);
  delay(1000);
  
  // break down 10-bit reading into two bytes and place in payload
  pin5 = analogRead(5);
  payload[0] = pin5 >> 8 & 0xff;
  payload[1] = pin5 & 0xff;
  ZBTxRequest zbTxR = ZBTxRequest(addr64, payload, sizeof(payload));//API ID 0x10

  xbee.send(zbTxR);
  delay(1000);
}
