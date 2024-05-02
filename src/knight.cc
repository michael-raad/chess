#include "knight.h"

Knight::Knight(Board* board, Colour colour, Square location) :
  Piece{ board, colour, 6, location } {  }


bool Knight::isLegalMove(Move move) {
  Board* board = getBoard();
  Colour c = getColour();

  // Check if valid location
  if (!board->isValidSquare(move.to)) return false;

  Piece* p = board->getPieceAt(move.to); // The piece we are capturing

  // Capturing your own piece is not a legal move
  if (p && c == p->getColour()) return false;

  // Simulate the move
  return (board->simulateMove(move, c ? Colour::White : Colour::Black) != 69);
}


std::vector<Move> Knight::getLegalMoves() {
  std::vector<Move> ret;

  // Check all our attack moves. For each one that is legal, put them in ret
  for (auto& m : getAttackMoves()) {
    if (isLegalMove(m)) {
      ret.emplace_back(m);
    }
  }

  return ret;
}


std::vector<Move> Knight::getAttackMoves() {
  std::vector<Move> ret;

  Board* board = getBoard();
  Square location = getLocation();

  ret.emplace_back(Move{ location, Square{ location.file - 2, location.rank - 1}, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file + 2, location.rank - 1}, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file - 2, location.rank + 1}, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file + 2, location.rank + 1}, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file - 1, location.rank - 2}, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file + 1, location.rank - 2}, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file - 1, location.rank + 2}, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file + 1, location.rank + 2}, 0, "" });

  // For each attack move
  for (auto it = ret.begin(); it != ret.end(); ) {
    // If the move goes to an invalid square, erase it
    if (!board->isValidSquare(it->to)) {
      it = ret.erase(it);
    }
    else {
      // Otherwise, if it attacks a piece of different colour
      Piece* p = board->getPieceAt(it->to);
      if (p && p->getColour() != getColour()) {
        it->value = p->getValue(); // give the move the value of the attacked piece
      }
      ++it;
    }
  }

  return ret;
}
