#include "OutputWindow.hpp"
#include "Evaluator.hpp"

#define MAX_SCREEN_WIDTH 1600
#define MAX_SCREEN_HEIGHT 900

dh::OutputWindow::OutputWindow()
{
}
dh::OutputWindow::~OutputWindow()
{
}

void dh::OutputWindow::Init(std::string map)
{
	assets.loadFont("Font", "res/coolvetica rg.ttf");
	sf::Image bg;
	bg.loadFromFile("res/" + map + ".jpg");
	bgTex.loadFromImage(bg);
	background.setTexture(bgTex);
	
	const unsigned int width = bg.getSize().x;
	const unsigned int height = bg.getSize().y;
	if (width > MAX_SCREEN_WIDTH) {
		background.setScale(MAX_SCREEN_WIDTH / (float)width, MAX_SCREEN_WIDTH / (float)width);
	}
	if (height > MAX_SCREEN_HEIGHT) {
		background.scale(MAX_SCREEN_HEIGHT / (float)height, MAX_SCREEN_HEIGHT / (float)height);
	}

	this->window.create(sf::VideoMode((unsigned int)background.getLocalBounds().width, (unsigned int)background.getLocalBounds().height), 
		"CSGO Position Analyzer", sf::Style::Close);
	this->window.setVerticalSyncEnabled(true);
	this->window.setPosition(sf::Vector2i(20, 20));
}
void dh::OutputWindow::Run(void)
{
	while (this->window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		this->window.clear();
		this->window.draw(background);
		for (size_t i = 0U; i < this->info.size(); ++i) {
			this->window.draw(this->info[i]);
		}
		this->window.display();
	}
}