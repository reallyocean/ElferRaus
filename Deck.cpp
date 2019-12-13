#include "Deck.hpp"

Deck::Deck()
{
  for (auto i = 0; i < colors.size(); ++i)
  {
    for (auto j = 0; j < numbers.size(); ++j)
    {
      Card c(numbers[j], colors[i]);
      deck.push_back(c);
    }
  }
}
std::vector<Card> Deck::getDeck()
{
  return deck;
}
