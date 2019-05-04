#pragma once

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace dh {
	template <typename T>
	struct Vector {
		T x;
		T y;
		T z;
	};

	class Evaluator
	{
	public:
		sf::RenderWindow* window;
		Evaluator();
		~Evaluator();

		void evalMap(std::string map, std::vector<sf::Text>& info);
	};
}
extern dh::Evaluator Eval;