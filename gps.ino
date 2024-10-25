#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Initialize the TinyGPS++ object
TinyGPSPlus gps;

// Initialize HardwareSerial for GPS communication
HardwareSerial SerialGPS(1);  // Using Serial1 (pins 16 and 17)

void setup()
{
  // Begin serial communication for debugging (baud rate: 115200)
  Serial.begin(115200);

  // Begin serial communication for the GPS module
  // TX pin: 17, RX pin: 16, Baud rate: 9600
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("GPS Tracker Initialized");
}

void loop()
{
  // Continuously read data from the GPS module
  while (SerialGPS.available() > 0)
  {
    // Feed the GPS data into the TinyGPS++ library
    if (gps.encode(SerialGPS.read()))
    {
      // Check if the GPS has a valid location fix
      if (gps.location.isValid())
      {
        // Get the latitude and longitude
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        // Print latitude and longitude to the Serial Monitor
        Serial.print("Latitude: ");
        Serial.println(latitude, 6);  // 6 decimal places for precision
        Serial.print("Longitude: ");
        Serial.println(longitude, 6);
      }
      else
      {
        Serial.println("Location not valid yet.");
      }
    }
  }

  // Add a small delay to prevent flooding the serial output
  delay(1000);
}
