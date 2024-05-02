#include "square.h"

bool Square::operator==(Square sq) {
  return file == sq.file && rank == sq.rank;
}
