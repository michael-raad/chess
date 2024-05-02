#include "piece.h"
#include "board.h"

Board* Piece::getBoard() const { return board; }

Square Piece::getLocation() const { return location; }

void Piece::generatingMoves(std::vector<Move>& vec, int dir) {
  // directions: 0 = left, 1 = right, 2 = up, 3 = down
  //             4 = left up, 5 = right up, 6 = left down, 7 = right down

  Square to{ location }; // Current location

  while (true) {
    switch (dir) { 
    case 0:
      to.file--;
      break;
    case 1:
      to.file++;
      break;
    case 2:
      to.rank++;
      break;
    case 3:
      to.rank--;
      break;
    case 4:
      to.file--;
      to.rank++;
      break;
    case 5:
      to.file++;
      to.rank++;
      break;
    case 6:
      to.file--;
      to.rank--;
      break;
    case 7:
      to.file++;
      to.rank--;
      break;
    default: break;
    }

    // Check if it's within the board
    if (!board->isValidSquare(to)) break;

    Piece* p = board->getPieceAt(to);

    // Check if we hit another piece
    if (p) {
      // Add to the list with a value if it's not same colour (capturing move)
      if (p->colour != colour) {
        vec.emplace_back(location, to, p->getValue(), "");
      } 
      // Otherwise add to list with value 0
      else {
        vec.emplace_back(location, to, 0, "");
      }
      
      // Have to end here cause can't get over the blocked piece
      return;
    }

    // If we did not hit a piece, add this square as a move.
    vec.emplace_back(location, to, 0, "");
  }
}


Piece::Piece(Board* board, Colour colour, int value, Square location) :
  board{ board }, colour{ colour }, value{ value }, location{ location } {}

Colour Piece::getColour() const { return colour; }

void Piece::setLocation(Square sq) { location = sq; }

int Piece::getValue() const { return value; }
