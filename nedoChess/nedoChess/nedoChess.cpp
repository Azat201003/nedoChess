#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum chessPieces {
	none   = 0,
	Bishop = 1,
	Rook   = 2,
	Pawn   = 3,
	Knight = 4,
	King   = 5,
	Queen  = 6,
};

enum Color {
	white = 0,
	black = 1
};

struct Figure {
	Color color;
	chessPieces piece;
};

/*
bishop - слон; 
rook   - ладья 
pawn   - пешка 
knight - конь 
king   - король 
queen  - ферзь
*/

struct pos {
	int x;
	int y;
};

bool isSpace(pos newPos, vector<vector<Figure>> chessField, Color color) {
	if (newPos.x >= 0 && newPos.x < 8 && newPos.y >= 0 && newPos.y < 8) {
		return ((chessField.at(newPos.x).at(newPos.y).color != color) || chessField.at(newPos.x).at(newPos.y).piece == chessPieces::none);
	}
	return false;
}

vector<pos> bishop(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector <pos> allSteps;
	pos newPos;
	for (int offset = -7; offset <= 7; offset++) {
		if (offset != 0) {
			newPos.x = position.x + offset;

			newPos.y = position.y + offset;
			if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);
			newPos.y = position.y - offset;
			if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);
		}
	}

	return allSteps;
}
vector<pos> rook(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector <pos> allSteps;
	pos newPos;
	for (int offset = -7; offset <= 7; offset++) {
		if (offset != 0) {
			newPos.x = position.x + offset;
			newPos.y = position.y;
			if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);

			newPos.x = position.x;
			newPos.y = position.y + offset;
			if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);
		}
	}

	return allSteps;
}

vector<pos> knight(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector<pos> allSteps;
	pos newPos;
	for (int x = -2; x <= 2; x++) {
		for (int y = -2; y <= 2; y++) {
			if (x != 0 && y != 0 && abs(x) != abs(y)) {
				newPos.x = position.x + x;
				newPos.y = position.y + y;
				if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);
			}
		}
	}

	return allSteps;
}



vector<pos> pawn(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector<pos> allSteps;
	pos newPos;

	newPos.x = position.x;
	newPos.y = position.y + 1;
	if(isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);

	if (position.y == 1) {
		newPos.y = position.y + 2;
		allSteps.push_back(newPos);
	}
	return allSteps;
}

vector<pos> king(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector<pos> allSteps;
	pos newPos;

	for (int offset = -1; offset <= 1; offset += 2) {
		newPos.x = position.x + offset;

		newPos.y = position.y + offset;
		if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);

		newPos.y = position.y - offset;
		if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);

		newPos.y = position.y;
		if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);

		newPos.x = position.x;
		newPos.y = position.y + offset;
		if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);
	}

	return allSteps;
}

vector<pos> queen(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector<pos> allSteps;
	pos newPos;

	for (int offset = -7; offset <= 7; offset++) {
		if (offset != 0) {
			newPos.x = position.x + offset;

			newPos.y = position.y + offset;
			if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);

			newPos.y = position.y - offset;
			if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);

			newPos.y = position.y;
			if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);

			newPos.x = position.x;
			newPos.y = position.y + offset;
			if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);
		}
	}

	return allSteps;
}

void printOfSteps(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector<pos> allSteps;
	switch (figure.piece)
	{
	case chessPieces::Bishop:
		cout << " \n\nслон:";
		allSteps = bishop(position, chessField, figure);
		break;
	case chessPieces::Knight:
		cout << " \n\nконь:";
		allSteps = knight(position, chessField, figure);
		break;
	case chessPieces::Pawn:
		cout << " \n\nпешка:";
		allSteps = pawn(position, chessField, figure);
		break;
	case chessPieces::Rook:
		cout << " \n\nладья:";
		allSteps = rook(position, chessField, figure);
		break;
	case chessPieces::King:
		cout << " \n\nкороль:";
		allSteps = king(position, chessField, figure);
		break;
	case chessPieces::Queen:
		cout << " \n\nферзь:";
		allSteps = queen(position, chessField, figure);
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

	Figure figure;
	Figure noneFigure;
	noneFigure.color = Color::white;
	noneFigure.piece = chessPieces::none;

	figure.color = Color::white;

	vector<vector<Figure>> chessField(8, vector<Figure>(8, noneFigure));

	initXY(&position);

	chessField.at(position.x).at(position.y) = figure;
	chessField.at(position.x).at(position.y+1) = figure;

	figure.piece = chessPieces::Bishop;
	printOfSteps(position, chessField, figure);
	figure.piece = chessPieces::King;
	printOfSteps(position, chessField, figure);
	figure.piece = chessPieces::Knight;
	printOfSteps(position, chessField, figure);
	figure.piece = chessPieces::Rook;
	printOfSteps(position, chessField, figure);
	figure.piece = chessPieces::Pawn;
	printOfSteps(position, chessField, figure);
	figure.piece = chessPieces::Queen;
	printOfSteps(position, chessField, figure);
}
