#include <SDL.h>
#include <iostream>
#ifndef BULLET_H
#define BULLET_H

class bullet{
	SDL_Rect box;
	int xvel, yvel;
	SDL_Surface* image;
public:
	bullet(SDL_Surface* img, int x, int y, int xvel, int yvel);
	void move();
	void show(SDL_Surface* screen);
	SDL_Rect* getRect();
};
#endif