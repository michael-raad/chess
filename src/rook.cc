#include "rook.h"

Rook::Rook(Board* board, Colour colour, Square location) :
  Piece{ board, colour, 10, location }, untouched{true} {  }

bool Rook::isUntouched() { return untouched; }

void Rook::touch() { untouched = false; }

void Rook::unTouch() { untouched = true; }

bool Rook::isLegalMove(Move move) {
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

std::vector<Move> Rook::getLegalMoves() {
  std::vector<Move> ret;

  // check all those possible moves
  for (auto& m : getAttackMoves()) {
    if (isLegalMove(m)) {
      ret.emplace_back(m);
    }
  }

  return ret;
}

std::vector<Move> Rook::getAttackMoves() {
  std::vector<Move> ret;
  // Generate all "vertical" and "horizontal" moves
  generatingMoves(ret, 0);
  generatingMoves(ret, 1);
  generatingMoves(ret, 2);
  generatingMoves(ret, 3);
  return ret;
}
