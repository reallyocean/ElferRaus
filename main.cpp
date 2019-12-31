#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iterator>
#include <limits>
#include <cstdlib>

#include "includeFiles.hpp"

using Cards = std::vector<Card>;

void menu();
int getPlayerCount();
std::vector<Cards> deal(int, Cards&);
std::vector<Card> createDeck();
void shuffleDeck(Cards&);
void displayAllHands(std::vector<Cards>&);
bool elevensInHands(Cards&);
bool redElevenInHands(std::vector<Cards>&);
bool elevenInHand(std::vector<Cards>&);
void firstMove(std::vector<Cards>&, Cards&, std::vector<Cards>&, int, int&);
void secondMove(std::vector<Cards>&, Cards&, std::vector<Cards>&, int, int&, int&, bool&);
void thirdMove(std::vector<Cards>&, std::vector<Cards>&, int, int, int&);
int getPlayer(std::vector<Cards>&, int, char);
int getPlayerByCardNumber(std::vector<Cards>&, int);
Cards::iterator getPositionOfCardByNumber(std::vector<Cards>&, int, int);
Cards::iterator getPositionOfCard(std::vector<Cards>&, int, int, char);
Cards::iterator getPositionOfPlayableCard(std::vector<Cards>&, std::vector<Cards>&, int);
Cards::iterator lowCardPosition(std::vector<Cards>&, std::vector<Cards>&, int, int, std::vector<int>&);
Cards::iterator highCardPosition(std::vector<Cards>&, std::vector<Cards>&, int, int, std::vector<int>&);
void playRedEleven(Cards::iterator, std::vector<Cards>&, std::vector<Cards>&, int);
void playCard(Cards::iterator, std::vector<Cards>&, std::vector<Cards>&, int);
bool cardIsRed(Card&);
bool cardIsGreen(Card&);
bool cardIsBlue(Card&);
bool cardIsYellow(Card&);
bool cardIsLow(Card&);
bool cardIsEleven(Card&);
bool cardIsHigh(Card&);
void draw(int, std::vector<Cards>&, Cards&);
void shuffleVector(std::vector<int>&);
bool hasEleven(std::vector<Cards>&, int);
char tableIndexToChar(int, std::vector<int>&);
bool lowCardMatches(std::vector<Cards>&, std::vector<Cards>&, int, int, std::vector<int>&);
bool highCardMatches(std::vector<Cards>&, std::vector<Cards>&, int, int, std::vector<int>&);
bool canPlay(std::vector<Cards>&, std::vector<Cards>&, int);
void displayBoard(std::vector<Cards>&);
int colorToTableDeckElevenIndex(char);

