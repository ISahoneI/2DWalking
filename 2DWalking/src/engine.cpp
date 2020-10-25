#include "engine.h"

Engine::Engine()
{
	init();
}

Engine::~Engine()
{
}

bool Engine::isRunning()
{
	return !window.closed();
}

void Engine::init()
{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	audioManager = new AudioManager();
	fontManager = new FontManager();

	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f));


	worldLayer = new WorldLayer(&shad);	layer2 = new Layer(&shad2);
	worldLayer->setCamera(camera);

	Texture* herosYzao = new Texture("res/textures/spritesheet/Heros_Yzao.png");
	//Entities
	map = new Sprite(0.0f, 0.0f, 800.0f, 1680.0f, new Texture("res/textures/Omara.png"), glm::vec4(255, 255, 255, 255));
	player = new Chara(herosYzao);
	skyle = new Sprite(350, 180, 24, 32, new Texture("res/textures/skyle_bas.png"));
	skyle->setLevel(SpriteLevel::LEVEL1);
	charaTest = new Chara(herosYzao);
	charaTest->move(281, 150);

	colliderTest = new Colliderbox(96, 144, 176, 96);
	colliderBordDown = new Colliderbox(-16, -16, 816, 16);

	brouillard = new Sprite(0, 0, ENGINE_RESOLUTION_X, ENGINE_RESOLUTION_Y, new Texture("res/textures/brouillard_bleu.png"), glm::vec4(255, 255, 255, 70));



	//worldLayer->add(map);
	worldLayer->add(skyle);
	worldLayer->add(player);
	worldLayer->add(charaTest);
	worldLayer->add(colliderTest);
	worldLayer->add(colliderBordDown);

	layer2->add(brouillard);

	tileMap = new TileMap(new Texture("res/textures/tilemaps/chipset.png"), "res/textures/tilemaps/map.tmx");
	worldLayer->setTilemap(tileMap);

	//AUDIO
	hp = new Sound3d();
	hp->setPosition(skyle->getPositionX(), skyle->getPositionY(), 100);
	hpRel = new Sound();
	hp2 = new Ambient3d();
	hp2->setPosition(skyle->getPositionX(), skyle->getPositionY(), 100);
	AudioManager::playMusic(DW_MUSIC_3);

}

void Engine::handleSound()
{
	AudioManager::updateMusic();

	if (InputManager::isKeyPressed(GLFW_KEY_M))
		AudioManager::stopMusic();

	if (InputManager::isKeyPressedOnce(GLFW_KEY_L))
		AudioManager::playAmbient(DW_AMBIENT_1, 1.0f, 1.0f);

	if (InputManager::isKeyPressedOnce(GLFW_KEY_O))
		AudioManager::playMusic(DW_MUSIC_4);

	AudioManager::setListenerPosition(glm::vec3(player->getPositionX(), player->getPositionY(), player->getPositionZ()));
	if (InputManager::isKeyPressedOnce(GLFW_KEY_I) || InputManager::isGamepadButtonPressedOnce(GAMEPAD_BUTTON_A))
		hp->play(AudioManager::getBufferSound(DW_SOUND_1), 1.0f, 1.0f);
	if (InputManager::isKeyPressedOnce(GLFW_KEY_P))
		hpRel->play(AudioManager::getBufferSound(DW_SOUND_1), 1.0f, 1.0f);
	if (InputManager::isKeyPressedOnce(GLFW_KEY_J))
		hp2->play(AudioManager::getBufferSound(DW_AMBIENT_1), 1.0f, 1.0f);

	if (InputManager::isKeyPressedOnce(GLFW_KEY_V))
		charaTest->playSound(DW_SOUND_1);

}


