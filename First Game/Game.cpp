#include "Game.h"


// private function
void Game::initVariables()
{
	this->window = nullptr;


	//Game logic
	this->points = 0;
	this->enemySpawnTimerMax = 50.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20;
	this->mouseHeld = false;
	this->health = 20;
	this->endGame = false;
	this->speed = 1;
	this->batas = 100;
	this->sizeX;
	this->sizeY;
}

void Game::initWindow()
{
	this->VideoMode.height = 600;
	this->VideoMode.width = 800;
	//this->VideoMode.getDesktopMode();

	this->window = new sf::RenderWindow(this->VideoMode, "My First Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);

	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/Rancho-Regular.ttf")) {
		std::cout << "ERROR::GAME::INITFONT::Failed to load Font!!" << std::endl;
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(30);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initEnemies()
{
	//kanan itu x positif, bawah itu y positif
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	// this->enemy.setOutlineColor(sf::Color::Green);
	// this->enemy.setOutlineThickness(5.f);	 

}

// constructors / Destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
	this->initText();
	this->initFonts();
}

Game::~Game() {
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

// function	ctrl + .
void Game::spawnEnemy()
{
	/*
		@return void

		Spawn enemies and sets their type and colors. spawn them on positions randomly
		-set a random type(diff)
		-set a random positions
		-set a random color
		-add enemy to the vector
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		 static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);

	//Randomize enemy type
	int type = rand() % 5;
	switch (type) {
	case 0:
		this->enemy.setSize(sf::Vector2f(200.f, 200.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(300.f, 300.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(320.f, 320.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f(350.f, 350.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case 4:
		this->enemy.setSize(sf::Vector2f(400.f, 400.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		this->enemy.setSize(sf::Vector2f(400.f, 400.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
		;

	}

	//spawn the enemy
	this->enemies.push_back(this->enemy);
}


void Game::pollEvent()
{
	//Event Polling
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
				break;
			}
		}
	}
}

void Game::updateMousePositions()
{
	/*
		@return void

		update mouse position:
		-Mouse position relative to window(vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateSpeed()
{
	this->speed += 0.5;
	this->batas += 100;
	this->enemySpawnTimerMax -= 1.f;
}


void Game::updateText()
{
	std::stringstream ss;

	ss << "Point = " << this->points << std::endl
		<< "Health = " << this->health << std::endl;

	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	/*
		@return void

		update the enemy spawn timer and spawns enemies
		when the total ammount of enemies is smaller than maximum
		move the enemies downwards.
		Removes the enemies at the edge of the screen //Todo
	*/

	//updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}

	//Move and updating the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->sizeX = this->enemies[i].getSize().x - this->speed;
		this->sizeY = this->enemies[i].getSize().y - this->speed;

		this->enemies[i].setSize(sf::Vector2f(sizeX, sizeY));

		//if the enemy pass the bottom of the window screen
		if (this->enemies[i].getSize().x <= 0)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health = " << this->health << std::endl;
		}
	}

	//check if click upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false) {

			this->mouseHeld = true;
			bool deleted = false;

			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gains points
					if (this->enemies[i].getFillColor() == sf::Color::Magenta) {
						this->points += 10;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Blue) {
						this->points += 8;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan) {
						this->points += 5;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Red) {
						this->points += 3;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Green) {
						this->points += 1;
					}
					std::cout << "Point = " << this->points << std::endl;

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}

			}
		}
	}
	else {
		this->mouseHeld = false;
	}

	if (this->points >= this->batas) {
		updateSpeed();
	}
}

void Game::update()
{
	this->pollEvent();
	if (this->endGame == false) {
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}
	if (this->health <= 0) {
		this->endGame = true;
	}
	//update mouse position
	//relative to the screen
		// std::cout << "Mouse Pos = " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
	//relative to the window
		/*
			std::cout << "Mouse Pos = "
			<< sf::Mouse::getPosition(*this->window).x << " "
			<< sf::Mouse::getPosition(*this->window).y << std::endl;
		*/
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//rendering all the enemies
	for (auto& e : this->enemies) {
		target.draw(e);
	}
}

void Game::render()
{
	/*
		@return void

		-Clear old frame
		-rander object
		-display frame in window

		Render Game Object

	*/

	this->window->clear(sf::Color::Black);

	// Draw game object
	this->renderEnemies(*this->window);
	this->renderText(*this->window);



	this->window->display();
}
