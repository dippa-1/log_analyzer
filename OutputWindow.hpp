#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "AssetManager.hpp"
#include <string>

namespace dh {
	class OutputWindow
	{
	private:
		sf::Sprite background;
		sf::Texture bgTex;
		sf::Font font;

	public:
		sf::RenderWindow window;
		std::vector<sf::Text> info;

		OutputWindow();
		~OutputWindow();
		void Init(std::string map);
		void Run(void);
	};
}