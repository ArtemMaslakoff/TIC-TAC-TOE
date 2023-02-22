#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
	private:
		int name;
		bool isClicked;
		sf::Texture texture;
		sf::Sprite sprite;

	public:
		Button() = default;
		~Button() = default;

		Button(std::string path, int name) : name(name), isClicked(false)
		{
			texture.loadFromFile(path);
			sprite.setTexture(texture);
		};




};

