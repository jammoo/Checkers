#include <iostream>

using std::cout;

class Board {
	Tile tiles[8][8] ;
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

