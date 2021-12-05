#include "Dandelion.h"
using namespace std;
Dandelion::Dandelion() {

}

Dandelion::~Dandelion() {

}

void Dandelion::init(const char* title, int xpos, int ypos, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems Initialized" << endl;

		window = SDL_CreateWindow(title, xpos, ypos, HEIGHT+100, WIDTH+200, flags);
		
		if (window) {
			cout << "Window Created!" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			cout << "Renderer Created!" << endl;
		}
		
		isRunning = true;
	}
	else {
		
		cerr << "Failed to initialize subsystems, SDL_GetError() - " << SDL_GetError() << "\n";
		
		isRunning = false;
		
	}

}

void Dandelion::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
	default:
		break;
	}
}

void Dandelion::render() {
	//SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, colorshift, colorshift, colorshift, colorshift-125);
	SDL_RenderPresent(renderer);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
}

void Dandelion::update() {
	
	 x1 = cos(SDL_GetTicks()) * WIDTH / 2 + WIDTH / 2 + colorshift;
	 y1 = sin(SDL_GetTicks()) * HEIGHT / 2 + HEIGHT / 2;
	 x2 = 0.001*(SDL_GetTicks()) * WIDTH/2  + 10 + WIDTH / 2;
	 y2 = 0.001* SDL_GetTicks() * HEIGHT/2  + 10 + HEIGHT / 2 + colorshift;
	 colorshift = colorshift + 2;
	 opacity = colorshift;

	 if ((y2 > HEIGHT) | (y2 < 0)) { y2 = 0.01 * rand() + HEIGHT / 2; }
	 if ((x2 > WIDTH) | (x2 < 0)) { x2 = 0.01 * rand() + WIDTH / 2; }
	 if ((y2 > HEIGHT) | (y2 < 0)) { y2 = 0.01*rand()+HEIGHT / 2; }
	 if ((x2 > WIDTH) | (x2 < 0)) { x2 = 0.01 * rand() + WIDTH / 2; }
	 if (colorshift > 0xff) { colorshift = 0x00 + 0.001 * rand();  }
}


void Dandelion::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Dandelionation Cleaned!" << endl;
}

void Dandelion::save() {
	// credits: StackOverflow user O'Neil: https://stackoverflow.com/questions/20233469/how-do-i-take-and-save-a-bmp-screenshot-in-sdl-2

string filepath = "dandelion.bmp";
SDL_Surface* infoSurface = NULL;
infoSurface = SDL_GetWindowSurface(window);
if (infoSurface == NULL) {
	std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
}
else {
	unsigned char* pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
	if (pixels == nullptr) {
		std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
		return;
	}
	else {
		if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
			std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
			delete[] pixels;
			return;
		}
		else {
			SDL_Surface* saveSurface = nullptr;
			saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
			if (saveSurface == NULL) {
				std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
				delete[] pixels;
				return;
			}
			SDL_SaveBMP(saveSurface, filepath.c_str());
			SDL_FreeSurface(saveSurface);
			saveSurface = NULL;
			cout << "Image Saved!\n";
		}
		delete[] pixels;
	}
	SDL_FreeSurface(infoSurface);
	infoSurface = NULL;
}

}

bool Dandelion::running() {

	return isRunning;
}
