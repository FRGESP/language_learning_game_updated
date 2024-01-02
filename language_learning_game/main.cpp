// language_learning_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// language_learning_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "grammar_game.h"
#include "game.h"
#include "mixnmatch.h"

using namespace std;
using namespace sf;


void menu()
{
    cout << endl << "---------------------------------------------------" << endl;
    cout << "               Lenguage learning game          " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << " 1. Mix and Match game (vocubulary game)" << endl;
    cout << " 2. Flappy bird (grammar game)" << endl;
    cout << " 3. Exit" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Select an option: ";
}
int main()
{

    MixNMatchGame MG;
    int option;
    do
    {
        menu();
        cin >> option;
        if (option == 1) {
            system("cls");
            MG.play();
            system("cls");
        }
        else if (option == 2) {
            grammar_game game1;
            system("cls");
            while (game1.getWindowIsOpen())
            {
                game1.play();
            }
            system("pause");
            system("cls");
        }
        else {
            return 0;
        }
    } while (option != 5);


}