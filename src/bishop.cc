#include "bishop.h"

Bishop::Bishop(Board* board, Colour colour, Square location) :
  Piece{ board, colour, 7, location } {  }

bool Bishop::isLegalMove(Move move) {
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

std::vector<Move> Bishop::getLegalMoves() {
  std::vector<Move> ret;
  // Check our attack moves. For each one that is legal, put them in ret
  for (auto& m : getAttackMoves()) {
    if (isLegalMove(m)) {
      ret.emplace_back(m);
    }
  }

  return ret;
}

std::vector<Move> Bishop::getAttackMoves() {
  std::vector<Move> ret;
  // Generate all "diagonal" moves
  generatingMoves(ret, 4);
  generatingMoves(ret, 5);
  generatingMoves(ret, 6);
  generatingMoves(ret, 7);
  return ret;
}
