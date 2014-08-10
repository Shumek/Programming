#include "paddle.h"

paddle::paddle(SDL_Surface* img, int x, int y, int w, int h, int yVel)
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	image = img;
	yvel = yVel;
	point = 0;
}

paddle::~paddle()
{
	SDL_FreeSurface(image);
}

void paddle::moveUp()
{
	if (box.y>0)
		box.y -= yvel;
}

void paddle::moveDown()
{
	if (box.y + box.h<SDL_GetVideoSurface()->clip_rect.h)
		box.y += yvel;
}

void paddle::show()
{
	SDL_BlitSurface(image, NULL, SDL_GetVideoSurface(), &box);
}

SDL_Rect* paddle::getRect()
{
	return &box;
}

void paddle::incpoint()
{
	point++;
}

void paddle::setBack(int x, int y, int w, int h, int yVel)
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	yvel = yVel;
}

int paddle::getPoints()
{
	return point;
}