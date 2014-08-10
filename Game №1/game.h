#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "base.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#ifndef GAME_H
#define GAME_H

class game:public baseclass{
	SDL_Surface *screen, *background, *block, *bul,*ene;
	SDL_Rect camera;
	std::vector<std::vector<int>> map;
	std::vector<bullet*> bullets;
	std::vector<enemy*> enemies;
	bool direction[2];
	TTF_Font* font;
	SDL_Rect finish;
	SDL_Surface* load_image(const char* filename);
	void loadmap(const char* filename);
	void showmap();
	void handleEvents();
	bool running;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	player* player1;
	int showmenu(SDL_Surface*);
	void showmessage(const char* c);
public:
	game();
	~game();
	void start();
};
#endif