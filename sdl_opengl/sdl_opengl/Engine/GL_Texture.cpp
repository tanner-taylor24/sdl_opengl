#include "headers\GL_Texture.h"

GL_Texture::GL_Texture(std::string file) {
	TILE_H = 1.0 / ((SCREEN_HEIGHT / 2.0f) / TILE_DRAW_SIZE);
	TILE_W = 1.0 / ((SCREEN_WIDTH  / 2.0f) / TILE_DRAW_SIZE);

	texture = loadTexture(file);
}

GL_Texture::~GL_Texture() {
	glDeleteTextures(1, (GLuint*) &texture);
}

void GL_Texture::drawTile(int xInt, int yInt, int srcX, int srcY) {
	draw(xInt * (TILE_DRAW_SIZE * 2), yInt * (TILE_DRAW_SIZE * 2), srcX, srcY);
}

void GL_Texture::draw(int xInt, int yInt, int srcX, int srcY) {
	GLfloat x, y, srcXf, srcYf, srcW, srcH;

	x = ((xInt - SCREEN_WIDTH)  * 1.0) / SCREEN_WIDTH;
	y = ((yInt - SCREEN_HEIGHT) * 1.0) / SCREEN_HEIGHT;

	// percentage of tile size -- used to add to coordinates of texture
	srcW = (TILE_SIZE * 1.0f) / w;
	srcH = (TILE_SIZE * 1.0f) / h;

	// get coordinates
	srcXf = (srcX * TILE_SIZE * 1.0f) / w;
	srcYf = (srcY * TILE_SIZE * 1.0f) / h;

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glTexCoord2f(srcXf, srcYf + srcH);
		glVertex2f(x, y);
		glTexCoord2f(srcXf + srcW, srcYf + srcH);
		glVertex2f( x + TILE_W, y);
		glTexCoord2f(srcXf + srcW, srcYf);
		glVertex2f( x + TILE_W,  y + TILE_H);
		glTexCoord2f(srcXf, srcYf);
		glVertex2f(x,  y + TILE_H);
	glEnd();
}

/* private */
int GL_Texture::loadTexture(std::string filename) {
	SDL_Surface *image = IMG_Load(filename.c_str());
	SDL_DisplayFormatAlpha(image);

	//printf("h: %d w: %d\n\n", image->h, image->w);
	h = image->h;
	w = image->w;

	unsigned object(0);
	glGenTextures(1, &object);
	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	SDL_FreeSurface(image);
	
	return object;
}