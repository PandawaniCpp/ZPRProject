/**
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "Command.h"
#include <queue>

class CommandQueue {
public:
	// Push command into the queue.
	void push (Command * command);

	// Take the first inserted.
	Command * pop ();

	// Check whether queue is empty.
	bool isEmpty () const;

private:
	std::queue<Command*>	queue;		// Queue from which scene graph is taking commands.
};
