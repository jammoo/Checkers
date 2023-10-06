#include <iostream>
#include <tuple>
#include <typeinfo>

using std::cout;
using std::pair;
using std::make_pair;
using std::endl;
using std::abs;

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

	void setWhiteTurn(bool whiteTurn) {
		this->whiteTurn = whiteTurn;
	}

	void alternateWhiteTurn() {
		this->setWhiteTurn(!this->isWhiteTurn());
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

	// Assume pm is memory allocated for four elements
	void possibleMoves(pair<int, int>* pm, int rank, int file) {
		if (typeid(*this->getTiles()[rank * 8 + file]) == typeid(Men)) {
			possibleMovesMen(pm, rank, file);
		}
		else if (typeid(*this->getTiles()[rank * 8 + file]) == typeid(King)) {
			possibleMovesKing(pm, rank, file);
		}
	}

	// Assume pa is memory allocated for four elements
	void possibleAttacks(pair<int, int>* pa, int rank, int file) {
		if (typeid(*this->getTiles()[rank * 8 + file]) == typeid(Men)) {
			possibleAttacksMen(pa, rank, file);
		}
		else if (typeid(*this->getTiles()[rank * 8 + file]) == typeid(King)) {
			possibleAttacksKing(pa, rank, file);
		}
	}

	// Assume pm is memory allocated for four elements
	void possibleMovesKing(pair<int, int>* pm, int rank, int file) {
		if (this->isEmpty(rank, file)) {
			pm[0] = make_pair(0, 0);
			pm[1] = make_pair(0, 0);
			pm[2] = make_pair(0, 0);
			pm[3] = make_pair(0, 0);
		}
		else {
			pm[0] = make_pair(-1, -1);
			pm[1] = make_pair(-1, 1);
			pm[2] = make_pair(1, -1);
			pm[3] = make_pair(1, 1);
		}
	}

	// Assume pa is memory allocated for four elements
	void possibleAttacksKing(pair<int, int>* pa, int rank, int file) {
		if (this->isEmpty(rank, file)) {
			pa[0] = make_pair(0, 0);
			pa[1] = make_pair(0, 0);
			pa[2] = make_pair(0, 0);
			pa[3] = make_pair(0, 0);
		}
		else {
			pa[0] = make_pair(-2, -2);
			pa[1] = make_pair(-2, 2);
			pa[2] = make_pair(2, -2);
			pa[3] = make_pair(2, 2);
		}
	}

	// Assume pm is memory allocated for four elements
	void possibleMovesMen(pair<int, int>* pm, int rank, int file) {
		if (this->whiteOccupied(rank, file)) {
			pm[0] = make_pair(0, 0);
			pm[1] = make_pair(0, 0);
			pm[2] = make_pair(1, -1);
			pm[3] = make_pair(1, 1);
		}
		else if (this->blackOccupied(rank, file)) {
			pm[0] = make_pair(-1, -1);
			pm[1] = make_pair(-1, 1);
			pm[2] = make_pair(0, 0);
			pm[3] = make_pair(0, 0);
		}
		else {
			pm[0] = make_pair(0, 0);
			pm[1] = make_pair(0, 0);
			pm[2] = make_pair(0, 0);
			pm[3] = make_pair(0, 0);
		}
	}

	// Assume pa is memory allocated for four elements
	void possibleAttacksMen(pair<int, int>* pa, int rank, int file) {
		if (this->whiteOccupied(rank, file)) {
			pa[0] = make_pair(0, 0);
			pa[1] = make_pair(0, 0);
			pa[2] = make_pair(2, -2);
			pa[3] = make_pair(2, 2);
		}
		else if (this->blackOccupied(rank, file)) {
			pa[0] = make_pair(-2, -2);
			pa[1] = make_pair(-2, 2);
			pa[2] = make_pair(0, 0);
			pa[3] = make_pair(0, 0);
		}
		else {
			pa[0] = make_pair(0, 0);
			pa[1] = make_pair(0, 0);
			pa[2] = make_pair(0, 0);
			pa[3] = make_pair(0, 0);
		}
	}

	// Assume am is memory allocated for four elements
	void actualMoves(pair<int, int>* am, int rank, int file) {
		this->possibleMoves(am, rank, file);
		for (int i = 0; i < 4; i++) {
			if (rank + am[i].first < 0 || rank + am[i].first > 7 || file + am[i].second < 0 || file + am[i].second  > 7) {
				am[i] = make_pair(0, 0);
			}
			if (!this->isEmpty(rank + am[i].first, file + am[i].second)) {
				am[i] = make_pair(0, 0);
			}
		}
	}

	// Assume aa is memory allocated for four elements
	void actualAttacks(pair<int, int>* aa, int rank, int file) {
		this->possibleAttacks(aa, rank, file);
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
	}

	// Assume aa is memory allocated for four elements
	void actualActions(pair<int, int>* aa, int rank, int file) {
		bool availableAttack = false;
		this->actualAttacks(aa, rank, file);
		for (int i = 0; i < 4; i++) {
			if (aa[i] != make_pair(0, 0)) {
				availableAttack = true;
			}
		}
		if (!availableAttack) {
			this->actualMoves(aa, rank, file);
		}
	}

	void turn(pair<int, int> vector, int rank, int file) {
		if (abs(vector.first) == 1 && abs(vector.second) == 1) {
			move(vector, rank, file);
		}
		else if (abs(vector.first) == 2 && abs(vector.second) == 2) {
			pair<int, int> aa[4];
			bool attackAvailable = false;
			do {
				attack(vector, rank, file);
				rank = rank + vector.first;
				file = file + vector.second;
				this->actualAttacks(aa, rank, file);
				for (int i = 0; i < 4; i++) {
					if (aa[i] != make_pair(0, 0)) {
						attackAvailable = true;
					}
				}
				// Waits for user to select new attack if have possible attack------------------------------------------------------------------------------
				if (attackAvailable = true) {



				}
			} while (attackAvailable);
		}
		this->alternateWhiteTurn();
	}

	// Assume valid move
	void move(pair<int, int> vector, int rank, int file) {
		this->getTiles()[(rank + vector.first) * 8 + (file + vector.second)] = this->getTiles()[rank * 8 + file];
		this->getTiles()[rank * 8 + file] = NULL;
	}

	// Assume valid attack
	void attack(pair<int, int> vector, int rank, int file) {
		this->getTiles()[(rank + vector.first) * 8 + (file + vector.second)] = this->getTiles()[rank * 8 + file];
		this->getTiles()[rank * 8 + file] = NULL;
		this->getTiles()[(rank + vector.first / 2) * 8 + (file + vector.second / 2)] = NULL;
		
		if (this->getTiles()[rank * 8 + file]->isWhite()) {
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

	/*
	pair<int, int>* am1 = b->actualMoves(2, 7);
	b->move(2, 7, am1[2]);
	pair<int, int>* am2 = b->actualMoves(3, 6);
	b->move(3, 6, am2[2]);
	pair<int, int>* aa1 = b->actualAttacks(5, 6);
	b->attack(5, 6, aa1[0]);
	pair<int, int>* aa2 = b->actualAttacks(2, 3);
	b->attack(2, 3, aa2[3]);
	*/

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
