#include "game.h"


SDL_Rect baseclass::coord;
void game::showmessage(const char* c)
{
	SDL_Color color = { 255, 0, 0 };
	SDL_Surface* text = TTF_RenderText_Solid(font, c, color);
	SDL_Rect tmprect = { screen->w / 2 - text->w / 2, 20 };
	SDL_BlitSurface(text, NULL, screen, &tmprect);
	SDL_FreeSurface(text);
	SDL_Flip(screen);
}

int game::showmenu(SDL_Surface* screen) 
{
	int x, y;
	bool run = true; 
	const int NUMMENU = 2;
	const char* array[NUMMENU] = { "Continue", "Exit" }; 
	SDL_Surface* menu[NUMMENU];
	bool selected[NUMMENU] = { 0, 0 };
	SDL_Color colors[2] = { { 255, 255, 255 }, { 255, 0, 0 } };

	for (int i = 0; i<NUMMENU; i++)
		menu[i] = TTF_RenderText_Solid(font, array[i], colors[0]); 

	SDL_Rect pos[NUMMENU];
	for (int i = 0; i<NUMMENU; i++)
	{
		pos[i].x = screen->clip_rect.w / 2 - menu[i]->clip_rect.w / 2;
		pos[i].y = screen->clip_rect.h / 2 + i*(menu[i]->clip_rect.h);
	}
	SDL_Event menuevent;  

	SDL_Surface* alpha = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, screen->w, screen->h, 32, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask); 
	SDL_FillRect(alpha, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); 
	SDL_SetAlpha(alpha, SDL_SRCALPHA, 129);  
	SDL_BlitSurface(alpha, NULL, screen, NULL);       
	SDL_FreeSurface(alpha); 
	while (run)
	{
		SDL_WaitEvent(&menuevent); 
		switch (menuevent.type)
		{
		case SDL_QUIT:  
			for (int i = 0; i<NUMMENU; i++)
				SDL_FreeSurface(menu[i]);
			return 1;
		case SDL_MOUSEMOTION: 
			x = menuevent.motion.x;   
			y = menuevent.motion.y;
			for (int i = 0; i<NUMMENU; i++) 
			{      
				if (x >= pos[i].x && x <= (pos[i].x + menu[i]->clip_rect.w) && y >= pos[i].y && y <= (pos[i].y + menu[i]->clip_rect.h))
				{
					if (!selected[i]) 
					{
						SDL_FreeSurface(menu[i]);  
						menu[i] = TTF_RenderText_Solid(font, array[i], colors[1]);
						selected[i] = 1;
					}
				}
				else{ 
					if (selected[i]) 
					{
						SDL_FreeSurface(menu[i]); 
						menu[i] = TTF_RenderText_Solid(font, array[i], colors[0]);
						selected[i] = 0;
					}
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:   
			x = menuevent.button.x;  
			y = menuevent.button.y;
			for (int i = 0; i<NUMMENU; i++) 
			{
				if (x >= pos[i].x && x <= (pos[i].x + menu[i]->clip_rect.w) && y >= pos[i].y && y <= (pos[i].y + menu[i]->clip_rect.h))
				{
					for (int j = 0; j<NUMMENU; j++)    
						SDL_FreeSurface(menu[j]);       
					return i;
				}
			}
			break;
		case SDL_KEYDOWN:   
			if (menuevent.key.keysym.sym == SDLK_ESCAPE) 
			{
				for (int i = 0; i<NUMMENU; i++)
					SDL_FreeSurface(menu[i]);
				return 0;      
			}
			break;
		}
		for (int i = 0; i<NUMMENU; i++)
			SDL_BlitSurface(menu[i], NULL, screen, &pos[i]);   
		SDL_Flip(screen);      
	}
}



game::game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
	block = load_image("E://Game//blocks.bmp");
	background = load_image("E://Game//endless.bmp");
	bul = load_image("E://Game//bullet.bmp");
	ene = load_image("E://Game//enemy.bmp");
	TTF_Init();
	font = TTF_OpenFont("E://Game//air.ttf", 20);
	baseclass::coord.x = baseclass::coord.y= camera.x = camera.y = 0;
	camera.w = baseclass::coord.w = SCREEN_WIDTH;
	camera.h = baseclass::coord.h = SCREEN_HEIGHT;
	direction[0] = direction[1] = 0;
	running = true;
	player1 = new player(load_image("E://Game//player.bmp"));
	finish.x = 0;
	finish.y = 0;
	finish.w = 50;
	finish.h = 50;
}

game::~game(){
	delete player1;
	SDL_FreeSurface(block);
	SDL_FreeSurface(background);
	SDL_FreeSurface(bul);
	for (int i = 0; i < bullets.size(); i++)
		delete bullets[i];
	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

SDL_Surface* game::load_image(const char* filename)
{
	SDL_Surface* tmp = SDL_LoadBMP(filename); 
	SDL_Surface* tmp2 = SDL_DisplayFormat(tmp);  
	SDL_SetColorKey(tmp2, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0x00, 0xff, 0xff));
	SDL_FreeSurface(tmp); 
	return tmp2;
}

void game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			return;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				direction[0] = 1;
				player1->setMoving(1);
				break;
			case SDLK_RIGHT:
				direction[1] = 1;
				player1->setMoving(1);
				break;
			case SDLK_SPACE:
				player1->setJump();
				break;
			case SDLK_f:
				if (player1->getDirection() == 'r')
					bullets.push_back(new bullet(bul, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 15, 5, 0));
				else
					bullets.push_back(new bullet(bul, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 15, -5, 0));
					break;
			case SDLK_ESCAPE:
				int h = showmenu(screen);
				if (h == 1)
					running = false;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				direction[0] = 0;
				player1->setMoving(0);
				break;
			case SDLK_RIGHT:
				direction[1] = 0;
				player1->setMoving(0);
				break;
			}
			break;
		}
	}
}

