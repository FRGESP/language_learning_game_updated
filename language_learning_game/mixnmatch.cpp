#include "mixnmatch.h"
#include <stdlib.h> // utilize the RAND function to implement random questions
#include <vector> // Used to contain the nessessary grammar strings for both english and spainish
#include <string> 
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <thread>// These two libraries
#include <chrono>//will be used to time user input


MixNMatchGame::MixNMatchGame() {
	playerSelect = 0;
	inGame = true; // When the function is created, the game state will be enabled
	playerHP = 3;
	playerScore = 0;
}

void MixNMatchGame::shuffle() {
	std::vector<std::pair<std::string, std::string>> pairsVector = {
		{"casa", "house"},
		{"perro", "dog"},
		{"gato", "cat"},
		{"libro", "book"},
		{"mesa", "table"},
		{"silla", "chair"},
		{"agua", "water"},
		{"sol", "sun"},
		{"luna", "moon"},
		{"flor", "flower"},
		{"ciudad", "city"},
		{"playa", "beach"},
		{"amigo", "friend"},
		{"familia", "family"},
		{"trabajo", "work"},
		{"coche", "car"},
		{"ropa", "clothes"},
		{"comida", "food"},
		{"tiempo", "time"},
		{"dinero", "money"}
	};

	// the proceeding function fills the grid with the given pairs to the right 
	int count = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			grid[i][j].setContent(pairsVector[count].first);
			grid[i][j + 1].setContent(pairsVector[count].second);
			count++;
			if (count == pairsVector.size()) {
				count = 0;
			}
			j++;
		}
	}
	count = 0; //reset count to 0 to use for assigning back into the grid
	//to randomize the matrix we flatten it into a 1d vector
	std::vector<std::string> temp;
	//next we copy everything in the matrix to the temp vector 
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			temp.push_back(grid[i][j].getContent());
		}
	}
	//We will now shuffle the vector using random_shuffle
	std::random_shuffle(temp.begin(), temp.end());

	//We will now reassign the given matrix 
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			grid[i][j].setContent(temp.at(count));
			count++;
		}
	}
}

void MixNMatchGame::display() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			std::cout << "+---------";
		}
		std::cout << "+\n";

		for (int j = 0; j < COL; j++) {
			std::cout << "| " << std::setw(8) << grid[i][j].getContent() << ' ';
		}
		std::cout << "|\n";
	};
	for (int j = 0; j < COL; ++j) {
		std::cout << "+---------";
	}
	std::cout << "+\n";

}

void MixNMatchGame::select() { // this function sets the selected to true
	std::vector<bool> temp;

	int count = 0;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			temp.push_back(grid[i][j].getSelected());
		}
	}
	temp.at(playerSelect) = true;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			grid[i][j].setSelected(temp.at(count));
			count++;
		}
	}
	playerSelect = 0;

}

bool MixNMatchGame::pairCheck() {
	std::vector<std::pair<std::string, std::string>> pairsVector = {
		{"casa", "house"},
		{"perro", "dog"},
		{"gato", "cat"},
		{"libro", "book"},
		{"mesa", "table"},
		{"silla", "chair"},
		{"agua", "water"},
		{"sol", "sun"},
		{"luna", "moon"},
		{"flor", "flower"},
		{"ciudad", "city"},
		{"playa", "beach"},
		{"amigo", "friend"},
		{"familia", "family"},
		{"trabajo", "work"},
		{"coche", "car"},
		{"ropa", "clothes"},
		{"comida", "food"},
		{"tiempo", "time"},
		{"dinero", "money"}
	};

	std::vector<std::string> temp;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (grid[i][j].getSelected() == true) {
				temp.push_back(grid[i][j].getContent());
			}
		}
	}

	if (temp.at(0) == temp.at(1)) {
		return false;
	}

	std::string pair;

	for (int j = 0; j < pairsVector.size(); j++) {
		if (temp.at(0) == pairsVector[j].first) {
			pair = pairsVector[j].second;
			break;
		}
		if (temp.at(0) == pairsVector[j].second) {
			pair = pairsVector[j].first;
			break;
		}
	}

	if (temp.at(1) == pair) {
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (grid[i][j].getSelected() == true) {
					grid[i][j].setMatched(true);
				}
			}
		}

		return true;
	}
	else {
		return false;
	}
}

void MixNMatchGame::resetSelect() { // Resets the entire selection state of the program

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			grid[i][j].setSelected(false);
		}
	}

}
void MixNMatchGame::resetMatched() { // Resets the entire selection state of the program

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			grid[i][j].setMatched(false);
		}
	}

}

bool MixNMatchGame::alreadyMatched() {//function to check if the selected is already matched

	std::vector<Tile> temp;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			temp.push_back(grid[i][j]);
		}
	}

	if (temp.at(playerSelect).isMatched() == true) {
		return true;
	}

	return false;
}


void MixNMatchGame::PLAYGAME() {
	shuffle(); // fills the grid and shuffles it
	selectionCount = 0;
	pairsFound = 0;
	resetSelect(); //incase function saves a selection from the state
	resetMatched();
	while (playerHP > 0) {
		if (pairsFound == PAIRS) {
			break;
		}
		if (selectionCount == 2) {
			if (pairCheck() == false) {
				system("cls");
				playerHP--;
				std::cout << "Not a pair, HP deducted" << std::endl;
				std::cout << "Current health: " << playerHP << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				resetSelect();
				selectionCount = 0;
			}
			else {
				system("cls");
				std::cout << "Pair found! Point Given!" << std::endl;
				pairsFound++;
				playerScore++;
				std::cout << "Current points: " << playerScore << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				resetSelect();
				selectionCount = 0;
			}

		}
		if (pairsFound == PAIRS) {
			break;
		}
		system("cls");
		display();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cin.clear();			 //Clears the input
		std::cin.ignore(100, '\n');
		std::cout << "Please select a number 0-11" << std::endl;
		std::cout << "From top left being 0 to bottom right being 11" << std::endl;
		if (!(std::cin >> playerSelect)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			playerHP--;
			std::cout << "Invalid selection. HP deducted" << std::endl;
			std::cout << "Current health: " << playerHP << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			selectionCount = 0;
			continue;
		}
		if (std::cin.fail() || playerSelect > 11 || playerSelect < 0 || alreadyMatched() == true) {
			playerHP--;
			system("cls");
			std::cout << "Invalid selection. HP deducted" << std::endl;
			std::cout << "Current health: " << playerHP << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			selectionCount = 0;
		}

		else if (playerSelect <= 11 && playerSelect >= 0) {
			system("cls");
			select();
			selectionCount++;

		}


	}
}

int MixNMatchGame::askChoice() {
	system("cls"); // Clears the screen after each game
	std::cout << "Please select the following options\n";
	std::cout << "1.Play Mix and Match" << "		" << "2.Exit to main\n";
	std::cin >> playerChoice;
	return playerChoice;
}
void MixNMatchGame::play() {
	while (inGame == true) {
		system("cls");
		askChoice();
		system("cls");
		if (playerChoice == 1) {
			playerHP = 3;
			PLAYGAME();
		}
		if (playerChoice == 2) {
			inGame = false;
		}
	}
}
