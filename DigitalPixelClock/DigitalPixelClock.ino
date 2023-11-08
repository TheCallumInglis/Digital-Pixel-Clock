#include <Adafruit_NeoPixel.h> // https://github.com/adafruit/Adafruit_NeoPixel
#include <ESP8266WiFi.h>
#include <RTClib.h> // https://github.com/adafruit/RTClib
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h> // "Time" by Michael Margolis

#include "secret.h"
#include "config.h"
#include "functions.h"

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Time
WiFiUDP ntpUDP;
NTPClient time_client(ntpUDP, NTPServer);
char timestr[4]; // Stores time, e.g. 2359 would be 23hrs 59mins

/** Setup WiFi
 * Tweak timeout value as required
 * @return True on Success, False otherwise
*/
bool setupWifi() {
  int timeout = 30;

  WiFi.hostname(GetDeviceUID());
  WiFi.begin(WIFI_SSID, WIFI_PASS); 

  Serial.print("[WiFi] :: Connecting");
  while (WiFi.status() != WL_CONNECTED && timeout > 0)
  {
    delay(500);
    Serial.print(".");
    timeout--;
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }

  // WiFi 
  Serial.print("[WiFi] :: Connected, IP address: ");
  Serial.println(WiFi.localIP());

  return true;
}

/** Get Time from NTP in the desired format.
 * Store result in &timestr, setting to 0000 in case of error.
 * @return True on Success, False otherwise
*/
bool getTime(char (&timestr)[4]) {
  char format[] = "hhmm";
  Serial.println("[TIME] :: Getting the time now...");

  if (time_client.update() || time_client.isTimeSet()) {
    strcpy(timestr, DateTime(time_client.getEpochTime()).toString(format));
    Serial.print("[TIME] :: Time Updated. It is now "); Serial.println(timestr);
    return true;

  } else {
    strcpy(timestr, "0000");
    Serial.println("[TIME] :: Failed to get the time");
    return false;
  }
}

/** Shuffle the given array using Fisher-Yates algorithm
 * @param arr Target Array
 * @param size Size of arr
 */
void shuffleArray(int arr[], int size) {
  for (int i = size - 1; i > 0; --i) {
    int j = rand() % (i + 1);
    std::swap(arr[i], arr[j]);
  }
}

/** Shuffle all arrays used for pixel mappings
*/
void shufflePixelArrays() {
  shuffleArray(hourTens, 3);
  shuffleArray(hourUnits, 9);
  shuffleArray(minTens, 6);
  shuffleArray(minUnits, 9);
}

/** Illuminate clock section in desired colour. [val] number of pixels are to be illuminated. 
 * @param val Numeric value for section, e.g. 6 would represent 6 pixels to illuminate
 * @param pixelArray Pool of Pixels to be illuminated
 * @param colour Colour for this section
*/
void lightUpSection(int val, int* pixelArray, uint32_t colour) {
  for (int i = 0; i < val; i++) {
    pixels.setPixelColor(pixelArray[i], colour);
  }
}

void setup() {
  delay(3000);
  Serial.begin(SERIAL_BAUD);

  // Setup Wifi
  if (!setupWifi()) {
    Serial.println("[ERROR] :: Failed to setup wifi");
    return;
  }

  // Setup Pixels
  pixels.begin();
}


void loop() {
  pixels.clear();

  delay(UPDATE_FQ);

  // Get Time
  if (!getTime(timestr)) {
    return; // TODO Handle failure
  }

  // Shuffle Pixels
  shufflePixelArrays();

  // Update Clock
  lightUpSection(toInt(timestr[0]), hourTens,   pixels.Color(0, 150, 0));     // Hour Tens
  lightUpSection(toInt(timestr[1]), hourUnits,  pixels.Color(150, 0, 0));     // Hour Units
  lightUpSection(toInt(timestr[2]), minTens,    pixels.Color(150, 150, 150)); // Minute Tens
  lightUpSection(toInt(timestr[3]), minUnits,   pixels.Color(0, 0, 150));     // Minute Units

  pixels.show();
}