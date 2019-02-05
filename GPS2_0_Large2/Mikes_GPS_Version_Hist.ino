/* Mike's GPS Receiver Version 1.01 - Using Arduino compatiable Mega 
 *  Using hardware serial 3 (Arduino RX pin 15, TX pin 14)
 *  
 *  Version 1.0 - Used basic Adafruit_GPS.h and displayed output to Serial Monitor
 *  
 *  Version 1.01 - Added lcd1 (16 x 2) to display GPS Time and Date - Tested OK
 *                 Removed GPS Time and Date from Serial Monitor
 *                 
 *  Version 1.02 - Added 2nd LCD screen (20 x 4) to display Quality, Fix, Lattitude, &
 *                 Longitude.  Removed these lines from Serial Monitor.  
 *                 Changed delay to 1000, so that seconds refresh at 1 second interval instead
 *                 of 2 seconds.
 *                 
 *                 Found the following bugs:-
 *                        Hours, Minutes, & seconds displaying as eg. 9:9:2 instead of 
 *                        09:09:02.
 *                        Lattitude and longitude displaying as eg. 3624.0000 14567.0000
 *                        instead of -36.2400 145.6700
 *                        
 *  Version 1.03 - Added IF statements to correct time, so it displays as 09:09:02.
 *                  however found that time was displaying as 009:009:002 - Corrected IF statements
 *                  so that it tests condition between 10 and -1.  Fixed
 *                 Added offset hours to reflect my timezone.  However found a bug:
 *                        When GPS UTC time is 21:00:00, offset hours displays 32.  Will have
 *                        to correct so when it gets to 24, display 00, but add +1 to day.
 *                        Also found that Fix and Quality only showing 1. 
 *                        
 *  Version 1.04 - Removed Fix and Quality from sketch, found it was of no use to me.
 *  
 *  Version 2.00 - Change LCD Screen to a 128 x 64 matrix screen.
 *                 re-worked code to write to matrix screen.
 *                 
 *  Version 2.01 - Re-worked time offset
 *                 Created void converter(void) to house Local conversion
 *                 Created void leap(void) to check if local date is within a leap year
 *                 Added local end of year check
 *                 Have a little bug that will not print a leading 0 to GMT GPS.day
 *
 *  Version 2.02 - Removed all items relating to Serial.print
 *                 Added section to rectify Latitude & longitude bug as per above
 */
