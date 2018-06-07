/*kyriakou xbee V1.1
  

  RECEIVER
  Router
  Series 2 XBee, Mode AP=2,API Options (AO)=0, MAC=0013A20040E98ACD 
  
  TRANSMITER
  Coordinator
  Series 2 XBee, Mode AP=2, API Options (AO)=0, MAC=13A20040E98ACE, 
  Sends a ZB TX request with the value of analogRead(5)

*/
#include <XBee.h>
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
}
void loop() {
String sample;
  xbee.readPacket(); 
    if (xbee.getResponse().isAvailable()) {
      Serial.println(xbee.getResponse().getApiId());
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        xbee.getResponse().getZBRxResponse(rx);
        for (int i = 0; i < rx.getDataLength(); i++) {
          sample += (char)rx.getData(i);
        }
        Serial.println(sample);
      }
    }else if (xbee.getResponse().isError()) {
      Serial.println("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
  } 
  delay(100);
}
