#include "standardboard.h"

StandardBoard::StandardBoard() :
  Board{ 8, 8 } { // A standard chess board is 8x8
  grid.resize(8);
  for (auto& row : grid) row.resize(8);
}


bool StandardBoard::isValidSquare(Square square) const {
  if (square.file < 0 || square.file >= getNumFile() ||
    square.rank < 0 || square.rank >= getNumRank()) return false;
  return true;
}


bool StandardBoard::isValidState() const {
  int whiteKingCount = 0;
  int blackKingCount = 0;
  for (int i = 0; i < getNumRank(); ++i) {
    for (int j = 0; j < getNumFile(); ++j) {
      if (grid[i][j] != nullptr) { // If there is a piece here

        // If the piece is a pawn on the first or last rank, board is invalid
        if (grid[i][j]->getValue() == 2 && (i == 0 || i == 7)) {
          return false;
        }

        // If the piece is a king, increment our king count
        if (grid[i][j]->getValue() == 69) {
          if (grid[i][j]->getColour() == Colour::White) ++whiteKingCount;
          else ++blackKingCount;
        }
      }
    }
  }

  // If there isn't exactly one of each king, our board is invalid
  if (whiteKingCount != 1 || blackKingCount != 1) return false;

  std::vector<Move> blackThreats = getAttackMoves(Colour::Black);
  std::vector<Move> whiteThreats = getAttackMoves(Colour::White);

  // Check if White is in check. If so, board is invalid.
  for (auto m : blackThreats) {
    if (m.value == 69) return false;
  }

  // Check if Black is in check. If so, board is invalid
  for (auto m : whiteThreats) {
    if (m.value == 69) return false;
  }

  // Otherwise board is valid.
  return true;
}


Piece* StandardBoard::getPieceAt(Square square) const {
  // Check if square is within bounds. If not return nullptr
  if (!isValidSquare(square)) return nullptr;
  return grid[square.rank][square.file].get();
}

void StandardBoard::clear() {
  int numRank = getNumRank();
  int numFile = getNumFile();
  grid.clear(); // Clear grid
  grid.resize(numRank);
  for (int i = 0; i < numRank; ++i) {
    grid[i].resize(numFile);
    for (int j = 0; j < numFile; ++j) {
      notifyDisplays(Square{ j, i }); // notify for each square we "reset"
    }
  }
}

void StandardBoard::config() {
  int numRank = getNumRank();
  int numFile = getNumFile();
  clear();

  // White pieces
  addPiece('w', 'p', Square{ 0, 1 });
  addPiece('w', 'p', Square{ 1, 1 });
  addPiece('w', 'p', Square{ 2, 1 });
  addPiece('w', 'p', Square{ 3, 1 });
  addPiece('w', 'p', Square{ 4, 1 });
  addPiece('w', 'p', Square{ 5, 1 });
  addPiece('w', 'p', Square{ 6, 1 });
  addPiece('w', 'p', Square{ 7, 1 });
  addPiece('w', 'r', Square{ 0, 0 });
  addPiece('w', 'n', Square{ 1, 0 });
  addPiece('w', 'b', Square{ 2, 0 });
  addPiece('w', 'q', Square{ 3, 0 });
  addPiece('w', 'k', Square{ 4, 0 });
  addPiece('w', 'b', Square{ 5, 0 });
  addPiece('w', 'n', Square{ 6, 0 });
  addPiece('w', 'r', Square{ 7, 0 });

  // Black pieces
  addPiece('b', 'p', Square{ 0, 6 });
  addPiece('b', 'p', Square{ 1, 6 });
  addPiece('b', 'p', Square{ 2, 6 });
  addPiece('b', 'p', Square{ 3, 6 });
  addPiece('b', 'p', Square{ 4, 6 });
  addPiece('b', 'p', Square{ 5, 6 });
  addPiece('b', 'p', Square{ 6, 6 });
  addPiece('b', 'p', Square{ 7, 6 });
  addPiece('b', 'r', Square{ 0, 7 });
  addPiece('b', 'n', Square{ 1, 7 });
  addPiece('b', 'b', Square{ 2, 7 });
  addPiece('b', 'q', Square{ 3, 7 });
  addPiece('b', 'k', Square{ 4, 7 });
  addPiece('b', 'b', Square{ 5, 7 });
  addPiece('b', 'n', Square{ 6, 7 });
  addPiece('b', 'r', Square{ 7, 7 });

  outputDisplays();
}

