#include "TextureHolder.h"

TextureHolder::TextureHolder () {
}

TextureHolder::~TextureHolder () {
}

void TextureHolder::load (Textures::ID id, const std::string & filename) {
	std::unique_ptr<Texture> texture (new Texture ());
	texture->loadFromFile (filename);
	textureMap.insert (std::make_pair (id, std::move (texture)));
}

Texture & TextureHolder::get (Textures::ID id) {
	return const_cast<Texture&> (static_cast<const TextureHolder*>(this)->get (id));
}

const Texture & TextureHolder::get (Textures::ID id) const {
	auto found = textureMap.find (id);
	return *found->second;
}



