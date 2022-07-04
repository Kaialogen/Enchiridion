#include "../common.h"

#define MOVE_DELAY		 5

extern AtlasImage *getAtlasImage(char *filename, int required);
extern void moveEntity(Entity *e, int dx, int dy);
extern void updateFogOfWar(void);
extern void nextMonster(void);

extern App app;
extern Dungeon dungeon;
