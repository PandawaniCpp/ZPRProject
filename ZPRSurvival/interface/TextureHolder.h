#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

using sf::Texture;

namespace Textures {
	enum ID {
		P_BASE = 1,		//P_xxx - player textures
		I_STONE = 100	//I_xxx - item textures
						//C_xxx - creature textures
						//M_xxx - map elements textures
	};
}

class TextureHolder {
public:
	TextureHolder ();
	virtual ~TextureHolder ();

	void load (Textures::ID id, const std::string& filename);	//load texture from file to be stored in given ID
	Texture & get (Textures::ID id);							//get texture by given Textures::ID
	const Texture & get (Textures::ID id) const;				//...

private:
	std::map <Textures::ID, std::unique_ptr<Texture> > textureMap;
};

