#include "board.h"
#include <iostream>

class Minesweeper {

private:
	Board* board;
	bool continue_play;


public:

	Minesweeper() {
		play();
	}

	~Minesweeper() {
		delete this->board;
	}

	void play() {
		cout << "Input the width, height, and the percentage of mines of the board: ";
		int width, height, pct;

		cin >> width;
		cin >> height;
		cin >> pct;

		this->board = new Board(width, height, pct);
		board->print_board();
		this->continue_play = true;

		while (this->continue_play) {
			make_turn();
		}

		cout << "Play again (y/n)? ";
		string response;
		cin >> response;

		if (response == "y") {
			cout << endl << endl;
			play();
		}

		// cout << "Type 'help' for instructions" << endl << endl;
		
	}

	void make_turn() {
		cout << "Make your move: ";
		string input;
		int x;
		int y;
		cin >> input;
		cin >> x;
		cin >> y;

		if (x > this->board->get_width() || y > this->board->get_height() || x <= 0 || y <= 0) {
			cout << "This isn't a valid coordinate." << endl;
			return;
		}

		if (input == "click") {
			if (this->board->click(x-1, y-1) <0) {
				cout << endl << "Sorry, you clicked on a mine! The correct board was:" << endl << endl;
				this->board->print_numbers();
				this->continue_play = false;
				return;
			}

			if (this->board->did_i_win()) {
				cout << endl << "Congrats! You've flagged all the mines!" << endl << endl;
				this->continue_play = false;
			}
		} else if (input == "flag") {
			this->board->flag(x-1,y-1);
		} else {
			cout << "The correct commands are: click x y, flag x y" << endl;
		}

		cout << "The current board:" << endl;
		this->board->print_board();
	}
};