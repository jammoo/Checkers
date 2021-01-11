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
		whiteTurn = false;
		numWhitePieces = 12;
		numBlackPieces = 12;
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
};

int main()
{
	cout << "Hello World!\n";

	system("pause>0");
}

