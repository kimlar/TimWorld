#include "ResourceManager.h"

//
// Texture
//
sf::Texture* ResourceManager::AcquireTexture(std::string filename, bool smooth)
{
	std::unordered_map<std::string, sf::Texture>::const_iterator it = textures.find(filename);

	if (it == textures.end())
	{
		if (!textures[filename].loadFromFile("Assets/Textures/" + filename)) //if (!textures[filename].loadFromFile(filename))
		{
			LogError("ResourceManager.cpp: Could not load texture: " + filename);
			return {};
		}
		textures[filename].setSmooth(smooth);
		texturesCount[filename] = 1;
		Log("ResourceManager::AcquireTexture(" + filename + ") .. Load texture .. count = 1");
		return &(textures[filename]);
	}
	texturesCount[filename]++;
	Log("ResourceManager::AcquireTexture(" + filename + ") .. Share texture .. count = " + std::to_string(texturesCount[filename]));
	return &(textures[filename]);
}
void ResourceManager::ReleaseTexture(std::string filename)
{
	std::unordered_map<std::string, sf::Texture>::const_iterator it = textures.find(filename);

	if (it != textures.end())
	{
		texturesCount[filename]--;

		Log("ResourceManager::ReleaseTexture(" + filename + ") .. Decrease count = " + std::to_string(texturesCount[filename]));
		return; // decreased texture count
	}
	LogError("ResourceManager.cpp: Tried to release a texture but somehow failed: " + filename);
	return; // not good!
}
void ResourceManager::CommitTextureChanges()
{
	std::vector<std::string> texturesToRemove;
	for (auto& it : texturesCount)
	{
		if (it.second <= 0)
			texturesToRemove.push_back(it.first);
	}

	for (int i = 0; i < texturesToRemove.size(); i++)
	{
		texturesCount.erase(texturesToRemove[i]);
		textures.erase(texturesToRemove[i]);
		Log("ResourceManager::CommitTextureChanges(" + texturesToRemove[i] + ") .. Releasing texture -> count = 0");
	}
}


//
// Font
//
sf::Font* ResourceManager::AcquireFont(std::string fileName)
{
	std::unordered_map<std::string, sf::Font>::const_iterator it = fonts.find(fileName);

	if (it == fonts.end())
		PreLoadFont(fileName);

	return &fonts[fileName];
}
void ResourceManager::PreLoadFont(std::string fileName)
{
	std::unordered_map<std::string, sf::Font>::const_iterator it = fonts.find(fileName);

	if (it == fonts.end())
	{
		LogTest(!fonts[fileName].loadFromFile("Assets/Fonts/" + fileName),
			"ResourceManager.cpp: Could not load font : " + fileName);
	}
}
