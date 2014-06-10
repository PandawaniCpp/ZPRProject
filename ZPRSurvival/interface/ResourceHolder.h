/**
	@date	03.04.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <map>
#include <memory>
#include <cassert>
#include <SFML/Graphics.hpp>

template <typename Resource, typename Identifier>
/**
	Template class for holding different resources.
	\ Resource - sf::Texture, sf::Font...
	\ Identifier - one of ResourceID.h enums (ex. Textures::ID, Fonts::ID...).
*/
class ResourceHolder {
public:
	// Default constructor.
	ResourceHolder ();

	// Default destructor.
	virtual ~ResourceHolder ();

	// Loading method for general purposes. Load new texture from file and store the pointer to it in resourceMap.
	// \param id - specified resource id (listed in ResourceID.h
	// \param filename - file to load
	void load (Identifier id, const std::string& filename);	

	template <typename Parameter>
	// Special load() overload for sf::Shaders.
	// \param secondParam - specifies the shader (fragment or vertex)
	void load (Identifier id, const std::string& filename, const Parameter& secondParam);

	// Returns the resource by given id (ex.Textures::P_BASE).
	// \param id - specified resource id (listed in ResourceID.h
	const Resource& get (Identifier id) const;

	// Calls the non-const method.
	Resource& get (Identifier id);

	// Erase resource from container.
	void erase (Identifier id);

private:
	// Resource container - type and pointer.
	std::map<Identifier, Resource*> resourceMap;
};

//------------------------------------------------------------------------------------------------------------------

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder () {
}

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder () {
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load (Identifier id, const std::string& filename)
{
	Resource* resource (new Resource ());
		//if file doesn't exist, we must terminate the game
	if (!resource->loadFromFile (filename))		
		throw std::runtime_error ("ResourceHolder::load - Failed to load " + filename);

		//check if the same texture is not loaded twice
	auto inserted = resourceMap.insert (std::make_pair (id, std::move (resource)));
	assert (inserted.second);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load (Identifier id, const std::string& filename, const Parameter& secondParam)
{
	Resource * resource (new Resource ());
	if (!resource->loadFromFile (filename, secondParam))
		throw std::runtime_error ("ResourceHolder::load - Failed to load " + filename);
	auto inserted = resourceMap.insert (std::make_pair (id, std::move (resource)));
	assert (inserted.second);
}

template <typename Resource, typename Identifier>
const Resource & ResourceHolder<Resource, Identifier>::get (Identifier id) const {
	auto found = resourceMap.find (id);		//find resource by id
	assert (found != resourceMap.end ());	//break if given resource doesn't exist
	return *found->second;
}

template <typename Resource, typename Identifier>
Resource & ResourceHolder<Resource, Identifier>::get (Identifier id) {
	return const_cast<Resource&> (static_cast<const ResourceHolder*>(this)->get (id));
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::erase (Identifier id) {
	resourceMap.erase (id);
}
