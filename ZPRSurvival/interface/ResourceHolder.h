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

	void load (Identifier id, const std::string& filename);
	Resource& get (Identifier id);
	const Resource& get (Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource >> resourceMap;
};

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder () {
}

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder () {
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load (Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource (new Resource ());
	if (!resource->loadFromFile (filename))
		throw std::runtime_error ("ResourceHolder::load - Failed to load " + filename);
	auto inserted = resourceMap.insert (std::make_pair (id, std::move (resource)));
	assert (inserted.second);
}

template <typename Resource, typename Identifier>
Resource & ResourceHolder<Resource, Identifier>::get (Identifier id) {
	return const_cast<Resource&> (static_cast<const ResourceHolder*>(this)->get (id));
}

template <typename Resource, typename Identifier>
const Resource & ResourceHolder<Resource, Identifier>::get (Identifier id) const {
	auto found = resourceMap.find (id);
	assert (found != resourceMap.end ());	//given resource doesn't exist
	return *found->second;
}

