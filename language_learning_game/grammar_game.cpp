#include "grammar_game.h"
#include "cstdlib"
#include "math.h"
#include "string.h"
using namespace std;

void grammar_game::initializeVariables()
{
    this->window = nullptr;
    this->player = nullptr;
    this->pipe = nullptr;
    this->live1 = nullptr;
    this->live2 = nullptr;
    this->live3 = nullptr;
    playerHP = 3;
    playerScore = 0;
    correctChoice = false;
    font.loadFromFile("font.ttf");
    i = 0;
    index = 0;//Remove this once they are not needed, this is just for the example
}

void grammar_game::initWindow() //Initialize the window
{
    this->videomode.height = 600;
    this->videomode.width = 800;
    this->player = new RectangleShape(Vector2f(100.0f, 100.0f));
    this->pipe = new RectangleShape(Vector2f(100.0f, 400.0f));
    this->live1 = new RectangleShape(Vector2f(30.0f, 30.0f));
    this->live2 = new RectangleShape(Vector2f(30.0f, 30.0f));
    this->live3 = new RectangleShape(Vector2f(30.0f, 30.0f));
    initText();
    initPlayer();
    initPipe();
    initLives();
    setSentenceToComplete(sentences[index]); //It is necessary to modify the parameter to use the data structure that you want to implement.
    initAnswers(correctWords[index], incorrectWords[index]); //It is necessary to modify the parameters to use the data structure that you want to implement. correctWords[i], incorrectWords[i]
    if (index < 100) {
        index++;
    }
    this->window = new RenderWindow(this->videomode, "Grammar Game", Style::Titlebar | Style::Close);

}



grammar_game::grammar_game() //Constructor
{
    this->initializeVariables();
    this->initWindow();
}

void grammar_game::initPlayer()
{
    playerTexture.loadFromFile("Flappy.png");
    player->setTexture(&playerTexture);
    player->setPosition(75, 300);
}

void grammar_game::initPipe()
{
    pipeTexture.loadFromFile("pipe.png");
    pipe->setTexture(&pipeTexture);
    pipe->setPosition(800, 100);
}

void grammar_game::initLives()
{
    liveTexture.loadFromFile("heart.png");
    live1->setTexture(&liveTexture);
    live1->setPosition(750, 10);
    live2->setTexture(&liveTexture);
    live2->setPosition(700, 10);
    live3->setTexture(&liveTexture);
    live3->setPosition(650, 10);

}

void grammar_game::initAnswers(string correctWordToShow, string incorrectWordToShow) //Put the words on the screen
{
    int position = rand() % 2;
    correct.setFont(font);
    correct.setString(correctWordToShow);
    correct.setCharacterSize(25);
    correct.setFillColor(Color::Black);

    incorrect.setFont(font);
    incorrect.setString(incorrectWordToShow);
    incorrect.setCharacterSize(25);
    incorrect.setFillColor(Color::Black);

    if (position == 1)
    {
        correct.setPosition(800, 100);
        incorrect.setPosition(800, 490);
    }
    if (position == 0)
    {
        incorrect.setPosition(800, 100);
        correct.setPosition(800, 490);
    }
}

void grammar_game::initText() //Init the word "score" and the string of the player score
{
    scoreWord.setFont(font);
    scoreWord.setString("Score:");
    scoreWord.setPosition(650, 60);
    scoreWord.setCharacterSize(25);
    scoreWord.setFillColor(Color::Black);

    scoreString.setFont(font);
    scoreString.setString(IntToString(playerScore));
    scoreString.setCharacterSize(25);
    scoreString.setFillColor(Color::Black);
    scoreString.setPosition(750, 60);
}


int grammar_game::getLivesleft()
{
    return playerHP;
}

void grammar_game::getscore()
{
    cout << "Your score was:" << IntToString(playerScore);
}

void grammar_game::collission() //Detects if the player passed through the correct option
{
    float vectorxPI = abs(incorrect.getPosition().x - player->getPosition().x); //Player to incorrect answer
    float vectoryPI = abs(incorrect.getPosition().y - player->getPosition().y); //Player to incorrect answer

    float vectorxPC = abs(correct.getPosition().x - player->getPosition().x); //Player to correct answer
    float vectoryPC = abs(correct.getPosition().y - player->getPosition().y); //Player to correct answer

    float markIncorrect = sqrt(pow(vectorxPI, 2) + pow(vectoryPI, 2));
    float markCorrect = sqrt(pow(vectorxPC, 2) + pow(vectoryPC, 2));


    if (markCorrect < 55)
    {
        correctChoice = true;
    }

}

