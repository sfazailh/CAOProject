#include <WiFi.h>
#include <HTTPClient.h>
#include <stdio.h> 
#include <string.h> 

// Wifi Information
const char* ssid = "YOUR WIFI ROUTER NAME";
const char* password = "YOUR WIFI PASSWORD";


char token[] = "5f1ed5ee6bfca8893b21f5073f3169bbd6dc089b";

// PIR 
// Connect PID to Pin D21 and D22
const int PIN_TO_SENSOR1 = 22;   // the pin that OUTPUT pin of sensor is connected to
const int PIN_TO_SENSOR2 = 21;   // the pin that OUTPUT pin of sensor is connected to


// ------  Static Request -------
// Title of Notification EX: Motion Sensor
char title[] = "Motion Sensor";

// Description of Notification EX: Motion Detected In Living Room
char descEntry[] = "Someone just entered";
char descDeparture[] = "Someone just left";

// Color of Notification: red, purple, yellow, green, blue, pink, orange
// If no color specified it will default to red
char color[] = "pink";

// Gourping Notifications in phone notification bar
// Leave it Defualt Unless you know what you are doing
char group[] = "1";

// Send Phone Push Notification Alert 
// If false it will still write the notification in the app and webapp but you will not receive notification
// If true it will notify your phone with a push notification
// "true" or "false"
/* IMPORTANT THIS MUST BE SPELLED CORRECTLY  */
/* true or false  */
char notify[] = "true";
// ------  END Static Request -------


// Dont Change Server Link
const char* serverName = "https://iotpush.app/api/notif";

// Post Array Init DONT TOUCH
char post[500];


int pinStateCurrent   = LOW; // current state of pin
int pinStatePrevious  = LOW; // previous state of pin

void setup() {
    pinMode(PIN_TO_SENSOR, INPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {

  pinStatePrevious = pinStateCurrent; // store old state
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state
  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    // Here We Send the Notificaiton  with true to notify our phone with push notification
    sendCustom("Motion Sensor","Living Sensor Motion Detected","red","true");
  }
  else
  if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    // Here we also send notification however with false so we dont get the push notification to our phone
    sendCustom("Motion Sensor","Living Sensor Motion Stoped","blue","false");
  }



}

void sendStatic(){

    if(WiFi.status()== WL_CONNECTED){
      // Preparing Data 
      // Combine Token For Header
      char tok[500] = "Token ";
      strcat(tok, token);

      // Init Http Client
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
          
      // Token Header
      http.addHeader("Authorization", tok);

      // Post Data
      strcat(post, "ST_title=");
      strcat(post, title);
      strcat(post, "&ST_text=");
      strcat(post, desc);
      strcat(post, "&ST_color=");
      strcat(post, color);
      strcat(post, "&BL_notify=");
      strcat(post, notify);
      strcat(post, "&OneID_group=");
      strcat(post, group);
      

      // Send HTTP POST request
      int httpResponseCode = http.POST(post);

      // Response 200 Means Notification Sent
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}




void sendCustom(char title[],char desc[],char color[],char notify[]){

    if(WiFi.status()== WL_CONNECTED){
      // Preparing Data 
      // Combine Token For Header
      char tok[500] = "Token ";
      strcat(tok, token);
      
      // Init Http Client
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
          
      // Token Header
      http.addHeader("Authorization", tok);
      // Post Data
      strcat(post, "ST_title=");
      strcat(post, title);
      strcat(post, "&ST_text=");
      strcat(post, desc);
      strcat(post, "&ST_color=");
      strcat(post, color);
      strcat(post, "&BL_notify=");
      strcat(post, notify);

     
      // Send HTTP POST request
      int httpResponseCode = http.POST(post);
      
      Serial.print("HTTP Response code: ");
      // Response 200 Means Notification Sent
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}
