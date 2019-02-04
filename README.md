# GPS-to-Local-Time-Date
To simulate or modify to work with an actual GPS, will calculate the offset local time.  It will work out if it is the end of the month, end of the year, and even check if February is in a leap year.

Please note:  This is my 1st complete code that I have done myself with out using examples.  It may not be perfect, and not structured as the more experienced coders do.  Please concider this before placing comments.  Constructive comments are most welcome.

This code will require you to change the following lines:

Simulator GPS Hours, Minutes, Seconds, Day, Month, and year
GPShour = 13;
GPSminute = 34;
GPSseconds = 38;
GPSday = 28;
GPSmonth = 2;
GPSyear = 19;

// Offset test data - Put your own offset details in the below 2 lines
ohour = 11;
ominute = 00;

**Using GPS (UTC) data to display local time and data

Note: GPSday, GPSmonth, GPSyear, GPShour, GPSminute, GPSseconds will need to be renamed GPS.day, GPS.month, GPS.year, GPS.hour, GPS.minute, and GPS.seconds.

This code does not directly work with a GPS module, with out making the changes above, or to match your GPS module.

