// Library includes
#include <cstdlib>
// End library includes

// Project includes
#include "Platform.h"
#include "AssetManager.h"
// End Project includes

// Constants
#define SIZE_X_MIN 10
#define SIZE_Y_MIN 1
#define SIZE_X_MAX 30
#define SIZE_Y_MAX 5
#define POS_Y_MIN 800
#define POS_Y_MAX 1000
#define GAP_SIZE 150

float Platform::s_furthestPoint = 0;

Platform::Platform()
	:m_sprite()
{

	m_sprite.setTexture(AssetManager::GetTexture("graphics/block.png"));

}

void Platform::Spawn()
{

	// Choose a random size for our platform
	sf::Vector2f size;
	size.x = rand() % (SIZE_X_MAX - SIZE_X_MIN) + SIZE_X_MIN;
	size.y = rand() % (SIZE_Y_MAX - SIZE_Y_MIN) + SIZE_Y_MIN;
	m_sprite.setScale(size.x, size.y);

	// Choose a random y position
	sf::Vector2f position;
	position.x = s_furthestPoint + GAP_SIZE;
	position.y = rand() % (POS_Y_MAX - POS_Y_MIN) + POS_Y_MIN;
	m_sprite.setPosition(position);

	// Update the furthest position
	// (Our platform is now furthest to the right)
	s_furthestPoint = position.x + m_sprite.getGlobalBounds().width;

}

void Platform::Draw(sf::RenderTarget& _target)
{

	_target.draw(m_sprite);

}

sf::FloatRect Platform::GetCollider()
{

	 return m_sprite.getGlobalBounds();

}