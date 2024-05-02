/**
 * @author      : stanleyarn (stanleyarn@$HOSTNAME)
 * @file        : minifab_daemon
 * @created     : Thursday May 02, 2024 11:40:20 CEST
 */

#include "gpiocb1.hpp"
#include "minifab_daemon.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool spindle_activated = true;

void start()
{
  try
  {
    ifstream log_file_in(log_file_path);
    string mode;
    getline(log_file_in, mode);
    mode = mode.substr(mode.find('=') + 1, mode.size());
    if (mode == "PRINT") gpiocb1::write(PRINT_LED_PIN, HIGH);
    else if (mode == "PENPLT") gpiocb1::write(PENPLT_LED_PIN, HIGH);
    else if (mode == "MILL") gpiocb1::write(MILL_LED_PIN, HIGH);
  }
  catch(...)
  {
    cerr << "Log file not found." << endl;
  }
}

void loop()
{

  /* SPINDLE INTERRUPT */
  if (gpiocb1::read(SPINDLE_INTERRUPT_PIN) == LOW and spindle_activated)
  {
    gpiocb1::execCommand("curl -d ""script=M112"" http://mfv3.local/printer/gcode/script"); 
    spindle_activated = false;
  }
  else
  {
    spindle_activated = true;
  }
}

int main()
{
  start();
  while (true) loop();

  return 0;
}
