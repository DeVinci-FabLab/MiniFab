/**
 * @author      : stanleyarn (stanleyarn@$HOSTNAME)
 * @file        : gpiocb1
 * @created     : Friday Apr 19, 2024 13:53:11 CEST
 */

#ifndef GPIOCB1_HPP
#define GPIOCB1_HPP

#include <string>
#include <iostream>
#include <map>

#define HIGH 1
#define LOW 0

using namespace std;

class gpiocb1
{
  public:
    gpiocb1() = delete;
    static void write(unsigned int pin, bool state);
    static int read(unsigned int pin);
    static string execCommand(const string cmd, int *out_exitStatus = nullptr);

  private:

    static const map<int, int> pin_mapping;
    
};

#endif 

