#include "player.h"

player::player(SDL_Surface* img)
{
	image = img;
	box.x = 0;
	box.y = 0;
	box.w = 50;
	box.h = 100;
	xvel = 0;
	yvel = 0;
	for (int i = 0; i < 4; i++)
	{
		clips[i].x = i * 50;
		clips[i].y = 0;
		clips[i].w = clips[i].h = 50;
	}
	ground = 0;
	jump = 0;
	direction = 'r';
	frame = 0.0;
	moving = 0;
	health = 10;
}

player::~player()
{
	SDL_FreeSurface(image);
}

SDL_Rect* player::getRect()
{
	return &box;
}

int player::getXvel()
{
	return xvel;
}

void player::setXvel(int vel)
{
	xvel = vel;
}

void player::show(SDL_Surface* screen)
{
	SDL_BlitSurface(image, &clips[(int)(frame+0.5)], screen, &box);
}


void player::setMoving(bool b)
{
	moving = b;
}

void player::setDirection(char c)
{
	if ((c == 'r' || c == 'l')&& direction != c)
	{
		direction = c;
		if (direction == 'r')
			frame = 0.0;
		else
			frame = 1.5;
	}
}

void player::move(const std::vector<std::vector<int> >& map)
{

	int start = (baseclass::coord.x - (baseclass::coord.x%baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50;
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
		SDL_Rect destrect = { j * 50 - baseclass::coord.x, i * 50, 50, 50 };
		if (collision(&box, &destrect)) 
		{
			nc = 1;
			if (destrect.y >= box.y + box.h-11) 
			{
				ground = 1;      
				yvel = 0;
			}
			else if (destrect.y + destrect.h <= box.y+11)     
			{
				box.y++;        
				yvel = 5;        
			}
			if (box.x + box.w >= destrect.x - 5 && box.y + box.h >= destrect.y + 6 && box.x + box.w <= destrect.x + 20)   
			{
				xvel = 0;
				box.x--;      
			}
			else if (box.x <= destrect.x + destrect.w && box.y + box.h >= destrect.y + 6) 
			{
				xvel = 0; 
				box.x++;
			}
		}
	}

	if (!nc && !jump)
	{
		yvel = 5;
	}
	if (jump && yvel < 5)
		yvel++;
	else
		jump = 0;
		
		box.x += xvel;
		box.y += yvel;

		if (moving)
		{
			frame += 0.2;
			if (direction == 'r'&& frame >= 1.4)
				frame = 0.0;
			else if (direction == 'l'&& frame >= 3.4)
				frame = 1.5;
		}
}

void player::setJump()
{
	if (ground&&!jump)
	{
		jump = 1;
		ground = 0;
		yvel = -17;//Сила прыжка
		box.y -= 5;
	}
}
int player::getHealth()
{
	return health;
}

void player::setHealth(int h)
{
	health = h;
}

char player::getDirection()
{
	return direction;
}