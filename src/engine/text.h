#include "../common.h"
#include "SDL_ttf.h"

#define FONT_SIZE            32
#define FONT_TEXTURE_SIZE    512
#define NUM_GLYPHS           128
#define MAX_WORD_LENGTH      32
#define MAX_LINE_LENGTH      1024

extern SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface);

extern App app;
