#pragma once
#include <string>
#include "../AnimatedObject.h"
#include "../controller/PlayerController.h"

using namespace std;

class Player : public AnimatedObject
{
	private:
	PlayerController playerController;
	public:
	Player ();
	virtual ~Player ();
};

