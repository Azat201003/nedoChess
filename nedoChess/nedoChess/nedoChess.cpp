#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> slon(int x, int y) {
	vector <vector <int>> b(14, vector<int>(2));
	int index = -1;
	for (int x1 = -4; x1 < 4; x1++) {
		index++;
		if (x + x1 < 8 && x + x1 > 0 && y + x1 < 8 && y + x1 > 0) {
			b[index][0] = x + x1;
			b[index][1] = y + x1;
		}
		index++;

		if (x + x1 < 8 && x + x1 > 0 && y - x1 < 8 && y - x1 > 0) {
			b[index][0] = x + x1;
			b[index][1] = y - x1;
		}
	}
	return b;
}

vector<vector<int>> hourse(int x, int y) {

	vector<vector<int>> b(8, vector<int>(2));
	int index = 0;
	for (int x1 = -2; x1 <= 2; x1++) {
		for (int y1 = -2; y1 <= 2; y1++) {
			if (x1 == 0 || y1 == 0 || x1 == y1) {
				continue;
			}
			else {
				if (x + x1 >= 0 && x + x1 < 8 && y + y1 >= 0 && y + y1 < 8) {
					b[index][0] = x1 + x;
					b[index][1] = y + y1;
					index++;
				}
			}
		}
	}
	return b;
}



vector<vector<int>> pe(int x, int y) {

	vector<vector<int>> b(2, vector<int>(2));
	b[0][0] = x;
	b[0][1] = y + 1;

	if (y == 1) {
		b[1][0] = x;
		b[1][1] = y + 1;
	}
	return b;
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

	vector<vector<int>> b = slon(x, y);
	cout << "слон: \n";
	for (auto i : b) {
		if (i[0] == -858993460) {
			break;
		}
		cout << "x: " << i[0] << "y: " << i[1];
	}
	b = hourse(x, y);
	cout << "конь: \n";
	for (auto i : b) {
		if (i[0] == -858993460) {
			break;
		}
		cout << "x: " << i[0] << "y: " << i[1];
	}
	b = pe(x, y);
	cout << "пешка: \n";
	for (auto i : b) {
		if (i[0] == -858993460) {
			break;
		}
		cout << "x: " << i[0] << "y: " << i[1];
	}
}
