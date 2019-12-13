// File
#include "Card.hpp"

Card::Card()
{
  number = 0;
  color = ' ';
}

Card::Card(int n, char c)
{
  number = n;
  color = c;
}

int Card::getNumber()
{
  return number;
}

char Card::getColor()
{
  return color;
}
