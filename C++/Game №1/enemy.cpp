#include "enemy.h"

enemy::enemy(SDL_Surface* img, int x, int y, int xVel, int yVel)
{
	image = img;
	box.x = x;
	box.y = y;
	box.w = image->w / 2;
	box.h = image->h;
	xvel = xVel;
	yvel = yVel;
	ground = 0;
	for (int i = 0; i < 2; i++)
	{
		clips[i].x = i * 40;
		clips[i].y = 0;
		clips[i].w = clips[i].h = 40;

	}
	frame = 0.0;
}

void enemy::show(SDL_Surface* screen)
{
	SDL_Rect tmp = { box.x - coord.x, box.y, 40, 40 };
	SDL_BlitSurface(image, &clips[(int)(frame+0.5)],screen, &tmp);
}

SDL_Rect* enemy::getRect()
{
	return &box;
}

void enemy::move(std::vector<std::vector<int> >&map)
{
	int start = (baseclass::coord.x - (baseclass::coord.x%baseclass::TILE_SIZE)) / baseclass::TILE_SIZE-2;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50+2;
	if (start<0)
		start = 0;
	if (end>map[0].size())
		end = map[0].size();
	bool nc = 0;
	for (int i = 0; i<map.size(); i++)
	for (int j = start; j<end; j++)
	{
		if (map[i][j] == 0)
			continue;
		SDL_Rect destrect = { j * 50, i * 50, 50, 50 };
		if (collision(&box, &destrect))
		{
			
			if (destrect.y >= box.y + box.h - 11)
			{
				ground = 1;
				yvel = 0;
				nc = 1;
			}
			else 
				xvel = -xvel;
			
		}
	}

	if (!nc )
		yvel = 5;

	box.x += xvel;
	box.y += yvel;

	if (frame >= 1.4)
		frame = 0.0;

}