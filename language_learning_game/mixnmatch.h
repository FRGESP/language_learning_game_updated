#ifndef MIXNMATCH_H
#define MIXNMATCH_H
#include "game.h"
#include <vector>

class Tile {
public:
	Tile() {
		id = -1;
		content = "Null";
		matched = false;
		isSelected = false;
	}
	void setMatched(bool m) {
		matched = m;
	}
	bool isMatched() {
		return matched;
	}
	void setContent(std::string c) {
		content = c;
	}
	std::string getContent() {
		return content;
	}
	void setID(int x) {
		id = x;
	}
	int getID() {
		return id;
	}
	void setSelected(bool s) {
		isSelected = s;
	}
	bool getSelected() {
		return isSelected;
	}

private:
	int id;
	std::string content;
	bool matched;
	bool isSelected;
};

class MixNMatchGame : public Game {
public:
	MixNMatchGame();
	int askChoice() override;
	void play() override;
	void shuffle();
	void display();
	void PLAYGAME();
	void select();
	bool pairCheck();
	void resetSelect();
	bool alreadyMatched();
	void resetMatched();
private:
	const int MAX_ROUNDS = 5;
	const int ROW = 2;
	const int COL = 6;
	const int PAIRS = COL;
	int pairsFound;
	Tile grid[2][6];
	int playerSelect;
	int selectionCount;


};


#endif
