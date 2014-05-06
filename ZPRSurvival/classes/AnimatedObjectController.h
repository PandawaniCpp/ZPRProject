///**
//	@author	Pawel Kaczynski
//	@date	03.04.2014
//
//	Part of the #TITLE survival game.
//
//	This software is provided 'as-is', without any express or implied warranty.
//	In no event will the authors be held liable for any damages arising from the use of this software.
//*/
//
//#pragma once
//#include <cmath>
//#include "../animated/AnimatedObject.h"
//#include "../survival/SurvivalObjectController.h"
//#include <sstream>
//
///**
//	MVC's Controller for AnimatedObject class. Provides functionality and mediate between
//	model and view. Do all the general calculations such as moving, rotating etc.
//*/
//class AnimatedObjectController : public SurvivalObjectController {
//public:
//	// Default constructor.
//	AnimatedObjectController();
//
//	// Default destructor.
//	virtual ~AnimatedObjectController();
//
//	// Set the displacement vector of an object (see: AnimatedObject::displacement) based on 
//	// rotation, direction and speed.
//	void calculateMove (AnimatedObject * animatedObject) const;
//
//	// Calculates new rotation based on vector.
//	// \param rotation - current rotation value
//	// \param rotationVector - which way heading
//	void calculateRotation (float & rotation, const sf::Vector2<float> & rotationVector) const;
//
//	// Updates position by displacement vector. Relatively to current position.
//	// \params position/displacement - current position/displacement from Model.
//	void move (sf::Vector2<float> & position, const sf::Vector2<float> & displacement) const;		
//};
//
///**
//	Practically the (demi)god of all living beings. It's endless posibilities include fames
//	such as: FLAWLESS positioning, EPIC rotation, EXTRAORDINARY object acceleation, PIXEL
//	PER PIXEL collisions, FAIRLY GOOD two dimensional texture animation and MUCH MORE....
//	HOLY MISSISIPI!!!
//*/
//
