#include "../common.h"

extern void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip);
extern AtlasImage *getAtlasImage(char *filename, int required);

extern Dungeon dungeon;
