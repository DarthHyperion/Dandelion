#pragma once

#include"SDL.h"
#include <iostream>
class Dandelion
{
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer* renderer;
	const int HEIGHT = 800;
	const int WIDTH = 600;

	int x1 ;
	int y1 ;
	int x2 ;
	int y2 ;
	Uint8 colorshift = 0;
	Uint8 opacity = 0xff;

public:
	Dandelion();
	~Dandelion();

	void init(const char* title, int xpos, int ypos, bool fullscreen);
	void update();
	void render();
	void clean();
	void handleEvents();
	void save();

	bool running();

};

