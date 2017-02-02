class Tile {

private:

	int x;
	int y;
	int value;
	bool isMine;
	bool isClicked;
	bool isFlagged;

public:

	Tile(int x, int y, bool isMine) {
		this->x = x;
		this->y = y;
		this->isMine = isMine;
		this->isClicked = false;
	}

	bool is_clicked() {
		return this->isClicked;
	}

	bool is_flagged() {
		return this->isFlagged;
	}

	bool is_mine() {
		return this->isMine;
	}

	void click() {
		this->isClicked = true;
	}

	void flag() {
		this->isFlagged = true;
	}

	void unflag() {
		this->isFlagged = false;
	}

	int get_value() {
		return this->value;
	}

	void set_value(int val) {
		this->value = val;
	}
};