/*
  Input-validation functions
*/

#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

#include <string>

size_t getMaxStreamSize();

void printInvalidInputWarning();

void displayInputPrompt(std::string promptText);

int getSafeInput(int maxVal, std::string promptText);

std::string getRangedNumberPrompt(int maxVal, std::string promptText);

#endif
