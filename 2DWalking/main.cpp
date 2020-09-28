#include "src/engine.h"

int main()
{

	int fpsInput = (int)MAX_FPS;

	Timer time;
	Engine* engine = new Engine();

	while (engine->isRunning()) {
		time.initFrameIteration(glfwGetTime());

		engine->handleSound();


		if (time.fpsPassed()) {
			engine->update(time.getDeltaTime(), time.getFixedDeltaTime(), time.elapsed());

			if (InputManager::isKeyPressed(GLFW_KEY_G)) {
				if (fpsInput > MIN_FPS) {
					fpsInput--;
					time.setFpsLimit(fpsInput);
				}
			}
			if (InputManager::isKeyPressed(GLFW_KEY_H)) {
				if (fpsInput < MAX_FPS) {
					fpsInput++;
					time.setFpsLimit(fpsInput);
				}
			}


			if (time.oneSecondPassed())
			{
				printf("%d fps | LimitFPS: %d | fixedDeltaTime: %f | deltaTime: %f | elapasedTime: %f\n", time.getFps(), fpsInput, (float)time.getFixedDeltaTime(), (float)time.getDeltaTime(), time.elapsed());
				time.resetFps();
			}
		}
		time.resetUpdateTime();
	}
	engine->clean();

	return 0;
}
