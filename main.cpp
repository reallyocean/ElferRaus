#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iterator>
#include <limits>

#include "includeFiles.hpp"

using Cards = std::vector<Card>;

void menu();
int getPlayerCount();
std::vector<Cards> deal(int, Cards&);
void shuffleDeck(Cards&);
void displayAllHands(std::vector<Cards>&);
bool elevensInHands(Cards&);
bool redElevenInHands(std::vector<Cards>&);
bool elevenInHand(std::vector<Cards>&);
void firstMove(std::vector<Cards>&, Cards&, std::vector<Cards>&);
int getPlayer(std::vector<Cards>&, int, char);
Cards::iterator positionOfEleven(Cards&);
Cards::iterator positionOfCard(std::vector<Cards>&, int, int, char);
void playRedEleven(Cards::iterator, Cards&, std::vector<Cards>&);
void playCard(Cards::iterator, std::vector<Cards>&, std::vector<Cards>&, int);
bool cardIsRed(Card&);
bool cardIsGreen(Card&);
bool cardIsBlue(Card&);
bool cardIsYellow(Card&);
bool cardIsLow(Card&);
bool cardIsEleven(Card&);
bool cardIsHigh(Card&);

int main()
{
  Deck d;
  auto deck = d.getDeck();
  shuffleDeck(deck);

  menu();
  auto playerCount = getPlayerCount();
  auto allHands = deal(playerCount, deck);
  std::vector<Cards> tableDecks(12);
  std::cout << "Size: " << tableDecks.size() << std::endl;
  std::cout << "Size: " << tableDecks[0].size() << std::endl;
  //std::cout << "To confirm this card is there, these should be blank: " << tableDecks[0][0].getColor() << " and number: " << tableDecks[0][0].getNumber() << "." << std::endl;


  std::cout << "Size of deck after dealing: " << deck.size() << std::endl;
  displayAllHands(allHands);

  firstMove(allHands, deck, tableDecks);

  return 0;
}

void menu()
{
  std::cout << "Welcome!" << std::endl;
}

int getPlayerCount()
{
  auto playerCount = getSafeInput(4, "Enter the number of players. (1-4)");

  return playerCount;
}

std::vector<Cards> deal(int playerCount, Cards& deck)
{
  const int HAND_SIZE = 7;
  std::vector<Cards> allHands;

  for (size_t i = 0; i < playerCount; ++i)
  {
    Cards singleHand;
    for (size_t j = 0; j < HAND_SIZE; ++j)
    {
      auto singleCard = deck.back();
      singleHand.push_back(singleCard);
      deck.pop_back();
    }
    allHands.push_back(singleHand);
  }

  return allHands;
}

void shuffleDeck(Cards& deck)
{
  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::default_random_engine e(seed);
  std::shuffle(deck.begin(), deck.end(), e);
}

void displayAllHands(std::vector<Cards>& allHands)
{
  for (size_t i = 0; i < allHands.size(); ++i)
  {
    std::cout << "Hand #" << i + 1 << std::endl;
    for (auto it = allHands[i].begin(); it != allHands[i].end(); ++it)
    {
      std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
    }
  }
}

bool elevensInHands(Cards& deck)
{
  int count{0};

  for (auto it = deck.begin(); it != deck.end(); ++it)
  {
    if (it->getNumber() == 11)
    {
      ++count;
    }
  }

  if (count == 4)
  {
    return false;
  }

  return true;
}

bool redElevenInHands(std::vector<Cards>& allHands)
{
  for (size_t i = 0; i < allHands.size(); ++i)
  {
    for (auto it = allHands[i].begin(); it != allHands[i].end(); ++it)
    {
      if ((it->getNumber() == 11) && (it->getColor() == 'R'))

      return true;
    }
  }
  return false;
}

void firstMove(std::vector<Cards>& allHands, Cards& deck, std::vector<Cards>& tableDecks)
{
  if (elevensInHands(deck))
  {
    std::cout << "There is an eleven in the hands." << std::endl;
    if (redElevenInHands(allHands))
    {
      std::cout << "There is a red eleven in the hands." << std::endl;
      auto player = getPlayer(allHands, 11, 'R');
      auto elevenHand = allHands[player - 1];
      std::cout << "This is player " << player << ". Press Enter to play this card." << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      auto position = positionOfEleven(elevenHand);
      playRedEleven(position, elevenHand, tableDecks);
      std::cout << "To confirm this card is there, these should be R and 11: " << tableDecks[1][0].getColor() << " and number: " << tableDecks[1][0].getNumber() << "." << std::endl;
      std::cout << "This is player " << player << "'s new hand: " << std::endl;

      for (auto it = elevenHand.begin(); it != elevenHand.end(); ++it)
      {
        std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
      }

      std::cout << "Size of deck before drawing: " << deck.size() << std::endl;/*
      std::cout << "Drawing card." << std::endl;
      //draw(allHands);

      std::cout << "This is player " << player << "'s new hand: " << std::endl;

      for (auto it = elevenHand.begin(); it != elevenHand.end(); ++it)
      {
        std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
      }
      std::cout << "Size of deck after drawing: " << deck.size() << std::endl;*/
    }
  }
}

