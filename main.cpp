#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Card.hpp"
#include "Deck.hpp"

void menu();
void processPlayerCount(int);
std::vector<Card> deal(std::vector<Card>&);

int main()
{
  Deck d;
  auto deck = d.getDeck();
  /*
  for (auto it = d.getDeck().begin(); it != d.getDeck().end(); ++it)
  {
    std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
  }*/
  auto rng = std::default_random_engine {};
  std::shuffle(deck.begin(), deck.end(), rng);
  /*
  for (auto it = d.getDeck().begin(); it != d.getDeck().begin() + 20; ++it)
  {
    std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
  }
  */

  menu();
  auto hand = deal(deck);

  for (auto it = hand.begin(); it != hand.end(); ++it)
  {
    std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
  }

  return 0;
}

void menu()
{
  int playerCount{0};

  std::cout << "Welcome!" << std::endl;
  std::cout << "How many players? 1-4" << std::endl;
  std::cin >> playerCount;
  processPlayerCount(playerCount);
}

void processPlayerCount(int playerCount)
{
  if (playerCount != 1)
  {
    std::cout << "You've entered too many players." << std::endl;
  }
}

std::vector<Card> deal(std::vector<Card>& deck)
{
  const int HAND_SIZE = 7;
  std::vector<Card> hand;

  for (size_t i = 0; i < HAND_SIZE; ++i)
  {
    auto singleCard = deck.back();
    hand.push_back(singleCard);
    deck.pop_back();
  }

  return hand;
}
