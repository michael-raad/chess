#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
#include "board.h"

class King : public Piece {

  bool untouched;

public:
  // Constructor
  King(Board* board, Colour colour, Square location);

  // Checks if the king has been moved
  bool isUntouched();

  // Sets untouched to false
  void touch();

  // Sets untouched to true
  void unTouch();

  // Checks if a move is legal:
  // Both squares are valid
  // Does not put king in check
  bool isLegalMove(Move move) override;

  // Returns a vector of legal moves the piece can make
  std::vector<Move> getLegalMoves() override;

  // Returns moves that the pawn can make to 
  // capture an opponent's piece
  std::vector<Move> getAttackMoves() override;
};

#endif
