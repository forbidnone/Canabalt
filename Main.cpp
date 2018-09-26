//---------------------------------------------------------------------------------------
// Included Libraries
//---------------------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
//---------------------------------------------------------------------------------------
// End Libraries
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
// Project Includes
//---------------------------------------------------------------------------------------
#include "AssetManager.h"
#include "Animation.h"

//---------------------------------------------------------------------------------------
// End Project Inlcudes
//---------------------------------------------------------------------------------------


int main()
{


	//-----------------------------------------------------------------------------------
	// Game Setup
	// ----------------------------------------------------------------------------------


	// Make a variable called gameWindow of type RenderWindow
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Canabalt",
		sf::Style::Titlebar | sf::Style::Close);



	//Timer functionallity
	sf::Clock gameClock;

	// Create AssetManager
	AssetManager assets;

	//Testing AssetManager
	sf::Sprite testSprite;
	testSprite.setTexture(AssetManager::GetTexture("graphics/playerJump.png"));
	sf::Sound testSound;
	testSound.setBuffer(AssetManager::GetSoundBuffer("audio/death.wav"));
	testSound.play();
	sf::Text testText;
	testText.setFont(AssetManager::GetFont("fonts/mainFont.ttf"));
	testText.setString("TEST TEXT");


	// Testing Animation
	Animation testAnimation;
	testAnimation.SetSprite(testSprite);
	testAnimation.AddFrame(AssetManager::GetTexture("graphics/playerrun1.png"));
	testAnimation.AddFrame(AssetManager::GetTexture("graphics/playerrun2.png"));
	testAnimation.SetLoop(true);
	testAnimation.SetPlayBackSpeed(10.0f);
	testAnimation.Play();


	//----------------------------------------------------------------------------------
	//End game Setup
	//----------------------------------------------------------------------------------





	//-----------------------------------------------------------------------------------
	// Game Loop
	//-----------------------------------------------------------------------------------
	// Runs every frame until the game window is closed


	while (gameWindow.isOpen())
	{


		//-------------------------------------------------------------------------------
		//Input
		//-------------------------------------------------------------------------------


		sf::Event gameEvent;

		while (gameWindow.pollEvent(gameEvent))
		{


			if (gameEvent.type == sf::Event::Closed)
			{
				gameWindow.close();
			}// end if(closed)


		} // End while 



		//-------------------------------------------------------------------------------
		// End Input
		//-------------------------------------------------------------------------------




		//-------------------------------------------------------------------------------
		// Update
		//-------------------------------------------------------------------------------

		sf::Time frameTime = gameClock.restart();

		// Update our Animation
		testAnimation.Update(frameTime);


		//-------------------------------------------------------------------------------
		// End Update
		//-------------------------------------------------------------------------------




		//-------------------------------------------------------------------------------
		// Draw
		//-------------------------------------------------------------------------------


		// Clear the window to a single colour
		gameWindow.clear(sf::Color::Black);



		// Draw Everything
		gameWindow.draw(testText);
		gameWindow.draw(testSprite);

		
		



		// Display the window contents on the screen
		gameWindow.display();




		//-------------------------------------------------------------------------------
		//End Draw
		//-------------------------------------------------------------------------------



	} //End game while loop

	//-----------------------------------------------------------------------------------
	// End Game Loop
	//-----------------------------------------------------------------------------------


	return 0;
} // End main function
