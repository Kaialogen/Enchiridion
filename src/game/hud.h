#include "../common.h"

extern void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip);
extern AtlasImage *getAtlasImage(char *filename, int required);
extern void drawRect(int x, int y, int w, int h, int r, int g, int b, int a);
extern void drawText(char *text, int x, int y, int r, int g, int b, int align, int maxWidth);
extern Entity *getEntityAt(int x, int y);

extern App app;
extern Dungeon dungeon;
