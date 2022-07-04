#include "player.h"

static double moveDelay;

void initPlayer(Entity *e)
{
	Monster *m;

	m = malloc(sizeof(Monster));
	memset(m, 0, sizeof(Monster));

	m->hp = m->maxHP = 25;
	m->defence = 4;
	m->minAttack = 1;
	m->maxAttack = 4;
	
	STRCPY(e->name, "Player");
	e->type = ET_PLAYER;
	e->texture = getAtlasImage("graphics/entities/player.png", 1);
	e->data = m;

	dungeon.player = e;

	moveDelay = 0;
}



void doPlayer(void)
{
	int dx, dy;

	moveDelay = MAX(moveDelay - app.deltaTime, 0);

	if (moveDelay == 0)
	{
		dx = dy = 0;

		if (app.keyboard[SDL_SCANCODE_W])
		{
			dy = -1;
		}

		if (app.keyboard[SDL_SCANCODE_S])
		{
			dy = 1;
		}

		if (app.keyboard[SDL_SCANCODE_A])
		{
			dx = -1;
		}

		if (app.keyboard[SDL_SCANCODE_D])
		{
			dx = 1;
		}

		if (dx != 0 || dy != 0)
		{
			moveEntity(dungeon.player, dx, dy);

			moveDelay = MOVE_DELAY;

			updateFogOfWar();
			
			nextMonster();

		}
	}
}
