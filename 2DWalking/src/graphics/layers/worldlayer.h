#pragma once

#include "layer.h"
#include "../../objects/charas/chara.h"

class WorldLayer : public Layer
{

public:
	WorldLayer(Shader* shader);
	~WorldLayer();

	void add(Sprite* renderable);
	void add(Chara* chara);
	void render();


	struct sortByLevelAndYPosition
	{
		inline bool operator() (Sprite* sprite1, Sprite* sprite2)
		{
			if ((int)sprite1->getLevel() != (int)sprite2->getLevel()) {
				return ((int)sprite1->getLevel() < (int)sprite2->getLevel());
			}
			else {
				return sprite1->getPositionY() > sprite2->getPositionY();
			}
		}
	};

};