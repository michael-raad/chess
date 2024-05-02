#include "pawn.h"

Pawn::Pawn(Board* board, Colour colour, Square location) :
  Piece{ board, colour, 2, location },
  untouched{ true },
  enPassant{ false } {  }

bool Pawn::isUntouched() { return untouched; }

void Pawn::touch() { untouched = false; }

void Pawn::unTouch() { untouched = true; }

bool Pawn::isEnPassant() { return enPassant; }

void Pawn::setEnPassant(bool b) { enPassant = b; }

bool Pawn::isLegalMove(Move move) {
  Board* board = getBoard();
  Colour c = getColour();

  // Check if valid location
  if (!board->isValidSquare(move.to)) return false;

  Piece* p = board->getPieceAt(move.to); // The piece at the location we're moving to

  // Capturing your own piece is not a legal move. 
  // Performing a non-capture move to a square containing a piece is not a legal move.
  if ((p && c == p->getColour()) || (p && move.value == 0)) return false;

  // Simulate the move
  return (board->simulateMove(move, c ? Colour::White : Colour::Black) != 69);
}

std::vector<Move> Pawn::getLegalMoves() {
  Board* board = getBoard();
  Square location = getLocation();
  std::vector<Move> ret;

  for (auto& m : getAttackMoves()) {
    if (isLegalMove(m)) {
      Piece* p = board->getPieceAt(m.to);
      if (p && (p->getColour() != getColour())) {
        if ((getColour() == Black && m.to.rank == 0) || (getColour() == White && m.to.rank == 7)) {
          m.special = "N";
          ret.emplace_back(m);
          m.special = "B";
          ret.emplace_back(m);
          m.special = "R";
          ret.emplace_back(m);
          m.special = "Q";
          ret.emplace_back(m);
        }
        else {
          ret.emplace_back(m);
        }
      }

      // En passant check
      p = board->getPieceAt(Square{ m.to.file, location.rank });
      // If there is a piece next to us and that piece is a pawn of opposite color
      if (p && (p->getValue() == 2) && (p->getColour() != getColour())) {
        Pawn* pawn = dynamic_cast<Pawn*>(p);
        // And it has en passant enabled, we can perform en passant
        if (pawn->isEnPassant()) {
          m.value = p->getValue();
          m.special = "en passant";
          ret.emplace_back(m);
        }
      }
    }
  }

  // Moving forward one step
  Move m = getColour() ? Move{ location, Square{ location.file, location.rank - 1}, 0, "" } :
    Move{ location, Square{ location.file, location.rank + 1}, 0, "" }; // Different direction for black and white
  if (isLegalMove(m)) {
    // If we are on the first or last rank (promoting), add all promotion moves
    if ((m.to.rank == 0) || (m.to.rank == board->getNumRank() - 1)) {
      m.special = "N";
      ret.emplace_back(m);
      m.special = "B";
      ret.emplace_back(m);
      m.special = "R";
      ret.emplace_back(m);
      m.special = "Q";
      ret.emplace_back(m);
    }
    else { ret.emplace_back(m); }
  }
  else { return ret; } // If moving one square is illegal, so will be moving two of them
  


  // Moving forward two steps
  m = getColour() ? Move{ location, Square{ location.file, location.rank - 2}, 0, "two steps" } :
    Move{ location, Square{ location.file, location.rank + 2}, 0, "two steps" }; // Different direction for black and white

  // If our pawn has not been touched and the move is legal
  if (untouched && isLegalMove(m)) {
    ret.emplace_back(m);
  }

  return ret;
}

std::vector<Move> Pawn::getAttackMoves() {
  std::vector<Move> ret;

  Board* board = getBoard();
  Square location = getLocation();

  if (getColour()) {
    // black
    ret.emplace_back(Move{ location, Square{ location.file - 1, location.rank - 1 }, 0, "" });
    ret.emplace_back(Move{ location, Square{ location.file + 1, location.rank - 1 }, 0, "" });
  }
  else {
    // white 
    ret.emplace_back(Move{ location, Square{ location.file - 1, location.rank + 1 }, 0, "" });
    ret.emplace_back(Move{ location, Square{ location.file + 1, location.rank + 1 }, 0, "" });
  }

  
  for (auto it = ret.begin(); it != ret.end(); ) {
    if (!board->isValidSquare(it->to)) {
      it = ret.erase(it);
    }
    else {
      Piece* p = board->getPieceAt(it->to);
      if (p && p->getColour() != getColour()) {
        it->value = p->getValue();
      }
      ++it;
    }
  }

  return ret;
}
