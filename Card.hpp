#ifndef CARD_H
#define CARD_H

class Card
{
public:
  Card();
  Card(short n, char c);
  short generateNumber();
  short getNumber();

  char generateColor();
  char getColor();

  ~Card() {};

private:
  short number;
  char color;
};

#endif
