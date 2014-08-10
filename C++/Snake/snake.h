#include <iostream>
#include <vector>
#include <cstdlib>
#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#ifndef SNAKE_H
#define SNAKE_H

struct snakepart{
	int x, y;
	snakepart(int col, int row);
	snakepart();
};

class snakeclass{
	int points, del, width, height;
	char direction;
	bool get;
	snakepart food;
	std::vector<snakepart> snake;
	SDL_Surface* screen;
	TTF_Font* font;

	void drawRect(int x, int y, Uint32 color, int w = 10, int h = 10);
	void putfood();
	bool collision();
	void movesnake();
public:
	snakeclass();
	~snakeclass();
	void start();
};

#endif