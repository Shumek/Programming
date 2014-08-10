#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "ball.h"
#include "paddle.h"

int showmenu(SDL_Surface* screen, TTF_Font* font)
{
	Uint32 time;
	int x, y;
	const int NUMMENU = 2;
	const char* labels[NUMMENU] = { "Continue", "Exit" };
	SDL_Surface* menus[NUMMENU];
	bool selected[NUMMENU] = { 0, 0 };
	SDL_Color color[2] = { { 100,255, 100 }, { 255, 0, 0 } };

	menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
	SDL_Rect pos[NUMMENU];
	pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[1].y = screen->clip_rect.h / 2 + menus[0]->clip_rect.h;

	SDL_Surface* alpha = SDL_LoadBMP("E://Game//back.bmp");

	//SDL_FillRect(alpha, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_SetAlpha(alpha, SDL_SRCALPHA, 128);
	SDL_BlitSurface(alpha, NULL, screen, NULL);
	SDL_FreeSurface(alpha);
	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < NUMMENU ; i++)
					SDL_FreeSurface(menus[i]);
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < NUMMENU; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = 1;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
						}
					}
					else{

							if (selected[i])
							{
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
							}
						}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < NUMMENU;i++)
				if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
				{
					for (int j = 0; j < NUMMENU; j++)
						SDL_FreeSurface(menus[j]);
					return i;

				}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE){
					for (int j = 0; j < NUMMENU; j++)
						SDL_FreeSurface(menus[j]);
					return 0;
				}
				
			}
		}

		for (int i = 0; i<NUMMENU; i++)
			SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);

		SDL_Flip(screen);
		if (1000 / 30>(SDL_GetTicks() - time))
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
	}
}

SDL_Surface* load_image(const char* c, Uint32 colorkey = 0)
{
	SDL_Surface* tmp = SDL_LoadBMP(c);
	if (colorkey != 0)
	{
		SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, colorkey);
	}
	return tmp;
}

int main(int argc, char* argv[])
{
	SDL_Surface* screen, *icon;
	const int width = 640;
	const int FPS = 50;
	const int height = 480;
	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	icon = load_image("E://Game//bmp1.bmp");
	SDL_WM_SetIcon(icon, NULL);
	SDL_WM_SetCaption("Pong game", NULL);
	TTF_Font* font;
	TTF_Init();
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Music* music;
	Mix_Chunk* effect;
	music = Mix_LoadMUS("E://Game//music.wav");
	effect = Mix_LoadWAV("E://Game//hit.wav");
	Mix_PlayMusic(music, -1);
	font = TTF_OpenFont("E://Game//Arial.ttf", 20);
	SDL_Color color = { 0, 0, 0 };
	SDL_Event event;
	Uint32 start;
	bool running = true;
	bool arr[4] = { 0, 0, 0, 0 };
	paddle player1(load_image("E://Game//bmp.bmp"), 0, 225, 10, 50, 7);
	paddle player2(load_image("E://Game//bmp.bmp"), width - 10, 225, 10, 50, 7);
	ball ball1(load_image("E://Game//ball.bmp", SDL_MapRGB(screen->format, 0x00, 0xff, 0xff)), 320, 240, 20, 20, 3, 3);
	int i = showmenu(screen, font);
	if (i == 1)
		running = false;
	while (running)
	{
		start = SDL_GetTicks();
		//handle events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					arr[0] = 1;
					break;
				case SDLK_DOWN:
					arr[1] = 1;
					break;

				case SDLK_w:
					arr[2] = 1;
					break;
				case SDLK_s:
					arr[3] = 1;
					break;
				case SDLK_ESCAPE:
					int i = showmenu(screen,font);
					if (i == 1)
						running = false;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					arr[0] = 0;
					break;
				case SDLK_DOWN:
					arr[1] = 0;
					break;

				case SDLK_w:
					arr[2] = 0;
					break;
				case SDLK_s:
					arr[3] = 0;
					break;
				}
				break;
			}
		}
		//logic
		if (arr[0])
			player2.moveUp();
		else if (arr[1])
			player2.moveDown();
		if (arr[2])
			player1.moveUp();
		else if (arr[3])
			player1.moveDown();
		ball1.move(player1.getRect(), player2.getRect(), effect);
		switch (ball1.isOut())
		{
		case 1:
			player2.incpoint();
			player1.setBack(0, 225, 10, 50, 7);
			player2.setBack(width - 10, 225, 10, 50, 7);
			ball1.setBack(320, 240, 20, 20, 3, 3);
			break;
		case 2:
			player1.incpoint();
			player1.setBack(0, 225, 10, 50, 7);
			player2.setBack(width - 10, 225, 10, 50, 7);
			ball1.setBack(320, 240, 20, 20, 3, 3);
			break;
		}

		//render
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));
		player1.show();
		player2.show();
		ball1.show();

		char c[5];
		SDL_Rect tmp = { 10, 0 };
		sprintf_s(c, "%d", player1.getPoints());
		SDL_Surface* text = TTF_RenderText_Solid(font, c, color);
		SDL_BlitSurface(text, NULL, screen, &tmp);

		tmp.x = width - 40;
		sprintf_s(c, "%d", player2.getPoints());
		text = TTF_RenderText_Solid(font, c, color);
		SDL_BlitSurface(text, NULL, screen, &tmp);
		SDL_FreeSurface(text);

		SDL_Flip(screen);
		//regulate FPS
		if (1000 / FPS>(SDL_GetTicks() - start))
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
	//deinitailaze everything
	SDL_FreeSurface(icon);
	Mix_FreeMusic(music);
	Mix_FreeChunk(effect);
	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}