void game::loadmap(const char* filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
	{
		std::cout << "Problem with loading the file" << std::endl;
		return;
	}
	int width, height;
	in >> width;
	in >> height;
	int current;
	for (int i = 0; i < height; i++)
	{
		std::vector<int> vec;
		for (int j = 0; j < width; j++)
		{
			if (in.eof())
			{
				std::cout << "File end reached too soon" << std::endl;
				return;
			}

			in >> current;
			if (current == -1)
			{
				enemies.push_back(new enemy(ene, j * 50, i * 50, 1, 0));
				vec.push_back(0);
			}
			else
			{

				if (current >= 0 && current <= 7)
				{
					if (current == 3)
					{
						finish.x = j * 50;
						finish.y = i * 50;
					}
					vec.push_back(current);
				}
				else{
					vec.push_back(0);
				}
			}
		}

		map.push_back(vec);
	}
	in.close();
}

void game::showmap()
{
	int start = (baseclass::coord.x - (baseclass::coord.x%baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
	int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50;
	if (start < 0)
		start = 0;
	if (end>map[0].size())
		end = map[0].size();
	for (int i = 0; i < map.size();i++)
	for (int j = start; j < end;j++)
	if (map[i][j] != 0){
		SDL_Rect blockrect = { (map[i][j] - 1)*baseclass::TILE_SIZE, 0, baseclass::TILE_SIZE, baseclass::TILE_SIZE };
		SDL_Rect destrect = { j*baseclass::TILE_SIZE - baseclass::coord.x, i * 50 };
		SDL_BlitSurface(block, &blockrect, screen, &destrect);
	}
}

void game::start()
{
	Uint32 start;
	loadmap("E://Game//map.map");
	while (running)
	{
		start = SDL_GetTicks();
		handleEvents();

		//logic

		if (direction[0])
		{
			player1->setDirection('l');
			if (player1->getRect()->x > 0)
				player1->setXvel(-1);
			else{
				player1->setXvel(0);
				camera.x--;
				baseclass::coord.x--;
			}
			if (camera.x < 0)
				camera.x = 2000 - SCREEN_WIDTH;
		}

		else if (direction[1])
		{
			player1->setDirection('r');
			if (player1->getRect()->x < 80)
				player1->setXvel(1);
			else
			{
				player1->setXvel(0);
				camera.x++;
				baseclass::coord.x++;
			}

			if (camera.x >= 2000 - SCREEN_WIDTH)
				camera.x = 0;
		}
		else
			player1->setXvel(0);


		int str = (baseclass::coord.x - (baseclass::coord.x%baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
		int end = (baseclass::coord.x + baseclass::coord.w + (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) % baseclass::TILE_SIZE)) / 50;
		if (start<0)
			start = 0;
		if (end>map[0].size())
			end = map[0].size();
		bool nc = 0;
		for (int i = 0; i < map.size(); i++)
		for (int j = str; j < end; j++)
		{
			if (map[i][j] == 0)
				continue;
			SDL_Rect destrect = { j * 50 - baseclass::coord.x, i * 50, 50, 50 };
			for (int g = 0; g < bullets.size(); g++)
			if (collision(bullets[g]->getRect(), &destrect))
			{
				delete bullets[g];
				bullets.erase(bullets.begin() + g);
			}
		}

		for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->getRect()->x >= screen->w || bullets[i]->getRect()->x  <= 0)
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
		for (int i = 0; i < bullets.size(); i++)
		for (int j = 0; j < enemies.size(); j++)
		{
			SDL_Rect tmprect = { enemies[j]->getRect()->x - baseclass::coord.x, enemies[j]->getRect()->y, 40, 40 };
			if (collision(&tmprect, bullets[i]->getRect()))
			{
				delete enemies[j];
				delete bullets[i];
				enemies.erase(enemies.begin() + j);
				bullets.erase(bullets.begin() + i);
			}
		}

		for (int j = 0; j < enemies.size(); j++)
		{
			SDL_Rect tmprect = { enemies[j]->getRect()->x - baseclass::coord.x, enemies[j]->getRect()->y, 40, 40 };
			if (collision(&tmprect, player1->getRect()))
			{
				if (player1->getRect()->y + player1->getRect()->h >= enemies[j]->getRect()->y && player1->getRect()->y + player1->getRect()->h <= enemies[j]->getRect()->y + 10)
				{
					delete enemies[j];
					enemies.erase(enemies.begin() + j);
				}
				else{
					player1->setHealth(player1->getHealth() - 1);
				}
			}
		}


		player1->move(map);
		for (int i = 0; i < bullets.size(); i++)
			bullets[i]->move();
		for (int i = 0; i < enemies.size(); i++)
			enemies[i]->move(map);

		SDL_BlitSurface(background, &camera, screen, NULL);
		showmap();
		player1->show(screen);

		for (int i = 0; i < bullets.size(); i++)
			bullets[i]->show(screen);

		for (int i = 0; i < enemies.size(); i++)
			enemies[i]->show(screen);

		SDL_Flip(screen);

		if (player1->getHealth() <= 0 || player1->getRect()-> y>= screen->h)
		{
			running = false;
			showmessage("game over");
			SDL_Delay(1000);
		}

		SDL_Rect tmprect = { finish.x - coord.x, finish.y, 50, 50 };
		if (collision(player1->getRect(), &tmprect))
		{
			running = false;
			showmessage("You Win");
			SDL_Delay(1000);
		}

		if (1000 / 30 > (SDL_GetTicks() - start))
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - start));
	}
}