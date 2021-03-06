
     
#include <Adafruit_GPS.h>
#include <U8glib.h>

#define GPSSerial Serial3
#define GPSECHO false
Adafruit_GPS GPS(&GPSSerial);
uint32_t timer = millis();

U8GLIB_ST7920_128X64 u8g(13, 12, 11, U8G_PIN_NONE);

//  Below 2 lines simply for quicker aceess to functions
#define upos u8g.setPrintPos 
#define uprint u8g.print  

int posX=0;
int posY=0;

// Time offset Section
int ohour;
int ominute;

// Extra int's for conversion process
int chour;
int cminute;
int cday;
int cmonth;
int cyear;

// Converted int's for final display of Offset Time / Date
int lhour;
int lminute;
int lseconds;
int lday;
int lmonth;
int lyear;

//  extra's for GPS coordinate calculations
float clatitude = 0.0000;
float clongitude = 0.0000;
float llatitude = 0.0000;
float llongitude = 0.0000;

//-----------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);  
  GPSSerial.println(PMTK_Q_RELEASE);
  
  //  Set matrix display
  
  
  // UTC (GMT) Offset data (Match your timezone offset here
  ohour = 11;
  ominute = 00;
}

//----------------------------------------------------------------------------

void leapcheck(void){
  if((GPS.year == 20) || (GPS.year == 24) || (GPS.year == 28) || (GPS.year == 32) || 
  (GPS.year == 36) || (GPS.year == 40)){
    lday = 29;
    lmonth = 2;
    int leap = 1;
    return;
  }
  else{
    lday = 1;
    lmonth = 3;
    return;
  }
}

//-------------------------------------------------------------------------

void  greeting(void){
  u8g.setFont(u8g_font_6x10);
  u8g.setColorIndex(1);
  upos (20, 20);
  uprint("Mike's GPS");
  upos (40, 40);
  uprint("Version 2.02");
  delay (5000)
}

void converter(void){
   // 1st stage of conversion
  chour = GPS.hour + ohour;
  cminute = GPS.minute + ominute;
  cday = GPS.day;
  cmonth = GPS.month;
  //cyear = GPS.year; // do I need this step?  Will leave in for now
  lyear = GPS.year;

  //Check if cmin is >= 60
  if(cminute >= 60){
    lminute = cminute - 60;
    chour ++;
  }
  else {
    lminute = cminute; }

  //  Check if c.day will become a new day
  if(chour >= 24){
    lhour = chour - 24;
    cday ++;
  }
  else{
    lhour = chour;
    lday = cday;
    lmonth = cmonth;
    return;
  }

  //  Is cday <= 28
  if(cday <= 28){
    lday = cday;
    lmonth = cmonth;
    return;
  }

  //  Check if day = 29 and if GPS.month = 2
  if(cday == 29 && GPS.month == 2){
    leapcheck();
    return;
  }

  //  Process for GPSday = 29, and GPSmonth = 2
  if((GPS.day ==29) && (GPS.month = 2)){
    lday = 1;
    lmonth = 3;
    return;
  }

  //  Process for cday is 31
  if(GPS.day == 31){
    if((GPS.month == 1) || (GPS.month == 3) || (GPS.month == 5) || 
    (GPS.month == 7) || (GPS.month) == 8 || (GPS.month == 10) || (GPS.month == 12)){
      //  Check if end of year
      if(GPS.month == 12){
           lday = 1;
          lmonth = 1;
          lyear ++;
          return;
        }
      else{
        lday = 1;
        lmonth = cmonth +1;
        return;
      }
    }
  }
  if(GPS.day == 30){
    if((GPS.month == 4) || (GPS.month == 6) || (GPS.month == 9) || 
    (GPS.month == 11)){
      lday = 1;
      lmonth = cmonth + 1;
      return;
    }
     else{
    lday = cday;
    lmonth = cmonth;
    return;
    }
  }
  lday = cday;
  lmonth = cmonth;
}

//------------------------------------------------------------------------------

