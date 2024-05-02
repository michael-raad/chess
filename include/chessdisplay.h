#ifndef __CHESSDISPLAY_H__
#define __CHESSDISPLAY_H__
#include <iostream>
#include "board.h"
#include "square.h"

class ChessDisplay {
public:
  // Pure virtual function to notify a display of change in "square"
  virtual void notify(Square square) = 0;

  // Pure virtual function to output changed display
  virtual void output() = 0;

  // Destructor
  virtual ~ChessDisplay() = default;
};

#endif
