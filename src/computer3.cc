#include "computer3.h"

Computer3::Computer3(Board* board, Colour colour) :
  PlayerController{ board, colour } { }

// Level 3: Avoids being checked or captures
TurnResult Computer3::doTurn() {
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
      std::vector<Move> goodMoves;

      for (auto& m: myLegalMoves) {
        int moveValue = getBoard()->evaluateMove(m, getColour(), 1);
        if (moveValue >= 0) {
          goodMoves.emplace_back(m);
        }
      }

      if (!goodMoves.empty()) {
        randI = getRandomIndex(goodMoves.size());
        getBoard()->makeMove(goodMoves[randI]);
        return TurnResult::SUCCESS;  
      }

      randI = getRandomIndex(myLegalMoves.size());
      getBoard()->makeMove(myLegalMoves[randI]);
      return TurnResult::SUCCESS;     
  //   }
  //   else if (command == "help") {
  //     std::cout << "Commands:" << std::endl;
  //     std::cout << "move   -- To make computer move!" << std::endl;
  //     std::cout << "resign -- To make computer resign!" << std::endl;
  //   }
  //   else std::cerr << "Error: Invalid Command. Enter \"help\" for list of commands." << std::endl;
  // }
  return TurnResult::ERROR; // Only occurs when EOF
}