void disp(){
  u8g.setFont(u8g_font_6x10);
  u8g.setColorIndex(1);
  int Line1=8;
  int Line2=Line1 + 9;
  int Line3=Line2 + 9;
  int Line4=Line3 + 9;
  int Line5=Line4 + 9;
  int Line6=Line5 + 9;
  int Line7=Line6 + 9;

  //  Line 1
  posY = Line1;
  posX = 0;
  upos(posX,posY); uprint("GMT "); upos(posX+100, posY); uprint("Local");

  //  Line 2
  //  UTC / GMT Time
    posY = Line2;
    posX = 0;
    if((GPS.hour < 10) && (GPS.hour > -1)){
      upos(posX,posY); uprint("0"); upos(posX+6,posY); uprint(GPS.hour);
    }
    else {
      upos(posX,posY); uprint(GPS.hour);
    }
    posX = posX+12;
    upos(posX,posY-1); uprint(":");
    posX = posX+6;
    if((GPS.minute < 10) && (GPS.minute > -1)){
      upos(posX,posY); uprint("0"); upos(posX+6,posY); uprint(GPS.minute);
    }
    else {
      upos(posX,posY); uprint(GPS.minute);
    }
    posX = posX+12;
    upos(posX,posY-1); uprint(":");
    posX=posX+6;
    if((GPS.seconds < 10) && (GPS.seconds > -1)){
      upos(posX,posY); uprint("0"); upos(posX+6,posY); uprint(GPS.seconds);
    }
    else {
      upos(posX,posY); uprint(GPS.seconds);
    }

    // Local Time
    posX = posX + 45;
    upos(posX, posY);
    if((lhour < 10) && (lhour > -1)){
      uprint("0"); uprint(lhour);
    }
    else{
      uprint(lhour);
    }
    posX = posX+12;
    upos(posX, posY-1);
    uprint(":");
    posX = posX+6;
    if((GPS.minute < 10) && (GPS.minute > -1)){
      upos(posX,posY); uprint("0"); upos(posX+6,posY); uprint(GPS.minute);
    }
    else {
      upos(posX,posY); uprint(GPS.minute);
    }
    posX = posX+12;
    upos(posX,posY-1); uprint(":");
    posX=posX+6;
    if((GPS.seconds < 10) && (GPS.seconds > -1)){
      upos(posX,posY); uprint("0"); upos(posX+6,posY); uprint(GPS.seconds);
    }
    else {
      upos(posX,posY); uprint(GPS.seconds);
    }
    
    //  Local Date
    posX = 69; posY = Line3;
    upos(posX, posY);
    if(lday < 10 && lday > 0){
      uprint("0"); uprint(lday);
    }
    else{
      uprint(lday);
    }
    uprint("/");
    if((lmonth < 10) && (lmonth > 0)){
      uprint("0"); uprint(lmonth);
    }
    else{
      uprint(lmonth);
    }
    uprint("/20"); 
    uprint(lyear);
    
    // UTC Date
    posX = 0; posY = Line3;
    if((GPS.day < 10) && (GPS.day > 0)){
      uprint("0"); upos(posX+6, posY); uprint(GPS.day);
    }
    else {
      upos(posX, posY);
      uprint(GPS.day);
    }
    uprint("/");
    if((GPS.month < 10) && (GPS.month > 0)){
      uprint("0"); uprint(GPS.month);
    }
    else {
      uprint(GPS.month);
    }
    uprint("/"); uprint("20");
    uprint(GPS.year);

    //  Line 4
    posX = 0; posY = Line4; upos (posX, posY);
    uprint("Fix = "); uprint(GPS.fix); uprint(" Quality = "); uprint(GPS.fixquality);

    // Line 5
    posX = 0; posY = Line5; upos(posX, posY);
    uprint(float(llatitude),4); uprint(GPS.lat); uprint(" "); uprint(float(llongitude),4); uprint(GPS.lon);

    // Line 6
    posX = 0; posY = Line6; upos(posX, posY); 
    uprint("S = "); uprint(GPS.satellites); uprint(" Alt = "); uprint(GPS.altitude);

    // Line 7
    posY = Line7; upos(posX, posY);
    uprint("A = "); uprint(GPS.angle); uprint(" Kn = "); uprint(GPS.speed);
}

//-------------------------------------------------------------------------------------------------

void GPScoord(void){
  
  //  North of the equator (Latitude) indicated as N (North) (Positive Numbers)
  //  South of the equator (Latitude) indicates as S (South) (Negative Numbers)
  //  West of the Prime Meridian (Longitude) indicates W (West) (Negative Numbers)
  //  East of the Prime Meridian (Longitude) indicates E (East) (Positive Numbers)

  clatitude = (float(GPS.latitude) / 100.0000);
  clongitude = (float(GPS.longitude) / 100.0000);
  
  if(GPS.lat == 83){  // Assci S = 83 Dec
    llatitude = float(clatitude * -1.0000);
  }
  else{
    llatitude = clatitude;
  }
  if(GPS.lon == 87){
    llongitude = float(clongitude * -1.0000 );
  }
  else{
    llongitude = clongitude;
  }
}


void loop() {
  char c = GPS.read();
  if (GPS.newNMEAreceived()) {
    //Serial.println(GPS.lastNMEA()); 
    if (!GPS.parse(GPS.lastNMEA())) 
      return; 
  }
  if (timer > millis()) timer = millis();
       
  if (millis() - timer > 1000) {
    timer = millis(); // reset the timer
    
    //  Call the converter code to calculate local data
    converter();

    //  Call the GPScoord code to correct GPS Lat & Lon
    GPScoord();

    // Display collected data onto screen
    u8g.firstPage();
    do{
      disp();
    } 
    while(u8g.nextPage());
  }
}
