#pragma once
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace std;

class Button
{
private:
	sf::Vector2f _position;
	function<void(void)> _onClick;
	sf::Sprite* _sprite;
public:
	Button(sf::Vector2f _position, function<void(void)> _onClick);
	sf::Vector2f getPosition() const;
	sf::Sprite* getSprite() const;
	void setSprite(sf::Sprite* _sprite);
	void onClick();
};

