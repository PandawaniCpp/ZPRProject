#pragma once
#include <map>
#include <memory>
#include <cassert>
#include <SFML/Graphics.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	ResourceHolder ();
	virtual ~ResourceHolder ();

		//for general purposes
	void load (Identifier id, const std::string& filename);	
		//special overload for sf::Shaders
	template <typename Parameter>
	void load (Identifier id, const std::string& filename, const Parameter& secondParam);
		//getters
	Resource& get (Identifier id);
	const Resource& get (Identifier id) const;

private:
		//resource container - type and pointer
	std::map<Identifier, std::unique_ptr<Resource >> resourceMap;
};

/** IMPLEMENTATION **/

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder () {
}

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder () {
}

/**
	Load new texture from file and store the pointer to it in resourceMap.

	Resource - sf::Texture, sf::Font...
	Identifier - one of ResourceID.h enums (ex. Textures::ID, Fonts::ID...)
	id - specified resource id (listed in ResourceID.h
	filename - file to load
*/
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load (Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource (new Resource ());
		//if file doesn't exist, we must terminate the game
	if (!resource->loadFromFile (filename))		
		throw std::runtime_error ("ResourceHolder::load - Failed to load " + filename);

		//check if the same texture is not loaded twice
	auto inserted = resourceMap.insert (std::make_pair (id, std::move (resource)));
	assert (inserted.second);
}

/**
	Special overload for sf::Shader

	secondParam - specifies the shader (fragment or vertex)
*/
template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load (Identifier id, const std::string& filename, const Parameter& secondParam)
{
	std::unique_ptr<Resource> resource (new Resource ());
	if (!resource->loadFromFile (filename, secondParam))
		throw std::runtime_error ("ResourceHolder::load - Failed to load " + filename);
	auto inserted = resourceMap.insert (std::make_pair (id, std::move (resource)));
	assert (inserted.second);
}

/**
	Returns the resource by given id (ex. Textures::P_BASE)

	id - specified resource id (listed in ResourceID.h
*/
template <typename Resource, typename Identifier>
const Resource & ResourceHolder<Resource, Identifier>::get (Identifier id) const {
	auto found = resourceMap.find (id);		//find resource by id
	assert (found != resourceMap.end ());	//break if given resource doesn't exist
	return *found->second;
}

/**
	Calls the non-const method
*/
template <typename Resource, typename Identifier>
Resource & ResourceHolder<Resource, Identifier>::get (Identifier id) {
	return const_cast<Resource&> (static_cast<const ResourceHolder*>(this)->get (id));
}


