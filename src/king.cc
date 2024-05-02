#include "king.h"

King::King(Board* board, Colour colour, Square location)
  : Piece{ board, colour, 69, location }, untouched{ true } {  }


bool King::isUntouched() { return untouched; }


void King::touch() { untouched = false; }

void King::unTouch() { untouched = true; }

bool King::isLegalMove(Move move) {
  Board* board = getBoard();
  Colour c = getColour();

  // check if valid location
  if (!board->isValidSquare(move.to)) return false;

  Piece* p = board->getPieceAt(move.to); // The piece we are capturing

  // Capturing your own piece is not a legal move
  if (p && c == p->getColour()) return false;

  // *Below needs to be changed if there are more than two colours*
  // Get opponent's attack moves (remember white = 0, black = 1)
  std::vector<Move> opponentThreats = 
    board->getAttackMoves(getColour() ? Colour::White : Colour::Black); 

  // Check for castling
  if (move.special == "castling") {
    Square firstNextTo, secondNextTo, thirdNextTo;
    // Short castle
    if (move.to.file > move.from.file) {
      firstNextTo.file = move.from.file + 1;
      firstNextTo.rank = move.from.rank;
      secondNextTo.file = move.from.file + 2;
      secondNextTo.rank = move.from.rank;
    }
    // Long Castle
    else {
      firstNextTo.file = move.from.file - 1;
      firstNextTo.rank = move.from.rank;
      secondNextTo.file = move.from.file - 2;
      secondNextTo.rank = move.from.rank;
      thirdNextTo.file = move.from.file - 3;
      thirdNextTo.rank = move.from.rank;
      if (board->getPieceAt(thirdNextTo)) return false;
    }

    // Cannot castle if there are pieces between the king and rook
    if (board->getPieceAt(firstNextTo) || board->getPieceAt(secondNextTo)) return false; 

    // check if the three squares from the king to the rook are under attack
    for (auto m : opponentThreats) {
      if (m.to == move.from || m.to == firstNextTo || m.to == secondNextTo)
        return false;
    }
  }
  // If we're not checking a castle move
  else {
    return (board->simulateMove(move, c ? Colour::White : Colour::Black) != 69);
  }

  return true;
}


std::vector<Move> King::getLegalMoves() {
  Square location = getLocation();
  Board* board = getBoard();
  std::vector<Move> ret;
  std::vector<Move> possibleMoves;

  // Add every attack angle
  for (auto m : getAttackMoves())
    possibleMoves.emplace_back(m);

  // Check if castling is possible
  if (untouched) {
    Piece* longRook = board->getPieceAt(Square{ 0, location.rank });
    Piece* shortRook = board->getPieceAt(Square{ 7, location.rank });
    if (longRook && longRook->getValue() == 10) {
      if (dynamic_cast<Rook *>(longRook)->isUntouched()) {
        possibleMoves.emplace_back(Move{ location, Square{ location.file - 2, location.rank }, 0, "castling"});
      }
    }
    if (shortRook && shortRook->getValue() == 10) {
      if (dynamic_cast<Rook *>(shortRook)->isUntouched()) {
        possibleMoves.emplace_back(Move{ location, Square{ location.file + 2, location.rank }, 0, "castling"});
      }
    }
  }

  // if all possibleMoves are legal
  for (auto& m : possibleMoves) {
    if (isLegalMove(m)) {
      ret.emplace_back(m);
    }
  }

  return ret;
}


std::vector<Move> King::getAttackMoves() {
  std::vector<Move> ret;

  Board* board = getBoard();
  Square location = getLocation();

  ret.emplace_back(Move{ location, Square{ location.file - 1, location.rank }, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file - 1, location.rank + 1 }, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file, location.rank + 1 }, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file + 1, location.rank + 1 }, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file + 1, location.rank }, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file + 1, location.rank - 1 }, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file, location.rank - 1 }, 0, "" });
  ret.emplace_back(Move{ location, Square{ location.file - 1, location.rank - 1 }, 0, "" });

  // For each attack move
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

// CASTLING
// do not move out of the standardBoard -> long or short castle
// call getAttackMoves for each space
