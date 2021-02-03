#include <iostream>
#include <tuple>
#include <typeinfo>

using std::cout;
using std::pair;
using std::make_pair;
using std::endl;

class Piece {
	bool white;
public:
	Piece() {} // look into why the code needs the default constructor
	Piece(bool isWhite) {
		this->white = isWhite;
	}
	virtual pair<int, int>* getAvailableMoves() = 0;
	virtual pair<int, int>* getAvailableAttacks() = 0;
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

class NullPiece : public Piece {
public:
	using Piece::Piece;
	pair<int, int>* getAvailableMoves() {
		return NULL;
	}

	pair<int, int>* getAvailableAttacks() {
		return NULL;
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



class Board {
	//Piece* tiles[8][8]; -> this is what should be in the final version, remove the public copy when ready to uncomment
	bool whiteTurn;
	int numWhitePieces;
	int numBlackPieces;
public:
	Piece** tiles;

	void setUp() {
		this->tiles = (Piece**)calloc(64, sizeof(Piece));
		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				if ((rank == 0 && file % 2 == 1) || (rank == 1 && file % 2 == 0) || (rank == 2 && file % 2 == 1)) {
					// Make tiles[rank][file] a new Tile occupied by white Men
					this->tiles[rank * 8 + file] = new Men(true);
				}
				else if ((rank == 5 && file % 2 == 0) || (rank == 6 && file % 2 == 1) || (rank == 7 && file % 2 == 0)) {
					// Make tiles[rank][file] a new Tile occupied by black Men
					this->tiles[rank * 8 + file] = new Men(false);
				}
				else {
					// Make tiles[rank][file] a new Tile unoccupied
					//this->tiles[rank * file] = NULL;
					this->tiles[rank * 8 + file] = NULL; // new NullPiece();
				}
			}
		}
		setWhiteTurn(false);
		setNumWhitePieces(12);
		setNumBlackPieces(12);
	}

	void cleanUp() {
		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				delete(this->tiles[rank * 8 + file]);
			}
		}
		free(this->tiles);
	}

	Piece** getTiles() {
		return (Piece**)this->tiles;
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

	bool isEmpty(int rank, int file) {
		return typeid(tiles[rank * 8 + file]) == typeid(NullPiece);
	}

	bool whiteOccupied(int rank, int file) {
		// check if the tile is empty
		if (not isEmpty(rank, file)) {
			// if the tile is occupied, return true iff the occupant is white
			return tiles[rank][file].isWhite();
		}
		// if tile is empty return false
		return false;
	}

	bool blackOccupied(int rank, int file) {
		// check if the tile is empty
		if (not isEmpty(rank, file)) {
			// if the tile is occupied, return true iff the occupant is not white
			return tiles[rank][file].isWhite();
		}
		// if tile is empty return false
		return false;
	}

};

int main()
{
	cout << "Creating Board\n";

	Board* b = new Board();
	b->setUp();

	Piece** t = b->getTiles();
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (t[i * 8 + j] == NULL) {
				cout << " ";
			}
			else if (typeid(*t[i * 8 + j]) == typeid(Men)) {
				cout << "M";
			}
			else if (typeid(*t[i * 8 + j]) == typeid(King)) {
				cout << "K";
			}
			cout << " ";
		}
		cout << "\n";
	}

	// free and delete allocated memory
	b->cleanUp();
	delete(b);

	cout << system("pause>0");
}

