#include <ESP8266WiFi.h>
#include <cstdlib>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <ctime> 


MAX30105 particleSensor;
WiFiClient client;


String apiKey = "HC5WAFO08VI2XPJ6"; // Keep Your Channel API Key
const char *ssid = "iQOO Z3 5G"; // Keep your Wi-Fi Username
const char *pass = "aviax321"; // Keep your Wi-Fi Password
const char *server = "api.thingspeak.com";

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;
float temperature;
float vref = 3.3;
float resolution = vref / 1023;

void setup()
{
  Serial.begin(9600);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println("Initializing...");
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) 
  {
    Serial.println("Heart Beat sensor not found");
    while (1);
  }
  Serial.println("Place your index finger on the sensor.");
  particleSensor.setup(); 
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
  delay(2000);
}

void loop()
{
  for(int i=0; i<500; i++)
    Heart_Beat();
  if(particleSensor.getIR()>50000){
      calculateSpO2();
      Heart_Beat();
  }else {
    Spo2 = 0; temp1 = 0;
  }
   
  Serial.print("BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
  Serial.print(", SpO2=");
  Serial.print(calculateSpO2());
  Serial.println();

  temperature = analogRead(A0);
  temperature = (temperature * resolution);
  temperature = temperature * 100;

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Update_Thingspeak();
  delay(5000);
}

void Heart_Beat() {
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue) == true) {
    long currentMillis = millis();
    long delta = currentMillis - lastBeat;  // Calculate the time since the last beat
    lastBeat = currentMillis;

    beatsPerMinute = 60 / (delta / 1000.0);
    
    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute; 
      rateSpot %= RATE_SIZE; 
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }
    
  if (irValue < 50000) {
    beatsPerMinute = 0;
    beatAvg = 0;
  }
}


float calculateSpO2() {
    uint32_t irValue = particleSensor.getIR();
    uint32_t redValue = particleSensor.getRed();

    if (irValue == 0) {
        return 0.0;
    }

    float ratio = (float)redValue / (float)irValue;


    float a = 112.0;
    float b = -1.22;

    // Calculate SpO2 using the empirical formula
    float spo2 = a * pow(ratio, b);

    // Ensure that SpO2 is within a valid range (0 to 100)
    spo2 = constrain(spo2, 0.0, 100.0);

    return spo2;
}



void Update_Thingspeak()
{
  if (client.connect(server,80))
  {                    
    String line;
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(temperature);
    postStr +="&field2=";
    postStr += String(beatsPerMinute);
    postStr +="&field3=";
    postStr += String(calculateSpO2());
    postStr += "\r\n\r\n";
     
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
   while (client.connected() || client.available())
    {
      if (client.available())
      {
        line = client.readString();
      }
    }
    Serial.println(line);
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else{
    client.stop();
    Serial.println("connection failed!]");
  }
}
