#ifndef GAME_H
#define GAME_H
#include <string>

class Game {
public:
	virtual ~Game() {};
	virtual void play() = 0; // Game state
	virtual int askChoice() = 0;
	bool inGame; // used to determine if the player is in the game
	int playerChoice;
	int playerHP;
	int playerScore;
};

#endif
