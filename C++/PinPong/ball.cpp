#include "ball.h"

ball::ball(SDL_Surface* img, int x, int y, int w, int h, int xVel, int yVel)
{
	image = img;
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	xvel = xVel;
	yvel = yVel;
}

ball::~ball()
{
	SDL_FreeSurface(image);
}

void ball::show()
{
	SDL_BlitSurface(image, NULL, SDL_GetVideoSurface(), &box);
}

void ball::move(SDL_Rect* player1, SDL_Rect* player2, Mix_Chunk* effect)
{
	box.x += xvel;
	box.y += yvel;
	if (box.y <= 0)
		yvel = -yvel;
	if (box.y + box.h >= SDL_GetVideoSurface()->clip_rect.h)
		yvel = -yvel;
	if (collision(&box, player1))
	{
		Mix_PlayChannel(-1, effect, 0);
		if (box.x + 3<player1->x + player1->w)
			yvel = -yvel;
		else
			xvel = -xvel;
	}
	if (collision(&box, player2))
	{
		Mix_PlayChannel(-1, effect, 0);
		if (box.x + box.w - 3 > player2->x)
			yvel = -yvel;
		else
			xvel = -xvel;

	}
}

bool ball::collision(SDL_Rect* rec1, SDL_Rect* rec2)
{
	if (rec1->y >= rec2->y + rec2->h)
		return 0;
	if (rec1->x >= rec2->x + rec2->w)
		return 0;
	if (rec1->y + rec1->h <= rec2->y)
		return 0;
	if (rec1->x + rec1->w <= rec2->x)
		return 0;
	return 1;
}


int ball::isOut()
{
	if (box.x <= 0)
		return 1;
	if (box.x >= SDL_GetVideoSurface()->clip_rect.w)
		return 2;
	return 0;
}


void ball::setBack(int x, int y, int w, int h, int xVel, int yVel)
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	xvel = xVel;
	yvel = yVel;
}