#include "House.h"

//House::House(SharedContext* sharedContext, std::string textureFileName, sf::Vector2f position, sf::Vector2i size)
//House::House(SharedContext* sharedContext, std::string textureFileName, sf::Vector2f position)
House::House(SharedContext* sharedContext, std::string objectFile, sf::Vector2f position)
{
	this->sharedContext = sharedContext;
	this->renderWindow = sharedContext->renderWindow;
	this->camera = sharedContext->camera;

	//LoadObjectFile("Assets/Objects/Building-treehouse-01.txt");
	LoadObjectFile(objectFile);

	// Create our pre render texture (compiled)
	renderTexture = new sf::RenderTexture();
	LogTest(!renderTexture->create(size.x, size.y), "House.cpp: Could not create render texture");

	// Load the house texture (raw parts)
	houseTexture = sharedContext->GetResourceManager()->AcquireTexture(textureFileName);
	LogTest(!houseTexture, "House.cpp: Could not load texture: " + textureFileName);
	houseSprite.setTexture(renderTexture->getTexture());
	houseSprite.setPosition(position);

	/*
	parts["stud-wooden"] = sf::IntRect(0, 0, 32, 32);
	parts["wall-wooden-WE"] = sf::IntRect(32, 0, 32, 32);
	parts["wall-wooden-NS"] = sf::IntRect(64, 0, 32, 32);
	*/
//	parts.push_back(sf::IntRect(0, 0, 32, 32));
//	parts.push_back(sf::IntRect(32, 0, 32, 32));
//	parts.push_back(sf::IntRect(64, 0, 32, 32));		


	PreRenderClear();
	for (int i = 0; i < vArr.size(); i++)
	{
		//PreRenderAdd(sf::Vector2f(kArr[1], kArr[2]), kArr[0]);
		PreRenderAdd(sf::Vector2f((float)vArr[i].y, (float)vArr[i].z), vArr[i].x);
	}
	PreRenderCompile();
}

House::~House()
{
	GetSharedContext()->GetResourceManager()->ReleaseTexture(textureFileName);
	
	delete renderTexture;
	renderTexture = nullptr;

	vArr.clear();
	parts.clear();
}

void House::Update(float delta)
{
	renderStates.transform = sf::Transform().translate(-camera->GetX(), -camera->GetY());
}

void House::Render()
{
	renderWindow->draw(houseSprite, renderStates);
}

void House::PreRenderClear()
{
	renderTexture->clear(sf::Color::Red);
	//renderTexture->clear();
}

//void House::PreRenderAdd(sf::Vector2f position, sf::IntRect texRect)
//void House::PreRenderAdd(sf::Vector2f position, std::string partName)
void House::PreRenderAdd(sf::Vector2f position, int partNum)
{
	sf::Sprite sprite;
	sprite.setTexture(*houseTexture);
	sprite.setPosition(position);
	//sprite.setTextureRect(texRect);
	//sprite.setTextureRect(parts[partName]);
	sprite.setTextureRect(parts[partNum]);

	renderTexture->draw(sprite, renderStates);
}

void House::PreRenderCompile()
{
	renderTexture->display();
}

SharedContext* House::GetSharedContext()
{
	return sharedContext;
}

