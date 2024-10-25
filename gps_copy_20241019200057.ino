#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Wire.h>       // For I2C communication
#include <SH1106.h>     // For OLED display

// GPS and display variables
float latitude, longitude;
String lat_str, lng_str;

// Initialize SH1106 OLED display (I2C address 0x3c, SDA pin 21, SCL pin 22)
SH1106 display(0x3c, 21, 22);

// Initialize the TinyGPS++ object and HardwareSerial for GPS
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

void setup()
{
  // Start serial communication for debugging (baud rate: 115200)
  Serial.begin(115200);

  // Initialize the SH1106 OLED display
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  // Start communication with the GPS module on Serial1 (TX pin 17, RX pin 16)
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
}

void loop()
{
  // Read data from the GPS module
  while (SerialGPS.available() > 0)
  {
    // Feed the GPS data into TinyGPS++ and check if location data is valid
    if (gps.encode(SerialGPS.read()) && gps.location.isValid())
    {
      // Retrieve latitude and longitude
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      lat_str = String(latitude, 6);  // 6 decimal places for precision
      lng_str = String(longitude, 6);

      // Print latitude and longitude to Serial Monitor
      Serial.print("Latitude = ");
      Serial.println(lat_str);
      Serial.print("Longitude = ");
      Serial.println(lng_str);

      // Clear display and set alignment and font
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_16);

      // Display latitude and longitude on OLED
      display.drawString(0, 23, "Lat:");
      display.drawString(45, 23, lat_str);
      display.drawString(0, 38, "Lng:");
      display.drawString(45, 38, lng_str);

      // Render data on the OLED display
      display.display();
    }
  }

  // Add a small delay to reduce GPS polling frequency
  delay(1000);
}
