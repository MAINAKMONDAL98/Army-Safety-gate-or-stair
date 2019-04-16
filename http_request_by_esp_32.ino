#include <WiFi.h>
#include <HTTPClient.h>  
 //int a;
const char* ssid = "ding dong";
const char* password =  "12120303";
 
void setup() {
 
  Serial.begin(115200);
  delay(4000);
pinMode(13,OUTPUT);
digitalWrite(13,LOW);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 digitalWrite(13,0);
 Serial.println((digitalRead(13)));
 //Serial.println(a);
 if(digitalRead(13)==1){
  Serial.println("Pin triggered");
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
   Serial.println("Pin triggered");

    HTTPClient http;
 
    http.begin("https://maker.ifttt.com/trigger/IndianArmy/with/key/ihnGg6Xjv4w_h7yt96sfB8htcyGT52132W9aKHRBI4L"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
   Serial.println("Pin triggered");

    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
      http.end(); //Free the resources
  }
 }
    else {
      Serial.println("Error on HTTP request");
    }
 
   
 

 
}
