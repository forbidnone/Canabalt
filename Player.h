#pragma once

// Library includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// End Library Includes

// Project includes
#include "AnimationSystem.h"
// End project includes


class Player
{

public:

	Player();

	void Input(sf::Event _gameEvent);
	void Update(sf::Time _frameTime);
	void Draw(sf::RenderTarget& _target);

	void Spawn();

	sf::Vector2f GetPosition();

private:

	// Assets
	sf::Sprite m_sprite;
	sf::Sound m_jumpSound;
	sf::Sound m_deathSound;
	sf::Sound m_landSound;
	AnimationSystem m_animation;

	// State
	sf::Vector2f m_velocity;

};