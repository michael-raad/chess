#include "computer5.h"
#include <iostream>
#include <random>
#include <vector>

Computer5::Computer5(Board* board, Colour colour) :
  PlayerController{ board, colour } { }

TurnResult Computer5::doTurn() {
  std::string command;
  std::vector<Move> myLegalMoves = getBoard()->getLegalMoves(getColour()); // This player's legal moves
  std::vector<Move> opponentMoves; // All moves an opponent is threatening (attacked squares)
  bool check = false; // True if we are in check

  // Determine what squares the opponent(s) is (are) attacking
  if (getColour() == Colour::White) {
    opponentMoves = getBoard()->getAttackMoves(Colour::Black); // Call this on more colours if we make more colours
  }
  else {
    opponentMoves = getBoard()->getAttackMoves(Colour::White); // Same here
  }

  // Check if we are in check
  for (auto& m : opponentMoves) { // For each move the opponent is threatening
    if (m.value == 69) {
      check = true;
      break;
    }
  }

  // Deal with check, checkmate, and stalemate. We can extend the below for more colours
  if (check && myLegalMoves.empty()) {
    std::cout << "Checkmate!" << std::endl;
    return TurnResult::OUTOFGAME;
  }
  else if (myLegalMoves.empty()) {
    std::cout << (getColour() ? "Black " : "White ") << "Has No Legal Moves!" << std::endl;
    return TurnResult::NOLEGALMOVE;
  }
  else if (check) {
    std::cout << (getColour() ? "Black " : "White ") << "is in Check!" << std::endl;
  }

  std::cout << (getColour() ? "Black's turn!" : "White's turn!") << std::endl;

  // Neither stalemate nor checkmate, make a move:
  // while (!std::cin.fail()) {
  //   std::cin >> command;

  //   if (command == "resign") {
  //     return TurnResult::OUTOFGAME;
  //   }
  //   else if (command == "move") {
      int randI;
      std::vector<std::pair<Move, int>> moves;
      std::vector<Move> goodMoves;

      if (depth != 4) {
        int numPieces = 0;
        for (int i = 0; i < getBoard()->getNumRank(); ++i) {
          for (int j = 0; j < getBoard()->getNumFile(); ++j) {
            if (getBoard()->getPieceAt(Square{ j, i })) {
              ++numPieces;
            }
          }
        }
        if (numPieces <= 12) { depth = 3; }
        if (numPieces <= 5) { depth = 4; }
      }

      int curBest = INT32_MIN;
      for (auto& m : myLegalMoves) {
        int moveValue = getBoard()->evaluateMove(m, getColour(), myLegalMoves.size() <= 8 ? depth + 1 : depth);
        curBest = std::max(curBest, moveValue);
        moves.emplace_back(m, moveValue);
      }

      for (auto& p : moves) {
        if (p.second == curBest) {
          goodMoves.emplace_back(p.first);
        }
      }
      randI = getRandomIndex(goodMoves.size());
      getBoard()->makeMove(goodMoves[randI]);
      return TurnResult::SUCCESS;
  //   }
  //   else if (command == "help") {
  //     std::cout << "Commands:" << std::endl;
  //     std::cout << "move   -- To make computer move!" << std::endl;
  //     std::cout << "resign -- To make computer move!" << std::endl;
  //   }
  //   else std::cerr << "Error: Invalid Command. Enter \"help\" for list of commands." << std::endl;
  // }
  return TurnResult::ERROR; // Only occurs when EOF
}