void Engine::update(double deltaTime, double fixedDeltaTime, float elapsedTime)
{
	window.clear();


	worldLayer->render();
	/***********INPUTS************/
	double scrollY = InputManager::getScrollYOffset();
	if (scrollY != 0)
	{
		camera->actionZoom((float)scrollY);
		//std::cout << "ScrollY = " << scrollY << std::endl;
	}


	if (InputManager::isKeyPressed(GLFW_KEY_SPACE))
	{
		player->setPosition(0.0f, 0.0f, 1.0f);
		camera->setZoom(1.0f);
	}


	if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE))
		window.close();


	if (InputManager::isKeyPressed(GLFW_KEY_T))
	{
		float player_trans = player->getTransparency() + 100.0f * (float)deltaTime;
		player->setTransparency(player_trans);
	}
	if (InputManager::isKeyPressed(GLFW_KEY_R))
	{
		float player_trans = player->getTransparency() - 100.0f * (float)deltaTime;
		player->setTransparency(player_trans);
	}
	if (InputManager::isKeyPressed(GLFW_KEY_U)) {
		layer2->add(FontManager::getTextToRender("We are\nVENOM !!", "msgothic12"));
		//skyle->setIsVisible(!skyle->getIsVisible());
		/*Sprite* mapTestAdd = new Sprite(player->getPositionX(), player->getPositionY(), 16.0f, 16.0f, texTest, glm::vec4(255, 255, 255, 255));
		mapTestAdd->setLevel(SpriteLevel::FOREGROUND);
		worldLayer->add(mapTestAdd);
		texCount++;
		std::cout << texCount << std::endl;*/
	}

	if (InputManager::isKeyPressed(GLFW_KEY_X))
		player->setSpeed(player->getSpeed() + 100.0f * (float)deltaTime);
	if (InputManager::isKeyPressed(GLFW_KEY_Z))
		player->setSpeed(player->getSpeed() - 100.0f * (float)deltaTime);


	//DEPLACEMENT
	float deplacement = player->getSpeed() * (float)deltaTime;
	float xdir = player->getPositionX();
	float ydir = player->getPositionY();

	if (InputManager::isKeyPressed(GLFW_KEY_RIGHT) || InputManager::isKeyPressed(GLFW_KEY_D) || InputManager::isGamepadButtonPressed(GAMEPAD_BUTTON_DPAD_RIGHT))
	{
		xdir += deplacement;
	}
	if (InputManager::isKeyPressed(GLFW_KEY_LEFT) || InputManager::isKeyPressed(GLFW_KEY_A) || InputManager::isGamepadButtonPressed(GAMEPAD_BUTTON_DPAD_LEFT))
	{
		xdir -= deplacement;
	}
	if (InputManager::isKeyPressed(GLFW_KEY_DOWN) || InputManager::isKeyPressed(GLFW_KEY_S) || InputManager::isGamepadButtonPressed(GAMEPAD_BUTTON_DPAD_DOWN))
	{
		ydir -= deplacement;
	}
	if (InputManager::isKeyPressed(GLFW_KEY_UP) || InputManager::isKeyPressed(GLFW_KEY_W) || InputManager::isGamepadButtonPressed(GAMEPAD_BUTTON_DPAD_UP))
	{
		ydir += deplacement;
	}

	float inputJoystickX = InputManager::gamepadJoystickValue(GAMEPAD_JOYSTICK_LEFT_X);
	float inputJoystickY = InputManager::gamepadJoystickValue(GAMEPAD_JOYSTICK_LEFT_Y);
	if (inputJoystickX != 0.0f || inputJoystickY != 0.0f) {
		xdir = player->getPositionX() + deplacement * inputJoystickX;
		ydir = player->getPositionY() + deplacement * inputJoystickY;
	}

	player->move(xdir, ydir);

	if (!player->getColliderbox()->isOverlap(charaTest->getColliderbox()))
		charaTest->move(charaTest->getPositionX() + charaTest->getSpeed() * (float)deltaTime, charaTest->getPositionY());

	player->collide(colliderTest);
	player->collide(colliderBordDown);
	player->collide(charaTest->getColliderbox());
	float playerColliderX = player->getColliderbox()->getCenterX();
	float playerColliderY = player->getColliderbox()->getCenterY();
	player->collide(tileMap->getTileAt((int)player->getLevel(), playerColliderX + TILE_RESOLUTION, playerColliderY)->getColliderbox());
	player->collide(tileMap->getTileAt((int)player->getLevel(), playerColliderX - TILE_RESOLUTION, playerColliderY)->getColliderbox());
	player->collide(tileMap->getTileAt((int)player->getLevel(), playerColliderX, playerColliderY + TILE_RESOLUTION)->getColliderbox());
	player->collide(tileMap->getTileAt((int)player->getLevel(), playerColliderX, playerColliderY - TILE_RESOLUTION)->getColliderbox());
	player->collide(tileMap->getTileAt((int)player->getLevel(), playerColliderX + TILE_RESOLUTION, playerColliderY + TILE_RESOLUTION)->getColliderbox());
	player->collide(tileMap->getTileAt((int)player->getLevel(), playerColliderX + TILE_RESOLUTION, playerColliderY - TILE_RESOLUTION)->getColliderbox());
	player->collide(tileMap->getTileAt((int)player->getLevel(), playerColliderX - TILE_RESOLUTION, playerColliderY + TILE_RESOLUTION)->getColliderbox());
	player->collide(tileMap->getTileAt((int)player->getLevel(), playerColliderX - TILE_RESOLUTION, playerColliderY - TILE_RESOLUTION)->getColliderbox());

	for (Colliderbox* collider : tileMap->getColliders()) {
		player->collide(collider);
	}

	player->update(deltaTime);

	charaTest->update(deltaTime);

	/************ CAMERA **************/
	camera->centerOn(player->getCenterX(), player->getCenterY());


	//std::cout << "x:" << (int)(player->getPositionX() / 16) << " y:" << (int)(player->getPositionY() / 16) << " TileID:" <<
	//	tileMap->getTileAt(1, (player->getCenterX()), (int)(player->getPositionY() + 4))->getColliderbox()->getIsCollidable() << std::endl;
	//if (tileMap->getTileAt(0, (player->getCenterX()), (int)(player->getPositionY() + 4)) != NULL)
	//	tileMap->getTileAt(0, (player->getCenterX()), (int)(player->getPositionY() + 4))->setIsVisible(false);

	/*float point_rotX = player->getPositionX();
	float point_rotY = player->getPositionY();
	glm::mat4 mat = glm::translate(glm::mat4(1), glm::vec3(point_rotX, point_rotY, point_rotX));
	mat = mat * glm::rotate(glm::mat4(1), elapsedTime * 0.05f, glm::vec3(0, 0, 1));
	mat = mat * glm::translate(glm::mat4(1), glm::vec3(-point_rotX, -point_rotY, -point_rotX));

	shad.setUniformMat4("modele_mat", mat);*/
	shad.enable();


	shad.setUniformMat4("projection_mat", camera->getProjectionMatrix());
	shad.setUniformMat4("view_mat", camera->getViewMatrix());
	worldLayer->update();

	shad2.enable();

	shad2.setUniformMat4("projection_mat", glm::ortho(0.0f, (float)ENGINE_RESOLUTION_X, 0.0f, (float)ENGINE_RESOLUTION_Y, -1.0f, 1.0f));
	layer2->render();


	window.update();
}


void Engine::clean()
{
}


