#include "playercontroller.h"
#include <iostream>

PlayerController::PlayerController(Board* board, Colour colour) :
    board{ board }, colour{ colour } { }

Board* PlayerController::getBoard() const { return board; }

int PlayerController::getRandomIndex(int index) const {
  static std::random_device rd; /// Obtain a random number from hardware
  static auto seed = rd();
  static std::mt19937 gen(seed); // Seed the random number generator
  std::cerr << seed << std::endl; // Uncomment to print the seed during each turn (for debugging purposes)
  // Define the distribution for integers from 0 to index - 1
  std::uniform_int_distribution<> distrib(0, index - 1);

  // Generate a random number within the specified range
  return distrib(gen);
}

Colour PlayerController::getColour() { return colour; }
