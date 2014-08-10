#include <SDL.h>
#ifndef BASE_H
#define BASE_H

class baseclass{
protected:
	bool collision(SDL_Rect* rec1, SDL_Rect* rec2);
public:
	static SDL_Rect coord;
	static const int TILE_SIZE = 50;
};
#endif