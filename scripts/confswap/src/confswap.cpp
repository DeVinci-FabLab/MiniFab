/**
 * @author      : stanleyarn (stanleyarn@$HOSTNAME)
 * @file        : confswap
 * @created     : Tuesday Apr 16, 2024 17:17:07 CEST
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

/* PATH VARIABLES */
const string printer_inc_dir = "PRINT";
const string engraver_inc_dir = "PENPLT";
const string cnc_inc_dir = "CNC";

const string printer_config_file = "/home/biqu/printer_data/config/printer.cfg";
/* -------------- */


int editConfig(string include_dir)
{
  string config_file_str;

  ifstream config_file;
  ofstream new_config_file;
  config_file.exceptions(ifstream::badbit | ifstream::failbit);
  new_config_file.exceptions(ifstream::badbit | ifstream::failbit);

  // open file
  try 
  {
    config_file.open(printer_config_file.c_str(), ios::in);
    stringstream sstr;
    sstr << config_file.rdbuf();
    config_file.close();
    config_file_str = sstr.str();
  } 
  catch (ifstream::failure &e) 
  {
    cout << "Error reading printer.cfg : " << e.what() << endl; 
    return 1;
  }

  int i = 0;
  int line_cnt = 0;

  string new_config_file_str = "";

  while (config_file_str[i] != 0)
  {
    char c = config_file_str[i];
    if (c == '\n') 
    {
      line_cnt++;

      if (line_cnt == 2 - 1)
      {
        new_config_file_str += "\n[include " + include_dir + "/*.cfg]";
      }

    }

    if (line_cnt != 2 - 1)
    {
        new_config_file_str += c;
    }

    i++;
  }

  remove(printer_config_file.c_str());

  try
  {
    new_config_file.open(printer_config_file.c_str(), ios::out);
    new_config_file << new_config_file_str;
    new_config_file.close();
  }
  catch (ofstream::failure &e)
  {
    cerr << "Error : " << e.what();
    return 1;
  }

  return 0;
}

int main(int c, char *v[])
{
  string selected_mode;
  if (c > 1)
  {
    selected_mode = v[1];
  }
  else
  {
    cerr << "No mode specified." << endl; 
    return 1;
  }

  if (selected_mode == "printer")
  {
     int err = editConfig(printer_inc_dir);

     if (err) cerr << "Error." << endl; 
     else cout << "Printer mode succefully set." << endl;
  }
  else if (selected_mode == "engraver")
  {
     int err = editConfig(engraver_inc_dir);

     if (err) cerr << "Error." << endl; 
     else cout << "Pen mode succefully set." << endl;
  }
  else if (selected_mode == "cnc")
  {
     int err = editConfig(cnc_inc_dir);
     
     if (err) cerr << "Error." << endl; 
     else cout << "Milling mode succefully set." << endl;
  }
  else
  {
    cerr << "The selected mode does not exist." << endl;
    return 1;
  }

  return 0;
}
