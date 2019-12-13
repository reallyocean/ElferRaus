#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.hpp"

class Deck
{
public:
  Deck();
  std::vector<Card> getDeck();

private:
  std::vector<Card> deck;
  std::vector<short> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  std::vector<char> colors = {'R', 'G', 'B', 'Y'};
};

#endif
