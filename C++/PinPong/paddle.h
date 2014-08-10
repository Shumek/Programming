#include <SDL.h>
#ifndef PADDLE_H
#define PADDLE_H

class paddle{
	SDL_Rect box;
	SDL_Surface* image;
	int yvel;
	int point;
public:
	paddle(SDL_Surface* img, int x, int y, int w, int h, int yVel);
	~paddle();
	SDL_Rect* getRect();
	void moveUp();
	void moveDown();
	void show();
	void incpoint();
	void setBack(int x, int y, int w, int h, int yVel);
	int getPoints();
};

#endif