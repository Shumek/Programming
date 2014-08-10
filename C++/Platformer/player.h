#include <SDL.h>
#include <iostream>
#include <vector>
#include "base.h"
#ifndef PLAYER_H
#define PLAYER_H
class player:baseclass{//Наследование
	SDL_Rect box;
	SDL_Surface* image;
	int xvel, yvel;
	SDL_Rect clips[4];
	bool ground,jump;
	char direction;
	double frame;
	bool moving;
	int health;
public:
	player(SDL_Surface* img);
	~player();
	SDL_Rect* getRect();
	void setXvel(int vel);
	int getXvel();
	void move(const std::vector<std::vector<int> >& map);
	void show(SDL_Surface* screen);
	void setJump();
	void setMoving(bool);
	void setDirection(char);
	char getDirection();
	int getHealth();
	void setHealth(int);
};
#endif