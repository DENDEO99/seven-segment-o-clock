#include <ESPert.h>

ESPert espert;

void setup() 
{
Serial.begin(115200);
  espert.init();

  espert.oled.init();

  // Use espert.dht.init(gpio, type);
  // Type can be DHT11 or DHT22
  // Defualt will use DHT22 on GPIO12
  espert.dht.init();

  delay(2000);
}

void loop() 
{
  bool isFarenheit = false;
  float t = espert.dht.getTemperature(isFarenheit);
  float h = espert.dht.getHumidity();

  if (!isnan(t) && !isnan(h)) {
    String dht = "Temperature: " + String(t) + (isFarenheit ?  " F" : " C") + "\n";
    dht += "Humidity...: " + String(h) + " %\n";

//    espert.oled.clear();
//    espert.oled.println(dht);
//    espert.println(dht);
  Serial.println(dht);

  }

  delay(100);
}
