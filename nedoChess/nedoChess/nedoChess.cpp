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

string intToName(pos position) {
	string letters = "abcdefgh";
	string result;

	result = letters[position.x] + to_string(position.y + 1);

	return result;
}

int letterToPosX(char x) {
	string letters = "abcdefgh";
	for (int i=0; i < letters.length(); i++) {
		if (letters[i] == x) {
			return i;
		}
	}
}

pos nameToInt(string position) {
	pos result;

	result.x = letterToPosX(position[0]);
	char y[] = { position[1] };
	result.y = (stoi(y)) - 1;

	return result;
}



bool isSpace(pos newPos, vector<vector<Figure>> chessField, Color color) {
	if (newPos.x >= 0 && newPos.x < 8 && newPos.y >= 0 && newPos.y < 8) {
		return ((chessField.at(newPos.x).at(newPos.y).color != color) || chessField.at(newPos.x).at(newPos.y).piece == chessPieces::none);
	}
	return false;
}

void moveTry(pos position, pos offset, vector<bool> *permissiosToPass, vector<pos> *allSteps, int index, vector<vector<Figure>> chessField, Figure figure) {
	pos newPos;
	newPos.x = position.x - offset.x;
	newPos.y = position.y - offset.y;
	if (isSpace(newPos, chessField, figure.color) && permissiosToPass->at(index)) {
		allSteps->push_back(newPos);
		if (chessField.at(newPos.x).at(newPos.y).color != figure.color &&
			chessField.at(newPos.x).at(newPos.y).piece != chessPieces::none) permissiosToPass->at(index) = false;
	}
	else permissiosToPass->at(index) = false;
}

vector<pos> bishop(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector <pos> allSteps;
	pos newPos;
	vector<bool> permissiosToPass(4, true);
	pos offsetPos;

	for (int offset = 1; offset <= 7; offset++) {
		offsetPos.x = offset;
		offsetPos.y = offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 0, chessField, figure);

		offsetPos.x = -offset;
		offsetPos.y = -offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 1, chessField, figure);

		offsetPos.x = offset;
		offsetPos.y = -offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 2, chessField, figure);

		offsetPos.x = -offset;
		offsetPos.y = offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 3, chessField, figure);
	}

	return allSteps;
}
vector<pos> rook(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector <pos> allSteps;
	pos newPos;
	vector<bool> permissiosToPass(4, true);
	pos offsetPos;

	for (int offset = 1; offset <= 7; offset++) {
		offsetPos.x = offset;
		offsetPos.y = 0;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 0, chessField, figure);

		offsetPos.x = -offset;
		offsetPos.y = 0;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 1, chessField, figure);

		offsetPos.x = 0;
		offsetPos.y = offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 2, chessField, figure);

		offsetPos.x = 0;
		offsetPos.y = -offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 3, chessField, figure);
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
	if (isSpace(newPos, chessField, figure.color)) {
		if (chessField.at(newPos.x).at(newPos.y).color != figure.color &&
			chessField.at(newPos.x).at(newPos.y).piece != chessPieces::none) { 
		} else {
			allSteps.push_back(newPos);

			if (position.y == 1) {
				newPos.y = position.y + 2;
				if (isSpace(newPos, chessField, figure.color)) allSteps.push_back(newPos);
			}
		}
	}
	newPos.x = position.x + 1;
	newPos.y = position.y + 1;
	if (isSpace(newPos, chessField, figure.color)) {
		if (chessField.at(newPos.x).at(newPos.y).color != figure.color &&
			chessField.at(newPos.x).at(newPos.y).piece != chessPieces::none) {
			allSteps.push_back(newPos);
		}
	}

	newPos.x = position.x - 1;
	newPos.y = position.y + 1;
	if (isSpace(newPos, chessField, figure.color)) {
		if (chessField.at(newPos.x).at(newPos.y).color != figure.color &&
			chessField.at(newPos.x).at(newPos.y).piece != chessPieces::none) {
			allSteps.push_back(newPos);
		}
	}

	return allSteps;
}

vector<pos> king(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector<pos> allSteps;
	pos newPos;

	for (int offset = -1; offset <= 1; offset += 2) {
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

vector<pos> queen(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector<pos> allSteps;
	pos newPos;
	vector<bool> permissiosToPass(8, true);
	pos offsetPos;

	for (int offset = 1; offset <= 7; offset++) {
		offsetPos.x = offset;
		offsetPos.y = 0;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 0, chessField, figure);

		offsetPos.x = -offset;
		offsetPos.y = 0;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 1, chessField, figure);

		offsetPos.x = 0;
		offsetPos.y = offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 2, chessField, figure);

		offsetPos.x = 0;
		offsetPos.y = -offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 3, chessField, figure);

		offsetPos.x = offset;
		offsetPos.y = offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 4, chessField, figure);

		offsetPos.x = -offset;
		offsetPos.y = -offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 5, chessField, figure);

		offsetPos.x = offset;
		offsetPos.y = -offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 6, chessField, figure);

		offsetPos.x = -offset;
		offsetPos.y = offset;
		moveTry(position, offsetPos, &permissiosToPass, &allSteps, 7, chessField, figure);
	}

	return allSteps;
}

void printOfSteps(pos position, vector<vector<Figure>> chessField, Figure figure) {
	vector<pos> allSteps;
	switch (figure.piece)
	{
	case chessPieces::Bishop:
		cout << " \n\nслон:\n\n";
		allSteps = bishop(position, chessField, figure);
		break;
	case chessPieces::Knight:
		cout << " \n\nконь:\n\n";
		allSteps = knight(position, chessField, figure);
		break;
	case chessPieces::Pawn:
		cout << " \n\nпешка:\n\n";
		allSteps = pawn(position, chessField, figure);
		break;
	case chessPieces::Rook:
		cout << " \n\nладья:\n\n";
		allSteps = rook(position, chessField, figure);
		break;
	case chessPieces::King:
		cout << " \n\nкороль:\n\n";
		allSteps = king(position, chessField, figure);
		break;
	case chessPieces::Queen:
		cout << " \n\nферзь:\n\n";
		allSteps = queen(position, chessField, figure);
		break;
	default:
		cout << "error, no this index in 'chessPieces'";
		break;
	}
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			bool empty = true;
			if (chessField.at(i).at(j).piece == none) {
				for (int k = 0; k < allSteps.size(); k++) {
					if (allSteps[k].x == j && allSteps[k].y == i) {
						cout << "+";
						empty = false;
					}
				}
				if(empty) {
					cout << " ";
				}
			} else {
				if (chessField.at(i).at(j).color == Color::black) {
					cout << "*";
				} else {
					cout << "x";
				}
			}
			cout << "|";
		}
		cout << i;
		cout << endl;
	}
	cout << "a b c d e f g h";
}


void initXY(pos *position) {
	string result;
	while (true) {
		cout << "введи позицию(буквацифра): ";
		cin >> result;
		*position = nameToInt(result);
;		if ((*position).x < 8 && (*position).x >= 0 && (*position).y < 8 && (*position).y >= 0) {
			break;
		}
		else {
			cout << "ti tupoi normalno pishi\n" << position->x << " " << position->y << "\n";
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

	figure.color = Color::black;
	chessField.at(position.x + 2).at(position.y + 2) = figure;

	figure.color = Color::white;

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
