#include <iostream>
#include "src/graphics/window.h"

int main()
{
	Window window("2D Walking", 640, 480);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!window.closed())
	{
		//std::cout << "Resolution: " << window.getWidth() << ":" << window.getHeight() << std::endl;
		//std::cout << "Position Curseur: " << "x:" << window.getInputManager()->getMousePosX() << " y: " << window.getInputManager()->getMousePosY() << std::endl;
		/*if (window.getInputManager()->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			std::cout << "CLIC gauche is pressed" << std::endl;*/
		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.update();
	}
	return 0;
}