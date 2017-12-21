#include <WiFi.h>

#define NEWLINE '\n'
#define CARRIAGE '\r'
#define HTTP_OK_RESP "HTTP/1.1 200 OK"

// WiFi network name and password:
const char *networkName = "KCCI_STC_S";
const char *networkPswd = "kcci098#";

// Internet domain to request from:
const char * hostDomain = "example.com";
const int hostPort = 80;

const int BUTTON_PIN = 0;
const int LED_PIN = 5;

WiFiServer server(hostPort);

void setup()
{
  // Initilize hardware:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  delay(10);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(networkName);

  connectToWiFi(networkName, networkPswd);
}

int value = 0;

void loop()
{
    WiFiClient client = server.available();

    if (client) 
    {
        Serial.println("New Client.");
        String currentLine = "";

        while(client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                Serial.write(c);
                if (c == NEWLINE)
                {
                    if (currentLine.length() == 0)
                    {
                        client.println(HTTP_OK_RESP);
                        client.println("Content-type:text/html");
                        client.println();

                        client.print("<h2>SmartPlug ESP32 WebServer</h2>");
                        client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
                        client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");
                        

                        // The HTTP response ends with another blank line:
                        client.println();
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != CARRIAGE) {
                    currentLine += c;
                }

                // Check to see if the client request was "GET /H" or "GET /L":
                if (currentLine.endsWith("GET /H")) 
                {
                    digitalWrite(5, HIGH);               // GET /H turns the LED on
                }
                if (currentLine.endsWith("GET /L")) 
                {
                    digitalWrite(5, LOW);                // GET /L turns the LED off
                }
            }
        }
        client.stop();
        Serial.println("Client Disconneccted.");
    }
}

void connectToWiFi(const char * ssid, const char * pwd)
{
    WiFi.begin(networkName, networkPswd);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}


/*
void requestURL(const char * host, uint8_t port)
{
  printLine();
  Serial.println("Connecting to domain: " + String(host));

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected!");
  printLine();

  // This will send the request to the server
  client.print((String)"GET / HTTP/1.1\r\n" +
               "Host: " + String(host) + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
  client.stop();
}
*/
