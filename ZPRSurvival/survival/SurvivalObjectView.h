#pragma once
#include <SFML/Graphics.hpp>

using sf::Sprite;
using sf::Texture;

class SurvivalObjectView : public Sprite {
public:
	SurvivalObjectView ();
	virtual ~SurvivalObjectView ();

		//setters
	void setTextureByID (int textureID);

protected:
	Texture texture;
};