bool StandardBoard::addPiece(char colour, char piece, Square location) {
  // check if valid location
  if (!isValidSquare(location)) return false;

  // decode colour
  Colour c;

  switch (colour) {
  case 'w':
    c = Colour::White;
    break;
  case 'b':
    c = Colour::Black;
    break;
  }

  std::unique_ptr<Piece> p;
  // Check if char represents valid piece. If so, make piece.
  switch (piece) {
  case 'p':
    p = std::make_unique<Pawn>(this, c, location);
    break;
  case 'n':
    p = std::make_unique<Knight>(this, c, location);
    break;
  case 'b':
    p = std::make_unique<Bishop>(this, c, location);
    break;
  case 'r':
    p = std::make_unique<Rook>(this, c, location);
    break;
  case 'q':
    p = std::make_unique<Queen>(this, c, location);
    break;
  case 'k':
    p = std::make_unique<King>(this, c, location);
    break;
  default: return false; // Runs when char not valid
  }

  // Place the piece at location. If a piece is already at location,
  //  it is replaced
  grid[location.rank][location.file] = std::move(p);
  notifyDisplays(location);

  return true;
}

bool StandardBoard::removePiece(Square location) {
  // check if valid location
  if (!isValidSquare(location)) return false;

  grid[location.rank][location.file].reset();
  notifyDisplays(location);

  return true;
}

std::vector<Move> StandardBoard::getLegalMoves(Colour colour) const {
  std::vector<Move> ret;
  // Loop through each square on the grid
  for (auto& row : grid) {
    for (auto& p : row) {
      // If there is a piece at this square with the same color
      if (p != nullptr && p->getColour() == colour) {
        for (auto m : p->getLegalMoves()) // Add this piece's legal moves
          ret.emplace_back(m);
      }
    }
  }

  return ret; // Return all of colour's legal moves
}

std::vector<Move> StandardBoard::getAttackMoves(Colour colour) const {
  std::vector<Move> ret;
  // Loop through each square on the grid
  for (auto& row : grid) {
    for (auto& p : row) {
      // If there is a piece at this square with the same colour
      if (p != nullptr && p->getColour() == colour) {
        for (auto m : p->getAttackMoves()) // Add this piece's attack moves
          ret.emplace_back(m);
      }
    }
  }

  return ret; // Return all of colour's attack moves. 
}

