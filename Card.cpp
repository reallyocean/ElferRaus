// File
#include "Card.hpp"

Card::Card()
{
  number = 0;
  color = ' ';
}

Card::Card(short n, char c)
{
  number = n;
  color = c;
}

short Card::generateNumber()
{
  short number = 3;

  return number;
}

short Card::getNumber()
{
  return number;
}

char Card::generateColor()
{
  char color = 'R';

  return color;
}

char Card::getColor()
{
  return color;
}
