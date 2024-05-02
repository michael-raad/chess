#include "standardboard.h"
#include "textdisplay.h"

TextDisplay::TextDisplay(StandardBoard* sb, int numFile, int numRank) :
  sb{ sb } {
  for (int i = 0; i < numRank; ++i) {
    std::vector<char> row;
    for (int j = 0; j < numFile; ++j) {
      (i + j) % 2 == 0 ? row.emplace_back('_') : row.emplace_back(' '); // even sum is black, odd sum is white.
    }
    theDisplay.emplace_back(row);
  }
}

void TextDisplay::notify(Square square) {
  // Maps the value of Piece to a character
  // 2: p, 6: n, 7: b, 10: r, 18: q, 69: k
  Piece* p = sb->getPieceAt(square);
  if (p == nullptr) {
    theDisplay[square.rank][square.file] = (square.file + square.rank) % 2 == 0 ? '_' : ' ';
  } else {
    switch (p->getValue()) {
      case 2:
        theDisplay[square.rank][square.file] = p->getColour() ? 'p' : 'P';
        break;
      case 6:
        theDisplay[square.rank][square.file] = p->getColour() ? 'n' : 'N';
        break;
      case 7:
        theDisplay[square.rank][square.file] = p->getColour() ? 'b' : 'B';
        break;
      case 10:
        theDisplay[square.rank][square.file] = p->getColour() ? 'r' : 'R';
        break;
      case 18:
        theDisplay[square.rank][square.file] = p->getColour() ? 'q' : 'Q';
        break;
      case 69:
        theDisplay[square.rank][square.file] = p->getColour() ? 'k' : 'K';
        break;
      default:
        theDisplay[square.rank][square.file] = 'E';
        break;
    }
  }
}

void TextDisplay::output() {
  int numRank = sb->getNumRank();
  int numFile = sb->getNumFile();

  for (int i = numRank - 1; i >= 0; --i) {
    std::cout << i + 1 << " ";         // Printing Rank number
    for (auto c : theDisplay[i]) {
      std::cout << c;                  // Printing each char
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  // Printing File character
  std::cout << "  ";                   // For alignment 
  for (int i = 0; i < numFile; ++i) {
    std::cout << static_cast<char>('a' + i);
  }
  std::cout << std::endl;
}
