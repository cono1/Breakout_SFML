#include "game.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

#include "GameObjects/ball.h"
#include "GameObjects/bricks.h"
#include "GameObjects/paddle.h"

#include "collisionManager.h"
#include "lifeManager.h"
#include "Menu/backButton.h"

extern int offset;

enum CurrentScreen {PLAY, CREDITS, RULES, EXIT, MENU};
const int quantMenuRects = 4;



namespace game
{
MenuRect menuRect[quantMenuRects];

static int activeBricks = quantX * quantY;

void initMenuRect();
void printMenu(sf::RenderWindow& window, sf::Font font);
bool checkMenuClick(sf::RenderWindow& window, MenuRect& menuRect, float initWidth, float maxWidth);
void printCredits(sf::Font font, sf::RenderWindow& window);
void printHowToPlay(sf::Font font, sf::RenderWindow& window);

void updateLife(int& life, Ball& ball, Paddle paddle, int wHeight, bool& win);

void loop()
{
    MenuRect pauseRect;
    Ball ball;
    Brick bricks[quantY][quantX];
    Paddle paddle;
    bool win = false;
    int life = 3;

    const int windowWidth = 1024;
    const int windowHeight = 768;

    CurrentScreen currentScreen = MENU;
    
    initMenuRect();
    initBackButton(pauseRect);

    sf::Font font;
    if (!font.loadFromFile("res/PermanentMarker-Regular.ttf"))
        std::cout << "Failed to load font\n";
    sf::Text lifeText;
    lifeText.setFont(font);
    lifeText.setPosition(10, 10);
    lifeText.setCharacterSize(40);
    lifeText.setFillColor(sf::Color::White);

    sf::Text winText;
    winText.setString("You win");
    winText.setFont(font);
    winText.setPosition(windowWidth / 2, windowHeight / 2);
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::White);
    sf::Text loseText;
    loseText.setString("You lose");
    loseText.setFont(font);
    loseText.setPosition(windowWidth / 2, windowHeight / 2);
    loseText.setCharacterSize(50);
    loseText.setFillColor(sf::Color::White);

    sf::Text creditsText;
    creditsText.setString("dev: Daniela Gonzalez");
    creditsText.setFont(font);
    creditsText.setPosition(windowWidth - 250, 10);
    creditsText.setCharacterSize(20);
    creditsText.setFillColor(sf::Color::Magenta);


    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BREAKOUT-Daniela Gonzalez");
    sf::Clock clock;
    sf::Time dt;
    srand(time(NULL));

    initBall(ball, 800, 500);
    initBrick(bricks);
    initPaddle(paddle, windowWidth, windowHeight);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        switch (currentScreen)
        {
        case MENU:
            for (int i = 0; i < quantMenuRects; i++)
            {
                if (checkMenuClick(window, menuRect[i], menuRect[i].initWidth, menuRect[i].maxWidth) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(i == PLAY)
                    currentScreen = PLAY;

                    if (i == CREDITS)
                        currentScreen = CREDITS;

                    if (i == RULES)
                        currentScreen = RULES;

                    if (i == EXIT)
                        currentScreen = EXIT;
                }
            }
            break;
        case PLAY:
            dt = clock.restart();
            updateBall(ball, dt, windowWidth, windowHeight);
            updatePaddle(paddle, windowWidth, dt);
            updateLife(life, ball, paddle, windowHeight, win);
            lifeText.setString("Lives: " + std::to_string(life));

            if (getBallToPaddCollision(ball, paddle))
            {
                ball.y = paddle.y - paddle.sprite.getGlobalBounds().height - offset;
                ball.dirY *= -1;
                ball.speedX = (ball.x - paddle.x) / (paddle.sprite.getGlobalBounds().width) * 5;
            }

            checkBallToBrickCollision(ball, bricks, activeBricks);

            if (win || life <= 0)
            {
                clearBall(ball);
                clearPaddle(paddle);
                clearBricks(bricks);
            }

            if (checkMenuClick(window, pauseRect, pauseRect.initWidth, pauseRect.maxWidth) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                currentScreen = MENU;
            }
            break;
        case CREDITS:
            if (checkMenuClick(window, pauseRect, pauseRect.initWidth, pauseRect.maxWidth) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                currentScreen = MENU;
            }
            break;
        case RULES:
            if (checkMenuClick(window, pauseRect, pauseRect.initWidth, pauseRect.maxWidth) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                currentScreen = MENU;
            }
            break;
        case EXIT:
            return;
            break;
        default:
            break;
        }

        window.clear();

        switch (currentScreen)
        {
        case MENU:
            printMenu(window, font);
            break;
        case PLAY:
            drawBackButton(pauseRect, window);
           //window.draw(creditsText);
            for (int i = 0; i < quantY; i++)
            {
                for (int j = 0; j < quantX; j++)
                {
                    window.draw(bricks[i][j].rect);
                }
            }

            window.draw(paddle.sprite);
            window.draw(ball.sprite);
            window.draw(lifeText);
            if (win)
            {
                window.draw(winText);
            }

            if (!win && life <= 0)
            {
                std::cout << "perdio";
                window.draw(loseText);
            }

            break;
        case CREDITS:
            drawBackButton(pauseRect, window);
            printCredits(font, window);
            break;
        case RULES:
            drawBackButton(pauseRect, window);
            printHowToPlay(font, window);
            break;
        case EXIT:
            return;
        default:
            break;
        }
        window.display();
    }
}

