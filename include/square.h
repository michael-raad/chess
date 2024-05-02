#ifndef __SQUARE_H__
#define __SQUARE_H__

struct Square {
  // row and column, respectively 
  int file, rank;

  // Returns 1 if the two squares are equal
  bool operator==(Square sq);
};

#endif
