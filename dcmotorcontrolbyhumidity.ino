#define BLYNK_TEMPLATE_ID "TMPL6nPXxwOgT"
#define BLYNK_TEMPLATE_NAME "Speed Controlby temp"
#define BLYNK_AUTH_TOKEN "N7lM1-cYozJLt9fG57lbwF2XHrQ3iZQE"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#define DHTPIN 5     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
#define FAN_PIN 2   // FAN RELAY
 
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

char auth[] = "N7lM1-cYozJLt9fG57lbwF2XHrQ3iZQE";
char ssid[] = "Mạng như chó nhai";
char pass[] = "15122001";

float humDHT = 0;
float tempDHT = 0;
 


void setup() {
  Serial.begin(115200);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  Blynk.begin( auth, ssid , pass );
}
 

void loop() {
  
  Blynk.run();

  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humDHT = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempDHT = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humDHT) || isnan(tempDHT))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(tempDHT);
  Serial.print(F("°C "));
  Serial.println();
  Serial.print(F("Humidity: "));
  Serial.print(humDHT);
  Serial.print(F("%"));
  Serial.println();
  
  Serial.println("***********************");
  Serial.println();

  // Compare Threshold value from Blynk and DHT Temperature value.
  if (humDHT<90)
  {
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("Bat");
   
}
  else {
    digitalWrite(FAN_PIN, LOW);
    Serial.println("Tat");
    
  } 

  Blynk.virtualWrite(V1, tempDHT);
  Blynk.virtualWrite(V2, humDHT);
}
