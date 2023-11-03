#include <iostream>

using namespace std;
int *slon(int x, int y) {
	int b[14][2];
	int index = -1;
	for (int x1 = -4; x1 <= 4; x1++) {
		index++;
		if (x + x1 >= 0 && x + x1 < 8 && y + x1 >= 0 && y + x1 < 8) {
			b[index][0] = x + x1;
			b[index][1] = y + x1;
		}
		index++;
		if (x + x1 >= 0 && x + x1 < 8 && y - x1 >= 0 && y - x1 < 8) {
			b[index][0] = x + x1;
			b[index][1] = y - x1;
		}
	}
	return *b;
}