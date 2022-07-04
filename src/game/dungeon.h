#include "../common.h"

extern void addMonsters(void);
extern void doEntities(void);
extern void doHud(void);
extern void doMonsters(void);
extern void doPlayer(void);
extern void drawEntities(void);
extern void drawHud(void);
extern void drawMap(void);
extern void generateEmptyMap(void);
extern void generateMap(void);
extern void initEntities(void);
extern Entity *initEntity(char *name);
extern void initHud(void);
extern void initMap(void);
extern void updateFogOfWar(void);

extern App app;
extern Dungeon dungeon;
