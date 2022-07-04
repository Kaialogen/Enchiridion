#include "common.h"

extern void cleanup(void);
extern void doInput(void);
extern void initDungeon(void);
extern void initGameSystem(void);
extern void initSDL(void);
extern void prepareScene(void);
extern void presentScene(void);

App app;
Dungeon dungeon;
