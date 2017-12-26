#include <WiFi.h>

#define NEWLINE '\n'
#define CARRIAGE '\r'
#define HTTP_OK_RESP "HTTP/1.1 200 OK"

#define SERIAL1_RXPIN 12
#define SERIAL1_TXPIN 13

HardwareSerial Serial2(2);            // UART2 Serial PORT (pin16 = RX, pin17 = TX);

// WiFi network name and password:
const char *networkName = "KCCI_STC_S";
const char *networkPswd = "kcci098#";

const int BUTTON_PIN = 0;
const int LED_PIN = 5;
const int LED_PIN2 = 4;

void setup()
{
    // Initilize hardware:
    Serial.begin(115200);
    // Serial1.begin(115200, SERIAL_8N1, SERIAL1_RXPIN, SERIAL1_TXPIN);
    Serial2.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);

    delay(10);
  
    connectToWiFi(networkName, networkPswd);
}

void loop()
{
    runWebServer();
}
