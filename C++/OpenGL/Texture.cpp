#include <SDL.h>
#include <glut.h>
#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363 
#endif #ifndef GL_CLAMP_TO_EDGE 
#define GL_CLAMP_TO_EDGE 0x812F

void drawCube(float size)
{
	float difamb[] = { 1.0, 0.5, 0.3, 1.0 };
	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
	// front face
	glNormal3f(0.0, 0.0, 1.0);
	//              glColor3f(1.0,0.0,0.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	// left face
	glNormal3f(-1.0, 0.0, 0.0);
	//              glColor3f(0.0,1.0,0.0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	// back face
	glNormal3f(0.0, 0.0, -1.0);
	//              glColor3f(0.0,0.0,1.0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	// right face
	glNormal3f(1.0, 0.0, 0.0);
	//              glColor3f(1.0,1.0,0.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// top face
	glNormal3f(0.0, 1.0, 0.0);
	//              glColor3f(1.0,0.0,1.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// bottom face
	glNormal3f(0.0, -1.0, 0.0);
	//              glColor3f(0.0,1.0,1.0);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();
}

float angle = 0.0;
const int triangle = 1;

unsigned int loadTexture(const char* filename)
{
	SDL_Surface* img = SDL_LoadBMP(filename);
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	return id;
}

unsigned int tex;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);  //background color and alpha
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	tex = loadTexture("E://Game//brick.bmp");
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 1.0, 1.0, 1.0);   // angle, x-axis, y-axis, z-axis
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 2.0);
	glVertex3f(-2.0, 2.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2.0, -2.0, 0.0);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(2.0, -2.0, 0.0);
	glTexCoord2f(2.0, 2.0);
	glVertex3f(2.0, 2.0, 0.0);
	glEnd();
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen;
	screen = SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE | SDL_OPENGL | SDL_FULLSCREEN);
	//      screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE|SDL_FULLSCREEN);
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