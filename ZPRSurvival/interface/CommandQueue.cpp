/**
	@date	03.04.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "CommandQueue.h"

void CommandQueue::push (Command * command)
{
	queue.push (command);
}

Command * CommandQueue::pop ()
{
	Command * command = queue.front ();
	queue.pop ();
	return command;
}

bool CommandQueue::isEmpty () const
{
	return queue.empty ();
}