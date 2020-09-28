#pragma once

#include "../../graphics/paints/sprite.h"
#include "../boxs/colliderbox.h"

class Tile : public Sprite {

private:
	Colliderbox* colliderbox;

public:
	Tile(float x, float y, float width, float height, Texture* tileset, SpriteLevel level);
	~Tile();

	void setTexUVTileset(const int x, const int y);
	void setTexUVTileset(const int pos);

	Colliderbox* getColliderbox() { return colliderbox; }

};