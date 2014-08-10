#include <SDL.h>
#include <vector>
#include "base.h"
#ifndef ENEMY_H
#define ENEMY_H
class enemy :public baseclass {
	SDL_Rect box;
	int xvel,yvel;
	SDL_Surface* image;
	bool ground;
	SDL_Rect clips[2];
	double frame;
public:
	enemy(SDL_Surface*,int x, int y, int xvel,int yvel);
	void move(std::vector<std::vector<int> >&);
	void show(SDL_Surface*);
	SDL_Rect* getRect();
};
#endif