#include <iostream>
#include "Minesweeper.h"

int main() {
	cout << "Do you want to play Minesweeper (y/n)? " << endl;
	string response;
	cin >> response;

	if (response == "y") {
		Minesweeper* game = new Minesweeper();
	}
	return 0;
}