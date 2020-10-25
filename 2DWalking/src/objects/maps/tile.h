#pragma once

#include "../../graphics/paints/sprite.h"
#include "../boxs/colliderbox.h"

class Tile : public Sprite {

private:
	Colliderbox* colliderbox;
	int idTile;

public:
	Tile(float x, float y, float width, float height, SpriteLevel level);
	Tile(float x, float y, float width, float height, Texture* tileset, SpriteLevel level);
	~Tile();

	void setTexUVTileset(const int x, const int y);
	void setTexUVTileset(const int pos);

	void setIdTile(int idTile) { this->idTile = idTile; }
	const int getIdTile() const { return idTile; }

	Colliderbox* getColliderbox() { return colliderbox; }

};