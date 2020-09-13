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


	shad.enable();
	shad2.enable();

	worldLayer = new WorldLayer(&shad);	layer2 = new Layer(&shad2);

	//Entities
	map = new Sprite(0.0f, 0.0f, 800.0f, 1680.0f, new Texture("res/textures/Omara.png"), glm::vec4(255, 255, 255, 255));
	player = new Chara();
	skyle = new Sprite(350, 180, 24, 32, new Texture("res/textures/skyle_bas.png"));
	skyle->setLevel(SpriteLevel::LEVEL1);
	charaTest = new Chara();
	charaTest->move(281, 150);

	colliderTest = new Colliderbox();
	colliderTest->setSize(176, 96);
	colliderTest->setPosition(96, 144);
	colliderBordDown = new Colliderbox();
	colliderBordDown->setPosition(-16, -16);
	colliderBordDown->setSize(816, 16);

	brouillard = new Sprite(0, 0, 16, 9, new Texture("res/textures/brouillard_bleu.png"), glm::vec4(255, 255, 255, 70));

	group = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(4, 4, 0)));
	group->add(new Sprite(4, 4, 4, 4, glm::vec4(255, 255, 0, 102)));
	group->add(new Sprite(4, 4, 3, 3, glm::vec4(0, 0, 255, 128)));
	group->add(new Sprite(4, 4, 2, 2, glm::vec4(255, 0, 255, 102)));
	group->add(new Sprite(4, 4, 1, 1, glm::vec4(0, 255, 0, 102)));

	worldLayer->add(map);
	worldLayer->add(skyle);
	worldLayer->add(player);
	worldLayer->add(charaTest);
	worldLayer->add(colliderTest);
	worldLayer->add(colliderBordDown);
	worldLayer->add(new Sprite(0.0f, 0.0f, 800.0f, 1680.0f, new Texture("res/textures/tilemaps/zone_sup.png"), glm::vec4(255, 255, 255, 255)));

	layer2->add(brouillard);

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

}


void Engine::update(double deltaTime)
{
	window.update();

	float playerCenterX = player->getPositionX() - (427.0f * 0.5f) + (player->getWidth() * 0.5f);
	float playerCenterY = player->getPositionY() - (240.0f * 0.5f) + (player->getHeight() * 0.5f);

	/***********INPUTS************/
	double scrollY = InputManager::getScrollYOffset();
	if (scrollY != 0)
	{
		camera.actionZoom((float)scrollY);
		//std::cout << "ScrollY = " << scrollY << std::endl;
	}


	if (InputManager::isKeyPressed(GLFW_KEY_SPACE))
	{
		player->setPosition(0.0f, 0.0f, 1.0f);
		camera.setZoom(1.0f);
		camera.setPosition((playerCenterX + 8.0f) * camera.getZoom(), (playerCenterY + 4.5f) * camera.getZoom());

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
	if (InputManager::isKeyPressedOnce(GLFW_KEY_U)) {
		skyle->setIsRender(false);
	}

	if (InputManager::isKeyPressed(GLFW_KEY_X))
		player->setSpeed(player->getSpeed() + 0.1f);
	if (InputManager::isKeyPressed(GLFW_KEY_Z))
		player->setSpeed(player->getSpeed() - 0.1f);


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

	player->collide(colliderTest);
	player->collide(colliderBordDown);
	player->collide(charaTest->getColliderbox());
	player->update(deltaTime);
}

void Engine::render()
{
	window.clear();
	double x, y;
	InputManager::getMousePosition(x, y);
	int largeur, hauteur;
	window.getDimension(largeur, hauteur);

	worldLayer->render();
	shad.setUniform2f("light_pos", glm::vec2((float)(x * 427.0f / (float)largeur), (float)(240.0f - y * 240.0f / (float)hauteur)));

	/***** TEST ROTATION  ************
		float point_rot = 6.0f;
		glm::mat4 mat = glm::translate(glm::mat4(1), glm::vec3(point_rot, point_rot, point_rot));
		mat = mat * glm::rotate(glm::mat4(1), time.elapsed(), glm::vec3(0, 0, 1));
		mat = mat * glm::translate(glm::mat4(1), glm::vec3(-point_rot, -point_rot, -point_rot));
		shad.setUniformMat4("modele_mat", mat);
		*****************/


	shad.setUniformMat4("projection_mat", projection);

	/**********Bord de map**********/
	//camera.setPosition(playerCenterX * camera.getZoom(), playerCenterY * camera.getZoom());
	shad.setUniformMat4("view_mat", camera.getViewMatrix());


	layer2->render();

	//shad2.setUniformMat4("modele_mat", mat);
		//shad2.setUniform2f("light_pos", glm::vec2(4.0f, 3.5f));

		/************ CAMERA **************/
			/****Centrer le zoom sur le heros*****/
	float playerCenterX = player->getPositionX() - (427.0f * 0.5f) + (player->getWidth() * 0.5f);
	float playerCenterY = player->getPositionY() - (240.0f * 0.5f) + (player->getHeight() * 0.5f);
	//if (player->getPositionX() >= ((camera.getZoom() * 427.0f - player->getWidth())) / 2.0f && player->getPositionX() <= map->getWidth() - ((camera.getZoom() * 427.0f + player->getWidth())) / 2.0f)
	camera.setPosX(playerCenterX * camera.getZoom());
	//if (player->getPositionY() >= ((camera.getZoom() * 240.0f - player->getHeight())) / 2.0f && player->getPositionY() <= map->getHeight() - ((camera.getZoom() * 240.0f + player->getHeight())) / 2.0f)
	camera.setPosY(playerCenterY * camera.getZoom());

	projection = glm::ortho(
		camera.getZoom() * (0.0f - (player->getPositionX() + 16.0f)) + player->getPositionX() + 16.0f,
		camera.getZoom() * (427.0f - (player->getPositionX() + 16.0f)) + player->getPositionX() + 16.0f,
		camera.getZoom() * (0.0f - (player->getPositionY() + 12.0f)) + player->getPositionY() + 12.0f,
		camera.getZoom() * (240.0f - (player->getPositionY() + 12.0f)) + player->getPositionY() + 12.0f,
		-1.0f,
		1.0f
	);

}

void Engine::clean()
{
}


