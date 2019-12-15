/*
  Input-validation functions
*/

#include "inputValidation.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <string>

size_t getMaxStreamSize()
{
  return std::numeric_limits<std::streamsize>::max();
}

void printInvalidInputWarning()
{
  std::cout << std::endl;
  std::cout << "Invalid input." << std::endl;
  std::cin.clear();
  std::cin.ignore(getMaxStreamSize(), '\n');
}

void displayInputPrompt(std::string promptText)
{
  std::cout << promptText << std::endl;
  std::cout << "> ";
  std::cout.flush();
}

int getSafeInput(int maxVal, std::string promptText = "Enter a number")
{
  while (true)
  {
    auto inputVal = -1;
    auto inputText = std::string{""};

    displayInputPrompt(promptText);
    std::cin >> inputText;

    try
    {
        // try to convert the string to an integer
        inputVal = std::stoi(inputText);
    }
    catch(std::out_of_range const &) // error handling catch 1
    {
        inputVal = 0;
    }
    catch(std::invalid_argument const &) // error handling catch 2
    {
        inputVal = 0;
    }

    auto isInRange = (inputVal > 0 && inputVal <= maxVal);
    // if it's not in range given, print that Invalid input message.
    if (!isInRange)
    {
      printInvalidInputWarning();
      continue;
    }

    return inputVal;
  }
}

std::string getRangedNumberPrompt(int maxVal, std::string promptText = "Enter some input")
{
  auto rangeText = std::string{"(1-"} + std::to_string(maxVal) + std::string{")"};

  return promptText + std::string{" "} + rangeText;
}
