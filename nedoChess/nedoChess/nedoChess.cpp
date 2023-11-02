#include <string>
#include <iostream>
using namespace std;


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

	for (auto i : b) {
		if (i[0] == -858993460) {
			break;
		}
		cout << "\n\nabeme x: " << i[0] << "\nabeme y: " << i[1];
	}

}
