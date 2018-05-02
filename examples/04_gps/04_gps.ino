#include <TimeLib.h>
#include <TinyGPS.h>       // http://arduiniana.org/libraries/TinyGPS/

#define SerialGPS Serial1

TinyGPS gps; 
const int offset = -5;  // Time Zone Offset
time_t lastSecond = 0; // when the digital clock was displayed

void setup()
{
  Serial.begin(115200);
  while (!Serial) ; // wait for Arduino Serial Monitor
  
  SerialGPS.begin(9600);
  Serial.println("Waiting for GPS time ... ");
}

void loop()
{
  while ( SerialGPS.available() )
  {
    if ( gps.encode( SerialGPS.read() ) )
    {
      unsigned long FixAge;
      int Year;
      byte Month, Day, Hour, Minute, Second, Hundredths;
      
      gps.crack_datetime(&Year, &Month, &Day, &Hour, &Minute, &Second, &Hundredths, &FixAge);

      Serial.println(FixAge); 
      if (FixAge < 500)
      {
        setTime(Hour, Minute, Second, Day, Month, Year);
        adjustTime(offset * SECS_PER_HOUR);
      }
    }
  }
  
  if ( timeStatus()!= timeNotSet )
  {
    if (now() != lastSecond)
    {  
      lastSecond = now();
      
      Serial.print(year()); 
      Serial.print(" ");
      Serial.print(month());
      Serial.print(" ");
      Serial.print(day());
      Serial.print(" ");
      Serial.print(hour());
      Serial.print(" ");
      Serial.print(minute());
      Serial.print(" ");
      Serial.print(second());
      Serial.println(); 
    }
  }
}
