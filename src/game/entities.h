#include "../common.h"

#define MAX_ENTS_TO_DRAW    64

extern void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip);
extern void doMeleeAttack(Entity *attacker, Entity *target);
extern void updateFogOfWar(void);

extern Dungeon dungeon;
