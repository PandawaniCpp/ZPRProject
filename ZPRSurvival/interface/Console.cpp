/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Console.h"
std::map<std::string, float> Console::params = {{"ZPR Survival", 0}};

Console::Console () {
}

Console::~Console () {
}

void Console::insert (const std::string & name, const float & value) {
	auto inserted = params.insert (std::make_pair (name, value));
	assert (inserted.second);
}

void Console::draw () {

}