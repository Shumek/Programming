#include "functions.h"

float angle = 0.0;

int cube;
void init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);      //background color and alpha
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	cube = loadObject("E://Game//td2.obj");
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.6);
	float color[] = { 0.5, 0.5, 0.5, 1.0 };
	glFogfv(GL_FOG_COLOR, color);
	float col[] = { 1., 1., 1., 1. };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float pos[] = { -1.0, 1.0, -2.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 1.0, 1.0, 1.0);
	glCallList(cube);

}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen;
	screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE | SDL_OPENGL);
	bool running = true;
	const int FPS = 30;
	Uint32 start;
	SDL_Event event;
	init();
	while (running) {
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					break;
				}
				break;
			}
		}

		display();
		SDL_GL_SwapBuffers();
		angle += 0.5;
		if (angle > 360)
			angle -= 360;
		if (1000 / FPS > SDL_GetTicks() - start)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
	SDL_Quit();
	return 0;
}