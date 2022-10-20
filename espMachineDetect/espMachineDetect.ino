#include <IotWebConf.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>

#define SENSOR D6
#define DETECTTIME 30

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

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword);

uint32_t workingCount;
uint8_t detectCount;
bool detectFlag;

// timer interrupt every 1 second
void time1sec()
{
  if (digitalRead(SENSOR)) {
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

  pinMode(SENSOR, INPUT);

  // timer interrupt every 1 sec
  timestamp.attach(1, time1sec);

  // -- Initializing the configuration.
  iotWebConf.init();
  iotWebConf.setWifiConnectionCallback(&wifiConnected);

  // -- Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/config", [] { iotWebConf.handleConfig(); });
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

  if (!digitalRead(SENSOR)) {
    detectCount = 0;
  }

  if(detectFlag){
    detectFlag=0;
    workingCount++;
    Serial.println("count:" + String(workingCount));
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
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>IotWebConf 01 Minimal</title></head><body>";
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