void StandardBoard::makeMove(Move move) {
  Piece* p = getPieceAt(move.from); // TODO for some reason, this may be NULL. investigate using seed.

  // First, go through board. Any pawns of the colour moving must
  //  have their en passant field turned off (en passant is only valid for 1 turn)
  for (auto& r : grid) {
    for (auto& s : r) {
      // if piece is a pawn fo same colour
      if (s && s->getValue() == 2 && s->getColour() == p->getColour()) {
        dynamic_cast<Pawn*>(s.get())->setEnPassant(false); // Turn en passant off
        break; // only one pawn of some colour can have their en passant field turned on at any given point
      }
    }
  }

  // If our piece is a pawn
  if (p->getValue() == 2) {
    Pawn* pawn = dynamic_cast<Pawn*>(p);
    pawn->touch(); // Mark it as touched
    // If it's pawn's first turn and moving two squares instead of one
    if (move.special == "two steps") {
      pawn->setEnPassant(true); // Allows en passant to be performed by the next players
    }
    // If pawn is promoting, add the promoted piece to the right square, delete the pawn
    else if (move.special.length() == 1) {
      switch (move.special[0]) {
      case 'N':
        grid[move.to.rank][move.to.file] =
          std::make_unique<Knight>(this, p->getColour(), move.to);
        break;
      case 'B':
        grid[move.to.rank][move.to.file] =
          std::make_unique<Bishop>(this, p->getColour(), move.to);
        break;
      case 'R':
        grid[move.to.rank][move.to.file] =
          std::make_unique<Rook>(this, p->getColour(), move.to);
        break;
      case 'Q':
        grid[move.to.rank][move.to.file] =
          std::make_unique<Queen>(this, p->getColour(), move.to);
        break;
      }
      grid[move.from.rank][move.from.file].reset();
      notifyDisplays(move.from);
      notifyDisplays(move.to);
      outputDisplays();
      return; // We've made the move so we can just return.
    }
    // If pawn is performing en passant
    else if (move.special == "en passant") {
      grid[move.from.rank][move.to.file].reset(); // For now delete the captured piece
      notifyDisplays(Square{ move.to.file, move.from.rank });
    }
  }

  // If our piece is a rook
  else if (p->getValue() == 10) {
    dynamic_cast<Rook*>(p)->touch(); // it is no longer untouched
  }

  // If our piece is a king
  else if (p->getValue() == 69) {
    dynamic_cast<King*>(p)->touch(); // It is no longer untouched
    // If the king wants to castle
    if (move.special == "castling") {
      if (move.to.file > move.from.file) { // Short castle
        makeMove(Move{ {7, move.from.rank}, {move.from.file + 1, move.from.rank}, 0, "" }); // Move the rook
      }
      else { // Long castle
        makeMove(Move{ {0, move.from.rank}, {move.from.file - 1, move.from.rank}, 0, "" }); // Move the rook
      }
    }
  }

  grid[move.to.rank][move.to.file] =
    std::move(grid[move.from.rank][move.from.file]); // Now move our piece

  grid[move.to.rank][move.to.file]->setLocation(move.to); // and give it its new location

  notifyDisplays(move.to);
  notifyDisplays(move.from);
  outputDisplays();
}

int StandardBoard::evaluatePosition() {
  std::vector<Move> whiteLegal = getLegalMoves(White);
  std::vector<Move> whiteAttack = getAttackMoves(White);
  std::vector<Move> blackLegal = getLegalMoves(Black);
  std::vector<Move> blackAttack = getAttackMoves(Black);
  bool whiteInCheck = false;
  bool blackInCheck = false;

  for (auto m : whiteAttack) {
    if (m.value == 69) {
      blackInCheck = true;
      break;
    }
  }

  for (auto m : blackAttack) {
    if (m.value == 69) {
      whiteInCheck = true;
      break;
    }
  }

  if (whiteLegal.size() == 0 && whiteInCheck) { // White is Checkmated
    return -10000;
  }
  else if (blackLegal.size() == 0 && blackInCheck) { // Black is Checkmated
    return 10000;
  }
  else if (whiteLegal.size() == 0 || blackLegal.size() == 0) { // Stalemate
    return 0;
  }

  int evaluation = 0;

  for (auto& r : grid) {
    for (auto& p : r) {
      if (p && p->getColour() == White) {
        evaluation += p->getValue();
      }
      else if (p) {
        evaluation -= p->getValue();
      }
    }
  }

  if (whiteInCheck) {
    --evaluation;
  }
  else if (blackInCheck) {
    ++evaluation;
  }

  return evaluation;
}

