// Library Includes

#include <assert.h>

//Project includes
#include "AssetManager.h"

//Initalise the static reference to our instance - to nullptr (aka zero)
AssetManager* AssetManager::s_instance = nullptr;

//Constructer
AssetManager::AssetManager()
	: m_textures	()
	, m_soundBuffers()
	, m_fonts		()
{

	// Throw an error and stop execution (in debug mode)
	// if a copy of this class has already been created
	assert(s_instance == nullptr);

	// Assign ourselves to the instance pointer
	// - this is the new instance of the class that has just been created
	s_instance = this;

}


sf::Texture& AssetManager::GetTexture(std::string _filename)
{

	// Create an iterator to hold a key and value pair
	// and search for the required key
	// using the passed in file name
	auto keyValuePair = s_instance->m_textures.find(_filename);
	// "auto" is this case is equivalent to writing
	// std::map<std::string, sf::Texture>::iterator
	// this keyword (auto) can be used in cases where the
	// compiler can figure out the type of a variable for you
	// YOU ARE NOT ALLOWED TO USE THIS EXCEPT FOR ITERATORS

	// Did we find the texture? (aka was it already loaded?)
	// (iterator will be at the end if we did Not find it)
	if (keyValuePair != s_instance->m_textures.end())
	{
		
		// Yes! We found it
		return keyValuePair->second;

	}
	else
	{
		
		//No we didn't find it

		// Let's create it then

		// Create a new key value pair using the filename
		// the subscript [] operator creates an entry in
		// the map if there is not already one there

		sf::Texture& texture = s_instance->m_textures[_filename];
		// blank texture has been created
		// now just load it from file using sfml

		texture.loadFromFile(_filename);

		// Return te texture to the calling code
		return texture;

	}
}



sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string _filename)
{

	// Create an iterator to hold a key and value pair
	// and search for the required key
	// using the passed in file name
	auto keyValuePair = s_instance->m_soundBuffers.find(_filename);
	// "auto" is this case is equivalent to writing
	// std::map<std::string, sf::SoundBuffer>::iterator
	// this keyword (auto) can be used in cases where the
	// compiler can figure out the type of a variable for you
	// YOU ARE NOT ALLOWED TO USE THIS EXCEPT FOR ITERATORS

	// Did we find the sound buffer? (aka was it already loaded?)
	// (iterator will be at the end if we did Not find it)
	if (keyValuePair != s_instance->m_soundBuffers.end())
	{

		// Yes! We found it
		return keyValuePair->second;

	}
	else
	{

		//No we didn't find it

		// Let's create it then

		// Create a new key value pair using the filename
		// the subscript [] operator creates an entry in
		// the map if there is not already one there

		sf::SoundBuffer& soundBuffer = s_instance->m_soundBuffers[_filename];
		// blank texture has been created
		// now just load it from file using sfml

		soundBuffer.loadFromFile(_filename);

		// Return te texture to the calling code
		return soundBuffer;

	}
}

sf::Font& AssetManager::GetFont(std::string _filename)
{

	auto keyValuePair = s_instance->m_fonts.find(_filename);

	if (keyValuePair != s_instance->m_fonts.end())
	{

		return keyValuePair->second;

	}
	else
	{

		sf::Font& font = s_instance->m_fonts[_filename];

		font.loadFromFile(_filename);

		return font;

	}

}