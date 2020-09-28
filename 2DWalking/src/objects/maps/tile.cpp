#include "tile.h"

Tile::Tile(float x, float y, float width, float height, Texture* tileset, SpriteLevel level) : Sprite(x, y, width, height, tileset)
{
	colliderbox = new Colliderbox(x, y, width, height);
	setLevel(level);
}

Tile::~Tile()
{
	delete colliderbox;
}

void Tile::setTexUVTileset(const int x, const int y)
{
	uv.clear();
	const float tx = (float)(x * getWidth()) / (float)texture->getWidth();
	const float ty = (float)(y * getHeight()) / (float)texture->getHeight();
	const float w = (float)getWidth() / (float)texture->getWidth();
	const float h = (float)getHeight() / (float)texture->getHeight();
	uv.push_back(glm::vec2(tx, h + ty));
	uv.push_back(glm::vec2(tx, ty));
	uv.push_back(glm::vec2(w + tx, ty));
	uv.push_back(glm::vec2(w + tx, h + ty));
}

void Tile::setTexUVTileset(const int pos)
{
	const int x = ((pos - 1) % (int)(texture->getWidth() / getWidth()));
	const int y = ((pos - x) / (int)(texture->getWidth() / getWidth()));
	setTexUVTileset(x, y);
}
