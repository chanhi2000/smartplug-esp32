#include <WiFi.h>

#define NEWLINE '\n'
#define CARRIAGE '\r'
#define HTTP_OK_RESP "HTTP/1.1 200 OK"

#define SERIAL1_RXPIN 12
#define SERIAL1_TXPIN 13

HardwareSerial Serial1(1);            // UART1 Serial PORT


// WiFi network name and password:
const char *networkName = "KCCI_STC_S";
const char *networkPswd = "kcci098#";

const int BUTTON_PIN = 0;
const int LED_PIN = 5;

void setup()
{
    // Initilize hardware:
    Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1, SERIAL1_RXPIN, SERIAL1_TXPIN);

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);

    delay(10);
  
    connectToWiFi(networkName, networkPswd);
}

void loop()
{
    Serial1.println("This message is sent to UART1 Serial ");     
    runWebServer();
}