void grammar_game::uploadScore() //Upload the number showes on the screen
{
    scoreString.setString(IntToString(playerScore));
}

string grammar_game::IntToString(int intVariable) //Transform int variable into string variable, used to transform the player's score into a string for display on the screen
{
    string s = to_string(intVariable);
    return s;
}



grammar_game::~grammar_game() //Destructor
{
    delete this->window;
}

int grammar_game::askChoice() //Required for inheritance between the game class and this class, modify if necessary
{
    return 0;
}

void grammar_game::play()
{
    update();
    render();
}


void grammar_game::update() //Update what is happening on the screen
{
    this->generalMove();
    this->pollEvents();
    this->collission();
}

void grammar_game::render() // This is going to render the objects, if you create a new object put it here
{
    this->window->clear(Color(171, 219, 227));
    //Draw Game
    this->window->draw(*player);
    this->window->draw(*pipe);
    this->window->draw(correct);
    this->window->draw(incorrect);
    this->window->draw(*live1);
    this->window->draw(*live2);
    this->window->draw(*live3);
    this->window->draw(scoreWord);
    this->window->draw(scoreString);
    this->window->draw(sentenceToComplete);
    this->window->display();
}

const bool grammar_game::getWindowIsOpen() const
{
    return this->window->isOpen();
}

void grammar_game::pollEvents() //This records events that happen
{
    float speed = 3.0; //Player speed. Modify if the player is slow or fast
    while (this->window->pollEvent(this->ev))
    {

        switch (this->ev.type)
        {
        case Event::Closed:
            getscore();
            this->window->close();
            break;
        case Event::KeyPressed:
            if (this->ev.key.code == Keyboard::Escape)
            {
                getscore();
                this->window->close();
            }
            break;
        default:
            break;
        }

        if ((Keyboard::isKeyPressed(Keyboard::Key::A) && (player->getPosition().x >= 50)))
            player->move(-speed, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::Key::D) && (player->getPosition().x <= 500))
            player->move(speed, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::Key::W) && (player->getPosition().y >= 50))
            player->move(0.0f, -speed);
        if (Keyboard::isKeyPressed(Keyboard::Key::S) && (player->getPosition().y <= 450))
            player->move(0.0f, speed);


    }
}

void grammar_game::generalMove()

{
    float speed= 0.02; //Obstacles and options speed. Modify if the obstacles is slow or fast
    if (pipe->getPosition().x > -100)
    {
        pipe->move(-speed, 0);
        correct.move(-speed, 0);
        incorrect.move(-speed, 0);
    }
    else
    {
        if (correctChoice == true)
        {
            playerScore++;
            uploadScore();
        }
        else
        {
            playerHP--;
        }
        if (index == 10)
        {
            getscore();
            this->window->close();
        }
        initPipe();
        initAnswers(correctWords[index], incorrectWords[index]); //It is necessary to modify the parameters to use the data structure that you want to implement  WORDS correctWords[i], incorrectWords[i]
        setSentenceToComplete(sentences[index]);  //It is necessary to modify the parameters to use the data structure that you want to implement.
        index++;
        correctChoice = false;
    }

    switch (getLivesleft()) //Movement of the hearths
    {
    case 0:
        while (i < 10)
        {
            live1->move(0, -0.02);
            i++;
        }
        getscore();
        this->window->close();  
        break;
    case 1:
        for (i = 0; i < 10; i++)
            live2->move(0, -0.02);
        break;
    case 2:
        for (i = 0; i < 10; i++)
            live3->move(0, -0.02);
        break;
    default:
        break;
    }
}

void grammar_game::setSentenceToComplete(string sentence) //This modify the sentenced showed on the screen
{
    sentenceToComplete.setFont(font);
    sentenceToComplete.setString(sentence);
    sentenceToComplete.setPosition(80, 25);
    sentenceToComplete.setCharacterSize(25);
    sentenceToComplete.setFillColor(Color::Black);
}
