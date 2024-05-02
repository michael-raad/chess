#include "board.h"
#include "chessdisplay.h"

Board::Board(int numFile, int numRank) :
  numFile{ numFile }, numRank{ numRank } { }

int Board::getNumFile() const { return numFile; }

int Board::getNumRank() const { return numRank; }


void Board::addDisplay(ChessDisplay* display) {
  displays.emplace_back(display);
}

void Board::removeDisplay(ChessDisplay* display) {
  for (auto it = displays.begin(); it != displays.end(); ++it) {
    if (*it == display) {
      displays.erase(it);
      break;
    }
  }
}

void Board::notifyDisplays(Square square) {
  for (auto& d : displays) d->notify(square);
}

void Board::outputDisplays() {
  for (auto& d : displays) d->output();
}
