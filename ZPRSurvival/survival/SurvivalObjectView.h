#pragma once
#include <SFML/Graphics.hpp>

using sf::Sprite;
using sf::Texture;

class SurvivalObjectView : public Sprite {
public:
	SurvivalObjectView ();
	virtual ~SurvivalObjectView ();
		//getters
	//Texture  getTexture ();	//any sense?
		//setters
	void setTextureID (int textureID);

protected:
	Texture texture;
};

