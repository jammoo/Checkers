#include <iostream>
#include <tuple>

using std::cout;
using std::pair;
using std::make_pair;

class Piece {
	bool white;
public:
	Piece(bool isWhite) {
		white = isWhite;
	}
	virtual pair<int, int>* getAvailableMoves() = 0;
	virtual pair<int, int>* getAvailableAttacks() = 0;
	bool isWhite() {
		return white == true;
	}
};

class Men : public Piece {
	pair<int, int>* getAvailableMoves() {
		if (isWhite()) {
			pair<int, int> am[2] = {make_pair(1, -1), make_pair(1, 1)};
			return am;
		}
		pair<int, int> am[2] = {make_pair(-1, -1), make_pair(-1, 1)};
		return am;
	}
	pair<int, int>* getAvailableAttacks() {
		if (isWhite()) {
			pair<int, int> aa[2] = {make_pair(2, -2), make_pair(2, 2)};
			return aa;
		}
		pair<int, int> aa[2] = {make_pair(-2, -2), make_pair(-2, 2)};
		return aa;
	}
};

class King : public Piece {
	pair<int, int>* getAvailableMoves() {
		pair<int, int> am[4] = {make_pair(-1, -1), make_pair(-1, 1), make_pair(1, -1), make_pair(1, 1)};
		return am;
	}
	pair<int, int>* getAvailableAttacks() {
		pair<int, int> aa[4] = {make_pair(-2, -2), make_pair(-2, 2), make_pair(2, -2), make_pair(2, 2)};
		return aa;
	}
};

class Tile {
	int rank;
	int file;
	bool isWhite;
	Piece currentOccupant;
public:
	Tile(int rank, int file, bool isWhite, Piece currentOccupant) {
		this->rank = rank;
		this->file = file;
		this->isWhite = isWhite;
		this->currentOccupant = currentOccupant;
	};

	bool isEmpty() {
		// return true iff the pointer to an object returns 0, indicating that it is empty
		return &currentOccupant == 0;
	}

	bool whiteOccupied() {
		// check if the tile is empty
		if (not isEmpty()) {
			// if the tile is occupied, return true iff the occupant is white
			return currentOccupant.isWhite();
		}
		// if tile is epty return false
		return false;
	}

	bool blackOccupied() {
		// check if the tile is empty
		if (not isEmpty()) {
			// if the tile is occupied, return true iff the occupant is not white
			return not currentOccupant.isWhite();
		}
		// if tile is epty return false
		return false;
	}

};

class Board {
	Tile tiles[8][8];
	bool whiteTurn;
	int numWhitePieces;
	int numBlackPieces;
public:
	Board() {
		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				if ((rank == 0 && file % 2 == 1) || (rank == 1 && file % 2 == 0) || (rank == 2 && file % 2 == 1)) {
					// Make tiles[rank][file] a new Tile occupied by white Men

				}
				else if ((rank == 5 && file % 2 == 0) || (rank == 6 && file % 2 == 1) || (rank == 7 && file % 2 == 0)) {
					// Make tiles[rank][file] a new Tile occupied by black Men

				}
				else {
					// Make tiles[rank][file] a new Tile unoccupied

				}
			}
		}
		setWhiteTurn(false);
		setNumWhitePieces(12);
		setNumBlackPieces(12);
	}

	bool checkmate() {
		return numWhitePieces == 0 || numBlackPieces == 0;
	}

	void decrementWhite() {
		numWhitePieces--;
	}

	void decrementBlack() {
		numBlackPieces--;
	}

	bool isWhiteTurn() {
		return this->whiteTurn;
	}

	void setWhiteTurn(bool whiteTurn) {
		this->whiteTurn = whiteTurn;
	}

	int getNumWhitePieces() {
		return numWhitePieces;
	}

	int getNumBlackPieces() {
		return numBlackPieces;
	}

	void setNumWhitePieces(int numWhitePieces) {
		this->numWhitePieces = numWhitePieces;
	}

	void setNumBlackPieces(int numBlackPieces) {
		this->numBlackPieces = numBlackPieces;
	}

};


int main()
{
	cout << "Hello World!\n";

	system("pause>0");
}

