#include "headers/core.h"

bool init() {
	// init vars
	quit = false;

	// init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	// calculate TILE_HW
	TILE_H = 1.0 / ((SCREEN_HEIGHT / 2.0f) / TILE_DRAW_SIZE);
	TILE_W = 1.0 / ((SCREEN_WIDTH  / 2.0f) / TILE_DRAW_SIZE);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);
	if (screen == NULL) {
		return false;
	}

	// Initialize OpenGL
	if (initOpenGL() == false) {
		return false;
	}

	// caption
	SDL_WM_SetCaption("OpenGL Test", NULL);

	player1 = new CXBOXController(1);
	pressed = false;

	return true;
}

bool initOpenGL() {
	// Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// Enable textures
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	// free opengl textures
	//glDeleteTextures(1, (GLuint*) &testTexture);
	//glDeleteTextures(1, (GLuint*) &tiles);
	delete playerTexture;
	delete tile;

	// clean up SDL
	SDL_Quit();

	delete player1;
}

/****** main *******/
void mainLoop() {
	//testTexture = loadTexture("images/red_player_sprite.png");
	//tiles       = loadTexture("images/tiles/test_tile.png");
	playerTexture = new GL_Texture("images/red_player_sprite.png");
	tile          = new GL_Texture("images/tiles/test_tile.png");

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

		if (player1->IsConnected()) {
			if (player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START) {
				std::cout << "Start was pressed\n\n";
				quit = true;
			}
			if (player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
				player1->Vibrate(0, 0);
			}
			if (player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) {
				player1->Vibrate(XBOX_VIBRATE_LIGHT, XBOX_VIBRATE_LIGHT);
			}
			if (player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X) {
				player1->Vibrate(XBOX_VIBRATE_MEDIUM, XBOX_VIBRATE_MEDIUM);
			}
			if (player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
				player1->Vibrate(XBOX_VIBRATE_HEAVY, XBOX_VIBRATE_HEAVY);
			}
			if (player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) {
				if (!pressed) {
					std::cout << "B was pressed: " << player1->GetState().Gamepad.sThumbLY << "\n";
					pressed = true;
				}
			}
			else {
				pressed = false;
			}
		}
		else {
			std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
			std::cout << "Press Any Key To Exit.";
			std::cin.get();
			break;
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

	// draw grass
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 8; j++) {
			drawTile(i, (j * 2) + (i % 2), tile->texture);
		}
	}

	playerTexture->drawTile(2, 2, 1, 2);

	// draw characters
	/*drawTile(0, 0, playerTexture->texture);
	drawTile(2, 2, playerTexture->texture);
	drawTile(4, 4, playerTexture->texture);
	drawTile(6, 6, playerTexture->texture);
	drawTile(8, 8, playerTexture->texture);
	drawTile(10, 6, playerTexture->texture);
	drawTile(12, 4, playerTexture->texture);
	drawTile(14, 2, playerTexture->texture);
	drawTile(16, 0, playerTexture->texture);
	for (int i = 4; i < 13; i++) {
		drawTile(i, 3, playerTexture->texture);
	}*/

    // Update screen
    SDL_GL_SwapBuffers();
}

void drawTile(int xInt, int yInt, GLuint texture) {
	draw(xInt * (TILE_DRAW_SIZE * 2), yInt * (TILE_DRAW_SIZE * 2), texture);
}

void draw(int xInt, int yInt, GLuint texture) {
	GLfloat x, y;

	x = ((xInt - SCREEN_WIDTH)  * 1.0) / SCREEN_WIDTH;
	y = ((yInt - SCREEN_HEIGHT) * 1.0) / SCREEN_HEIGHT;

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0.25);
		glVertex2f(x, y);
		glTexCoord2f(0.25, 0.25);
		glVertex2f( x + TILE_W, y);
		glTexCoord2f(0.25, 0);
		glVertex2f( x + TILE_W,  y + TILE_H);
		glTexCoord2f(0, 0);
		glVertex2f(x,  y + TILE_H);
	glEnd();
}


/**** loading ******/

/*int createTexture(std::string a, std::string b) {
	SDL_Surface *imageA = IMG_Load(a.c_str());
	SDL_Surface *imageB = IMG_Load(b.c_str());

	SDL_Surface *image = SDL_CreateRGBSurface(0, 128, 128, 32, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

	SDL_Rect source, dest;
	source.h = 128;
	source.w = 128;
	source.x = 0;
	source.y = 0;
	dest.h = 128;
	dest.w = 128;
	dest.x = 0;
	dest.y = 0;

	SDL_BlitSurface(imageB, &source, image, &dest);
	SDL_Flip(image);

	SDL_DisplayFormatAlpha(image);

	unsigned object(0);
	glGenTextures(1, &object);
	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	
	SDL_FreeSurface(imageA);
	SDL_FreeSurface(imageB);
	SDL_FreeSurface(image);
	
	return object;
}*/