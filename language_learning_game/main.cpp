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

using namespace std;
using namespace sf;

int main()
{

    grammar_game game1;

    //Game Loop

    while (game1.getWindowIsOpen())
    {
        game1.play();
    }

}
