#include <ESP8266WiFi.h>
#include <Servo.h>
const char* ssid = "Oneplus A5000"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "ABCDEFGH"; // Your Wifi password, in case you have open network comment the whole statement.
int pos = 0;
int armup = 5;//d1  // GPIO13 or for NodeMCU you can directly write D7 
int armdown = 4; // D2
int left_f = 0;//d3
int left_b = 12;//d6
int right_b = 13;//d7
int right_f = 15;//d8
WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.
Servo servo;
void setup() {
  Serial.begin(115200);
  delay(10);
  servo.attach(16);
  pinMode(armup, OUTPUT);
  pinMode(armdown, OUTPUT);
  pinMode(left_f, OUTPUT);
  pinMode(left_b, OUTPUT);
  pinMode(right_f, OUTPUT);
  pinMode(right_b, OUTPUT);
  pinMode(A0, OUTPUT);
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  // Start the server
  server.begin();
 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
 
}
void forward(){
  digitalWrite(right_f,HIGH);
  digitalWrite(right_b,LOW);
  digitalWrite(left_f,HIGH);
  digitalWrite(left_b,LOW);
  
  Serial.println("f");
}
void back(){
    digitalWrite(right_f,LOW);
  digitalWrite(right_b,HIGH);
  digitalWrite(left_f,LOW);
  digitalWrite(left_b,HIGH);
  Serial.println("b");

  }

 void stp(){
  digitalWrite(right_f,LOW);
  digitalWrite(right_b,LOW);
  digitalWrite(left_f,LOW);
  digitalWrite(left_b,LOW);
   Serial.println("stp");
}

 void right(){
    digitalWrite(right_f, HIGH);
  digitalWrite(right_b,LOW);
  digitalWrite(left_f,LOW);
  digitalWrite(left_b,LOW);
  Serial.println("right");

 }
 void left(){
    digitalWrite(right_f,LOW);
  digitalWrite(right_b,LOW);
  digitalWrite(left_f,HIGH);
  digitalWrite(left_b,LOW);
  Serial.println("left");

 }

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  client.flush();
 
 
  if (request.indexOf("/armup") != -1)  {
    digitalWrite(armup, HIGH);
    digitalWrite(armdown, LOW);
    Serial.println("armup");
    
    
  }
  if (request.indexOf("/armdown") != -1)  {
    digitalWrite(armup, LOW);
    digitalWrite(armdown, HIGH);
    Serial.println("armdown");
    
    
  }
  if (request.indexOf("/armstp") != -1)  {
    digitalWrite(armup, LOW);
    digitalWrite(armdown, LOW);
    Serial.println("armdown");
    
    
  }
  if (request.indexOf("/in") != -1)  {
//    digitalWrite(armdown, HIGH);
    pos-=5;
    pos = pos<0 ? 0 : pos;
//    analogWrite(A0, pos);
    servo.write(pos);
    Serial.println(pos);
    
  }
  if (request.indexOf("/out") != -1)  {
    pos+=5;
    pos = pos> 180 ? 180: pos;
//    servo.write(pos);
//    analogWrite(A0, pos);
    servo.write(pos);
    Serial.println(pos);
    
  }
  if (request.indexOf("/forward") != -1)  {
  forward();
  
  }
  if (request.indexOf("/fands") != -1)  {
  forward();
  delay(150);
  stp();
  }
  if (request.indexOf("/back") != -1)  {
    back();
   
  }
if (request.indexOf("/bands") != -1)  {
    back();
   delay(150);
   stp();
  }
  
  if (request.indexOf("/right") != -1)  {
    right();
   
  }
  if (request.indexOf("/rands") != -1)  {
    right();
    delay(150);
    stp();
  }
  if (request.indexOf("/left") != -1)  {
    left();
  }
  if (request.indexOf("/lands") != -1)  {
    left();
    delay(150);
    stp();
  }
  if (request.indexOf("/stp") != -1)  {
    stp();
  }
   if (request.indexOf("/close") != -1)  {
    pos = 0;
    servo.write(pos);
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html><body >");
 
  client.println("<br><br>");
  client.println("<a href=\"/armup\"\"><button style=\"width:30%;height:160px;font-size:100px;\">up </button></a>");  
  client.println("<a href=\"/armdown\"\"><button style=\"width:30%;height:160px;font-size:100px;\">down </button></a>");  
  client.println("<a href=\"/armstp\"\"><button style=\"width:30%;height:160px;font-size:50px;\">Stop Arm</button></a><br/><br/>");  
  client.println("<a href=\"/in\"\"><button style=\"width:40%;height:160px;font-size:100px;\">in</button></a>");  
  client.println("<a href=\"/out\"\"><button style=\"width:40%;height:160px;font-size:100px;\">out </button></a><br /><br/>");  
  client.println("<a href=\"/forward\"\"><button style=\"width:40%;height:160px;font-size:100px;\">forward</button></a>");  
  client.println("<a href=\"/back\"\"><button style=\"width:40%;height:160px;font-size:100px;\">backward</button></a><br /><br/>");  
  client.println("<a href=\"/fands\"\"><button style=\"width:40%;height:160px;font-size:30px;\">forward and stop</button></a>");  
  client.println("<a href=\"/bands\"\"><button style=\"width:40%;height:160px;font-size:30px;\">backward and stop</button></a><br /><br/>");  
  client.println("<a href=\"/right\"\"><button style=\"width:40%;height:160px;font-size:100px;\">left</button></a>");  
  client.println("<a href=\"/left\"\"><button style=\"width:40%;height:160px;font-size:100px;\"> right</button></a><br /><br/>");  
  client.println("<a href=\"/rands\"\"><button style=\"width:40%;height:160px;font-size:30px;\">left and stop</button></a>");  
  client.println("<a href=\"/lands\"\"><button style=\"width:40%;height:160px;font-size:30px;\"> right and stop</button></a><br /><br/>");  
  client.println("<a href=\"/stp\"\"><button style=\"width:40%;height:160px;font-size:100px;\">stop</button></a><br /><br/>");  
  client.println("<a href=\"/close\"\"><button style=\"width:40%;height:160px;font-size:100px;\">close</button></a><br /><br/>");  
  
  client.println("</body></html>");
 
  delay(1);
 
}
