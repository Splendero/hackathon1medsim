#include <WiFiNINA.h>
#include <WiFiServer.h>

// Set up SoftAP credentials

int EA = 2; // Wheel PWM pin (must be a PWM pin)
int I1 = 4; // Wheel direction digital pin 1
int I2 = 3; // Wheel direction digital pin 2
int EB = 5; // Wheel PWM pin (must be a PWM pin)
int I3 = 7; // Wheel direction digital pin 1
int I4 = 6; // Wheel direction digital pin 
const int u = 255; //Wheel spd

char ssid[] = "testrobotAP";
char pass[] = "testpwd123";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  // Configure digital pins for output
  pinMode(EA, OUTPUT);
  pinMode(I1, OUTPUT); 
  pinMode(I2, OUTPUT);
  pinMode(EB, OUTPUT);
  pinMode(I3, OUTPUT); 
  pinMode(I4, OUTPUT);

  // Set up SoftAP
  WiFi.beginAP(ssid, pass);

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  handleClient();
}

void handleClient() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait for the client to send a request
  while (!client.available()) {
    delay(20);
  }

  // Read the request
  String request = client.readStringUntil('\r');
  client.flush();

  // Check if the request contains "GET /button" (button press)
  for (int i = 1; i <= 5; i++) {
    String buttonPath = "/button" + String(i);
    if (request.indexOf(buttonPath) != -1) {
      //action
      drivestate(i,u);
      Serial.println("Button " + String(i) + " Pressed via Web Interface!");
    }
  }

  // Send a response to the client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println("<html><body>");
  client.println("<h1>Arduino SoftAP WebServer</h1>");
  client.println("<p>Click <a href='/button0'>here</a> to reset.</p>");
  client.println("<p>Click <a href='/button1'>here</a> to go forward.</p>");
  client.println("<p>Click <a href='/button2'>here</a> to go backward.</p>");
  client.println("<p>Click <a href='/button3'>here</a> to turn right.</p>");
  client.println("<p>Click <a href='/button4'>here</a> to turn left.</p>");
  client.println("</body></html>");

  // Close the connection
  delay(20);
  client.stop();
}

void leftwheeldrive(int spd, int drc) // speed btw 0 -255
{
  if (drc < 0)
    {
      digitalWrite(I3, HIGH);  
      digitalWrite(I4, LOW);
    }
  else
    {
      digitalWrite(I3, LOW);  
      digitalWrite(I4, HIGH);
    }
  analogWrite(EB, spd);
}

void rightwheeldrive(int spd, int drc) // speed btw 0 -255
{
  if (drc > 0)
    {
      digitalWrite(I1, HIGH);  
      digitalWrite(I2, LOW);
    }
  else
    {
      digitalWrite(I1, LOW);  
      digitalWrite(I2, HIGH);
    }
  analogWrite(EA, spd);
}

void drivestate(int stat, int spd){
  switch(stat){
    case 0:
      leftwheeldrive(0,0);
      rightwheeldrive(0,0);
      break;
    case 1:
      leftwheeldrive(spd,1);
      rightwheeldrive(spd,1);
      break;
    case 2:
      leftwheeldrive(spd,-1);
      rightwheeldrive(spd,-1);
      break;
    case 3:
      leftwheeldrive(spd,1);
      rightwheeldrive(spd,-1);
      break;
    case 4:
      leftwheeldrive(spd,-1);
      rightwheeldrive(spd,1);
      break;
  }
}