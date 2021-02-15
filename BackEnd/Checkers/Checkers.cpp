#include <iostream>
#include <tuple>
#include <typeinfo>

using std::cout;
using std::pair;
using std::make_pair;
using std::endl;

class Piece {
protected:
	bool white;
public:
	Piece(bool isWhite) {
		this->white = isWhite;
	}
	virtual bool isWhite() {
		return this->white == true;
	};
};

class Men : public Piece {
	using Piece::Piece;
};

class King : public Piece {
	using Piece::Piece;
};


class Board {
	Piece** tiles;
	bool whiteTurn;
	int numWhitePieces;
	int numBlackPieces;
public:

	Board() {
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

	~Board() {
		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				delete(this->tiles[rank * 8 + file]);
			}
		}
		free(this->tiles);
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

	void alternateWhiteTurn(bool whiteTurn) {
		this->whiteTurn = !whiteTurn;
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

	void decrementNumWhitePieces() {
		this->setNumWhitePieces(this->getNumWhitePieces() - 1);
	}

	void decrementNumBlackPieces() {
		this->setNumBlackPieces(this->getNumBlackPieces() - 1);
	}

	bool isEmpty(int rank, int file) {
		return this->getTiles()[rank * 8 + file] == NULL;
	}

	bool whiteOccupied(int rank, int file) {
		// check if the tile is empty
		if (not isEmpty(rank, file)) {
			// if the tile is occupied, return true iff the occupant is white
			return tiles[rank * 8 + file]->isWhite();
		}
		// if tile is empty return false
		return false;
	}

	bool blackOccupied(int rank, int file) {
		// check if the tile is empty
		if (not isEmpty(rank, file)) {
			// if the tile is occupied, return true iff the occupant is not white
			return !(tiles[rank * 8 + file]->isWhite());
		}
		// if tile is empty return false
		return false;
	}

	pair<int, int>* possibleMoves(int rank, int file) {
		if (typeid(*this->getTiles()[rank * 8 + file]) == typeid(Men)) {
			return possibleMovesMen(rank, file);
		}
		else if (typeid(*this->getTiles()[rank * 8 + file]) == typeid(King)) {
			return possibleMovesKing(rank, file);
		}
		return NULL;
	}

	pair<int, int>* possibleAttacks(int rank, int file) {
		if (typeid(*this->getTiles()[rank * 8 + file]) == typeid(Men)) {
			return possibleAttacksMen(rank, file);
		}
		else if (typeid(*this->getTiles()[rank * 8 + file]) == typeid(King)) {
			return possibleAttacksKing(rank, file);
		}
		return NULL;
	}

	pair<int, int>* possibleMovesKing(int rank, int file) {
		pair<int, int> am[4] = { make_pair(-1, -1), make_pair(-1, 1), make_pair(1, -1), make_pair(1, 1) };
		return am;
	}

	pair<int, int>* possibleAttacksKing(int rank, int file) {
		pair<int, int> aa[4] = { make_pair(-2, -2), make_pair(-2, 2), make_pair(2, -2), make_pair(2, 2) };
		return aa;
	}

	pair<int, int>* possibleMovesMen(int rank, int file) {
		if (this->whiteOccupied(rank, file)) {
			pair<int, int> pm[4] = { make_pair(0, 0), make_pair(0, 0), make_pair(1, -1), make_pair(1, 1) };
			return pm;
		}
		else if (this->blackOccupied(rank, file)) {
			pair<int, int> pm[4] = { make_pair(-1, -1), make_pair(-1, 1), make_pair(0, 0), make_pair(0, 0) };
			return pm;
		}
		return NULL;
	}

	pair<int, int>* possibleAttacksMen(int rank, int file) {
		if (this->whiteOccupied(rank, file)) {
			pair<int, int> pa[4] = { make_pair(0, 0), make_pair(0, 0), make_pair(2, -2), make_pair(2, 2) };
			return pa;
		}
		else if (this->blackOccupied(rank, file)) {
			pair<int, int> pa[4] = { make_pair(-2, -2), make_pair(-2, 2), make_pair(0, 0), make_pair(0, 0) };
			return pa;
		}
		return NULL;
	}

	pair<int, int>* actualMoves(int rank, int file) {
		pair<int, int>* am;
		am = this->possibleMoves(rank, file);
		if (am == NULL) {
			return NULL;
		}
		for (int i = 0; i < 4; i++) {
			if (rank + am[i].first < 0 || rank + am[i].first > 7 || file + am[i].second < 0 || file + am[i].second  > 7) {
				am[i] = make_pair(0, 0);
			}
			if (!this->isEmpty(rank + am[i].first, file + am[i].second)) {
				am[i] = make_pair(0, 0);
			}
		}
		return am;
	}

	pair<int, int>* actualAttacks(int rank, int file) {
		pair<int, int>* aa;
		aa = this->possibleAttacks(rank, file);
		if (aa == NULL) {
			return NULL;
		}
		for (int i = 0; i < 4; i++) {
			if (rank + aa[i].first < 0 || rank + aa[i].first > 7 || file + aa[i].second < 0 || file + aa[i].second  > 7) {
				aa[i] = make_pair(0, 0);
			}
			if (!this->isEmpty(rank + aa[i].first, file + aa[i].second)) {
				aa[i] = make_pair(0, 0);
			}
			if (this->whiteOccupied(rank, file)) {
				if (!this->blackOccupied(rank + aa[i].first / 2, file + aa[i].second / 2)) {
					aa[i] = make_pair(0, 0);
				}
			}
			if (this->blackOccupied(rank, file)) {
				if (!this->whiteOccupied(rank + aa[i].first / 2, file + aa[i].second / 2)) {
					aa[i] = make_pair(0, 0);
				}
			}
		}
		return aa;
	}

	// Assume valid move
	void move(int rank, int file, pair<int, int> direction) {
		this->getTiles()[(rank + direction.first) * 8 + (file + direction.second)] = this->getTiles()[rank * 8 + file];
		this->getTiles()[rank * 8 + file] = NULL;
	}

	// Assume valid attack
	void attack(int rank, int file, pair<int, int> direction) {
		bool isWhite = this->getTiles()[rank * 8 + file]->isWhite();
		this->getTiles()[(rank + direction.first) * 8 + (file + direction.second)] = this->getTiles()[rank * 8 + file];
		this->getTiles()[rank * 8 + file] = NULL;
		this->getTiles()[(rank + direction.first / 2) * 8 + (file + direction.second / 2)] = NULL;
		if (isWhite) {
			decrementNumBlackPieces();
		}
		else {
			decrementNumWhitePieces();
		}
	}
};


int main()
{
	cout << "Creating Board\n";

	Board* b = new Board();

	Piece** t = b->getTiles();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (t[i * 8 + j] == NULL) {
				cout << " ";
			}
			else if (typeid(*t[i * 8 + j]) == typeid(Men)) {
				//cout << "M";
				if (t[i * 8 + j]->isWhite()) {
					cout << "W";
				}
				else {
					cout << "B";
				}
			}
			else if (typeid(*t[i * 8 + j]) == typeid(King)) {
				cout << "K";
			}
			cout << " ";
		}
		cout << "\n";
	}

	pair<int, int>* am1 = b->actualMoves(2, 7);
	b->move(2, 7, am1[2]);
	pair<int, int>* am2 = b->actualMoves(3, 6);
	b->move(3, 6, am2[2]);
	pair<int, int>* aa1 = b->actualAttacks(5, 6);
	b->attack(5, 6, aa1[0]);
	pair<int, int>* aa2 = b->actualAttacks(2, 3);
	b->attack(2, 3, aa2[3]);

	cout << "\n";
	cout << "\n";

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (t[i * 8 + j] == NULL) {
				cout << " ";
			}
			else if (typeid(*t[i * 8 + j]) == typeid(Men)) {
				//cout << "M";
				if (t[i * 8 + j]->isWhite()) {
					cout << "W";
				}
				else {
					cout << "B";
				}
			}
			else if (typeid(*t[i * 8 + j]) == typeid(King)) {
				cout << "K";
			}
			cout << " ";
		}
		cout << "\n";
	}

	cout << system("pause>0");
}