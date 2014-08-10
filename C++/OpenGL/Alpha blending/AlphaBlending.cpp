#include "functions.h"

float angle = 0.0;

int cube;
void init()
{
	glClearColor(.5, .5, .5, 1.);     
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	cube = loadObject("E://Game//td2.obj");
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float col[] = { 1., 1., 1., 1. };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float pos[] = { -1.0, 1.0, -2.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	
	glColor4f(0., 0., 1., 1.); 
	glVertex3f(-2., 2., -10.);
	glVertex3f(-2., -2., -10.);
	glVertex3f(2., -2., -10.);
	glVertex3f(2., 2., -10.);

	glColor4f(1., 0., 0., .5);
	glVertex3f(-1., 3., -9.);
	glVertex3f(-1., -3., -9.);
	glVertex3f(3., -3., -9.);
	glVertex3f(3., 3., -9.);
	glEnd();
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