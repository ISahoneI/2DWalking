#pragma once

#include <iostream>

#include "utilities/timer.h"
#include "graphics/rendering/shader.h"
#include "inputs/window.h"
#include "utilities/mathmanager.h"

#include "graphics/rendering/renderer2d.h"
#include "graphics/paints/sprite.h"

#include "objects/boxs/colliderbox.h"

#include "graphics/layers/layer.h"
#include "graphics/layers/group.h"

#include "graphics/paints/texture.h"
#include "graphics/paints/colormanager.h"

#include "inputs/camera.h"

#include "audio/audiomanager.h"
#include "audio/sound.h"
#include "audio/ambient.h"
#include "audio/sound3d.h"
#include "audio/ambient3d.h"
#include "objects/charas/chara.h"
#include "graphics/layers/worldlayer.h"
#include "objects/maps/tilemap.h"

#include "utilities/global.h"
#include "graphics/fonts/fontmanager.h"

class Engine {

private:
	//2560x1440		1280x720	854x480	  427x240
	Window window = Window("2D Walking", 1280, 720, false);
	AudioManager* audioManager;
	FontManager* fontManager;

	Camera* camera;


	Shader& shad = *new Shader("src/shaders/simple.vert", "src/shaders/simple.frag");
	Shader& shad2 = *new Shader("src/shaders/simple.vert", "src/shaders/simple.frag");
	WorldLayer* worldLayer;
	Layer* layer2;

	//Entities test
	Sprite* map;
	Chara* player;
	Sprite* skyle;
	Chara* charaTest;
	Colliderbox* colliderTest;
	Colliderbox* colliderBordDown;
	Sprite* brouillard;

	TileMap* tileMap;

	Texture* texTest = new Texture("res/textures/test2.png");
	int texCount = 0;
	//Audio test;
	Sound3d* hp;
	Sound* hpRel;
	Ambient3d* hp2;


public:
	Engine();
	~Engine();

	bool isRunning();

	void init();
	void handleSound();
	void update(double deltaTime, double fixedDeltaTime, float elapsedTime);
	void clean();

private:


};