int main()
{
  int player{0};
  int winner{0};
  bool keepPlaying = true;

  auto deck = createDeck();
  shuffleDeck(deck);

  menu();
  auto playerCount = getPlayerCount();
  auto allHands = deal(playerCount, deck);
  std::vector<Cards> tableDecks(12);
  displayBoard(tableDecks);
  displayAllHands(allHands);

  firstMove(allHands, deck, tableDecks, playerCount, player);
  secondMove(allHands, deck, tableDecks, playerCount, player, winner, keepPlaying);
  std::cout << "Player " << winner << " has played their last card." << std::endl;
  std::cout << "Player " << winner << " wins!" << std::endl;

  if (keepPlaying)
  {
    thirdMove(allHands, tableDecks, playerCount, player, winner);

    std::cout << "Player " << winner << " has played their last card." << std::endl;
    std::cout << "Player " << winner << " wins!" << std::endl;
  }

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

std::vector<Card> createDeck()
{
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  std::vector<char> colors = {'R', 'G', 'B', 'Y'};
  std::vector<Card> deck;

  for (size_t i = 0; i < colors.size(); ++i)
  {
    for (size_t j = 0; j < numbers.size(); ++j)
    {
      Card c(numbers[j], colors[i]);
      deck.push_back(c);
    }
  }

  return deck;
}

void shuffleDeck(Cards& deck)
{
  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::default_random_engine e(seed);
  std::shuffle(deck.begin(), deck.end(), e);
}

void displayBoard(std::vector<Cards>& tableDecks)
{
  for (size_t i = 0; i < tableDecks.size(); ++i)
  {
    std::cout << "Table deck size #" << i  << ": " << tableDecks[i].size() << std::endl;
    if (tableDecks[i].size() != 0)
    {
      for (auto it = tableDecks[i].begin(); it != tableDecks[i].end(); ++it)
      {
        std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
      }
    }
  }
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

bool hasEleven(std::vector<Cards>& allHands, int player)
{
  for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
  {
    if (it->getNumber() == 11)
    {
      return true;
    }
  }

  return false;
}

// If eleven in hands, search for a red eleven.
// If red eleven is found, play it and leave first move function.
// else, Play eleven from random player.
// else no eleven is found, draw until you get one and play it.
void firstMove(std::vector<Cards>& allHands, Cards& deck, std::vector<Cards>& tableDecks, int playerCount, int& player)
{
  if (elevensInHands(deck))
  {
    std::cout << "There is an eleven in the hands." << std::endl;
    if (redElevenInHands(allHands))
    {
      std::cout << "There is a red eleven in the hands." << std::endl;
      player = getPlayer(allHands, 11, 'R');
      auto elevenHand = allHands[player - 1];
      std::cout << "This is player " << player << ". Press Enter to play this card." << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      auto position = getPositionOfCard(allHands, player, 11, 'R');
      playRedEleven(position, allHands, tableDecks, player);
    }
    else
    {
      std::cout << "Eleven in the hand but it's not red." << std::endl;
      player = getPlayerByCardNumber(allHands, 11);
      auto position = getPositionOfCardByNumber(allHands, player, 11);
      playCard(position, allHands, tableDecks, player);
    }
  }
  else
  {
    std::cout << "Size of deck before drawing: " << deck.size() << std::endl;
    std::cout << "Eleven is not in hands. Drawing." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();
    player = 1;
    int count{1};

    while (!elevensInHands(deck))
    {
      std::cout << "Running through draw #" << count << "." << std::endl;
      draw(player, allHands, deck);
      ++player;
      ++count;
      // first run through, player and count increment to 2.
      if (player == playerCount + 1)
      {
        player = 1;
      }
    }
    std::cout << "Eleven found." << std::endl;
  }

  std::cout << "Size of deck after drawing: " << deck.size() << std::endl;
  for (size_t player = 1; player <= allHands.size(); ++player)
  {
    std::cout << "This is player " << player << "'s new hand: " << std::endl;
    for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
    {
      std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
    }
  }
  displayBoard(tableDecks);
  ++player;
}

void thirdMove(std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int playerCount, int player, int& winner)
{
  std::cout << "Starting third move with player " << player << "." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.ignore();
  while (1)
  {
    std::cout << "Board:" << std::endl;
    displayBoard(tableDecks);
    std::cout << "Player " << player << " is going." << std::endl;
    std::cout << "Player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
    for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
    {
      std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();
    if (canPlay(allHands, tableDecks, player))
    {
      std::cout << "Player " << player << " can currently play." << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      if (hasEleven(allHands, player))
      {
        std::cout << "Player " << player << " already has an eleven. Playing it." << std::endl;
        std::cout << "Player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
        auto position = getPositionOfCardByNumber(allHands, player, 11);
        playCard(position, allHands, tableDecks, player);
        std::cout << "Player " << player << " has played an eleven." << std::endl;
        std::cout << "Player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cout << "New board:" << std::endl;
        displayBoard(tableDecks);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
      }
      else
      {
        std::cout << "Player " << player << " doesn't already have an eleven but can play. Playing card." << std::endl;
        std::cout << "Player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
        auto position = getPositionOfPlayableCard(allHands, tableDecks, player);
        playCard(position, allHands, tableDecks, player);
        std::cout << "Player " << player << " has played a card." << std::endl;
        std::cout << "Player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cout << "New board:" << std::endl;
        displayBoard(tableDecks);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
      }
    }
    else
    {
      if (player == 4)
      {
        std::cout << "Player " << player << " can't play after their final draw so it's now player 1's turn." << std::endl;
      }
      else
      {
        std::cout << "Player " << player << " can't play after their final draw so it's now player " << player + 1 << "'s turn." << std::endl;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
    }
    std::cout << "Player " << player << " is being incremented." << std::endl;
    std::cout << "But first, player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
    for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
    {
      std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();
    winner = player;

    if (allHands[player - 1].empty())
    {
      return;
    }

    ++player;
    if (player == playerCount + 1)
    {
      std::cout << "Player " << player << " is being reset to 1." << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      player = 1;
    }
    std::cout << "End of while loop. Resetting." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();
  }
}

Cards::iterator lowCardPosition(std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player, int i, std::vector<int>& randomIndex)
{
  int numberToBeFoundInDeck{0};
  auto color = tableIndexToChar(i, randomIndex);

  if (tableDecks[randomIndex[i]].empty())
  {
    numberToBeFoundInDeck = 10;
  }
  else
  {
    numberToBeFoundInDeck = tableDecks[randomIndex[i]].back().getNumber() - 1;
  }

  return std::find_if(allHands[player - 1].begin(), allHands[player - 1].end(), [&](Card& card){ return (card.getNumber() == numberToBeFoundInDeck && card.getColor() == color); });
}

Cards::iterator highCardPosition(std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player, int i, std::vector<int>& randomIndex)
{
  int numberToBeFoundInDeck{0};
  auto color = tableIndexToChar(i, randomIndex);

  if (tableDecks[randomIndex[i]].empty())
  {
    numberToBeFoundInDeck = 12;
  }
  else
  {
    // if this is called in the high green function, if this function is called then we already know there is a green 12 or higher in the deck.
    // figure out way to identify 10 or 12 of that color.
    numberToBeFoundInDeck = tableDecks[randomIndex[i]].back().getNumber() + 1;
  }

  return std::find_if(allHands[player - 1].begin(), allHands[player - 1].end(), [&](Card& card){ return (card.getNumber() == numberToBeFoundInDeck && card.getColor() == color); });
}

Cards::iterator getPositionOfPlayableCard(std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player)
{
  // player = 4, and decks.
  Cards::iterator position;
  // Look through all table decks and compare the top cards with the players' hands' cards.
  // if they match, return position iterator.
  std::vector<int> randomIndex = {0, 2, 3, 5, 6, 8, 9, 11};
  shuffleVector(randomIndex);
  std::cout << "declared variables and shuffled vector." << std::endl;
  std::cout << "Shuffled vector: " << std::endl;
  for (auto it = randomIndex.begin(); it != randomIndex.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  std::cout << "Testing first if playable card is an eleven." << std::endl;

  if (hasEleven(allHands, player))
  {
    std::cout << "Player " << player << " already has an eleven. Playing it." << std::endl;
    std::cout << "Player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
    for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
    {
      std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();
    position = getPositionOfCardByNumber(allHands, player, 11);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();
  }
  else
  {
    std::cout << "Playable card is not an eleven." << std::endl;
    for (int i = 0; i < randomIndex.size(); ++i)
    {
      if (randomIndex[i] == 0) // low red deck
      {
        if (lowCardMatches(allHands, tableDecks, player, i, randomIndex))
        {
          position = lowCardPosition(allHands, tableDecks, player, i, randomIndex);
        }
      }
      else if (randomIndex[i] == 2) // high red deck
      {
        if (highCardMatches(allHands, tableDecks, player, i, randomIndex))
        {
          position = highCardPosition(allHands, tableDecks, player, i, randomIndex);
        }
      }
      else if (randomIndex[i] == 3) // low green deck
      {
        if (lowCardMatches(allHands, tableDecks, player, i, randomIndex))
        {
          position = lowCardPosition(allHands, tableDecks, player, i, randomIndex);
        }
      }
      else if (randomIndex[i] == 5) // high green deck
      {
        if (highCardMatches(allHands, tableDecks, player, i, randomIndex))
        {
          position = highCardPosition(allHands, tableDecks, player, i, randomIndex);
        }
      }
      else if (randomIndex[i] == 6) // low blue deck
      {
        if (lowCardMatches(allHands, tableDecks, player, i, randomIndex))
        {
          position = lowCardPosition(allHands, tableDecks, player, i, randomIndex);
        }
      }
      else if (randomIndex[i] == 8) // high blue deck
      {
        if (highCardMatches(allHands, tableDecks, player, i, randomIndex))
        {
          position = highCardPosition(allHands, tableDecks, player, i, randomIndex);
        }
      }
      else if (randomIndex[i] == 9) // low yellow deck
      {
        if (lowCardMatches(allHands, tableDecks, player, i, randomIndex))
        {
          position = lowCardPosition(allHands, tableDecks, player, i, randomIndex);
        }
      }
      else if (randomIndex[i] == 11) // high yellow deck
      {
        if (highCardMatches(allHands, tableDecks, player, i, randomIndex))
        {
          position = highCardPosition(allHands, tableDecks, player, i, randomIndex);
        }
      }
    }
  }

  return position;
}

void secondMove(std::vector<Cards>& allHands, Cards& deck, std::vector<Cards>& tableDecks, int playerCount, int& player, int& winner, bool& keepPlaying)
{
  std::cout << "Starting with player " << player << "." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.ignore();
  while (deck.size() != 0)
  {
    std::cout << "Board:" << std::endl;
    displayBoard(tableDecks);
    std::cout << "Player " << player << " is going." << std::endl;
    std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
    for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
    {
      std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();
    if (canPlay(allHands, tableDecks, player))
    {
      std::cout << "Player " << player << " can currently play." << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      if (hasEleven(allHands, player))
      {
        std::cout << "Player " << player << " already has an eleven. Playing it." << std::endl;
        std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
        auto position = getPositionOfCardByNumber(allHands, player, 11);
        playCard(position, allHands, tableDecks, player);
        std::cout << "Player " << player << " has played an eleven." << std::endl;
        std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cout << "New board:" << std::endl;
        displayBoard(tableDecks);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
      }
      else
      {
        std::cout << "Player " << player << " doesn't already have an eleven but can play. Playing card." << std::endl;
        std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
        auto position = getPositionOfPlayableCard(allHands, tableDecks, player);
        playCard(position, allHands, tableDecks, player);
        std::cout << "Player " << player << " has played a card." << std::endl;
        std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cout << "New board:" << std::endl;
        displayBoard(tableDecks);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
      }
    }
    else
    {
      std::cout << "Player " << player << " can't play so they must draw their first card." << std::endl;
      std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
      for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
      {
        std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      draw(player, allHands, deck);
      std::cout << "Player " << player << " has drawn their first card." << std::endl;
      std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
      for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
      {
        std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      if (canPlay(allHands, tableDecks, player))
      {
        std::cout << "Player " << player << " can now play. Playing card." << std::endl;
        std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
        auto position = getPositionOfPlayableCard(allHands, tableDecks, player);
        playCard(position, allHands, tableDecks, player);
        std::cout << "Player " << player << " played a card." << std::endl;
        std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cout << "New board:" << std::endl;
        displayBoard(tableDecks);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
      }
      else
      {
        std::cout << "Player " << player << " can't play so they must draw their second card." << std::endl;
        std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
        draw(player, allHands, deck);
        std::cout << "Player " << player << " has drawn their second card." << std::endl;
        std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
        for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
        {
          std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.ignore();
        if (canPlay(allHands, tableDecks, player))
        {
          std::cout << "Player " << player << " can now play. Playing card." << std::endl;
          std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
          }
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cin.ignore();
          auto position = getPositionOfPlayableCard(allHands, tableDecks, player); // player is 2, allHands is that, tableDecks has one green 11.
          playCard(position, allHands, tableDecks, player);
          std::cout << "Player " << player << " played a card." << std::endl;
          std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
          }
          std::cout << "New board:" << std::endl;
          displayBoard(tableDecks);
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cin.ignore();
        }
        else
        {
          std::cout << "Player " << player << " can't play so they must draw a final time." << std::endl;
          std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
          }
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cin.ignore();
          draw(player, allHands, deck);
          std::cout << "Player " << player << " has drawn their final card." << std::endl;
          std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
          }
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cin.ignore();
          if (canPlay(allHands, tableDecks, player))
          {
            std::cout << "Player " << player << " can now play. Playing card." << std::endl;
            std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
            for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
            {
              std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.ignore();
            auto position = getPositionOfPlayableCard(allHands, tableDecks, player);
            playCard(position, allHands, tableDecks, player);
            std::cout << "Player " << player << " played a card." << std::endl;
            std::cout << "Current deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
            for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
            {
              std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
            }
            std::cout << "New board:" << std::endl;
            displayBoard(tableDecks);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.ignore();
          }
          if (player == 4)
          {
            std::cout << "Player " << player << " can't play after their final draw so it's now player 1's turn." << std::endl;
          }
          else
          {
            std::cout << "Player " << player << " can't play after their final draw so it's now player " << player + 1 << "'s turn." << std::endl;
          }
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cin.ignore();
        }
      }
    }
    std::cout << "Player " << player << " is being incremented." << std::endl;
    std::cout << "But first, the deck size: " << deck.size() << ", player " << player << "'s hand size: " << allHands[player - 1].size() << ", player " << player << "'s hand: " << std::endl;
    for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
    {
      std::cout << "Card color: " << it->getColor() << " and number: " << it->getNumber() << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();

    winner = player;

    if (allHands[player - 1].empty())
    {
      keepPlaying = false;
      return;
    }

    ++player;
    if (player == playerCount + 1)
    {
      std::cout << "Player " << player << " is being reset to 1." << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.ignore();
      player = 1;
    }
    std::cout << "End of while loop. Resetting." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.ignore();
  }
  std::cout << "Deck is empty." << std::endl;
}

bool lowCardMatches(std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player, int i, std::vector<int>& indexVector)
{
  if (!tableDecks[indexVector[i]].empty())
  {
    // if the deck being looked at has cards on it
    auto topTableCardNumber = tableDecks[indexVector[i]].back().getNumber();
    auto color = tableIndexToChar(i, indexVector);

    for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
    {
      // if the number of the card in hand is equal to the top of the deck - 1
      if ((it->getNumber() == topTableCardNumber - 1) && (it->getColor() == color))
      {
        return true;
      }
    }
  }
  else
  {
    // if the deck being looked at is empty, get color of the deck
    auto color = tableIndexToChar(i, indexVector);
    auto index = colorToTableDeckElevenIndex(color);
    // number isn't needed because this is the highCardMatches function so card number must be == 12.
    // if it's empty, check that there is an eleven for that color first before adding it.
    if (!tableDecks[index].empty())
    {
      for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
      {
        // if the number of the card in hand is equal to the top of the deck - 1
        if ((it->getNumber() == 10) && (it->getColor() == color))
        {
          return true;
        }
      }
    }
  }

  return false;
}

int colorToTableDeckElevenIndex(char color)
{
  int index{0};

  if (color == 'R')
  {
    index = 1;
  }
  else if (color == 'G')
  {
    index = 4;
  }
  else if (color == 'B')
  {
    index = 7;
  }
  else
  {
    index = 10;
  }

  return index;
}

/*

Goes through all decks to check for a card which will fit.
Go through low red, check hand for a match.
Go through high red, check hand for a match.
etc.

If table deck is empty, check hand for appropriate card to lie down.
If table deck is not empty, auto topTableCardNumber and try to match that card as before.

*/
bool highCardMatches(std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player, int i, std::vector<int>& indexVector)
{
  if (!tableDecks[indexVector[i]].empty())
  {
    // if the deck being looked at has cards on it
    auto topTableCardNumber = tableDecks[indexVector[i]].back().getNumber();
    auto color = tableIndexToChar(i, indexVector);

    for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
    {
      // if the number of the card in hand is equal to the top of the deck - 1
      if ((it->getNumber() == topTableCardNumber + 1) && (it->getColor() == color))
      {
        return true;
      }
    }
  }
  else
  {
    // if the deck being looked at is empty, get color of the deck
    auto color = tableIndexToChar(i, indexVector);
    auto index = colorToTableDeckElevenIndex(color);
    // number isn't needed because this is the highCardMatches function so card number must be == 12.
    // if it's empty, check that there is an eleven for that color first before adding it.
    if (!tableDecks[index].empty())
    {
      // number isn't needed because this is the highCardMatches function so card number must be == 12.
      for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
      {
        // if the number of the card in hand is equal to the top of the deck - 1
        if ((it->getNumber() == 12) && (it->getColor() == color))
        {
          return true;
        }
      }
    }
  }

  return false;
}

char tableIndexToChar(int i, std::vector<int>& randomIndex)
{
  char color = ' ';

  if ((randomIndex[i] == 0) || (randomIndex[i] == 2))
  {
    color = 'R';
  }
  else if ((randomIndex[i] == 3) || (randomIndex[i] == 5))
  {
    color = 'G';
  }
  else if ((randomIndex[i] == 6) || (randomIndex[i] == 8))
  {
    color = 'B';
  }
  else
  {
    color = 'Y';
  }

  return color;
}

bool canPlay(std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player)
{
  // run through, player = 1.

  for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
  {
    if (it->getNumber() == 11)
    {
      return true;
    }
  }

  std::vector<int> randomIndex = {0, 2, 3, 5, 6, 8, 9, 11};
  for (int i = 0; i < randomIndex.size(); ++i)
  {
    if ((randomIndex[i] % 3 == 0) && (tableDecks[randomIndex[i]].size() < 11)) // if there are free spots on the low decks
    {
      if (tableDecks[randomIndex[i]].size() != 0)
      {
        // if the number in hand is equal to the last number of the table deck + 1, return true;
        if (i == 0) // R
        {
          // if the color of the table deck is red
          if (lowCardMatches(allHands, tableDecks, player, i, randomIndex))
          {
            return true;
          }
        }
        else if (i == 2) // G
        {
          // if the color of the table deck is green
          if (lowCardMatches(allHands, tableDecks, player, i, randomIndex))
          {
            return true;
          }
        }
        else if (i == 4) // B
        {
          // if the color of the table deck is blue
          if (lowCardMatches(allHands, tableDecks, player, i, randomIndex))
          {
            return true;
          }
        }
        else // Y
        {
          // if the color of the table deck is yellow
          if (lowCardMatches(allHands, tableDecks, player, i, randomIndex))
          {
            return true;
          }
        }
      }
      else
      {
        auto color = tableIndexToChar(i, randomIndex);
        // at this point, the bottom red deck is empty.
        // if the deck we're checking is a red deck and the red eleven deck is full.
        if ((color == 'R') && (tableDecks[1].size() != 0)) // red
        {
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            // if the number of the card in hand is equal to the top of the deck - 1
            if ((it->getNumber() == 10) && (it->getColor() == color))
            {
              return true;
            }
          }
        }
        else if ((color == 'G') && (tableDecks[4].size() != 0)) // green
        {
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            // if the number of the card in hand is equal to the top of the deck - 1
            if ((it->getNumber() == 10) && (it->getColor() == color))
            {
              return true;
            }
          }
        }
        else if ((color == 'B') && (tableDecks[7].size() != 0)) // blue
        {
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            // if the number of the card in hand is equal to the top of the deck - 1
            if ((it->getNumber() == 10) && (it->getColor() == color))
            {
              return true;
            }
          }
        }
        else if ((color == 'Y') && (tableDecks[10].size() != 0))// yellow
        {
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            // if the number of the card in hand is equal to the top of the deck - 1
            if ((it->getNumber() == 10) && (it->getColor() == color))
            {
              return true;
            }
          }
        }
      }
    }
    else if (tableDecks[randomIndex[i]].size() < 10) // if there are free spots on the high decks
    {
      // if the number in hand is equal to the last number of the table deck - 1, return true;
      if (tableDecks[randomIndex[i]].size() != 0)
      {
        // if the number in hand is equal to the last number of the table deck + 1, return true;
        if (i == 1) // R
        {
          // if the color of the table deck is red
          if (highCardMatches(allHands, tableDecks, player, i, randomIndex))
          {
            return true;
          }
        }
        else if (i == 3) // G
        {
          // if the color of the table deck is green
          if (highCardMatches(allHands, tableDecks, player, i, randomIndex))
          {
            return true;
          }
        }
        else if (i == 5) // B
        {
          // if the color of the table deck is blue
          if (highCardMatches(allHands, tableDecks, player, i, randomIndex))
          {
            return true;
          }
        }
        else // Y
        {
          // if the color of the table deck is yellow
          if (highCardMatches(allHands, tableDecks, player, i, randomIndex))
          {
            return true;
          }
        }
      }
      else
      {
        auto color = tableIndexToChar(i, randomIndex);
        // at this point, the top red deck is empty.
        // if the deck we're checking is a red deck and the red eleven deck is full.
        if ((color == 'R') && (tableDecks[1].size() != 0)) // red
        {
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            // if the number of the card in hand is equal to the top of the deck - 1
            if ((it->getNumber() == 12) && (it->getColor() == color))
            {
              return true;
            }
          }
        }
        else if ((color == 'G') && (tableDecks[4].size() != 0)) // green
        {
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            // if the number of the card in hand is equal to the top of the deck - 1
            if ((it->getNumber() == 12) && (it->getColor() == color))
            {
              return true;
            }
          }
        }
        else if ((color == 'B') && (tableDecks[7].size() != 0)) // blue
        {
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            // if the number of the card in hand is equal to the top of the deck - 1
            if ((it->getNumber() == 12) && (it->getColor() == color))
            {
              return true;
            }
          }
        }
        else if ((color == 'Y') && (tableDecks[10].size() != 0))// yellow
        {
          for (auto it = allHands[player - 1].begin(); it != allHands[player - 1].end(); ++it)
          {
            // if the number of the card in hand is equal to the top of the deck - 1
            if ((it->getNumber() == 12) && (it->getColor() == color))
            {
              return true;
            }
          }
        }
      }
    }
  }

  return false;
}

void shuffleVector(std::vector<int>& v)
{
  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::default_random_engine e(seed);
  std::shuffle(v.begin(), v.end(), e);
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

int getPlayerByCardNumber(std::vector<Cards>& allHands, int number)
{
  int player{0};

  for (size_t i = 0; i < allHands.size(); ++i)
  {
    for (auto it = allHands[i].begin(); it != allHands[i].end(); ++it)
    {
      if (it->getNumber() == number)
      {
        player = i + 1;
      }
    }
  }

  return player;
}

Cards::iterator getPositionOfCardByNumber(std::vector<Cards>& allHands, int player, int number)
{
  auto position = std::find_if(allHands[player - 1].begin(), allHands[player - 1].end(), [&](Card& card){ return card.getNumber() == number; });

  return position;
}

Cards::iterator getPositionOfCard(std::vector<Cards>& allHands, int player, int number, char color)
{
  auto position = std::find_if(allHands[player - 1].begin(), allHands[player - 1].end(), [&](Card& card){ return (card.getNumber() == number && card.getColor() == color); });

  return position;
}

void playRedEleven(Cards::iterator position, std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player)
{
  auto index = std::distance(allHands[player - 1].begin(), position);
  auto redEleven = allHands[player - 1][index];
  allHands[player - 1].erase(position);
  tableDecks[1].push_back(redEleven);
}

void playCard(Cards::iterator position, std::vector<Cards>& allHands, std::vector<Cards>& tableDecks, int player)
{
  auto index = std::distance(allHands[player - 1].begin(), position);
  auto cardToBePlayed = allHands[player - 1][index];
  allHands[player - 1].erase(position);

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

void draw(int player, std::vector<Cards>& allHands, Cards& deck)
{
  auto singleCard = deck.back();
  deck.pop_back();
  allHands[player - 1].push_back(singleCard);
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
