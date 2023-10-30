#pragma once

#include <SFML/Window.hpp>

class WindowStub : public sf::Window
{
public:
    sf::Vector2u getSize() const;
};