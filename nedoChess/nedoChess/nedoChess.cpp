#include <string>
#include <iostream>
#include <vector>

using namespace std;
/*
bishop - слон; 
rook - ладья 
pawn - пешка 
knight- конь 
*/
struct pos {
	int x;
	int y;
};

void _clear(int index, vector<pos>* allSteps) {
	for (int i = index; i < (*allSteps).size(); i++) {
		(*allSteps).at(i).x = -1;
	}
}

vector<pos> bishop(int x, int y) {
	vector <pos> allSteps(14);
	int index = 0;
	for (int x1 = -8; x1 < 8; x1++) {
		if (x1 != 0) {
			if (x + x1 < 8 && x + x1 >= 0 && y + x1 < 8 && y + x1 >= 0) {
				allSteps.at(index).x = x + x1;
				allSteps.at(index).y = y + x1;
				index++;
			}

			if (x + x1 < 8 && x + x1 >= 0 && y - x1 < 8 && y - x1 >= 0) {
				allSteps.at(index).x = x + x1;
				allSteps.at(index).y = y - x1;
				index++;
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}
vector<pos> rook(int x, int y) {
	vector <pos> allSteps(14);
	int index = 0;
	for (int x1 = -8; x1 < 8; x1++) {
		if (x1 != 0) {
			if (x + x1 < 8 && x + x1 >= 0) {
				allSteps.at(index).x = x + x1;
				allSteps.at(index).y = y;
				index++;
			}

			if (y + x1 < 8 && y + x1 >= 0) {
				allSteps.at(index).x = x;
				allSteps.at(index).y = y + x1;
				index++;
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}

vector<pos> knight(int x, int y) {

	vector<pos> allSteps(8);
	int index = 0;
	for (int x1 = -2; x1 <= 2; x1++) {
		for (int y1 = -2; y1 <= 2; y1++) {
			if (x1 != 0 && y1 != 0 && abs(x1) != abs(y1)) {
				if (x + x1 >= 0 && x + x1 < 8 && y + y1 >= 0 && y + y1 < 8) {
					allSteps.at(index).x = x1 + x;
					allSteps.at(index).y = y + y1;
					index++;
				}
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}



vector<pos> pawn(int x, int y) {

	vector<pos> allSteps(2);
	allSteps.at(1).x = -1;

	allSteps.at(0).x = x;
	allSteps.at(1).y = y + 1;

	if (y == 1) {
		allSteps.at(1).x = x;
		allSteps.at(1).y = y + 2;
	}
	return allSteps;
}

enum chessPieces {
	Bishop = 0,
	Rook = 1,
	Pawn = 2,
	Knight = 3,
};

void printOfSteps(int x, int y, chessPieces piece) {
	vector<pos> allSteps;
	switch (piece)
	{
	case chessPieces::Bishop:
		cout << " \n\nслон:";
		allSteps = bishop(x, y);
		break;
	case chessPieces::Knight:
		cout << " \n\nконь:";
		allSteps = knight(x, y);
		break;
	case chessPieces::Pawn:
		cout << " \n\nпешка:";
		allSteps = pawn(x, y);
		break;
	case chessPieces::Rook:
		cout << " \n\nладья:";
		allSteps = rook(x, y);
		break;
	default:
		cout << "error, no this index in 'chessPieces'";
		break;
	}
	for (auto i : allSteps) {
		if (i.x == -1) {
			continue;
		}
		cout << "\n\nx: " << i.x << "\ny: " << i.y;
	}
}

void initXY(int* x, int* y) {
	while (true) {
		cout << "введи х: ";
		cin >> *x;
		cout << "введи y: ";
		cin >> *y;
;		if (*x < 8 && *x >= 0 && *y < 8 && *y >= 0) {
			break;
		}
		else {
			cout << "ti tupoi normalno pishi\n";
		}
	}
}

int main() {	
	setlocale(LC_ALL, "RUSSIAN");
	int y, x;
	initXY(&x, &y);
	printOfSteps(x, y, chessPieces::Bishop);
	printOfSteps(x, y, chessPieces::Knight);
	printOfSteps(x, y, chessPieces::Pawn);
	printOfSteps(x, y, chessPieces::Rook);
}
