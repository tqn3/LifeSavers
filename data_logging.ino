/*
 * The stuff in the setup loop is just to check that we can write (except for closing the file).
 * So to integrate, just copy/paste the defined functions to your code and call open_file on 
 * startup, and write_to_file to write a string (char array, this is C) to the file.
 * THEN MAKE SURE YOU CLOSE THE FILE
 */

#include <SD.h>
#include <stdlib.h>
#include <stdio.h>

void setup() {
  delay(1000);
  File log_file = open_file("testlog");

  int i = 0;
  for (i; i < 5; i++)
  {
    char str[5] = "";
    delay(1000);
    write_to_file(log_file, strcat(strcat("testing, logged at: ", sprintf(str, "%d")),(int)millis())); 
  }

  //MAKE SURE you close the file when done writing to it.
  log_file.close();
}

// Call this function before writing; it opens the file.
File open_file(char logname[])
{
  if(!SD.exists("STDSlogs/"))
  {
    SD.mkdir("STDSlogs");
  }
  char* filepath = strcat(strcat("STDSlogs/", logname), ".log");
  File logfile = SD.open(filepath, FILE_WRITE);
  if(logfile == NULL)
  {
    int lognum = 0;
    logname = "";
    do
    {
      filepath = strcat(strcat("STDSlogs/run", sprintf(logname, "%d", lognum)), ".log");
      lognum++;
      logname = "";
    } while(SD.exists(filepath));
    logname = "";
    filepath = strcat(strcat("STDSlogs/run", sprintf(logname, "%d", lognum)), ".log");
    logfile = SD.open(filepath, FILE_WRITE);
    while (logfile == NULL)
    {
      logfile = open_file("log");
    }
  }
  char str[5] = "";
  unsigned long start = millis();
  int start_sec = (int) start / 1000;
  char* logmessage = strcat(strcat("Log started at ", sprintf(str, "%d", start_sec)), " seconds.\n\n");
  logfile.write(logmessage);
  return logfile;
}

// Call this function to write to the file
bool write_to_file(File logfile, char* message)
{
  logfile.write(strcat(message, "\n"));
}

void loop() {
  

}
