#include "graphicsdisplay.h"
#include "standardboard.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(StandardBoard* sb, int numFile, int numRank) :
  sb{ sb },
  numFile{ numFile },
  numRank{ numRank },
  squareWidth{ 800 / numFile },
  squareHeight{ 800 / numRank } {
    for (int i = 0; i < numRank; ++i) {
      for (int j = 0; j < numFile; ++j) {
        w.fillRectangle(j * squareWidth, i * squareHeight, squareWidth, squareHeight, (i + j) % 2 == 0 ? 3 : 4);
      }
    }
  }

void GraphicsDisplay::notify(Square square) {
  // Maps the value of Piece to a piece
  // 2: p, 6: n, 7: b, 10: r, 18: q, 69: k
  Piece *p = sb->getPieceAt(square); 
  w.fillRectangle(square.file * squareWidth, (numRank - square.rank - 1) * squareHeight, squareWidth, squareHeight, (square.file + square.rank) % 2 == 0 ? 4 : 3);
  if (p) {
    if (p->getValue() == 2) {
      drawPawn(square.file * squareWidth, (numRank - square.rank - 1) * squareHeight, p->getColour());
    }
    else if (p->getValue() == 6) {
      drawKnight(square.file * squareWidth, (numRank - square.rank - 1) * squareHeight, p->getColour());
    }
    else if (p->getValue() == 7) {
      drawBishop(square.file * squareWidth, (numRank - square.rank - 1) * squareHeight, p->getColour());
    }
    else if (p->getValue() == 10) {
      drawRook(square.file * squareWidth, (numRank - square.rank - 1) * squareHeight, p->getColour());
    }
    else if (p->getValue() == 18) {
      drawQueen(square.file * squareWidth, (numRank - square.rank - 1) * squareHeight, p->getColour());
    }
    else if (p->getValue() == 69) {
      drawKing(square.file * squareWidth, (numRank - square.rank - 1) * squareHeight, p->getColour());
    }
  }
  string letterArray[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
  if (square.file == 0) {
    w.drawString(5, squareHeight * (numRank - square.rank - 1) + 15, to_string(square.rank + 1));
  }
  if (square.rank == 0) {
    w.drawString(squareWidth * (square.file + 1) - 10, squareHeight * numRank - 5, letterArray[square.file]);
  }
}

void GraphicsDisplay::drawPawn(int x, int y, Colour colour) {
  w.fillRectangle(
    x + 20,
    y + 80,
    60,
    20,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 70,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 60,
    20,
    10,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 40,
    40,
    20,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 30,
    20,
    10,
    colour
  );
}

void GraphicsDisplay::drawKnight(int x, int y, Colour colour) {
  w.fillRectangle(
    x + 20,
    y + 80,
    60,
    20,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 70,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 60,
    50,
    10,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 50,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 50,
    y + 20,
    30,
    30,
    colour
  );
  w.fillRectangle(
    x + 20,
    y + 30,
    10,
    20,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 20,
    10,
    30,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 10,
    10,
    30,
    colour
  );
  w.fillRectangle(
    x + 50,
    y + 10,
    20,
    20,
    colour
  );
}

void GraphicsDisplay::drawBishop(int x, int y, Colour colour) {
  w.fillRectangle(
    x + 20,
    y + 80,
    60,
    20,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 70,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 50,
    20,
    20,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 30,
    40,
    20,
    colour
  );
  w.fillRectangle(
    x + 60,
    y + 20,
    10,
    10,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 15,
    20,
    15,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 5,
    10,
    10,
    colour
  );
}

void GraphicsDisplay::drawRook(int x, int y, Colour colour) {
  w.fillRectangle(
    x + 20,
    y + 80,
    60,
    20,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 30,
    40,
    50,
    colour
  );
  w.fillRectangle(
    x + 20,
    y + 20,
    10,
    10,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 20,
    20,
    10,
    colour
  );
  w.fillRectangle(
    x + 70,
    y + 20,
    10,
    10,
    colour
  );
}

void GraphicsDisplay::drawQueen(int x, int y, Colour colour) {
  w.fillRectangle(
    x + 20,
    y + 80,
    60,
    20,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 70,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 60,
    20,
    10,
    colour
  );
   w.fillRectangle(
    x + 30,
    y + 50,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 35,
    20,
    15,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 25,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 20,
    y + 15,
    60,
    10,
    colour
  );
  w.fillRectangle(
    x + 20,
    y + 8,
    10,
    7,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 5,
    20,
    10,
    colour
  );
  w.fillRectangle(
    x + 70,
    y + 8,
    10,
    7,
    colour
  );
}

void GraphicsDisplay::drawKing(int x, int y, Colour colour) {
  w.fillRectangle(
    x + 20,
    y + 80,
    60,
    20,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 70,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 45,
    20,
    25,
    colour
  );
  w.fillRectangle(
    x + 30,
    y + 35,
    40,
    10,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 27,
    20,
    8,
    colour
  );
  w.fillRectangle(
    x + 20,
    y + 12,
    60,
    15,
    colour
  );
  w.fillRectangle(
    x + 40,
    y + 2,
    20,
    10,
    colour
  );
}

void GraphicsDisplay::output() {} // Do nothing, let notify update graphics

