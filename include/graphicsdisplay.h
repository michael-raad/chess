#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <vector>
#include "window.h"
#include "chessdisplay.h"
#include "colour.h"

class StandardBoard;

class GraphicsDisplay : public ChessDisplay {
  // Private fields
  StandardBoard* sb;
  const int numFile, numRank, squareWidth, squareHeight;
  Xwindow w;

  void drawPawn(int x, int y, Colour colour);
  void drawKnight(int x, int y, Colour colour);
  void drawBishop(int x, int y, Colour colour);
  void drawRook(int x, int y, Colour colour);
  void drawQueen(int x, int y, Colour colour);
  void drawKing(int x, int y, Colour colour);
public:
  // Constructor
  GraphicsDisplay(StandardBoard* sb, int numFile, int numRank);

  // Notifies graphics display about change in 'square'
  void notify(Square square) override;

  // Display out the new graphics display
  void output() override;
};

#endif