int StandardBoard::evaluateMove(const Move& move, Colour c, int depth) {
	int moveValue = move.value;
	if (depth == 0) { return moveValue; }

  std::unique_ptr<Piece> pieceHolder; // Store the piece captured during move simulation
  std::unique_ptr<Piece> pieceHolderTheSecond; // Stores promoting pawn

  Square offPassant{-1, -1}; // Location of Pawn whose en passant field has been turned off this turn
  Square touchedPawn{-1, -1}; // Location of Pawn touched for the first time
  Square touchedRook{-1, -1}; // Location of Rook touched for the first time 
  Square touchedKing{-1, -1}; // Location of King touched for the first time

  // First, go through board. Any pawns of the colour moving must
  //  have their en passant field turned off (en passant is only valid for 1 turn)
  for (auto& r : grid) {
    for (auto& s : r) {
      // if piece is a pawn fo same colour
      if (s && s->getValue() == 2 && s->getColour() == c && dynamic_cast<Pawn*>(s.get())->isEnPassant()) {
        dynamic_cast<Pawn*>(s.get())->setEnPassant(false); // Turn en passant off
        offPassant = s->getLocation();
        break;
      }
    }
  }

  // Depending on the move performed, store the captured piece and put
  //  the board in the state after the move
  if (move.special == "en passant") {
    pieceHolder = std::move(grid[move.from.rank][move.to.file]);

    grid[move.to.rank][move.to.file] =
      std::move(grid[move.from.rank][move.from.file]);
    grid[move.to.rank][move.to.file]->setLocation(move.to);
  }
  else if (move.special == "castling") {
    grid[move.to.rank][move.to.file] =
      std::move(grid[move.from.rank][move.from.file]);
    grid[move.to.rank][move.to.file]->setLocation(move.to);
    dynamic_cast<King*>(grid[move.to.rank][move.to.file].get())->touch();

    if (move.to.file > move.from.file) {
      grid[move.from.rank][move.from.file + 1] =
        std::move(grid[move.from.rank][7]);
      grid[move.from.rank][move.from.file + 1]->setLocation(Square{move.from.file + 1, move.from.rank});
      dynamic_cast<Rook*>(grid[move.from.rank][move.from.file + 1].get())->touch();
    }
    else {
      grid[move.from.rank][move.from.file - 1] =
        std::move(grid[move.from.rank][0]);
      grid[move.from.rank][move.from.file - 1]->setLocation(Square{move.from.file - 1, move.from.rank});
      dynamic_cast<Rook*>(grid[move.from.rank][move.from.file - 1].get())->touch();
    }
  }
  else if (move.special.length() == 1) { // Promotion
    pieceHolder = std::move(grid[move.to.rank][move.to.file]); // Save the captured piece
    pieceHolderTheSecond = std::move(grid[move.from.rank][move.from.file]); // Save the pawn
    // Place the promoted piece
    switch (move.special[0]) {
    case 'N':
      grid[move.to.rank][move.to.file] =
        std::make_unique<Knight>(this, pieceHolderTheSecond->getColour(), Square{ move.to.file, move.to.rank });
      break;
    case 'B':
      grid[move.to.rank][move.to.file] =
        std::make_unique<Bishop>(this, pieceHolderTheSecond->getColour(), Square{ move.to.file, move.to.rank });
      break;
    case 'R':
      grid[move.to.rank][move.to.file] =
        std::make_unique<Rook>(this, pieceHolderTheSecond->getColour(), Square{ move.to.file, move.to.rank });
      break;
    case 'Q':
      grid[move.to.rank][move.to.file] =
        std::make_unique<Queen>(this, pieceHolderTheSecond->getColour(), Square{ move.to.file, move.to.rank });
      break;
    }
  }
  else {
    pieceHolder = std::move(grid[move.to.rank][move.to.file]);

    grid[move.to.rank][move.to.file] =
      std::move(grid[move.from.rank][move.from.file]);
    grid[move.to.rank][move.to.file]->setLocation(move.to); // ->setLocation(Square{move.to.file, move.to.rank});

    if (grid[move.to.rank][move.to.file]->getValue() == 2 && dynamic_cast<Pawn*>(grid[move.to.rank][move.to.file].get())->isUntouched()) {
      dynamic_cast<Pawn*>(grid[move.to.rank][move.to.file].get())->touch();
      touchedPawn = move.to;
    }
    else if (grid[move.to.rank][move.to.file]->getValue() == 10 && dynamic_cast<Rook*>(grid[move.to.rank][move.to.file].get())->isUntouched()) {
      dynamic_cast<Rook*>(grid[move.to.rank][move.to.file].get())->touch();
      touchedRook = move.to;
    }
    else if (grid[move.to.rank][move.to.file]->getValue() == 69 && dynamic_cast<King*>(grid[move.to.rank][move.to.file].get())->isUntouched()) {
      dynamic_cast<King*>(grid[move.to.rank][move.to.file].get())->touch();
      touchedKing = move.to;
    } 
  }
	
	bool opponentInCheck = false;
	std::vector<Move> opponentMoves = getLegalMoves(c ? White : Black);
	std::vector<Move> attacking = getAttackMoves(c);
	for (auto& m : attacking) {
		if (m.value == 69) {
			opponentInCheck = true;
			break;
		}
	}

	if (opponentMoves.empty() && opponentInCheck) {
		moveValue = 100000;
	}
	else if (opponentMoves.empty()) {
		moveValue = 0;
		for (auto& r : grid) {
			for (auto & p : r) {
				if (p && p->getColour() == c) {
					moveValue -= p->getValue();
				}
				else if (p) {
					moveValue += p->getValue();
				}
			}
		}
	}
	else {
		int bestOppMove = -100000;
		for (auto& m : opponentMoves) {
			bestOppMove = std::max(evaluateMove(m, c ? White : Black, depth - 1), bestOppMove);
		}
		moveValue -= bestOppMove;
		if (opponentInCheck) { ++moveValue; }
	} 
  
  // Move the piece back and add back the captured piece
  if (move.special == "en passant") {
    grid[move.from.rank][move.from.file] =
      std::move(grid[move.to.rank][move.to.file]);
    grid[move.from.rank][move.from.file]->setLocation(move.from);

    grid[move.from.rank][move.to.file] =
      std::move(pieceHolder);
  }
  else if (move.special == "castling") {
    dynamic_cast<King*>(grid[move.to.rank][move.to.file].get())->unTouch();
    grid[move.from.rank][move.from.file] =
      std::move(grid[move.to.rank][move.to.file]);
    grid[move.from.rank][move.from.file]->setLocation(move.from);

    if (move.to.file > move.from.file) {
      dynamic_cast<Rook*>(grid[move.from.rank][move.from.file + 1].get())->unTouch();
      grid[move.from.rank][7] =
        std::move(grid[move.from.rank][move.from.file + 1]);
      grid[move.from.rank][7]->setLocation(Square{7, move.from.rank});
    }
    else {
      dynamic_cast<Rook*>(grid[move.from.rank][move.from.file - 1].get())->unTouch();
      grid[move.from.rank][0] =
        std::move(grid[move.from.rank][move.from.file - 1]);
      grid[move.from.rank][0]->setLocation(Square{0, move.from.rank});
    }
  }
  else if (move.special.length() == 1) {
    grid[move.to.rank][move.to.file] = std::move(pieceHolder);
    grid[move.from.rank][move.from.file] = std::move(pieceHolderTheSecond);
  }
  else {
    if (touchedPawn.file != -1 && touchedPawn.rank != -1) {
      dynamic_cast<Pawn*>(grid[touchedPawn.rank][touchedPawn.file].get())->unTouch();
    }
    if (touchedRook.file != -1 && touchedRook.rank != -1) {
      dynamic_cast<Rook*>(grid[touchedRook.rank][touchedRook.file].get())->unTouch();
    }
    if (touchedKing.file != -1 && touchedKing.rank != -1) {
      dynamic_cast<King*>(grid[touchedKing.rank][touchedKing.file].get())->unTouch();
    } 

    grid[move.from.rank][move.from.file] =
      std::move(grid[move.to.rank][move.to.file]);
    grid[move.from.rank][move.from.file]->setLocation(move.from);

    grid[move.to.rank][move.to.file] =
      std::move(pieceHolder);
  }

  if (offPassant.file != -1 && offPassant.rank != -1) {
    dynamic_cast<Pawn*>(grid[offPassant.rank][offPassant.file].get())->setEnPassant(true);
  }

  return moveValue;
}

