#include "Button.h"

// Simple constructor
Button::Button(sf::Vector2f _position, function<void(void)> _onClick)
{
    this->_position = _position;
    this->_onClick = _onClick;
    this->_sprite = nullptr;
}

// Get position from button
sf::Vector2f Button::getPosition() const
{
    return _position;
}

// Get sprite from button
sf::Sprite* Button::getSprite() const
{
    return _sprite;
}

// Set sprite and set its position with the button position
void Button::setSprite(sf::Sprite* _sprite)
{
    this->_sprite = _sprite;
    this->_sprite->setPosition(_position);
}

// Do stored onClick
void Button::onClick()
{
    _onClick();
}
