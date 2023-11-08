/** Converts a numeric character, i.e. '1' to an integer, 1
 * @param c Integer as a character
 * @returns Integer representation of c
*/
int toInt(char c) {
  return c - '0';
}

/** Create a device UID based on the harware MAC Address
 * @returns CLOCK-XXXXXX where XXXXXX is a partial MAC address of the chip
*/
String GetDeviceUID() {
  return "CLOCK-" + String(ESP.getChipId());
}
