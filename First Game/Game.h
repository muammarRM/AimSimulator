#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
/*
	Class yang bertindak sebagai game engine
	Wrapper Class
*/
class Game
{
private:
	//variabel
	//window
	sf::RenderWindow* window;
	sf::VideoMode VideoMode;
	sf::Event ev;


	//Mouse Position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logiC
	bool endGame;
	unsigned points;          //bilangan positif
	int health;				  //Darah
	float enemySpawnTimer;    //1...2...3...4..5..6..7..8...9..10..until max
	float enemySpawnTimerMax; //Max
	int maxEnemies;           // Max Enemies on your screen
	bool mouseHeld;           //Check if your mouse held
	float speed;
	float scaleX;
	float scaleY;
	int batas;
	float sizeX;
	float sizeY;

	//Game Object
		// sf::Sprite for texture
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	

	// private function
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();
public:
	//Constructor | Destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;

	//function
	void spawnEnemy();


	void pollEvent();
	void updateMousePositions();
	void updateSpeed();
	void updateSize();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};