int StandardBoard::simulateMove(const Move& move, Colour c) {
  std::unique_ptr<Piece> pieceHolder; // Store the piece captured during move simulation
  std::unique_ptr<Piece> pieceHolderTheSecond; // Stores promoting pawn
  int highestPiece = 0; // Maximum value piece that colour c is attacking

  // Depending on the move performed, store the captured piece and put
  //  the board in the state after the move
  if (move.special == "en passant") {
    pieceHolder = std::move(grid[move.from.rank][move.to.file]);

    grid[move.to.rank][move.to.file] =
      std::move(grid[move.from.rank][move.from.file]);
  }
  else if (move.special == "castling") {
    grid[move.to.rank][move.to.file] =
      std::move(grid[move.from.rank][move.from.file]);
    if (move.to.file > move.from.file) {
      grid[move.from.rank][move.from.file + 1] =
        std::move(grid[move.from.rank][7]);
    }
    else {
      grid[move.from.rank][move.from.file - 1] =
        std::move(grid[move.from.rank][0]);
    }
  }
  else if (move.special.length() == 1) { // Promotion
    pieceHolder = std::move(grid[move.to.rank][move.to.file]); 
    pieceHolderTheSecond = std::move(grid[move.from.rank][move.from.file]); // Save the pawn

    // Place the promoted piece
    switch (move.special[0]) {
    case 'N':
      grid[move.to.rank][move.to.file] =
        std::make_unique<Knight>(this, pieceHolderTheSecond->getColour(), Square{ move.to.file, move.to.rank });
      break;
    case 'B':
      grid[move.to.rank][move.to.file] =
        std::make_unique<Bishop>(this, pieceHolderTheSecond->getColour(), Square{ move.to.file, move.to.rank });
      break;
    case 'R':
      grid[move.to.rank][move.to.file] =
        std::make_unique<Rook>(this, pieceHolderTheSecond->getColour(), Square{ move.to.file, move.to.rank });
      break;
    case 'Q':
      grid[move.to.rank][move.to.file] =
        std::make_unique<Queen>(this, pieceHolderTheSecond->getColour(), Square{ move.to.file, move.to.rank });
      break;
    }
  }
  else {
    pieceHolder = std::move(grid[move.to.rank][move.to.file]);

    grid[move.to.rank][move.to.file] =
      std::move(grid[move.from.rank][move.from.file]);
  }

  // Determine what moves the opposing colour is attacking
  std::vector<Move> opponentMoves = getAttackMoves(c);

  // For each of these moves
  for (auto m : opponentMoves) {
    // If the piece attacked has higher value 
    // than our stored highest value, replace it
    highestPiece = std::max(m.value, highestPiece);
  }

  // Move the piece back and add back the captured piece
  if (move.special == "en passant") {
    grid[move.from.rank][move.from.file] =
      std::move(grid[move.to.rank][move.to.file]);
    grid[move.from.rank][move.to.file] =
      std::move(pieceHolder);
  }
  else if (move.special == "castling") {
    grid[move.from.rank][move.from.file] =
      std::move(grid[move.to.rank][move.to.file]);
    if (move.to.file > move.from.file) {
      grid[move.from.rank][7] =
        std::move(grid[move.from.rank][move.from.file + 1]);
    }
    else {
      grid[move.from.rank][0] =
        std::move(grid[move.from.rank][move.from.file - 1]);
    }
  }
  else if (move.special.length() == 1) {
    grid[move.to.rank][move.to.file] = std::move(pieceHolder);
    grid[move.from.rank][move.from.file] = std::move(pieceHolderTheSecond);
  }
  else {
    grid[move.from.rank][move.from.file] =
      std::move(grid[move.to.rank][move.to.file]);
    grid[move.to.rank][move.to.file] =
      std::move(pieceHolder);
  }

  return highestPiece;
}


// Below is for evaluate move using evaluate position
// Now that the move is simulated, evaluate the position
//  int evaluation = 0;
//  std::vector<Move> nextMoves = getLegalMoves(c ? White : Black);
//  if (depth == 0 || nextMoves.empty()) { // Base case: depth is 0 or we have reached checkmate/stalemate
//    evaluation = evaluatePosition();
//  }
//  else {
//    auto it = nextMoves.begin(); // Must be at least one legal move, otherwise base case
//    evaluation = c ? evaluateMove(*it, White, depth - 1) : evaluateMove(*it, Black, depth - 1);
//    ++it;
//    for (; it != nextMoves.end(); ++it) {
//      evaluation = (c ? std::max(evaluation, evaluateMove(*it, White, depth - 1)) : std::min(evaluation, evaluateMove(*it, Black, depth - 1)));
//    }
//  }

// Sometimes the display doesn't load properly. Also useful when debugging with gdb
void StandardBoard::refreshDisplays() {
  for (int f = 0; f < getNumFile(); ++f) {
    for (int r = 0; r < getNumRank(); ++r) {
      notifyDisplays(Square{ f, r });
    }
  }
  outputDisplays();
}