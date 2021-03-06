//---------------------------------------------------------------------------------------
// Included Libraries
//---------------------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
//---------------------------------------------------------------------------------------
// End Libraries
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
// Project Includes
//---------------------------------------------------------------------------------------
#include "AssetManager.h"
#include "Player.h"
#include "Platform.h"

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

	// Seed random number generator
	srand(time(NULL));

	Player player;
	player.Spawn();

	// Create game camera
	sf::View camera = gameWindow.getDefaultView();

	// Create platforms
	
	std::vector<Platform> platforms;
	for (int i = 0; i < 5; i++)
	{

		platforms.push_back(Platform());
		platforms.back().Spawn();
	}

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

			//Pass input to game objects
			player.Input(gameEvent);



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
		
		// Process all game objects
		player.Update(frameTime);

		// Collision Detection
		std::vector<sf::FloatRect> platformColliders;
		for (auto it = platforms.begin(); it != platforms.end(); it++)
		{

			platformColliders.push_back(it->GetCollider());

		}
		player.HandleCollision(platformColliders);


		// Update camera position
		camera.setCenter(player.GetPosition().x + camera.getSize().x * 0.4f, camera.getCenter().y);


		//-------------------------------------------------------------------------------
		// End Update
		//-------------------------------------------------------------------------------




		//-------------------------------------------------------------------------------
		// Draw
		//-------------------------------------------------------------------------------


		// Clear the window to a single colour
		gameWindow.clear();



		// Draw Everything

		// Draw the game world using the camera
		gameWindow.setView(camera);
		player.Draw(gameWindow);
		for (auto it = platforms.begin(); it != platforms.end(); it++)
		{

			it->Draw(gameWindow);

		}

		//Draw the UI to the window
		gameWindow.setView(gameWindow.getDefaultView());




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
