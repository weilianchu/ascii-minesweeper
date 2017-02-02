#include <vector>
#include <cmath>
#include <stdlib.h>
#include "tile.h"
#include <random>
using namespace std;

vector<int> generate_rand(int num_tiles, int num_mines) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0,num_tiles);

	vector<int> mines;
	for (int i = 0; i < num_mines; i++) {
		
		int r = dis(gen);

		while (find(mines.begin(), mines.end(), r) != mines.end()) {
			r = dis(gen);
		}
		mines.push_back(r);
	}

	sort(mines.begin(), mines.begin() + num_mines);
	return mines;
};

class Board {

private:

	int width;
	int height;
	int total_mines;
	int num_clicked;
	int num_flagged;
	vector<vector<Tile*> > Tiles;

public:

	Board(int width, int height, int mine_pct) {
		this->width = width;
		this->height = height;
		this->num_flagged = 0;
		this->num_clicked = 0;
		this->total_mines =  floor(width*height*mine_pct/100);

		vector<int> mines = generate_rand(width*height, total_mines);
		int tile_counter = 0;
		int mine_counter = 0;

		vector<vector<Tile*> > tiles;

		this->Tiles = tiles;

		// creating the tiles
		for (int i = 0; i < height; i++) {
			vector<Tile*> row;
			for (int j = 0 ; j < width; j++) {
				Tile* tile;
				if (tile_counter == mines[mine_counter] && mine_counter < mines.size()) {
					mine_counter++;
					tile = new Tile(j, i, true);
				} else {
					tile = new Tile(j, i , false);
				}
				row.push_back(tile);
				tile_counter++;
			}
			this->Tiles.push_back(row);
		}

		assign_numbers();
	}

	~Board() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				delete this->Tiles[i][j];
			}
		}
	}

	int get_width() {
		return this->width;
	}

	int get_height() {
		return this->height;
	}

	int remaining_flags() {
		return total_mines - num_flagged;
	}

	int get_surrounding(int i , int j) {
		int x_start = -1;
		int x_end = 1;
		int y_start = -1;
		int y_end = 1;

		if (i == 0) {
			x_start = 0;
		} else if (i == width - 1) {
			x_end = 0;
		}

		if (j == 0) {
			y_start = 0;
		} else if (j == height - 1) {
			y_end = 0;
		}

		int mine_count = 0;

		for (int a = i + x_start; a < i + x_end + 1; a++) {
			for (int b = j + y_start; b < j + y_end + 1; b++) {
				if (this->Tiles[b][a]->is_mine()) {
					mine_count++;
				}
			}
		}

		return mine_count;
	}

	void assign_numbers() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Tile* tile = this->Tiles[i][j];
				if (tile->is_mine()) {
					tile->set_value(-1);
				} else {
					tile->set_value(get_surrounding(j, i));
				}
			}
		}
	}

	void flag(int x, int y) {
		if (remaining_flags() <= 0) {
			cout << "You have no more flags!" << endl;
			return;
		}
		Tile* tile = this->Tiles[y][x];
		if (tile->is_flagged()) {
			tile->unflag();
			num_flagged--;
		} else if (tile->is_clicked()) {
			cout << "That tile has already been clicked" << endl;
		} else {
			tile->flag();
			num_flagged++;
		}
	}

	int click(int x, int y) {
		Tile* tile = this->Tiles[y][x];
		if (tile->is_mine()) {
			return -1;
		} else {
			int x_start = -1;
			int x_end = 1;
			int y_start = -1;
			int y_end = 1;

			if (x == 0) {
				x_start = 0;
			} else if (x == width - 1) {
				x_end = 0;
			}

			if (y == 0) {
				y_start = 0;
			} else if (y == height - 1) {
				y_end = 0;
			}

			tile->click();
			num_clicked++;
			if (tile->get_value() == 0) {
				for (int i = x + x_start; i < x + x_end + 1; i++) {
					for (int j = y + y_start; j < y + y_end + 1; j++) {
						// cout << i << " " << j << endl;
						Tile* neighbour = this->Tiles[j][i];
						if (!neighbour->is_clicked()){
							click(i, j);
						}
					}
				}
			}

			return 1;
		}
	}

	void print_numbers() {
		for(int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Tile* tile = this->Tiles[i][j];
				if (tile->is_mine()) {
					cout << "M";
				} else {
					cout << tile->get_value();
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	void print_board() {
		for(int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Tile* tile = this->Tiles[i][j];
				if (tile->is_clicked()) {
					cout << tile->get_value();
				} else if (tile->is_flagged()) {
					cout << "F";
				} else {
					cout << "-";
				}
			}
			cout << endl;
		}
		cout << endl;
		cout << "You have " << remaining_flags() << " flags left." << endl;
	}

	bool did_i_win() {
		return this->num_clicked == (this->width*this->height - total_mines);
	}

};