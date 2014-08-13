#include "snake.h"

void snakeclass::drawRect(int x, int y, Uint32 color, int w, int h)
{
	SDL_Rect tmp = { x, y, w, h };
	SDL_FillRect(screen, &tmp, color);
}


snakepart::snakepart(int col, int row)
{
	x = col;
	y = row;
}

snakepart::snakepart()
{
	x = 0;
	y = 0;
}

snakeclass::snakeclass()
{
	width = 800;
	height = 400;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	font = TTF_OpenFont("E://Game//Arial.ttf", 20);
	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

	for (int i = 0; i<5; i++)
		snake.push_back(snakepart(40 + i, 10));
	points = 0;
	del = 110;
	get = false;
	direction = 'l';
	srand(time(0));
	putfood();
	//отрисовка границ
	drawRect(0, 0, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00), width, 10);
	drawRect(0, 0, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00), 10, height - 20);
	drawRect(0, height - 30, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00), width, 10);
	drawRect(width - 10, 0, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00), 10, height - 20);
	//Отрисовка змеи
	for (int i = 0; i<snake.size(); i++)
	{
		drawRect(snake[i].x * 10, snake[i].y * 10, SDL_MapRGB(screen->format, 0x00, 0xff, 0x00));
	}
}
snakeclass::~snakeclass()
{
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

void snakeclass::putfood()
{
	while (1)
	{
		int tmpx = rand() % width / 10 + 1;
		int tmpy = rand() % height / 10 + 1;
		for (int i = 0; i<snake.size(); i++)
		if (snake[i].x == tmpx && snake[i].y == tmpy)
			continue;
		if (tmpx >= width / 10 - 2 || tmpy >= height / 10 - 3)
			continue;
		food.x = tmpx;
		food.y = tmpy;
		break;
	}
	drawRect(food.x * 10, food.y * 10, SDL_MapRGB(screen->format, 0xff, 0x00, 0xff));
}

bool snakeclass::collision()
{
    //Врезаетс в стенку
	if (snake[0].x == 0 || snake[0].x == width / 10 - 1 || snake[0].y == 0 || snake[0].y == height / 10 - 3)
		return true;

	for (int i = 2; i<snake.size(); i++)
	if (snake[0].x == snake[i].x && snake[i].y == snake[0].y)
		return true;
	if (snake[0].x == food.x && snake[0].y == food.y)
	{
		get = true;
		putfood();
		points += 10;
		char c[5];
		sprintf_s(c, "%d", points);
		SDL_Surface *text,*score;
		SDL_Color color = { 255, 255, 255 };
		text = TTF_RenderText_Solid(font,"Score: ", color);
		score = TTF_RenderText_Solid(font, c, color);
		SDL_Rect tmp = { 0, 380 };
		SDL_Rect tmp2 = {60, 380 };
		drawRect(60, 380, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00), 100, 20);
		SDL_BlitSurface(text, NULL, screen, &tmp);
		SDL_BlitSurface(score, NULL, screen, &tmp2);
		SDL_FreeSurface(text);
		SDL_FreeSurface(score);
		if ((points % 100) == 0 && del > 0)
			del -= 10;

	}
	else
		get = false;
	return false;
}

void snakeclass::movesnake()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				if (direction != 'r')
					direction = 'l';
				break;
			case SDLK_UP:
				if (direction = 'd')
					direction = 'u';
				break;
			case SDLK_DOWN:
				if (direction != 'u')
					direction = 'd';
				break;
			case SDLK_RIGHT:
				if (direction != 'l')
					direction = 'r';
				break;
			case SDLK_ESCAPE:
				direction = 'q';
				break;
			}
		}
		else if (event.type == SDL_QUIT)
			direction = 'q';
	}
	if (!get)
	{
		drawRect(snake[snake.size() - 1].x * 10, snake[snake.size() - 1].y * 10, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
		snake.pop_back();
	}
	if (direction == 'l')
		snake.insert(snake.begin(), snakepart(snake[0].x - 1, snake[0].y));
	else if (direction == 'r')
		snake.insert(snake.begin(), snakepart(snake[0].x + 1, snake[0].y));
	else if (direction == 'u')
		snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y - 1));
	else if (direction == 'd')
		snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y + 1));
	drawRect(snake[0].x * 10, snake[0].y * 10, SDL_MapRGB(screen->format, 0x00, 0xff, 0x00));
}


void snakeclass::start()
{
	while (1)
	{
		if (collision())
		{
			std::cout << "game over" << std::endl;
			break;
		}
		movesnake();
		if (direction == 'q')
			break;
		SDL_Flip(screen);
		SDL_Delay(del);
	}
}
