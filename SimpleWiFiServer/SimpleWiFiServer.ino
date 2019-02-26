/* SimpleWiFiServer.ino
/********* Rui Santos, detail complete project at https://randomnerdtutorials.com *********/
#include <WiFi.h>          // Load Wi-Fi library
const char *ssid = "ESP32", *password = "derek123";  // Replace network credentials
WiFiServer server(80);          // Set web server port number to 80
String header;            // store the HTTP request
const int LED = 16;         // the LED pin on WIFIBOY ESP32
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);         // Initialize the LED pin as output device
  digitalWrite(LED, LOW);       // turn off the LED
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);        // Connect to Wi-Fi network with SSID and password
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
}
int level;
char* state;
void loop(){
  WiFiClient client = server.available(); // Listen for incoming clients
  if (client) {         // If a new client connects,
    Serial.println("New Client.");    // print a message out in the serial port
    String currentLine = "";      // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client connected
      if (client.available()) {     // if there's bytes need to read from the client,
        char c = client.read();     // read a byte
        Serial.write(c);      // echo it on the serial monitor
        header += c;        
        if (c == '\n') {      // if the byte is a newline
          if (currentLine.length() == 0) {  // blank line is the end of the client HTTP request
            client.println("HTTP/1.1 200 OK");  // HTTP header always start with the following response
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            Serial.printf("length %d >> ", header.length());
            Serial.println(header);

      if (header.indexOf("GET /LED=HIGH HTTP/1.1") >= 0) level=HIGH;
      else if (header.indexOf("GET /LED=LOW HTTP/1.1") >= 0) level=LOW;

            state = level==HIGH ? (char*)"HIGH" : (char*)"LOW";
      Serial.printf("GPIO %d %s\n", LED, state);
            digitalWrite(LED, level);

            client.println("<!DOCTYPE html><html>");    // begin to display the HTML web page
            client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("<link rel='icon' href='data:,'>");  // CSS to style the on/off buttons
            client.println("<style>html{font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button{ background-color: #00AA00; border: 3; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2{background-color: #005500;}</style></head>");
            client.println("<body><h1>ESP32 Web Server</h1>");  // Web Page Heading
            client.printf("<p>LED - State %s</p>\n", state);  // Display LED current state
                
            if (state=="LOW") // If the LED State is LOW, display the ON button
              client.println("<p><a href=\"/LED=HIGH\"><button class=\"button\">ON</button></a></p>");
            else    // else display the OFF button
              client.println("<p><a href=\"/LED=LOW\"><button class=\"button button2\" onclick='send()'>OFF</button></a></p>");
            client.println(); // The HTTP response ends with another blank line
            client.println("<br><hl>ssid<input id='ssid'>pswd<input id='pswd'><button onclick='onClick()'>send</button></body></html>");  // Web Page Heading
            
            break;    // Break out of the while loop
          }
          currentLine = "";
        } else if (c != '\r') { // if anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
