#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include "constants.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "Timer.h"
#include "../../xbox360/CXBOXController.h"
#include <iostream>
#include <string>
#include "GL_Texture.h"

// openGL Constants
static GLfloat TILE_H;
static GLfloat TILE_W;

static bool quit;
static SDL_Event event;
static Timer fps;
static CXBOXController* player1;
static bool pressed;
static SDL_Surface* screen;

// test
static GL_Texture* playerTexture;
static GL_Texture* tile;
/*static int testTexture;
static int tiles;*/

// init
bool init();
void cleanup();
bool initOpenGL();

// main 
void mainLoop();

// events
void handleKeys(unsigned char key, int x, int y);

// drawing
void update();
void render();
void draw(int, int, GLuint);
void drawTile(int, int, GLuint);

#endif // CORE_H_INCLUDED