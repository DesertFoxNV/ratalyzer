#define countof(a) (sizeof(a) / sizeof(a[0]))

String getDate(const RtcDateTime& dt, byte format = 0) {
  char datestring[20];

  if (!format) {
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
  } else { // For getting file name
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u-%02u-%04u_%02u-%02u-%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
  }

  return datestring;
}
