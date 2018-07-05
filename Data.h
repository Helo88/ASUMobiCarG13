
#define GPS_I2C_ADDRESS 0x5D

enum {
  GPS_NONE,
  GPS_COUNT,
  GPS_DATE,
  GPS_TIME,
  GPS_LOCATION
};

struct GPSInfo {
  unsigned long readCount;
  unsigned long validCount;
  unsigned short year;
  byte month;
  byte day;
  byte hour;
  byte minute;
  byte second;  
  float lat;
  float lon;
};

GPSInfo gpsInfo;
