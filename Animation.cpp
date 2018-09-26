// Project Includes
#include "Animation.h"

Animation::Animation()
	: m_frames()
	, m_sprite(nullptr)
	, m_playBackSpeed(15)
	, m_loop(false)
	, m_playing(false)
	, m_nextFrameChange()
	, m_currentFrame(0)
{

}


void Animation::Update(sf::Time _FrameTime)
{

	// Only process the animation if it is playing
	if (m_playing)
	{

		//Is it time to change to a new frame?
		m_nextFrameChange -= _FrameTime;
		if (m_nextFrameChange.asSeconds() < -0)
		{

			// It's time to change the frame!

			// Change to the next frame
			++m_currentFrame;


			//Did we reach the end?
			if (m_currentFrame >= m_frames.size())
			{

				// We did reach the end!

				// Should we loop
				if (m_loop)
				{

					// We should loop
					m_currentFrame = 0;

				}
				else
				{

					// We should not loop

					// Set our frame as the lst in the list
					m_currentFrame = m_frames.size() - 1;

					// Stop playback
					m_playing = false;

				}
				// Wrap around to the beginning
				

			}

			// Update sprite's texture to match new frame
			// Does our sprite exist
			if (m_sprite) // is not = 0 aka nullptr
			{
				m_sprite->setTexture(*m_frames[m_currentFrame]);
			}


			//Determine time for next frame change
			float timeToChange = 1.0f / m_playBackSpeed;
			m_nextFrameChange = sf::seconds(timeToChange);


		}
	}
}


void Animation::Play()
{

	// Update our sprite to the current frame immediately
	if (m_sprite)
	{

		m_sprite->setTexture(*m_frames[m_currentFrame]);
			
	}



	if (m_playBackSpeed != 0)
	{

		// Only start playing and set next frame time IF playback is not zero
		// Avoid a divide by zero error
		m_playing = true;

		// Determine time for next frame change
		// Convert frames per second to seconds per frame
		float timeToChange = 1.0f / m_playBackSpeed;
		m_nextFrameChange = sf::seconds(timeToChange);

	}
}


void Animation::Pause()
{

	// Stop playback, keeping current frame as is
	m_playing = false;

}


void Animation::Stop()
{

	// Stop playback and reset to first frame
	m_playing = false;
	m_currentFrame = 0;

}


bool Animation::isPlaying()
{
	// Tell the calling code if we are currently playing
	return m_playing;
}

void Animation::AddFrame(sf::Texture& _newframe)
{
	m_frames.push_back(&_newframe);
}



void Animation::SetSprite(sf::Sprite& _sprite)
{
	m_sprite = &_sprite;
}


void Animation::SetPlayBackSpeed(float _framesPerSecond)
{

	m_playBackSpeed = _framesPerSecond;

	// if the playback speed is zero,
	// pause to protec form divide by zero erro

	if (m_playBackSpeed == 0)
	{
		Pause();
	}
}

void Animation::SetLoop(bool _loop)
{
	m_loop = _loop;
}