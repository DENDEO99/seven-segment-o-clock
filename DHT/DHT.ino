#include <ESPert.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

ESPert espert;
void D_H_T(void);
void o_clock(void);

void setup()
{

  Serial.begin(115200);
  espert.init();
  while (!Serial) ;
  espert.oled.init();

  // Use espert.dht.init(gpio, type);
  // Type can be DHT11 or DHT22
  // Defualt will use DHT22 on GPIO12
  espert.dht.init();

  delay(2000);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
}

void loop()
{
  void D_H_T(void);
  void o_clock(void);
  //  delay(100);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void D_H_T(void)
{
  tmElements_t tm;
  bool isFarenheit = false;
  float t = espert.dht.getTemperature(isFarenheit);
  float h = espert.dht.getHumidity();

  if (!isnan(t) && !isnan(h))
  {
    String dht = "Temperature: " + String(t) + (isFarenheit ?  " F" : " C") + "\n";
    dht += "Humidity...: " + String(h) + " %\n";

    //    espert.oled.clear();
    //    espert.oled.println(dht);
    //    espert.println(dht);
    Serial.println(dht);

  }
}

void o_clock(void)
{
  tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  }
  else
  {
    if (RTC.chipPresent())
    {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    }
    else
    {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}


