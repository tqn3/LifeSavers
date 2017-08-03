/*
 * The stuff in the setup loop is just to check that we can write (except for closing the file).
 * So to integrate, just copy/paste the defined functions to your code and call open_file on
 * startup, and write_to_file to write a string (char array, this is C) to the file.
 * THEN MAKE SURE YOU CLOSE THE FILE
 */

#include <SD.h>
#include <SPI.h>
#include <stdlib.h>
#include <stdio.h>

void setup() {
  delay(1000);
  File log_file = open_file("testlog");

  int i = 0;
  for (i; i < 5; i++)
  {
    String str = "testing, logged at: ";
    delay(1000);
    str += (int)millis();
    write_to_file(log_file, str);
  }

  //MAKE SURE you close the file when done writing to it.
  log_file.close();
}

// Call this function before writing; it opens the file.
File open_file(String logname)
{
  if (!SD.exists("STDSlogs/"))
  {
    SD.mkdir("STDSlogs");
  }
  String filepath = "STDSlogs/" + logname + ".log";
  char path[50]; filepath.toCharArray(path, 50);
  File logfile = SD.open(path, FILE_WRITE);
  if (logfile == NULL)
  {
    int lognum = 0;
    logname = "";
    do
    {
      filepath += "STDSlogs/run" + logname + lognum + ".log";
      lognum++;
      logname = "";
    } while (SD.exists(path));
      logname = "";
      filepath += "STDSlogs/run" + logname + lognum + ".log";
      logfile = SD.open(path, FILE_WRITE);
      filepath.toCharArray(path, 50);
    while (path == NULL)
    {
      logfile = open_file("log");
    }
  }
  unsigned long start = millis();
  int start_sec = (int) start / 1000;
  String lgmsg = "Log started at ";
  lgmsg += start_sec + " seconds.\n\n";
  char logmessage[50];
  lgmsg.toCharArray(logmessage, 50);
  logfile.write(logmessage);
  return logfile;
}

// Call this function to write to the file
//bool write_to_file(File logfile, char* message)
bool write_to_file(File logfile, String message)
{
  char charBuf[50];
  message.toCharArray(charBuf, 50);
  logfile.write(strcat(charBuf, "\n"));
}

void loop() {


}
