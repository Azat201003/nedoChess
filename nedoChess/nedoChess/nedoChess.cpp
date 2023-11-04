#include <string>
#include <iostream>
#include <vector>

using namespace std;

void _clear(int index, vector<vector<int>>* allSteps) {
	for (int i = index; i < (*allSteps).size(); i++) {
		(*allSteps).at(i).at(0) = -1;
	}
}

vector<vector<int>> bishop(int x, int y) {
	vector <vector <int>> allSteps(14, vector<int>(2));
	int index = 0;
	for (int x1 = -8; x1 < 8; x1++) {
		if (x1 != 0) {
			if (x + x1 < 8 && x + x1 >= 0 && y + x1 < 8 && y + x1 >= 0) {
				allSteps.at(index).at(0) = x + x1;
				allSteps.at(index).at(1) = y + x1;
				index++;
			}

			if (x + x1 < 8 && x + x1 >= 0 && y - x1 < 8 && y - x1 >= 0) {
				allSteps.at(index).at(0) = x + x1;
				allSteps.at(index).at(1) = y - x1;
				index++;
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}
vector<vector<int>> rook(int x, int y) {
	vector <vector <int>> allSteps(14, vector<int>(2));
	int index = 0;
	for (int x1 = -8; x1 < 8; x1++) {
		if (x1 != 0) {
			if (x + x1 < 8 && x + x1 >= 0) {
				allSteps.at(index).at(0) = x + x1;
				allSteps.at(index).at(1) = y;
				index++;
			}

			if (y + x1 < 8 && y + x1 >= 0) {
				allSteps.at(index).at(0) = x;
				allSteps.at(index).at(1) = y + x1;
				index++;
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}

vector<vector<int>> knight(int x, int y) {

	vector<vector<int>> allSteps(8, vector<int>(2));
	int index = 0;
	for (int x1 = -2; x1 <= 2; x1++) {
		for (int y1 = -2; y1 <= 2; y1++) {
			if (x1 != 0 && y1 != 0 && abs(x1) != abs(y1)) {
				if (x + x1 >= 0 && x + x1 < 8 && y + y1 >= 0 && y + y1 < 8) {
					allSteps.at(index).at(0) = x1 + x;
					allSteps.at(index).at(1) = y + y1;
					index++;
				}
			}
		}
	}
	_clear(index, &allSteps);

	return allSteps;
}



vector<vector<int>> pawn(int x, int y) {

	vector<vector<int>> allSteps(2, vector<int>(2));
	allSteps.at(1).at(0) = -1;

	allSteps.at(0).at(0) = x;
	allSteps.at(0).at(1) = y + 1;

	if (y == 1) {
		allSteps.at(1).at(0) = x;
		allSteps.at(1).at(1) = y + 2;
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
	vector<vector<int>> allSteps;
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
		if (i.at(0) == -1) {
			continue;
		}
		cout << "\n\nx: " << i.at(0) << "\ny: " << i.at(1);
	}
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int y, x;
	while (true) {

		cin >> x >> y;
		if (x < 8 && x >= 0 && y < 8 && y >= 0) {
			break;
		}
		else {
			cout << "ti tupoi normalno pishi\n";
		}
	}
	printOfSteps(x, y, chessPieces::Bishop);
	printOfSteps(x, y, chessPieces::Knight);
	printOfSteps(x, y, chessPieces::Pawn);
	printOfSteps(x, y, chessPieces::Rook);
}
