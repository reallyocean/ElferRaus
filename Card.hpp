#ifndef CARD_H
#define CARD_H

class Card
{
public:
  Card();
  Card(int n, char c);
  int getNumber();
  char getColor();

  ~Card() {};

private:
  int number = 0;
  char color = ' ';
};

#endif
