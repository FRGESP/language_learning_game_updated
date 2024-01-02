#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "string.h"
#include "game.h"
using namespace std;
using namespace sf;
class grammar_game : public Game
{
	//Variables
	RenderWindow* window; 
	VideoMode videomode;
	Event ev;
	RectangleShape* player; //Player on the user interface
	Texture playerTexture;
	RectangleShape* pipe; //Obstacle
	Texture pipeTexture;
	RectangleShape* live1; //First hearth on the screen
	RectangleShape* live2;//Second hearth on the screen
	RectangleShape* live3; //Third hearth on the screen
	Texture liveTexture;
	Font font;
	Text scoreWord; // The word "score" on the screen
	Text scoreString; //Number showed on the screen
	Text correct; // The word showed on screen
	Text incorrect; // The word showed on screen
	Text sentenceToComplete; // The sentence showed on screen
	bool correctChoice;
	string correctWord, incorrectWord, datasentenceToComplete;
	//Remove the string[100] and int i statements once they are not needed, this is just for the example
	int i,index;
	string sentences[100] = { "Hello, _ are you? ","Yo ___ al gymnasio  ","You are _ " /*STOPS HERE*/,"Mi color favorito es _" ,"I will _ in the library"," ¿ _ hambre?",  "I like to read _","La _ se llama Sofia","The teacher _ spanish" ,"La casa es __" };
	string correctWords[100] = { "How","voy","beautiful"/*STOPS HERE*/ ,"amarillo" ,"study","Tienes",  "Books","Niña","teaches" ,"Grande" };
	string incorrectWords[100] = { "red","perro","tree"/*STOPS HERE*/,"encantado" ,"sing","Poner",  "Food","Niño","throws" ,"Gato" };
	void initializeVariables();
	void initWindow();
	void initPlayer();
	void initPipe();
	void initLives();
	void initAnswers(string correctWordToShow, string incorrectWordToShow); //Method for show the words on the screen, it needs two strings  (correct and incorrect word)
	void initText();
	int getLivesleft();
	void getscore();
	void collission();
	void uploadScore();
	string IntToString(int intVariable); //Transforms int variable to string variable

public:
	//Constructors / destructors
	grammar_game();
	virtual ~grammar_game();
	
	//Accesors
	const bool getWindowIsOpen() const;

	//Functions
	void update();
	void pollEvents();
	void render();
	void generalMove();
	void setSentenceToComplete(string sentence);
	int askChoice() override;
	void play() override;
};

