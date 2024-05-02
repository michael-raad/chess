#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
#include "board.h"

class Queen : public Piece {
public:
  // Constructor
  Queen(Board *board, Colour colour, Square location);

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
