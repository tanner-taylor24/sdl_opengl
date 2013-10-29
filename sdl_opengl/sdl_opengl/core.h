#include "constants.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "Timer.h"

static bool quit;
static SDL_Event event;
static Timer fps;

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