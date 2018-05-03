#include <TimeLib.h>
#include <TinyGPS.h>       // http://arduiniana.org/libraries/TinyGPS/

#define SerialGPS Serial1

TinyGPS gps; 
const int offset = -5;  // Time Zone Offset
time_t lastSecond = 0; // when the digital clock was displayed

byte millis_then, millis_now, hundredths_then;

unsigned long FixAge;
int Year;
byte Month, Day, Hour, Minute, Second, Hundredths;
byte centiseconds;

void setup()
{
  Serial.begin(115200);
  while (!Serial) ; // wait for Arduino Serial Monitor
  
  SerialGPS.begin(9600);
  Serial.println("Waiting for GPS time ... ");

  //Setup initial values
  millis_then = (byte)(millis())/10;
  gps.crack_datetime(&Year, &Month, &Day, &Hour, &Minute, &Second, &hundredths_then, &FixAge);
}

void loop()
{
  while ( SerialGPS.available() )
  {
    if ( gps.encode( SerialGPS.read() ) )
    {

      gps.crack_datetime(&Year, &Month, &Day, &Hour, &Minute, &Second, &Hundredths, &FixAge);
      millis_now = (byte)(millis())/10;

      Serial.println(FixAge); 
      Serial.println(Hundredths); 
      if (FixAge < 500)
      {
        setTime(Hour, Minute, Second, Day, Month, Year);
        adjustTime(offset * SECS_PER_HOUR);
      }
    }
  }
  
  if ( timeStatus()!= timeNotSet )
  {
    centiseconds = ((millis_now + hundredths_then-millis_then) % 100);  //if milliseconds aren't provided, make our own by adding delta in millis/10 to hundredths
    if (now() != lastSecond || (centiseconds - Hundredths) >= 3)
    {  
      lastSecond = now();
      centiseconds = Hundredths;
      
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
      Serial.print(" mt: ");
      Serial.print(millis_then);
      Serial.print(" mn: ");
      Serial.print(millis_now);
      Serial.print(" ht: ");
      Serial.print(hundredths_then);
      Serial.print(" hn: ");
      Serial.print(Hundredths);
      Serial.print(" cs: ");
      Serial.print(centiseconds);
      Serial.println(); 
    }
  }
  millis_then = millis_now;
  hundredths_then = Hundredths;
}
