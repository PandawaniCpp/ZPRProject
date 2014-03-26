#include "SurvivalObjectView.h"

SurvivalObjectView::SurvivalObjectView () {
}

SurvivalObjectView::~SurvivalObjectView () {
}

void SurvivalObjectView::attachChild (Ptr child)
{
	child->parent = this;		//caller is parent for attached child
	children.push_back (std::move (child));		//insert new child
}

SurvivalObjectView::Ptr SurvivalObjectView::detachChild (const SurvivalObjectView& node)
{
	//lambda-expression search for child; return true if found
	auto found = std::find_if (children.begin (), children.end (), [&] (Ptr& p) -> bool { return p.get () == &node; });
	assert (found != children.end ());
	Ptr result = std::move (*found);		//assign child pointer to 'result'
	result->parent = nullptr;				//erase parent
	children.erase (found);					//erase child
	return result;
}

void SurvivalObjectView::drawCurrent (sf::RenderWindow& window) const {
	window.draw (*this);
}

void SurvivalObjectView::drawAll (sf::RenderWindow& window) const {
	drawCurrent (window);
	for (const Ptr& child : children) {
		child->drawAll (window);
	}
}


void SurvivalObjectView::setTextureByID (int textureID) {

}
