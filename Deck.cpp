#include "Deck.hpp"

Deck::Deck()
{
  for (size_t i = 0; i < colors.size(); ++i)
  {
    for (size_t j = 0; j < numbers.size(); ++j)
    {
      Card c(numbers[j], colors[i]);
      deck.push_back(c);
    }
  }
}

void Deck::setupDeck()
{

}

std::vector<Card> &Deck::getDeck()
{
  return deck;
}
