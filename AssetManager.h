#pragma once

//Library includes
#include<map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AssetManager
{

public :

	// Public interface / behaviours

	// Constructer
	AssetManager();

	// Get a texture based on a file name
	static sf::Texture& GetTexture(std::string _filename);

	// Get a sound buffer based on a file name
	//static sf::SoundBuffer& GetSoundBuffer(std::string _filename);

	// Get a font based on a file name
	//static sf::Font& GetFont(std::string _filename);


private:

	// Private data for this class

	// A pointer to the class itself
	// for the singleton design pattern
	// the one and only instance of this class
	static AssetManager* s_instance;

	// List of Textures
	std::map<std::string, sf::Texture> m_textures;

	// List of SoundBuffers
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;

	// List of Fonts
	std::map<std::string, sf::Font> m_fonts;


};