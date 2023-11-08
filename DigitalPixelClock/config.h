// Serial
#define SERIAL_BAUD 9600

// I/O
#define PIN       D1
#define NUMPIXELS 36    // (27 rows x 3 columns)
#define UPDATE_FQ 5000  // ms

// Time
#define NTPServer "uk.pool.ntp.org"

// Pixels (What pixels apply to each time component)
int hourTens[]  = {0, 12, 24};
int hourUnits[] = {2, 3, 4, 14, 15, 16, 26, 27, 28};
int minTens[]   = {6, 7, 18, 19, 30, 31};
int minUnits[]  = {9, 10, 11, 21, 22, 23, 33, 34, 35};