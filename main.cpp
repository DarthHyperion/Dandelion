#include "Dandelion.h"

Dandelion* anim = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	anim = new Dandelion();

	anim->init("Dandelion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

	while (anim->running()) {
		frameStart = SDL_GetTicks();

		anim->handleEvents();
		anim->update();
		anim->render();
	
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	anim->save();
	anim->clean();

	return 0;
}
