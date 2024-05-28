/**
 * @author      : stanleyarn (stanleyarn@$HOSTNAME)
 * @file        : confswap
 * @created     : Thursday May 02, 2024 12:22:06 CEST
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "gpiocb1.hpp"
#include "minifab_daemon.hpp"

using namespace std;

#define INCLUDE_LINE_INDEX 0

string config_file_path = "/home/biqu/printer_data/config/printer.cfg";

int main(int argc, char *argv[])
{
  ifstream config_file_in;
  ofstream config_file_out;
  ofstream log_file_out;

  try
  {
    config_file_in.open(config_file_path);
  }
  catch (...)
  {
    cerr << "Error loading config file." << endl;
    return -1;
  }


  /* USER INPUT */
  string replaced_dir;
  string input;
  try
  {
    if (argc < 2)
    {
      cerr << "No argument specified." << endl;
      throw -1;
    }
    else if (argc == 2)
    {
      input = argv[1];
      if (input == "print" or input == "penplt" or input == "mill")
      {

        gpiocb1::write(PRINT_LED_PIN, LOW);
        gpiocb1::write(PENPLT_LED_PIN, LOW);
        gpiocb1::write(MILL_LED_PIN, LOW);

        if (input == "print")
        {
          replaced_dir = "PRINT";
          gpiocb1::write(PRINT_LED_PIN, HIGH);
        }
        else if (input == "penplt")
        {
          replaced_dir = "PENPLT";
          gpiocb1::write(PENPLT_LED_PIN, HIGH);
        }
        else if (input == "mill")
        {
          replaced_dir = "MILL"; 
          gpiocb1::write(MILL_LED_PIN, HIGH);
        }
      }
      else
      {
        cerr << "Specified mode is not recognized." << endl;
        throw -1;
      }
    }
    else
    {
      cerr << "Too much arguments specified." << endl;
      throw -1;
    }
  }
  catch (int e)
  {
    cerr << "confswap [print|penplt|mill]" << endl;
    return e;
  }

  /* EDIT FILE  */
  string edited_config_file_str = "";
  int i = 0;
  for (string line; getline(config_file_in, line);)
  {
    if (i == INCLUDE_LINE_INDEX)
    {
      edited_config_file_str += "[include " + replaced_dir + "/*.cfg]" + '\n';
    }
    else
    {
      edited_config_file_str += line + '\n';
    }
    i++;
  }

  config_file_in.close();

  log_file_out.open(log_file_path);
  log_file_out << replaced_dir;
  log_file_out.close();

  config_file_out.open(config_file_path);
  config_file_out << edited_config_file_str;
  config_file_out.close();

  cout << "MiniFab succefully switched to '" + replaced_dir + "' mode." << endl;

  return 0;
}
