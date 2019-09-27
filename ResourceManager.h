#pragma once

class ResourceManager
{
public:

	//
	// Texture
	//
	sf::Texture* AcquireTexture(std::string fileName, bool smooth = false);
	void ReleaseTexture(std::string filename);
	void CommitTextureChanges();

	//
	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, int> texturesCount;	// TODO: Redo this to a better solution
	//std::vector<std::string> texturesToRemove;

	//
	// Font
	//
	sf::Font* AcquireFont(std::string fileName);
	void PreLoadFont(std::string fileName);
	//
	std::unordered_map<std::string, sf::Font> fonts;
	
private:
};