int getPlayer(std::vector<Cards>& allHands, int number, char color)
{
  int player{0};

  for (size_t i = 0; i < allHands.size(); ++i)
  {
    for (auto it = allHands[i].begin(); it != allHands[i].end(); ++it)
    {
      if ((it->getNumber() == number) && (it->getColor() == color))
      {
        player = i + 1;
      }
    }
  }

  return player;
}

Cards::iterator positionOfEleven(Cards& hand)
{
  auto position = std::find_if(hand.begin(), hand.end(), [](Card& card){ return card.getNumber() == 11; });

  return position;
}

Cards::iterator positionOfCard(std::vector<Cards>& allHands, int player, int number, char color)
{
  auto position = std::find_if(allHands[player - 1].begin(), allHands[player - 1].end(), [&](Card& card){ return (card.getNumber() == number && card.getColor() == color); });

  return position;
}

void playRedEleven(Cards::iterator position, Cards& hand, std::vector<Cards>& tableDecks)
{
  auto index = std::distance(hand.begin(), position);
  auto redEleven = hand[index];
  hand.erase(position);
  tableDecks[1].push_back(redEleven);
}

void playCard(Cards::iterator position, std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player)
{
  auto index = std::distance(allHands[0].begin(), position);
  auto cardToBePlayed = allHands[0][index];
  allHands[0].erase(position);

  if (cardIsRed(cardToBePlayed))
  {
    if (cardIsLow(cardToBePlayed))
    {
      tableDecks[0].push_back(cardToBePlayed);
    }
    else if (cardIsHigh(cardToBePlayed))
    {
      tableDecks[2].push_back(cardToBePlayed);
    }
    else
    {
      tableDecks[1].push_back(cardToBePlayed);
    }
  }
  else if (cardIsGreen(cardToBePlayed))
  {
    if (cardIsLow(cardToBePlayed))
    {
      tableDecks[3].push_back(cardToBePlayed);
    }
    else if (cardIsHigh(cardToBePlayed))
    {
      tableDecks[5].push_back(cardToBePlayed);
    }
    else
    {
      tableDecks[4].push_back(cardToBePlayed);
    }
  }
  else if (cardIsBlue(cardToBePlayed))
  {
    if (cardIsLow(cardToBePlayed))
    {
      tableDecks[6].push_back(cardToBePlayed);
    }
    else if (cardIsHigh(cardToBePlayed))
    {
      tableDecks[8].push_back(cardToBePlayed);
    }
    else
    {
      tableDecks[7].push_back(cardToBePlayed);
    }
  }
  else // card is yellow
  {
    if (cardIsLow(cardToBePlayed))
    {
      tableDecks[9].push_back(cardToBePlayed);
    }
    else if (cardIsHigh(cardToBePlayed))
    {
      tableDecks[11].push_back(cardToBePlayed);
    }
    else
    {
      tableDecks[10].push_back(cardToBePlayed);
    }
  }
}

bool cardIsRed(Card& card)
{
  if (card.getColor() == 'R')
  {
    return true;
  }

  return false;
}

bool cardIsGreen(Card& card)
{
  if (card.getColor() == 'G')
  {
    return true;
  }

  return false;
}

bool cardIsBlue(Card& card)
{
  if (card.getColor() == 'B')
  {
    return true;
  }

  return false;
}

bool cardIsYellow(Card& card)
{
  if (card.getColor() == 'Y')
  {
    return true;
  }

  return false;
}

bool cardIsLow(Card& card)
{
  if (card.getNumber() < 11)
  {
    return true;
  }

  return false;
}

bool cardIsEleven(Card& card)
{
  if (card.getNumber() == 11)
  {
    return true;
  }

  return false;
}

bool cardIsHigh(Card& card)
{
  if (card.getNumber() > 11)
  {
    return true;
  }

  return false;
}
