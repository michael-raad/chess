#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <vector>
#include <iostream>
#include "chessdisplay.h"

class StandardBoard;

class TextDisplay : public ChessDisplay {
  // Private fields
  std::vector<std::vector<char>> theDisplay; // TextDisplay can only represent two players (caps and w\o caps)
  StandardBoard* sb;
  
public:
  // Constructor
  TextDisplay(StandardBoard* sb, int numFile, int numRank);

  // Notifies text display about change in 'square'
  void notify(Square square) override;

  // Prints out the new text display
  void output() override;
};

#endif
