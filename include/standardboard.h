#ifndef __STANDARDBOARD_H__
#define __STANDARDBOARD_H__
#include <vector>
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class StandardBoard : public Board {
  std::vector<std::vector<std::unique_ptr<Piece>>> grid;

public:
  // Constructor
  StandardBoard();

  // Returns if square is within the 8x8 bounds of the board
  bool isValidSquare(Square square) const override;

  // Returns if the board is in a valid state, described by having
  //  exactly 1 king for each colour, neither king in check, 
  //  and no pawns on the first or last rank.
  bool isValidState() const override;

  // Returns a pointer to the piece at square in the grid. Returns nullptr if
  //  square is not a valid square or does not contain a piece.
  Piece* getPieceAt(Square square) const override;

  // Clears the board of all pieces.
  void clear() override;

  // Sets default configuration of pieces for a standard 8x8 board.
  void config() override;

   // Adds a piece ('p', 'n', 'b', 'r', 'q', 'k') of colour white ('w')
  //  or black ('b') at location. If a piece is already at location, it is
  //  overritten. Returns success of the operation
  bool addPiece(char colour, char piece, Square location) override;

  // Removes the piece at location. Returns success of operation
  bool removePiece(Square location) override;

  // Returns all possible legal moves for colour to perform
  std::vector<Move> getLegalMoves(Colour colour) const override;

  // Returns all squares colour is attacking (in the form of a move).
  //  **An attack move isn't necessarily a legal move, it's just all squares
  //  the pieces with colour are "looking" at (or putting "under attack").**
  std::vector<Move> getAttackMoves(Colour colour) const override;

  // Performs move, with the assumption that move is legal. 
  void makeMove(Move move) override;

  // Evaluates the position of the board. A positive evaluation is in favour of white.
  //   A negative evaluation is nn favour of black. 0 means the position is even. 
  int evaluatePosition() override;

  // Evaluates the move performed by specified colour at the provided depth.
  int evaluateMove(const Move& move, Colour c, int depth) override;

  // Simulates move, returns the value of the largest piece threatened by colour c after
  //  performing this move.
  int simulateMove(const Move& move, Colour c) override;

  // Notifies all displays for all squares and outputs the display. Only needed for testing.
  void refreshDisplays();
};

#endif
