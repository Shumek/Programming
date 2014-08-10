#include "bullet.h"
bullet::bullet(SDL_Surface* img, int x, int y, int xVel, int yVel)
{
	box.x = x;
	box.y = y;
	image = img;
	box.w = image->w;
	box.h = image->h;
	xvel = xVel;
	yvel = yVel;
}
void bullet::move()
{
	box.x += xvel;
	box.y += yvel;
}

void bullet::show(SDL_Surface* screen)
{
	SDL_BlitSurface(image, NULL, screen, &box);
}

SDL_Rect* bullet::getRect()
{
	return &box;
}