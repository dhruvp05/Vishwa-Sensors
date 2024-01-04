#include <TinyGPS++.h>
#include <TinyGPSPlus.h>

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
/*
   This sample code demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 0, TXPin = 1;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  // Serial.println(F("FullExample.ino"));
  // Serial.println(F("An extensive example of many interesting TinyGPSPlus features"));
  // Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  // Serial.println(F("by Mikal Hart"));
//   Serial.println();
//   Serial.println(F("Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
//   Serial.println(F("           (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
//   Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------------"));
// }
}
void loop()
{

  Serial.print("Satellites: ");
  Serial.print(gps.satellites.value());
  Serial.println();
  Serial.print("Latitude: ");
  Serial.print(gps.location.lat(),4);
  Serial.println();
  Serial.print("Longitude: ");
  Serial.print(gps.location.lng(),4);
  Serial.println();
  Serial.print("UTC Time: ");
  printDateTime(gps.time);
  Serial.println();
  Serial.print("Altitude: ");
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 1);
  Serial.println();
  Serial.println("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");

  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10){
    Serial.println(F("No GPS data received: check wiring"));
  }
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSTime &t)
{
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  //printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

// static void printStr(const char *str, int len)
// {
//   int slen = strlen(str);
//   for (int i=0; i<len; ++i)
//     Serial.print(i<slen ? str[i] : ' ');
//   smartDelay(0);
// }
