/*************************************************************************
 *
 * Project: Test driver for ImdbGraph
 *
 * File Name: ImdbGraphDriver.cpp
 * Course:    CPTR 242
 */
#include "ImdbGraphMenu.h"
#include <iostream>
#include <string>

int main() {
  std::string outputLabel = "Student Test";

  std::ofstream outStream;
  outStream.open("solutions.txt");

  ImdbGraphMenu(std::cin, outStream, outputLabel);
};
