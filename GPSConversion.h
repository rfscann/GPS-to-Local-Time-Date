#define sp Serial.print
#define spl Serial.println
// GPS Simulator Section
int GPShour;
int GPSminute;
int GPSseconds;
int GPSday;
int GPSmonth;
int GPSyear;

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

void setup() {
  // GPS sample data to test final results
  Serial.begin(9600);
  
  Serial.println("Mike's virtual GPS Time and Local Time Conversion");  
  GPShour = 13;
  GPSminute = 34;
  GPSseconds = 38;
  GPSday = 28;
  GPSmonth = 2;
  GPSyear = 19;

  // Offset test data
  ohour = 11;
  ominute = 00;
}

void leapcheck(void){
  if((GPSyear == 20) || (GPSyear == 24) || (GPSyear == 28) || (GPSyear == 32) || 
  (GPSyear == 36) || (GPSyear == 40)){
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

void converter(void){
   // 1st stage of conversion
  chour = GPShour + ohour;
  cminute = GPSminute + ominute;
  cday = GPSday;
  cmonth = GPSmonth;
  cyear = GPSyear; // do I need this step?  Will leave in for now
  lyear = GPSyear;

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
  if(cday == 29 && GPSmonth == 2){
    leapcheck();
    return;
  }

  //  Process for GPSday = 29, and GPSmonth = 2
  if((GPSday ==29) && (GPSmonth = 2)){
    lday = 1;
    lmonth = 3;
    return;
  }

  //  Process for cday is 31
  if(GPSday == 31){
    if((GPSmonth == 1) || (GPSmonth == 3) || (GPSmonth == 5) || 
    (GPSmonth == 7) || (GPSmonth) == 8 || (GPSmonth == 10) || (GPSmonth == 12)){
      //  Check if end of year
      if(GPSmonth == 12){
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
  if(GPSday == 30){
    if((GPSmonth == 4) || (GPSmonth == 6) || (GPSmonth == 9) || 
    (GPSmonth == 11)){
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

void loop() {
  sp("GPS Time: "); sp(GPShour); sp(":"); sp(GPSminute); sp(":"); spl(GPSseconds);
  sp("GPS Date: "); sp(GPSday); sp("/"); sp(GPSmonth); sp("/"); spl(GPSyear);
  converter();
  sp("Loc Time: "); sp(lhour); sp(":"); sp(lminute); sp(":"); spl(GPSseconds);
  sp("Loc Date: "); sp(lday); sp("/"); sp(lmonth); sp("/"); spl(lyear);

  sp("C.day: "); spl(cday);
  
  delay(1000);
}
