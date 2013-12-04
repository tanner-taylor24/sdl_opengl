#ifndef GL_TEXTURE_H_INCLUDED
#define GL_TEXTURE_H_INCLUDED

#include "SDL_opengl.h"
#include "SDL.h"
#include "SDL_Image.h"
#include <string>
#include "constants.h"

class GL_Texture {
	public:
		int h, w;
		GLuint texture;
		GLfloat TILE_W, TILE_H;

		GL_Texture(std::string);
		~GL_Texture();

		void draw(int, int, int, int);
		void drawTile(int, int, int, int);

	private:
		int loadTexture(std::string);
};

#endif // GL_TEXTURE_H_INCLUDED