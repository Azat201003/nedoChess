#include <string>
#include <iostream>
using namespace std;

int* hourse(int x, int y) {

	int b[8][2];
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
	return *b;
}

int* Pe(int x, int y) {

	int b[2][2];
	int y1;
	int index = 0;
	b[0][0] = x;
	b[0][1] = y + 1;

	if (y == 1) {
		b[1][0] = x;
		b[1][1] = y + 1;
	}
	return *b;
}



int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int x,y;
	
	for (auto i :hourse(x,y)) {
		if (i[0] == -858993460) {
			break;
		}
		cout << "x: " << i[0] << "y: " << i[1];
	}
		
}

