#include <iostream>

#include "src/utilities/timer.h"
#include "src/graphics/rendering/shader.h"
#include "src/inputs/window.h"
#include "src/utilities/mathmanager.h"

#include "src/graphics/rendering/renderer2d.h"
#include "src/graphics/paints/sprite.h"

#include "src/objects/boxs/colliderbox.h"

#include "src/graphics/layers/layer.h"
#include "src/graphics/layers/group.h"

#include "src/graphics/paints/texture.h"
#include "src/graphics/paints/colormanager.h"

#include "src/inputs/camera.h"

#include "src/audio/audiomanager.h"
#include "src/audio/sound.h"
#include "src/audio/ambient.h"
#include "src/audio/sound3d.h"
#include "src/audio/ambient3d.h"

int main()
{
	//2560x1440		1280x720	854x480	  426x240
	Window window("2D Walking", 854, 480, false);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//srand((unsigned int)time(NULL));
	//glm::mat4 ort = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	Shader& shad = *new Shader("src/shaders/simple.vert", "src/shaders/simple.frag");
	Shader& shad2 = *new Shader("src/shaders/simple.vert", "src/shaders/simple.frag");
	shad.enable();
	shad2.enable();
	Texture* textures[]
	{
		new Texture("res/textures/test2.png"),
		new Texture("res/textures/test3.png")
	};

	Layer layer(&shad), layer2(&shad2);
	float tilescale = 0.6f;

	Texture* yzao_tex[]
	{
		new Texture("res/textures/yzao_bas.png"),
		new Texture("res/textures/yzao_haut.png"),
		new Texture("res/textures/yzao_droite.png"),
		new Texture("res/textures/yzao_gauche.png")
	};
	Sprite* map = new Sprite(0.0f, 0.0f, tilescale * 800.0f / 16, tilescale * 1680.0f / 16, new Texture("res/textures/Omara.png"), ColorManager::getHexaColori(255, 255, 255, 255));
	layer.add(map);
	Sprite* player = new Sprite(12, 8, 0.6f * 24 / 16, 0.6f * 32 / 16, yzao_tex[0], ColorManager::getHexaColori(255, 254, 253, 252));
	Sprite* skyle = new Sprite(12, 8, 0.6f * 24 / 16, 0.6f * 32 / 16, new Texture("res/textures/skyle_bas.png"));
	layer.add(skyle);
	layer.add(player);
	layer.add(new Colliderbox());

	Sprite* brouillard = new Sprite(0, 0, 16, 9, new Texture("res/textures/brouillard_bleu.png"), ColorManager::getHexaColori(255, 255, 255, 70));
	layer2.add(brouillard);

	/******TEST AJOUT DE VRAI SPRITE AVEC TEXTURE******/
	/*for (float y = 0; y < 9.0f; y += tilescale)
	{
		for (float x = 0; x < 16.0f; x += tilescale)
		{
			layer.add(new Sprite(x, y, tilescale, tilescale, textures[0]));
		}
	}*/

	/***TEST GROUPE DE SPRITE SANS TEXTURE***/
	Group* group = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(4, 4, 0)));
	group->add(new Sprite(4, 4, 4, 4, glm::vec4(1, 1, 0, 0.4f)));
	group->add(new Sprite(4, 4, 3, 3, 0x880000ff));
	group->add(new Sprite(4, 4, 2, 2, glm::vec4(1, 0, 1, 0.4f)));
	group->add(new Sprite(4, 4, 1, 1, glm::vec4(0, 1, 0, 0.4f)));
	//layer2.add(group);
	//layer2.add(new Sprite(8, 6, 1, 1, ColorManager::getHexaColorf(0.3f, 0.3f, 0.3f, 0.8f)));

	/*******SOUND*********/
	AudioManager aud;
	ALuint buff = AudioManager::getBufferSound(DW_SOUND_1);
	ALuint buff2 = AudioManager::getBufferSound(DW_AMBIENT_1);
	Sound3d* hp = new Sound3d();
	hp->setPosition(skyle->getPositionX(), skyle->getPositionY(), 2);
	Sound* hpRel = new Sound();
	Ambient3d* hp2 = new Ambient3d();
	hp2->setPosition(skyle->getPositionX(), skyle->getPositionY(), 2);
	AudioManager::playMusic(DW_MUSIC_3);
	/*AudioStream musicStream;
	AudioStreamInit(&musicStream);
	AudioStreamOpen(&musicStream, DW_MUSIC_1);*/

	/*******CONFIG********/
	bool input_i = false;
	float player_speed = 6.0f;
	float player_trans = 1.0f;
	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

	Timer time;
	while (!window.closed())
	{

		window.clear();
		time.initFrameIteration(glfwGetTime());

		double x, y;
		InputManager::getMousePosition(x, y);
		int largeur, hauteur;
		window.getDimension(largeur, hauteur);

		layer.render();
		shad.setUniform2f("light_pos", glm::vec2((float)(x * 16.0f / (float)largeur), (float)(9.0f - y * 9.0f / (float)hauteur)));

		/***** TEST ROTATION  ************
		float point_rot = 6.0f;
		glm::mat4 mat = glm::translate(glm::mat4(1), glm::vec3(point_rot, point_rot, point_rot));
		mat = mat * glm::rotate(glm::mat4(1), time.elapsed(), glm::vec3(0, 0, 1));
		mat = mat * glm::translate(glm::mat4(1), glm::vec3(-point_rot, -point_rot, -point_rot));
		shad.setUniformMat4("modele_mat", mat);
		*****************/

		/************ CAMERA **************/
		/****Centrer le zoom sur le heros*****/
		float playerCenterX = player->getPositionX() - 16.0f / 2 + player->getWidth() / 2;
		float playerCenterY = player->getPositionY() - 9.0f / 2 + player->getHeight() / 2;
		if (player->getPositionX() >= 16.0f * camera.getZoom() / 2 && player->getPositionX() <= ((map->getWidth() - 0.6) - 16.0f / 2))
			camera.setPosX(playerCenterX * camera.getZoom());
		if (player->getPositionY() >= 9.0f * camera.getZoom() / 2 && player->getPositionY() <= ((map->getHeight() - 0.6) - 9.0f / 2))
			camera.setPosY(playerCenterY * camera.getZoom());

		glm::mat4 projection = glm::ortho(
			(0.0f - (player->getPositionX() + 0.45f)) * camera.getZoom() + (player->getPositionX() + 0.45f),
			(16.0f - (player->getPositionX() + 0.45f)) * camera.getZoom() + (player->getPositionX() + 0.45f),
			(0.0f - (player->getPositionY() + 0.5f)) * camera.getZoom() + (player->getPositionY() + 0.5f),
			(9.0f - (player->getPositionY() + 0.5f)) * camera.getZoom() + (player->getPositionY() + 0.5f),
			-1.0f, 1.0f);
		shad.setUniformMat4("projection_mat", projection);

		/**********Bord de map**********/
		//camera.setPosition(playerCenterX * camera.getZoom(), playerCenterY * camera.getZoom());
		shad.setUniformMat4("view_mat", camera.getViewMatrix());

		/***********INPUTS************/
		double scrollY = InputManager::getScrollYOffset();
		if (scrollY != 0)
		{
			camera.actionZoom((float)scrollY);
			//std::cout << "ScrollY = " << scrollY << std::endl;
		}

		if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();


		if (InputManager::isKeyPressedOnce(GLFW_KEY_G)) {
			time.setFpsLimit(250);
		}
		if (InputManager::isKeyPressedOnce(GLFW_KEY_H)) {
			time.setFpsLimit(60);
		}
		if (InputManager::isKeyPressedOnce(GLFW_KEY_B)) {
			time.setFpsLimit(30);
		}
		if (InputManager::isKeyPressedOnce(GLFW_KEY_N)) {
			time.setFpsLimit(20);
		}

		if (InputManager::isKeyPressed(GLFW_KEY_SPACE))
		{
			player->setPosition(0.0f, 0.0f, 1.0f);
			camera.setZoom(1.0f);
			camera.setPosition((playerCenterX + 8.0f) * camera.getZoom(), (playerCenterY + 4.5f) * camera.getZoom());

		}
		if (InputManager::isKeyPressed(GLFW_KEY_T))
		{
			if (player_trans < 1.0f)
				player_trans += 0.001f;
			//player->setColor(ColorManager::getHexaColorf(1.0f, 1.0f, 1.0f, player_trans));
			player->setTransparency(player_trans);
		}
		if (InputManager::isKeyPressed(GLFW_KEY_R))
		{
			if (player_trans > 0.0f)
				player_trans -= 0.001f;
			//player->setColor(ColorManager::getHexaColorf(1.0f, 1.0f, 1.0f, player_trans));
			player->setTransparency(player_trans);
		}
		/*	if (InputManager::isKeyPressed(GLFW_KEY_I) && input_i == false)
			{
				hp->play(buff);
				input_i = true;
			}
			if (!InputManager::isKeyPressed(GLFW_KEY_I))
				input_i = false;*/
		AudioManager::setListenerPosition(glm::vec3(player->getPositionX(), player->getPositionY(), player->getPositionZ()));
		if (InputManager::isKeyPressedOnce(GLFW_KEY_I) || InputManager::isGamepadButtonPressedOnce(GAMEPAD_BUTTON_A))
			hp->play(buff, 1.0f, 1.0f);
		if (InputManager::isKeyPressedOnce(GLFW_KEY_P))
			hpRel->play(buff, 1.0f, 1.0f);
		if (InputManager::isKeyPressedOnce(GLFW_KEY_J))
			hp2->play(buff2, 1.0f, 1.0f);
		if (InputManager::isKeyPressedOnce(GLFW_KEY_L))
			AudioManager::playAmbient(DW_AMBIENT_1, 1.0f, 1.0f);

		if (InputManager::isKeyPressed(GLFW_KEY_O))
			AudioManager::playMusic(DW_MUSIC_4);

		if (InputManager::isKeyPressed(GLFW_KEY_M))
			AudioManager::stopMusic();

		AudioManager::updateMusic();
		layer2.render();
		//shad2.setUniformMat4("modele_mat", mat);
		//shad2.setUniform2f("light_pos", glm::vec2(4.0f, 3.5f));


		if (time.fpsPassed())
		{
			if (InputManager::isKeyPressed(GLFW_KEY_RIGHT) || InputManager::isKeyPressed(GLFW_KEY_D) || InputManager::isGamepadButtonPressed(GAMEPAD_BUTTON_DPAD_RIGHT))
			{
				player->setTexture(yzao_tex[2]);
				if (player->getPositionX() < (map->getWidth() - 0.8f))
					player->setPositionX(player->getPositionX() + player_speed * (float)time.getDeltaTime());
			}
			if (InputManager::isKeyPressed(GLFW_KEY_LEFT) || InputManager::isKeyPressed(GLFW_KEY_A) || InputManager::isGamepadButtonPressed(GAMEPAD_BUTTON_DPAD_LEFT))
			{
				player->setTexture(yzao_tex[3]);
				if (player->getPositionX() > 0.2f)
					player->setPositionX(player->getPositionX() - player_speed * (float)time.getDeltaTime());
			}
			if (InputManager::isKeyPressed(GLFW_KEY_DOWN) || InputManager::isKeyPressed(GLFW_KEY_S) || InputManager::isGamepadButtonPressed(GAMEPAD_BUTTON_DPAD_DOWN))
			{
				player->setTexture(yzao_tex[0]);
				if (player->getPositionY() > 0.4f)
					player->setPositionY(player->getPositionY() - player_speed * (float)time.getDeltaTime());
			}
			if (InputManager::isKeyPressed(GLFW_KEY_UP) || InputManager::isKeyPressed(GLFW_KEY_W) || InputManager::isGamepadButtonPressed(GAMEPAD_BUTTON_DPAD_UP))
			{
				player->setTexture(yzao_tex[1]);
				if (player->getPositionY() < (map->getHeight() - 0.8f))
					player->setPositionY(player->getPositionY() + player_speed * (float)time.getDeltaTime());
			}

			if (InputManager::isKeyPressed(GLFW_KEY_X))
				player_speed += 0.1f;
			if (InputManager::isKeyPressed(GLFW_KEY_Z))
				player_speed -= 0.1f;

			player->setPositionX(player->getPositionX() + player_speed * (float)time.getDeltaTime() * InputManager::gamepadJoystickValue(GAMEPAD_JOYSTICK_LEFT_X));
			player->setPositionY(player->getPositionY() + player_speed * (float)time.getDeltaTime() * InputManager::gamepadJoystickValue(GAMEPAD_JOYSTICK_LEFT_Y));

			window.update();


			if (time.oneSecondPassed())
			{
				printf("V 1.0 | Window: %d x %d | Gamepad: %s\n", window.getWidth(), window.getHeight(), InputManager::getGamepadName().c_str());
				printf("Player position: X:%f   Y:%f | DeltaTime: %lf \n", player->getPositionX(), player->getPositionY(), time.getDeltaTime());
				printf("%d fps\n", time.getFps());
				printf("Joystick GAUCHE X:%f | Y:%f\n", InputManager::gamepadJoystickValue(GAMEPAD_JOYSTICK_LEFT_X), InputManager::gamepadJoystickValue(GAMEPAD_JOYSTICK_LEFT_Y));
				printf("Joystick DROITE X:%f | Y:%f\n", InputManager::gamepadJoystickValue(GAMEPAD_JOYSTICK_RIGHT_X), InputManager::gamepadJoystickValue(GAMEPAD_JOYSTICK_RIGHT_Y));
				printf("Trigger: L:%f | R:%f\n", InputManager::gamepadJoystickValue(GAMEPAD_TRIGGERS_L), InputManager::gamepadJoystickValue(GAMEPAD_TRIGGERS_R));

				time.resetFps();
			}
		}
		time.resetUpdateTime();

	}

	delete textures[0];
	delete textures[1];
	return 0;
}
