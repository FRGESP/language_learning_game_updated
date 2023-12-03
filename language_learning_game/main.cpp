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
    grammar_game game1;
    MixNMatchGame MG;
    int option;
    do
    {
        menu();
        cin >> option;
        switch (option)
        {
        case 1:
            system("cls");
            MG.play();
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            while (game1.getWindowIsOpen())
            {
                game1.play();
            }
            system("pause");
            system("cls");
            break;;
        default:
            break;
        }
    } while (option != 3);
    return 0;

}