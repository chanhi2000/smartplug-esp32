
String getHttpBody(void)
{
    String retStr = String("");
    retStr += "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>ESP32 System Server</title></head>";
    retStr += "<h2>SmartPlug ESP32 WebServer</h2>";
    retStr += "Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>"; 
    retStr += "Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>";
    retStr += "Set period for STM32 LED blinking: ";
    retStr += "<form name=\"period\">";
    retStr += "<input type=\"text\" name=\"period\">";
    retStr += "<input type=\"button\" onClick=\"changePeriod()\" value=\"change\"><br>";
    retStr += "Click <a href=\"/period=10\">here</a> to change period to 10.<br>";
    retStr += "Click <a href=\"/period=50\">here</a> to change period to 50.<br>";
    retStr += "Click <a href=\"/period=100\">here</a> to change period to 100.<br>";
    retStr += "Click <a href=\"/period=500\">here</a> to change period to 500.<br>";
    retStr += "Click <a href=\"/period=1000\">here</a> to change period to 1000.<br>";
    retStr += "</form>";
    retStr += "<script type=\"text/javascript\">";
    retStr += "function changePeriod() {";
    retStr += "    console.log(\"changePeriod\")";
    retStr += "}";
    retStr += "</script>";
    return retStr;
}

