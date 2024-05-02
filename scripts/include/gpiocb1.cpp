/**
 * @author      : stanleyarn (stanleyarn@$HOSTNAME)
 * @file        : gpiocb1
 * @created     : Friday Apr 19, 2024 13:53:00 CEST
 */

#include "gpiocb1.hpp"

const map<int, int> gpiocb1::pin_mapping =
{
  { 7, 71 },
  { 11, 78 },
  { 13, 76 },
  { 15, 74 },
  { 19, 231 },
  { 21, 232 },
  { 23, 230 },
  { 35, 198 },
  { 37, 79 },
  { 12, 77 },
  { 16, 75 },
  { 18, 73 },
  { 26, 200 },
  { 32, 201 },
  { 38, 234 },
  { 40, 72 }
};

void gpiocb1::write(unsigned int pin, bool state)
{
  execCommand("sudo gpioset gpiochip0 " + to_string(pin_mapping.at(pin)) + "=" + to_string((int)state));
}

int gpiocb1::read(unsigned int pin)
{
  string ret = execCommand("sudo gpioget gpiochip0 " + to_string(pin_mapping.at(pin)));
  int iret = 0;

  try
  {
    iret = stoi(ret);
  }
  catch(...) { }

  return iret;
}

string gpiocb1::execCommand(const string cmd, int *out_exitStatus)
{
    if (out_exitStatus != nullptr) *out_exitStatus = 0;
    auto pPipe = ::popen(cmd.c_str(), "r");
    if(pPipe == nullptr)
    {
        throw runtime_error("Cannot open pipe");
    }

    array<char, 256> buffer;

    string result;

    while(!feof(pPipe))
    {
        auto bytes = fread(buffer.data(), 1, buffer.size(), pPipe);
        result.append(buffer.data(), bytes);
    }

    auto rc = ::pclose(pPipe);

    if(WIFEXITED(rc))
    {
      if (out_exitStatus != nullptr) *out_exitStatus = WEXITSTATUS(rc);
    }

    return result;
}
