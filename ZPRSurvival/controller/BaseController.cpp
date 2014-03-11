#include "BaseController.h"


BaseController::BaseController ()
{
	position.x = 0;
	position.y = 0;
	viewAngle = 0;
}

BaseController::BaseController (BaseController & baseController)
{
	position.x = baseController.position.x;
	position.y = baseController.position.y;
	viewAngle = baseController.viewAngle;
}


BaseController::~BaseController ()
{
}

void BaseController::Move (Vector2<double> positionDelta)
{
	position.x += positionDelta.x;
	position.y += positionDelta.y;
}
