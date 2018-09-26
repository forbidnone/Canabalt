#pragma once

//Library Includes
#include <vector>
#include <SFML/Graphics.hpp>
//End Library includes

class Animation
{



public:

	Animation();

	void Update(sf::Time _frameTime);

	void Play();
	void Pause();
	void Stop();

	bool isPlaying();

	void AddFrame(sf::Texture& _newFrame);
	void SetSprite(sf::Sprite& _sprite);
	void SetPlayBackSpeed(float _framesPerSecond);
	void SetLoop(bool _loop);



private:

	// Settings
	std::vector<sf::Texture*>m_frames;
	sf::Sprite* m_sprite;
	bool m_loop;
	float m_playBackSpeed;

	// State
	int m_currentFrame;
	sf::Time m_nextFrameChange;
	bool m_playing;
};