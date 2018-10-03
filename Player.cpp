//Library Includes

//End Library Includes


//Project Includes
#include "Player.h"
#include "AssetManager.h"
//End Project Includes

// Constants
#define jump_SPEED -1500.0f
#define GRAVITY 2000.0f
#define run_SPEED_INITIAL 500.0f

Player::Player()
	: m_sprite()
	, m_jumpSound()
	, m_deathSound()
	, m_landSound()
	, m_animation()
	, m_velocity(0.0f, 0.0f)
	, m_touchingGround(false)
{

	// Sprite setup
	m_sprite.setTexture(AssetManager::GetTexture("graphics/playerJump.png"));

	//Sound Setup
	m_jumpSound.setBuffer(AssetManager::GetSoundBuffer("audio/jump.wav"));
	m_deathSound.setBuffer(AssetManager::GetSoundBuffer("audio/death.wav"));
	m_landSound.setBuffer(AssetManager::GetSoundBuffer("audio/landing.wav"));


	// Animation Setup
	m_animation.SetSprite(m_sprite);


	Animation& runAnimation = m_animation.CreateAnimation("run");
	runAnimation.AddFrame(AssetManager::GetTexture("graphics/playerrun1.png"));
	runAnimation.AddFrame(AssetManager::GetTexture("graphics/playerrun2.png"));
	runAnimation.SetLoop(true);
	runAnimation.SetPlayBackSpeed(10.0f);

	Animation& jumpAnimation = m_animation.CreateAnimation("jump");
	jumpAnimation.AddFrame(AssetManager::GetTexture("graphics/playerjump.png"));

	m_animation.Play("jump");

}


void Player::Input(sf::Event _gameEvent)
{

	//Check if the player has pressed the jump button
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		if (_gameEvent.key.code == sf::Keyboard::Space)
		{

			//Player has tried to jump
			if (m_touchingGround == true)
			{
				//Play jump sound
				m_jumpSound.play();

				//Set to the players velocity
				m_velocity.y = jump_SPEED;
			}
		}
	}
}

void Player::Update(sf::Time _frameTime)
{

	// Process te animation
	m_animation.Update(_frameTime);
	
	
	

	// Apply Gravity to our velocity
	if (m_touchingGround == false)
	{
		float velocityChange = GRAVITY * _frameTime.asSeconds();
		m_velocity.y += velocityChange;
	}


	//Move sprite based on velocity
	sf::Vector2f currentPosition = m_sprite.getPosition();
	sf::Vector2f positionChange = m_velocity * _frameTime.asSeconds();
	m_sprite.setPosition(currentPosition + positionChange);



}


void Player::Draw(sf::RenderTarget& _target)
{

	_target.draw(m_sprite);

}

void Player::Spawn()
{

	m_sprite.setPosition(0, 0);
	m_animation.Play("jump");
	m_velocity.y = 0;
	m_velocity.x = run_SPEED_INITIAL;

}

sf::Vector2f Player::GetPosition()
{

	return m_sprite.getPosition();

}

void Player::HandleCollision(std::vector<sf::FloatRect> _platforms)
{

	// Assume we did not collide
	bool wereTouchingGround = m_touchingGround;

	m_touchingGround = false;

	// Get the collider for the player
	sf::FloatRect playerCollider = m_sprite.getGlobalBounds();

	// loop through each platform collider
	for (auto it = _platforms.begin(); it != _platforms.end(); ++it)
	{

		sf::FloatRect platformCollider = *it;



		if (playerCollider.intersects(platformCollider))
		{

			// Yes it does!

			// Check if the bottom of our feet are touching the top of the platform

			// Create feet collider
			sf::FloatRect feetCollider = playerCollider;
			// Set our feet top to be 10 pixels from the bottom of the player collider
			feetCollider.top += playerCollider.height - 10;
			// set our feet collider height to be 10 pixels
			feetCollider.height - 10;

			// Create platform top collider
			sf::FloatRect platformTop = platformCollider;
			platformTop.height = 10;

			//Are the feet touching the top of the platform
			if (feetCollider.intersects(platformTop))
			{

				//Yes feet are touching

				m_touchingGround = true;

				if (wereTouchingGround == false && m_velocity.y > 0) // Check if we are falling downwards
				{

					// We have touched the ground
					m_animation.Play("run");
					m_landSound.play();
					m_velocity.y = 0;

				}
			}
		}

	}

	// if there was not a collision set touching ground to false
	if (m_touchingGround == false && wereTouchingGround == true)
	{
		m_animation.Play("jump");
	}

}