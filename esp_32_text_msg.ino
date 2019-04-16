#include <WiFi.h>

const char* ssid = "ding dong";
const char* password = "12120303";
const char* host = "maker.ifttt.com";
const char* apiKey = "dRmFArL4ZGqR_02A_8LFauvQvuOQI6h3rUHAjCQST8D";
String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;
int pin = 4;

volatile int flag = false;
const char* PIN_state = "not pressed";

void PINStatus() {
            PIN_state = "SOS pressed";  
             flag = true;
}


void setup() {
    Serial.begin(115200);

    Serial.println("SOS button integration with IFTTT");
    delay(100);
    pinMode(pin, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(pin), PINStatus, FALLING);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  
}

void loop() {   


          if(flag){
          Serial.print("connecting to ");
          Serial.println(host);
          
          WiFiClient client;
          const int httpPort = 80;
           if (client.connect("maker.ifttt.com",80)) {
   apiKey ="ihnGg6Xjv4w_h7yt96sfB8htcyGT52132W9aKHRBI4L";
    MakerIFTTT_Event ="sms";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, apiKey);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "8017959612");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "I am in denger");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "");
    p = append_str(p, "\"}");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);
   flag = false;

  }
      } 
   
      delay(100);
      
}