void House::LoadObjectFile(std::string filename)
{
	std::vector<std::string> vLines;
	std::string line;
	std::ifstream houseObjectFile("Assets/Objects/" + filename);
	if (houseObjectFile.is_open())
	{
		while (std::getline(houseObjectFile, line))
		{
			//Process(line);
			vLines.push_back(line);
		}
		houseObjectFile.close();
	}
	else
	{
		LogError("House.cpp: Could not read file: " + filename);
	}

	///////////////////////////////////////////////////////////////////////

	/*
		"General"=
		{
		size=352,192
		texture="Building-treehouse-01.png"
		}

		"TextureCoords"=
		{
		0,0,32,32
		32,0,32,32
		64,0,32,32
		}
	*/

	std::string sectionName = "";
	bool insideBlock = false;
	for (int i = 0; i < vLines.size(); i++)
	{
		if (vLines[i] == "//" || vLines[i] == "")
			continue;

		if (!insideBlock)
		{
			if (vLines[i].size() > 3)
			{
				if (vLines[i][0] == '\"')
				{
					for (int j = 1; j < vLines[i].size(); j++)
					{
						if (vLines[i][j - 1] == '\"')
						{
							if (vLines[i][j] == '=')
							{
								sectionName = vLines[i].substr(1, j - 2);
								//Debug("#" + sectionName + "#");
								break;
							}
						}
					}
				}
			}
			else
			{
				if (vLines[i][0] == '{')
				{
					insideBlock = true;
					continue;
				}
			}
		}
		else
		{
			if (vLines[i][0] == '}')
			{
				insideBlock = false;
				continue;
			}
		}

		if (sectionName == "General" && insideBlock)
		{
			//Debug("#" + vLines[i] + "#");

			if (vLines[i].size() > 5)
			{
				if (vLines[i].substr(0, 5) == "size=")
				{
					//Debug("#" + vLines[i].substr(0, 5) + "#");
					//size.x = 10;
					for (int k = 6; k < vLines[i].size(); k++)
					{
						if (vLines[i][k] == ',')
						{
							//Debug("#" + vLines[i].substr(5, k-5) + "#");
							size.x = std::stoi(vLines[i].substr(5, k - 5));
							size.y = std::stoi(vLines[i].substr(k + 1));
							break;
						}
					}
				}
				if (vLines[i].substr(0, 8) == "texture=")
				{
					//Debug("#" + vLines[i].substr(9, vLines[i].size() - 10) + "#");
					textureFileName = vLines[i].substr(9, vLines[i].size() - 10);
				}
			}
		}

		if (sectionName == "TextureCoords" && insideBlock)
		{
			//Debug("#" + vLines[i] + "#");
			//int,int,int,int
			//parts.push_back(sf::IntRect(0, 0, 32, 32));
			int kArr[4] = { 0,0,0,0 };
			int kCount = 0;
			int k = 0;
			for (int j = 0; j < vLines.size(); j++)
			{
				if (vLines[i][j] == ',')
				{
					if (kCount == 0)
					{
						//Debug("#" + vLines[i].substr(k, j - k) + "#");
						kArr[kCount] = std::stoi(vLines[i].substr(k, j - k));
					}
					else
					{
						//Debug("#" + vLines[i].substr(k + 1, j - k - 1) + "#");
						kArr[kCount] = std::stoi(vLines[i].substr(k + 1, j - k - 1));
					}
					k = j;
					kCount++;
					if (kCount > 2)
					{
						//Debug("#" + vLines[i].substr(k+1) + "#");
						kArr[kCount] = std::stoi(vLines[i].substr(k + 1));

						//Debug("#" + std::to_string(kArr[0]) + "," + std::to_string(kArr[1]) + "," + std::to_string(kArr[2]) + "," + std::to_string(kArr[3]) + "#");
						parts.push_back(sf::IntRect(kArr[0], kArr[1], kArr[2], kArr[3]));
						break;
					}
				}
			}
		}

		if (sectionName == "Layer 0" && insideBlock)
		{
			//Debug("#" + vLines[i] + "#");
		}

		if (sectionName == "Layer 1" && insideBlock)
		{
			//Debug("#" + vLines[i] + "#");

			if (vLines[i].size() > 1 && vLines[i][0] == '/' && vLines[i][1] == '/')
				continue;

			int kArr[3] = { 0,0,0 };
			int kCount = 0;
			int k = 0;
			for (int j = 0; j < vLines.size(); j++)
			{
				if (vLines[i][j] == ',')
				{
					if (kCount == 0)
					{
						//Debug("#" + vLines[i].substr(k, j - k) + "#");
						kArr[kCount] = std::stoi(vLines[i].substr(k, j - k));
					}
					else
					{
						//Debug("#" + vLines[i].substr(k + 1, j - k - 1) + "#");
						kArr[kCount] = std::stoi(vLines[i].substr(k + 1, j - k - 1));
					}
					k = j;
					kCount++;
					if (kCount > 1)
					{
						//Debug("#" + vLines[i].substr(k+1) + "#");
						kArr[kCount] = std::stoi(vLines[i].substr(k + 1));

						//Debug("#" + std::to_string(kArr[0]) + "," + std::to_string(kArr[1]) + "," + std::to_string(kArr[2]) + "#");
						//kArr[0]
						//kArr[1]
						//kArr[2]

						//PreRenderAdd(sf::Vector2f(kArr[1], kArr[2]), kArr[0]);
						//vArr.push_back(kArr[0], kArr[1], kArr[2]);
						vArr.push_back(sf::Vector3i(kArr[0], kArr[1], kArr[2]));
						break;
					}
				}
			}

		}
	}
}