void initMenuRect()
{
    int spaceBetweenRects = 20;
    int firstRectYPosition = 180;

    for (int i = 0; i < quantMenuRects; i++)
    {
        menuRect[i].width = 160;
        menuRect[i].height = 80;
        menuRect[i].x = (1024 - menuRect[i].width) / 2;
        menuRect[i].y = static_cast<int>(firstRectYPosition + (menuRect[i].height + spaceBetweenRects) * i);
        menuRect[i].initWidth = menuRect[i].width;
        menuRect[i].maxWidth = menuRect[i].width + 20;
        menuRect[i].rect.setFillColor(sf::Color::Red);
        menuRect[i].rect.setSize(sf::Vector2f(menuRect[i].width, menuRect[i].height));
        menuRect[i].rect.setPosition(menuRect[i].x, menuRect[i].y);
    }
}

void printMenu(sf::RenderWindow& window, sf::Font font)
{
    sf::Text title;
    title.setString("BREAKOUT");
    title.setPosition(window.getSize().x / 3, 10);
    title.setFont(font);
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(40);
    text1.setFillColor(sf::Color::White);
         
    for (int i = 0; i < quantMenuRects; i++)
    {
        window.draw(menuRect[i].rect);
        if (i == PLAY)
        {  
            text1.setString("PLAY");
            text1.setPosition(menuRect[i].x, menuRect[i].y);
            window.draw(text1);
        }   

        if (i == CREDITS)
        {
            text1.setString("CREDITS");
            text1.setPosition(menuRect[i].x, menuRect[i].y);
            window.draw(text1);
        }

        if (i == RULES)
        {
            text1.setString("RULES");
            text1.setPosition(menuRect[i].x, menuRect[i].y);
            window.draw(text1);
        }

        if (i == EXIT)
        {
            text1.setString("EXIT");
            text1.setPosition(menuRect[i].x, menuRect[i].y);
            window.draw(text1);
        }
    }
}


bool checkMenuClick(sf::RenderWindow& window, MenuRect& menuRect, float initWidth, float maxWidth)
{
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    if (menuRect.rect.getPosition().x <= mouseX &&
        menuRect.rect.getPosition().y <= mouseY &&
        menuRect.rect.getPosition().x + menuRect.rect.getSize().x >= mouseX &&
        menuRect.rect.getPosition().y + menuRect.rect.getSize().y >= mouseY)
    {
        if (menuRect.width < maxWidth)
        {
            menuRect.width += 5;
            menuRect.rect.setSize(sf::Vector2f(menuRect.width, menuRect.height));
        }
        std::cout << "Boton";
        return true;
    }
    else
    {
        menuRect.width = initWidth;
        menuRect.rect.setSize(sf::Vector2f(menuRect.width, menuRect.height));
        return false;
    }
}


void printCredits(sf::Font font, sf::RenderWindow& window)
{
    sf::Text credits;
    credits.setString("Developed by: Daniela Gonzalez");
    credits.setPosition(window.getSize().x / 3, 100);
    credits.setFont(font);
    credits.setScale(1,1);
    credits.setCharacterSize(30);
    credits.setFillColor(sf::Color::White);

    window.draw(credits);

    sf::Text credits2;
    credits2.setString("Paddle texture by Grapho boy:\n https: //www.vecteezy.com/vector-art/7544384-abstract-geometric\n-gradient-color-halftone-modern-shape-background/\n/https:/ /www.vecteezy.com/members/graphoboy9158803"); 
    credits2.setPosition(10, 220);
    credits2.setFont(font);
    credits.setScale(0.1, 0.1);
    credits2.setCharacterSize(30);
    credits2.setFillColor(sf::Color::White);

    window.draw(credits2);
}

void printHowToPlay(sf::Font font, sf::RenderWindow& window)
{
    sf::Text text1;
    text1.setString("Use LEFT and RIGHT to move");
    text1.setPosition(window.getSize().x / 3, 120);
    text1.setFont(font);
    text1.setCharacterSize(30);
    text1.setFillColor(sf::Color::White);

    sf::Text text2;
    text2.setString("Break all the bircks to win");
    text2.setPosition(window.getSize().x / 3, 220);
    text2.setFont(font);
    text2.setCharacterSize(30);
    text2.setFillColor(sf::Color::White);

    sf::Text text3;
    text3.setString("If the ball falls you lose one life");
    text3.setPosition(window.getSize().x / 3, 320);
    text3.setFont(font);
    text3.setCharacterSize(30);
    text3.setFillColor(sf::Color::White);

    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
}

void updateLife(int& life, Ball& ball, Paddle paddle, int wHeight, bool& win)
{
    if (ball.y >= wHeight)
    {
        restartBall(ball, paddle.x, wHeight / 2);
        decreasePlayerLife(life);
    }

    if (activeBricks <= 0)
    {
        win = true;
    }
}
}