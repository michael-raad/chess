#ifndef __MOVE_H__
#define __MOVE_H__
#include <string>
#include "square.h"

// Struct to represent a single move
struct Move {
  Square from, to;
  int value; // value of the piece being captured
  std::string special; // string to represent if a "special" move is being make
                       // eg: castle, pawn promotion
};

#endif
