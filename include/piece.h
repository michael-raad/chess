#ifndef __PIECE_H__
#define __PIECE_H__
#include <vector>
#include "colour.h"
#include "square.h"
#include "move.h"

class Board;

class Piece {
  Board* board;
  Colour colour;
  int value; // Pawn = 2, Knight = 6, Bishop = 7, Rook = 10, Queen = 18, King = 69
  Square location;

protected:
  // Returns pointer to the board
  Board* getBoard() const;

  // Adds all moves in direction 'dir' to the vector 'vec' if it is
  //  valid (within bounds). Does not check if moves are legal
  void generatingMoves(std::vector<Move>& vec, int dir);

public:
  // Constructor
  Piece(Board* board, Colour colour, int value, Square location);

  // Destructor
  virtual ~Piece() = default;

  // Pure virtual function to check if a move is legal:
  // Both squares are valid, does not put king in check
  virtual bool isLegalMove(Move move) = 0;

  // Pure virtual fn to return a vector of legal moves the piece can make
  virtual std::vector<Move> getLegalMoves() = 0;
  
  // Pure virtual fn which returns moves that the pawn can make to 
  // capture an opponent's piece
  virtual std::vector<Move> getAttackMoves() = 0;

  // Returns location of the piece
  Square getLocation() const;
  
  // Sets location of the piece
  void setLocation(Square sq);

  // Returns colour of piece
  Colour getColour() const;

  // Gets value of piece
  int getValue() const;
};


#endif
