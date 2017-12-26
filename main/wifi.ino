#include <WiFi.h>

// Internet domain to request from:
const char * hostDomain = "example.com";
const int hostPort = 80;

WiFiServer server(hostPort);

void connectToWiFi(const char * ssid, const char * pwd)
{
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(networkName);  
    WiFi.begin(ssid, pwd);
    
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

void runWebServer()
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

                        client.print(getHttpBody());
                        
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
                if (  currentLine.endsWith("GET /H")  ) 
                {
                    digitalWrite(LED_PIN, HIGH);               // GET /H turns the LED on
                }
                if (  currentLine.endsWith("GET /L")  ) 
                {
                    digitalWrite(LED_PIN, LOW);                // GET /L turns the LED off
                }
                
                if (  currentLine.endsWith("GET /period=10")  )
                {    
                    Serial2.print("period 5000");
                    Serial2.println("");
                    // digitalWrite(LED_PIN2, HIGH);
                }
                if (  currentLine.endsWith("GET /period=50")  )
                {    
                    Serial2.print("period 2500");
                    Serial2.println("");
                    digitalWrite(LED_PIN2, LOW);
                }
            }
        }
        client.stop();
        Serial.println("Client Disconneccted.");
    }
}

void setPeriod(String current, int led_num) 
{
    if (  current.endsWith("GET /period=10")  )
    {
        digitalWrite(LED_PIN2, HIGH);   
    }

    if (  current.endsWith("GET /period=50")  )
    {
        digitalWrite(LED_PIN2, LOW);
    }

    if (  current.endsWith("GET /period=100")  )
    {
        
    }
}

