#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include "colour.h"
#include "square.h"
#include "move.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

class ChessDisplay;

// Subject
class Board {
  std::vector<ChessDisplay*> displays;
  int numFile, numRank; // file -> column, rank -> row

public:
  // Constructor & Destructor
  Board(int numFile, int numRank);
  virtual ~Board() = default;

  // Gets number of files (columns)
  int getNumFile() const;

  // Gets number of ranks (rows)
  int getNumRank() const;

  // Adds the display as an observer
  void addDisplay(ChessDisplay* display);

  // Removes the display as an observer
  void removeDisplay(ChessDisplay* display);

  // Notifies all displays that square has changed
  void notifyDisplays(Square square);

  // Tells all displays to output their data
  void outputDisplays();

  // Pure virtual functions. View concrete boards for documentation.
  virtual bool isValidSquare(Square square) const = 0;
  virtual bool isValidState() const = 0;
  virtual Piece* getPieceAt(Square square) const = 0;
  virtual void clear() = 0;
  virtual void config() = 0;
  virtual bool addPiece(char colour, char piece, Square location) = 0;
  virtual bool removePiece(Square location) = 0;
  virtual std::vector<Move> getLegalMoves(Colour colour) const = 0;
  virtual std::vector<Move> getAttackMoves(Colour colour) const = 0;
  virtual void makeMove(Move move) = 0;
  virtual int evaluatePosition() = 0;
  virtual int evaluateMove(const Move& move, Colour c, int depth) = 0;
  virtual int simulateMove(const Move& move, Colour c) = 0;
};

#endif
