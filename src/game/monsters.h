#include "../common.h"
#include "../json/cJSON.h"

extern void addEntityToDungeon(Entity *e);
extern void createAStarRoute(Entity *e, int x, int y, int *dx, int *dy);
extern AtlasImage *getAtlasImage(char *filename, int required);
extern int getDistance(int x1, int y1, int x2, int y2);
extern int hasLOS(Entity *src, int x2, int y2);
extern Entity *initEntity(char *name);
extern void moveEntity(Entity *e, int dx, int dy);
extern void nextMonster(void);

extern Dungeon dungeon;
