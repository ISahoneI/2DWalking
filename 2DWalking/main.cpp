#include <iostream>

#include "src/utilities/timer.h"
#include "src/graphics/rendering/shader.h"
#include "src/inputs/window.h"
#include "src/utilities/mathmanager.h"

#include "src/graphics/rendering/renderer2d.h"
#include "src/graphics/paints/sprite.h"

#include "src/graphics/layers/layer.h"
#include "src/graphics/layers/group.h"

#include "src/graphics/paints/texture.h"
#include "src/graphics/paints/colormanager.h"

#include "src/inputs/camera.h"

#include "src/audio/audiomanager.h"
#include "src/audio/source.h"

int main()
{
	//1280x720	854x480	  426x240
	Window window("2D Walking", 854, 480, false);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
	int count = 0;
	float tilescale = 0.6f;
	/*for (float y = 0; y < 9.0f; y += tilescale)
	{
		for (float x = 0; x < 16.0f; x += tilescale)
		{
			layer.add(new Sprite(x, y, tilescale, tilescale, textures[0]));
			count++;
		}
	}*/
	std::cout << "Taille liste sprite :" << count << std::endl;
	Texture* yzao_tex[]
	{
		new Texture("res/textures/yzao_bas.png"),
		new Texture("res/textures/yzao_haut.png"),
		new Texture("res/textures/yzao_droite.png"),
		new Texture("res/textures/yzao_gauche.png")
	};
	Sprite* map = new Sprite(0.0f, 0.0f, tilescale * 800.0f/16, tilescale * 1680.0f/16, new Texture("res/textures/Omara.png"), ColorManager::getHexaColori(255, 255, 255, 255));
	layer.add(map);
	Sprite* player = new Sprite(12, 8, 0.6f * 24/16, 0.6f * 32/16, yzao_tex[0], ColorManager::getHexaColori(255, 254, 253, 252));
	layer.add(player);

	Sprite* brouillard = new Sprite(0, 0, 16, 9, new Texture("res/textures/brouillard_bleu.png"), ColorManager::getHexaColori(255, 255, 255, 70));
	layer2.add(brouillard);
	/*Group* group = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(4, 4, 0)));
	group->add(new Sprite(4, 4, 4, 4, glm::vec4(1, 1, 0, 0.4f)));
	group->add(new Sprite(4, 4, 3, 3, 0x880000ff));
	group->add(new Sprite(4, 4, 2, 2, glm::vec4(1, 0, 1, 0.4f)));
	group->add(new Sprite(4, 4, 1, 1, glm::vec4(0, 1, 0, 0.4f)));
	layer2.add(group);
	layer2.add(new Sprite(8, 6, 1, 1, glm::vec4(0.3f, 0.3f, 0.3f, 0.8f)));*/
	
	//-------------SOUND-------------------
	//-------------------------------------
	AudioManager* aud = new AudioManager();
	ALuint buff = aud->loadSound(DW_SOUND_1);
	Source* hp = new Source();

	bool input_i = false;
	float player_speed = 3.0f;
	float player_trans = 1.0f;
	Timer time;
	float timer = 0;
	unsigned int frame = 0;
	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
	float lastFrame = 0.0f, deltaTime = 0.0f;
	bool firstMouse = true;
	while (!window.closed())
	{
		float point_rot = 6.0f;
		glm::mat4 mat = glm::translate(glm::mat4(1), glm::vec3(point_rot, point_rot, point_rot));
		mat = mat * glm::rotate(glm::mat4(1), time.elapsed(), glm::vec3(0, 0, 1));
		mat = mat * glm::translate(glm::mat4(1), glm::vec3(-point_rot, -point_rot, -point_rot));
		window.clear();
		double x, y;
		InputManager::getMousePosition(x, y);
		int largeur, hauteur;
		window.getDimension(largeur, hauteur);

		layer.render();
		shad.setUniform2f("light_pos", glm::vec2((float)(x * 16.0f / (float)largeur), (float)(9.0f - y * 9.0f / (float)hauteur)));
		//shad.setUniformMat4("modele_mat", mat);
		//glm::mat4 projection = glm::ortho(playerCenterX - (16.0f/2)*camera.zoom, playerCenterX + (16.0f/2) * camera.zoom, playerCenterY - (9.0f / 2)*camera.zoom, playerCenterY + (9.0f / 2) * camera.zoom, -1.0f, 1.0f);
		//glm::mat4 projection = glm::ortho(4.5f, 11.5f, 2.25f, 6.75f, -1.0f, 1.0f);
		glm::mat4 projection = glm::ortho(
			(0.0f - (player->getPositionX() + 0.45f)) * camera.getZoom() + (player->getPositionX() + 0.45f),
			(16.0f - (player->getPositionX() + 0.45f)) * camera.getZoom() + (player->getPositionX() + 0.45f),
			(0.0f - (player->getPositionY() + 0.5f)) * camera.getZoom() + (player->getPositionY() + 0.5f),
			(9.0f - (player->getPositionY() + 0.5f)) * camera.getZoom() + (player->getPositionY() + 0.5f),
			-1.0f, 1.0f);
		/*std::cout << (0.0f - playerCenterX) * camera.zoom + playerCenterX << " , "
			<< (16.0f - playerCenterX) * camera.zoom + playerCenterX << " , "
			<< (0.0f - playerCenterY) * camera.zoom + playerCenterY << " , "
			<< (9.0f - playerCenterY) * camera.zoom + playerCenterY << std::endl;*/
		float playerCenterX = player->getPositionX() - 16.0f / 2 + player->getWidth() / 2;
		float playerCenterY = player->getPositionY() - 9.0f / 2 + player->getHeight() / 2;
		if (player->getPositionX() >= 16.0f*camera.getZoom() / 2 && player->getPositionX() <= ((map->getWidth()-0.6) - 16.0f / 2))
			camera.setPosX(playerCenterX * camera.getZoom());
		if(player->getPositionY() >= 9.0f*camera.getZoom() / 2 && player->getPositionY() <= ((map->getHeight()-0.6) - 9.0f / 2))
			camera.setPosY(playerCenterY * camera.getZoom());
		//camera.setPosition(playerCenterX * camera.getZoom(), playerCenterY * camera.getZoom());
		shad.setUniformMat4("projection_mat", projection);
		shad.setUniformMat4("view_mat", camera.getViewMatrix());
		//Inputs
		//------------

		double scrollY = InputManager::getScrollYOffset();
		if (scrollY != 0)
		{
			camera.actZoom((float)scrollY);
			//std::cout << "ScrollY = " << scrollY << std::endl;
		}

		if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (InputManager::isKeyPressed(GLFW_KEY_RIGHT) || InputManager::isKeyPressed(GLFW_KEY_D))
		{
			player->setTexture(yzao_tex[2]);
			if(player->getPositionX() < (map->getWidth() - 0.8f))
				player->setPositionX(player->getPositionX() + deltaTime * player_speed);
			//camera.ProcessKeyboard(CameraDirection::RIGHT, deltaTime);
		}
		if (InputManager::isKeyPressed(GLFW_KEY_LEFT) || InputManager::isKeyPressed(GLFW_KEY_A))
		{
			player->setTexture(yzao_tex[3]);
			if(player->getPositionX() > 0.2f)
				player->setPositionX(player->getPositionX() - deltaTime * player_speed);
			//camera.ProcessKeyboard(CameraDirection::LEFT, deltaTime);
		}
		if (InputManager::isKeyPressed(GLFW_KEY_DOWN) || InputManager::isKeyPressed(GLFW_KEY_S))
		{
			player->setTexture(yzao_tex[0]);
			if(player->getPositionY() > 0.4f)
				player->setPositionY(player->getPositionY() - deltaTime * player_speed);
			//camera.ProcessKeyboard(CameraDirection::BACKWARD, deltaTime);
		}
		if (InputManager::isKeyPressed(GLFW_KEY_UP) || InputManager::isKeyPressed(GLFW_KEY_W))
		{
			player->setTexture(yzao_tex[1]);
			if(player->getPositionY() < (map->getHeight() - 0.8f))
				player->setPositionY(player->getPositionY() + deltaTime * player_speed);
			//camera.ProcessKeyboard(CameraDirection::FORWARD, deltaTime);
		}
		if (InputManager::isKeyPressed(GLFW_KEY_X))
			player_speed += 0.1f;
		if (InputManager::isKeyPressed(GLFW_KEY_Z))
			player_speed -= 0.1f;
		
		if (InputManager::isKeyPressed(GLFW_KEY_SPACE))
		{
			player->setPosition(0.0f, 0.0f, 1.0f);
			camera.setZoom(1.0f);
			camera.setPosition((playerCenterX + 8.0f) * camera.getZoom(), (playerCenterY + 4.5f) * camera.getZoom());

		}
		if (InputManager::isKeyPressed(GLFW_KEY_T))
		{
			if(player_trans < 1.0f)
				player_trans += 0.001f;
			player->setColor(ColorManager::getHexaColorf(1.0f, 1.0f, 1.0f, player_trans));
		}
		if (InputManager::isKeyPressed(GLFW_KEY_R))
		{
			if(player_trans > 0.0f)
				player_trans -= 0.001f;
			player->setColor(ColorManager::getHexaColorf(1.0f, 1.0f, 1.0f, player_trans));
			//player->setTransparency(player_trans);
		}
	/*	if (InputManager::isKeyPressed(GLFW_KEY_I) && input_i == false)
		{
			hp->play(buff);
			input_i = true;
		}
		if (!InputManager::isKeyPressed(GLFW_KEY_I))
			input_i = false;*/
		if (InputManager::isKeyPressedOnce(GLFW_KEY_I))
			hp->play(buff);
		if (InputManager::isMouseButtonPressedOnce(GLFW_MOUSE_BUTTON_1))
			hp->play(buff);

		layer2.render();
		//shad2.setUniformMat4("modele_mat", mat);
		//shad2.setUniform2f("light_pos", glm::vec2(4.0f, 3.5f));

		window.update();
		frame++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("Window : %d x %d \n", window.getWidth(), window.getHeight());
			printf("Player position : X:%f   Y:%f \n", player->getPositionX(), player->getPositionY());
			printf("DeltaTime : %f \n", deltaTime);
			printf("%d fps\n", frame);
			frame = 0;
		}
	}
	delete textures[0];
	delete textures[1];
	return 0;
}
