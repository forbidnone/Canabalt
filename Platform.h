#pragma once

//Library includes
#include<SFML/Graphics.hpp>

class Platform
{

public:

	Platform();

	void Spawn();

	void Draw(sf::RenderTarget& _target);

private:

	sf::Sprite m_sprite;


};