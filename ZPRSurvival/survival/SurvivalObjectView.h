/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <SFML/Graphics.hpp>

using sf::Sprite;
using sf::Texture;

class SurvivalObjectView : public Sprite {
public:
	typedef std::unique_ptr<SurvivalObjectView> Ptr;		//very often use of this particular unique_ptr

	SurvivalObjectView ();
	virtual ~SurvivalObjectView ();

	virtual void draw (sf::RenderWindow& window) const;
	void SurvivalObjectView::attachChild (Ptr & child);	//add child to vector 'children'
	SurvivalObjectView::Ptr SurvivalObjectView::detachChild (const SurvivalObjectView& node);	//remove child from vector

		//setters
	void setTextureByID (int textureID);

	virtual void drawAll (sf::RenderWindow& window) const;

protected:
	//virtual void draw (sf::RenderWindow& window) const;
	
	std::vector<Ptr> children;
	SurvivalObjectView* parent;

	Texture texture;
};

