#include "core.h"

bool init() {
	// init vars
	quit = false;

	// init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL) == NULL) {
		return false;
	}

	// Initialize OpenGL
	if (initOpenGL() == false) {
		return false;
	}

	// caption
	SDL_WM_SetCaption("OpenGL Test", NULL);

	return true;
}

bool initOpenGL() {
	// Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Check for error
    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
        printf("Error initializing OpenGL! %s\n", gluErrorString(error));
        return false;
    }

	return true;
}

void cleanup() {
	// clean up SDL
	SDL_Quit();
}

/****** main *******/
void mainLoop() {
	// While there are events to handle
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				//Handle keypress with current mouse position
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);
				handleKeys(event.key.keysym.unicode, x, y);
			}
		}

		//Run frame update
		update();

		//Render frame
		render();
        
		//Cap the frame rate
		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}
}

/****** events *******/
void handleKeys(unsigned char key, int x, int y) {
    //Toggle quad
    if (key == 'q') {
    }
}


/****** drawing *******/
void update() {
}

void render() {
	// Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Render quad
    glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.75f,  0.75f);
    glEnd();

    // Update screen
    SDL_GL_SwapBuffers();
}

