
#include <gpiocb1.hpp>

int main(int c, char *v[])
{
  try
  {
    if (c > 2)
    {
      int pin = stoi(v[2]);
      int state = -1;
      if (c > 3) state = stoi(v[3]);

      if (string(v[1]) == "read") 
      {
        cout << gpiocb1::read(pin);
      }
      else if (string(v[1]) == "write")
      {
        if (state == -1) throw 2;
        gpiocb1::write(pin, state);
      }
    }
    else
    {
      throw 1;
    }
  }
  catch (int e)
  {
    cerr << "Error.\n - gpio read <pin>\n - gpio write <pin> <0/1>" << endl;
    return -1;
  }

  return 0;
}
