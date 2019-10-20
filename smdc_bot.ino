
#include <ESP8266WiFi.h>
#include <Servo.h> 
const char* ssid = "arpit"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "12345678"; // Your Wifi password, in case you have open network comment the whole statement.
 
int ledPin = 13; // GPIO13 or for NodeMCU you can directly write D7 
int mlf = D0;
int mlb = D1;
int mrf = D2;
int mrb = D3;
int arup = D6;
int ardown = D7;


int pos = 0;

WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.
Servo servo; 
void setup() {
  Serial.begin(115200);
  delay(10);
  servo.attach(A0);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  if (request.indexOf("/mlf") != -1)  {
    digitalWrite(mlf, HIGH);
  }

  if (request.indexOf("/mlb") != -1)  {
    digitalWrite(mlb, HIGH);
  }
  if (request.indexOf("/mrf") != -1)  {
    digitalWrite(mrf, HIGH);
  }
  if (request.indexOf("/mrb") != -1)  {
    digitalWrite(mrb, HIGH);
  }
  if (request.indexOf("/clin") != -1)  {
    pos = pos < 0? 0: pos;
    pos-=10;
    servo.write(pos);
//    digitalWrite(clin, HIGH);
  }
  if (request.indexOf("/clout") != -1)  {
    pos+=10;
    pos = pos > 180 ? 180: pos;
    servo.write(pos);
//    digitalWrite(clout, HIGH);
  } 
  
  if (request.indexOf("/arup") != -1)  {
    digitalWrite(arup, HIGH);
  }
  if (request.indexOf("/ardown") != -1)  {
    digitalWrite(ardown, HIGH);
  }
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html><head>");
  client.println("<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\">");
  client.println("<style></style></head><br><br><body style=\"background-color:2f2fA2\">");
  client.println("SMDC 2.O Team QUADCORE");
  client.println("<a class = \"btn\" href=\"/mlf\"\"><button>Left Forward</button></a>");
  client.println("<a class = \"btn\" href=\"/mrf\"\"><button>Right Forward</button></a><br />");
  client.println("<a class = \"btn\"  href=\"/mlb\"\"><button>Left Backward</button></a>");
  client.println("<a class = \"btn\"  href=\"/mrb\"\"><button>Right Forward</button></a><br/><br/><br/>");
  
  client.println("<a class = \"btn\"  href=\"/clin\"\"><button>Clamp in</button></a>");
  client.println("<a class = \"btn\"  href=\"/clout\"\"><button>Clamp out</button></a><br/><br/><br/>");

  client.println("<a class = \"btn\"  href=\"/arup\"\"><button>Arm Up</button></a>");
  client.println("<a class = \"btn\"  href=\"/ardown\"\"><button>Arm Down</button></a><br/>");

  client.println("</body></html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
