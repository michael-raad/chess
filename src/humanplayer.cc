#include <iostream>
#include <sstream>
#include "humanplayer.h"

HumanPlayer::HumanPlayer(Board* board, Colour colour) :
  PlayerController{ board, colour } { }


TurnResult HumanPlayer::doTurn() {
  std::string line, command, from, to, promote = "";
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
  // If not checkmate or stalemate, take input for move
  while (getline(std::cin, line)) {
    std::istringstream iss{ line };
    iss >> command;

    // If we resign
    if (command == "resign") {
      return TurnResult::OUTOFGAME; // We are out of game
    }

    // If we move
    else if (command == "move") {
      iss >> from >> to;
      if (iss.fail()) {
        std::cerr << "Error: Invalid read for move" << std::endl;
      }
      iss >> promote; // Remains empty if not provided
      Square squareFrom{ from[0] - 'a', from[1] - '1' };
      Square squareTo{ to[0] - 'a', to[1] - '1' };

      // auto movess = getBoard()->getPieceAt(squareFrom)->getLegalMoves();
      // ^ TODO REMOVE WHEN EVERYTHING DONE ^ (Above is for debugging purposes)
      // ONLY UNCOMMENT THE ABOVE FOR TESTING, OTHERWISE SEG FAULT WHEN PICKING WRONG PIECE

      // For each move in the legal move list
      for (auto m : myLegalMoves) {
        // If the desired move matches with the legal move 
        if ((squareFrom == m.from) && (squareTo == m.to) && (m.special == promote || m.special.length() != 1)) {
          getBoard()->makeMove(m); // make that move
          return TurnResult::SUCCESS;
        }
      }
      std::cerr << "Error: Illegal Move!" << std::endl; // otherwise we have made an illegal move
    }
    else if (command == "help") {
      std::cout << "Commands:" << std::endl;
      std::cout << "move [from] [to] -- To move a piece from [from] to [to]" << std::endl;
      std::cout << "resign           -- To resign from the game" << std::endl;
    }

    else if (!command.empty()) {
      std::cerr << "Error: Invalid Command. Enter \"help\" for list of commands." << std::endl;
    }
  }
  return TurnResult::ERROR; // Only occurs when EOF
}
