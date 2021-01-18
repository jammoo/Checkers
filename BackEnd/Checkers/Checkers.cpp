#include <iostream>
#include <tuple>

using std::cout;
using std::pair;
using std::make_pair;

class Piece {
	bool white;
public:
	Piece(bool isWhite) {
		this->white = isWhite;
	}
	virtual pair<int, int>* getAvailableMoves() {};
	virtual pair<int, int>* getAvailableAttacks() {};
	bool isWhite() {
		return this->white == true;
	}
};

class Men : public Piece {
public:
	using Piece::Piece;
	pair<int, int>* getAvailableMoves() {
		if (this->isWhite()) {
			pair<int, int> am[2] = { make_pair(1, -1), make_pair(1, 1) };
			return am;
		}
		pair<int, int> am[2] = { make_pair(-1, -1), make_pair(-1, 1) };
		return am;
	}
	pair<int, int>* getAvailableAttacks() {
		if (this->isWhite()) {
			pair<int, int> aa[2] = { make_pair(2, -2), make_pair(2, 2) };
			return aa;
		}
		pair<int, int> aa[2] = { make_pair(-2, -2), make_pair(-2, 2) };
		return aa;
	}
};

class King : public Piece {
public:
	using Piece::Piece;
	pair<int, int>* getAvailableMoves() {
		pair<int, int> am[4] = { make_pair(-1, -1), make_pair(-1, 1), make_pair(1, -1), make_pair(1, 1) };
		return am;
	}
	pair<int, int>* getAvailableAttacks() {
		pair<int, int> aa[4] = { make_pair(-2, -2), make_pair(-2, 2), make_pair(2, -2), make_pair(2, 2) };
		return aa;
	}
};

class Tile {
	int rank;
	int file;
	Piece* currentOccupant;
public:
	Tile(int rank, int file, Piece* currentOccupant) {
		this->rank = rank;
		this->file = file;
		this->currentOccupant = currentOccupant;
	};

	bool isEmpty() {
		return currentOccupant == NULL;
	}

	bool whiteOccupied() {
		// check if the tile is empty
		if (not isEmpty()) {
			// if the tile is occupied, return true iff the occupant is white
			return (*currentOccupant).isWhite();
		}
		// if tile is empty return false
		return false;
	}

	bool blackOccupied() {
		// check if the tile is empty
		if (not isEmpty()) {
			// if the tile is occupied, return true iff the occupant is not white
			return not (*currentOccupant).isWhite();
		}
		// if tile is empty return false
		return false;
	}
};

class Board {
	Piece* tiles[8][8];
	bool whiteTurn;
	int numWhitePieces;
	int numBlackPieces;
public:
	Board() {
		this->setUp();
	}

	void setUp() {
		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				if ((rank == 0 && file % 2 == 1) || (rank == 1 && file % 2 == 0) || (rank == 2 && file % 2 == 1)) {
					// Make tiles[rank][file] a new Tile occupied by white Men
					this->tiles[rank][file] = new Men(true);
				}
				else if ((rank == 5 && file % 2 == 0) || (rank == 6 && file % 2 == 1) || (rank == 7 && file % 2 == 0)) {
					// Make tiles[rank][file] a new Tile occupied by black Men
					this->tiles[rank][file] = new Men(false);
				}
				else {
					// Make tiles[rank][file] a new Tile unoccupied
					this->tiles[rank][file] = NULL;
				}
			}
		}
		setWhiteTurn(false);
		setNumWhitePieces(12);
		setNumBlackPieces(12);
	}

	Piece** getTiles() {
		return this->tiles;
	}

	bool checkmate() {
		return this->numWhitePieces == 0 || this->numBlackPieces == 0;
	}

	void decrementWhite() {
		this->numWhitePieces--;
	}

	void decrementBlack() {
		this->numBlackPieces--;
	}

	bool isWhiteTurn() {
		return this->whiteTurn;
	}

	void setWhiteTurn(bool whiteTurn) {
		this->whiteTurn = whiteTurn;
	}

	int getNumWhitePieces() {
		return this->numWhitePieces;
	}

	int getNumBlackPieces() {
		return this->numBlackPieces;
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
	Board* b = new Board();
	Piece** t = b->getTiles();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (typeid(t[i][j]).name() == "NULL") {
				cout << " ";
			}
			else if (typeid(t[i][j]).name() == "Men") {
				cout << "M";
			}
			else if (typeid(t[i][j]).name() == "King") {
				cout << "K";
			}
			cout << " ";
		}
		cout << "\n";
	}
	cout << 

	system("pause>0");
}

