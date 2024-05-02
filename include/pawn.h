#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"
#include "board.h"

class Pawn : public Piece {
  // private fields
  bool untouched, enPassant;
  
public:
  // Constructor
  Pawn(Board* board, Colour colour, Square location);

  // Checks if the pawn has moved
  bool isUntouched();

  // sets untouched to false
  void touch();

  // Sets untouched to true
  void unTouch();

  // Set to 1 if the pawn is moving two steps ahead
  // Let's the opponent's pawn know that enPassant is possible 
  bool isEnPassant();

  // Sets isEnPassant field to 1
  void setEnPassant(bool b);

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
