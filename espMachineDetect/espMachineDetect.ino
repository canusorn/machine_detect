#include <IotWebConf.h>
#include <IotWebConfUsing.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <EEPROM.h>

#define SENSOR D6
#define DETECTTIME 10

// ip ของเครือง pc
// String serverIP = "192.168.1.210";

// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
const char thingName[] = "icemachine";

// -- Initial password to connect to the Thing, when it creates an own Access Point.
const char wifiInitialApPassword[] = "123456789";

// -- Method declarations.
void handleRoot();

// timer interrupt
Ticker timestamp;

DNSServer dnsServer;
WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

#define STRING_LEN 128
#define NUMBER_LEN 32

char sensorIdParamValue[NUMBER_LEN];
char ipParamValue[STRING_LEN];

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword);

IotWebConfParameterGroup group1 = IotWebConfParameterGroup("group1", "อื่นๆ");
IotWebConfTextParameter ipParam = IotWebConfTextParameter("IP Address", "ipParam", ipParamValue, STRING_LEN, "192.168.1.210");
IotWebConfNumberParameter sensorIdParam = IotWebConfNumberParameter("Sensor ID", "sensorIdParam", sensorIdParamValue, NUMBER_LEN, "1");

uint32_t workingCount;
uint8_t detectCount;
bool detectFlag, releaseFlag;

// timer interrupt every 1 second
void time1sec()
{
  if (!digitalRead(SENSOR)) {
    if (!releaseFlag && detectCount < DETECTTIME)
      detectCount++;

    Serial.println(detectCount);

    if (detectCount >= DETECTTIME) {
      detectFlag = 1;
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");

  pinMode(SENSOR, INPUT_PULLUP);

  // timer interrupt every 1 sec
  timestamp.attach(1, time1sec);

  group1.addItem(&sensorIdParam);
  group1.addItem(&ipParam);

  // -- Initializing the configuration.
  iotWebConf.setStatusPin(D4);
  iotWebConf.addParameterGroup(&group1);

  // -- Define how to handle updateServer calls.
  iotWebConf.setupUpdateServer(
    [](const char* updatePath) { httpUpdater.setup(&server, updatePath); },
    [](const char* userName, char* password) { httpUpdater.updateCredentials(userName, password); });
  
  iotWebConf.init();
  iotWebConf.setWifiConnectionCallback(&wifiConnected);

  // -- Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/config", [] { iotWebConf.handleConfig(); });
  server.on("/cleareeprom", clearEEPROM);
  server.on("/reboot", reboot);
  server.onNotFound([]() {
    iotWebConf.handleNotFound();
  });

  Serial.println("Ready.");
}

void loop()
{
  // -- doLoop should be called as frequently as possible.
  iotWebConf.doLoop();
  WebServer server(80);
  MDNS.update();

  if (digitalRead(SENSOR)) {
    detectCount = 0;
    releaseFlag = 0;
  }

  if (detectFlag) {
    if (WiFi.status() != WL_CONNECTED) {
      //      Serial.println("wifi disconnect");
      return;
    }
    if (!httpGet()) {
      //      Serial.println("request failed");
      return;
    }
    if (!releaseFlag) {
      releaseFlag = 1;
      detectFlag = 0;
      detectCount = 0;
      workingCount++;
      Serial.println("count:" + String(workingCount));
    }
  }
}

/**
   Handle web requests to "/" path.
*/
void handleRoot()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>ICE Machine Count</title></head><body>";
  s += "<div><h4>Count:" + String(workingCount) + "</h4></div>";
  s += "<div><h4>SensorID:" + String(sensorIdParamValue) + "</h4></div>";
  s += "<div><h4>Server IP Address:";
  s += ipParamValue;
  s += "</h4></div>";
  s += "Go to <a href='config'>configure page</a> to change settings.";
  s += "</body></html>\n";

  server.send(200, "text/html", s);
}

void wifiConnected()
{
  Serial.println("WiFi was connected.");
  MDNS.begin(iotWebConf.getThingName());
  MDNS.addService("http", "tcp", 80);

  Serial.printf("Ready! Open http://%s.local in your browser\n", String(iotWebConf.getThingName()));

}

bool httpGet() {
  bool result = false;
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://" + String(ipParamValue) + "/get.php?id=" + String(sensorIdParamValue))) {  // HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        result = true;
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

  return result;
}

void clearEEPROM()
{
  EEPROM.begin(512);
  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++)
  {
    EEPROM.write(i, 0);
  }

  EEPROM.end();
  server.send(200, "text/plain", "Clear all data\nrebooting");
  delay(1000);
  ESP.restart();
}

void reboot()
{
  server.send(200, "text/plain", "rebooting");
  delay(1000);
  ESP.restart();
}
