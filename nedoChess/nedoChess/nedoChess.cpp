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

vector<pos> bishop(pos position) {
	vector <pos> allSteps(14);
	int index = 0;
	for (int x = -8; x < 8; x++) {
		if (x != 0) {
			if (position.x + x < 8 && position.x + x >= 0 && position.y + x < 8 && position.y + x >= 0) {
				allSteps.at(index).x = position.x + x;
				allSteps.at(index).y = position.y + x;
				index++;
			}

			if (position.x + x < 8 && position.x + x >= 0 && position.y - x < 8 && position.y - x >= 0) {
				allSteps.at(index).x = position.x + x;
				allSteps.at(index).y = position.y - x;
				index++;
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}
vector<pos> rook(pos position) {
	vector <pos> allSteps(14);
	int index = 0;
	for (int x = -8; x < 8; x++) {
		if (x != 0) {
			if (position.x + x < 8 && position.x + x >= 0) {
				allSteps.at(index).x = position.x + x;
				allSteps.at(index).y = position.y;
				index++;
			}

			if (position.y + x < 8 && position.y + x >= 0) {
				allSteps.at(index).x = position.x;
				allSteps.at(index).y = position.y + x;
				index++;
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}

vector<pos> knight(pos position) {

	vector<pos> allSteps(8);
	int index = 0;
	for (int x = -2; x <= 2; x++) {
		for (int y = -2; y <= 2; y++) {
			if (x != 0 && y != 0 && abs(x) != abs(y)) {
				if (position.x + x >= 0 && position.x + x < 8 && position.y + y >= 0 && position.y + y < 8) {
					allSteps.at(index).x = position.x + x;
					allSteps.at(index).y = position.y + y;
					index++;
				}
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}



vector<pos> pawn(pos position) {

	vector<pos> allSteps(2);
	allSteps.at(1).x = -1;

	allSteps.at(0).x = position.x;
	allSteps.at(0).y = position.y + 1;

	if (position.y == 1) {
		allSteps.at(1).x = position.x;
		allSteps.at(1).y = position.y + 2;
	}
	return allSteps;
}

enum chessPieces {
	Bishop = 0,
	Rook = 1,
	Pawn = 2,
	Knight = 3,
};

void printOfSteps(pos position, chessPieces piece) {
	vector<pos> allSteps;
	switch (piece)
	{
	case chessPieces::Bishop:
		cout << " \n\nслон:";
		allSteps = bishop(position);
		break;
	case chessPieces::Knight:
		cout << " \n\nконь:";
		allSteps = knight(position);
		break;
	case chessPieces::Pawn:
		cout << " \n\nпешка:";
		allSteps = pawn(position);
		break;
	case chessPieces::Rook:
		cout << " \n\nладья:";
		allSteps = rook(position);
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

void initXY(pos *position) {
	while (true) {
		cout << "введи х: ";
		cin >> (*position).x;
		cout << "введи y: ";
		cin >> (*position).y;
;		if ((*position).x < 8 && (*position).x >= 0 && (*position).y < 8 && (*position).y >= 0) {
			break;
		}
		else {
			cout << "ti tupoi normalno pishi\n";
		}
	}
}

int main() {	
	setlocale(LC_ALL, "RUSSIAN");
	pos position;
	initXY(&position);
	printOfSteps(position, chessPieces::Bishop);
	printOfSteps(position, chessPieces::Knight);
	printOfSteps(position, chessPieces::Pawn);
	printOfSteps(position, chessPieces::Rook);
}
