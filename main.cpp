#include <iostream>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"

int main()
{
  Deck d;
  for (auto it = d.getDeck().begin(); it != d.getDeck().end(); ++it)
  {
    std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
  }

  return 0;
}
