#include "entities.h"

static int isBlocked(Entity *e, int x, int y);
static int isOccupied(int x, int y);
static void drawEntity(Entity *e);
static int drawComparator(const void *a, const void *b);

static Entity *entsToDraw[MAX_ENTS_TO_DRAW];

void initEntities(void)
{
	dungeon.entityTail = &dungeon.entityHead;
	dungeon.deadTail = &dungeon.deadHead;
}

void doEntities(void)
{
	Entity *e, *prev;
	int updateFOW, i;

	updateFOW = 0;

	i = 0;

	memset(entsToDraw, 0, sizeof(Entity*) * MAX_ENTS_TO_DRAW);

	prev = &dungeon.entityHead;

	for (e = dungeon.entityHead.next ; e != NULL ; e = e->next)
	{
		if (!e->dead)
		{
			if (dungeon.map[e->x][e->y].visible && i < MAX_ENTS_TO_DRAW)
			{
				entsToDraw[i++] = e;
			}
		}
		else
		{
			if (e->solid)
			{
				updateFOW = 1;
			}

			prev->next = e->next;

			if (e == dungeon.entityTail)
			{
				dungeon.entityTail = prev;
			}

			e->next = NULL;

			dungeon.deadTail->next = e;
			dungeon.deadTail = e;

			e = prev;
		}

		prev = e;
	}

	qsort(entsToDraw, i, sizeof(Entity*), drawComparator);

	if (updateFOW)
	{
		updateFogOfWar();
	}
}

void moveEntity(Entity *e, int dx, int dy)
{
	int x, y;

	x = e->x + dx;
	y = e->y + dy;

	if (dx < 0)
	{
		e->facing = FACING_LEFT;
	}
	else if (dx > 0)
	{
		e->facing = FACING_RIGHT;
	}

	if (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT && dungeon.map[x][y].tile >= TILE_GROUND && dungeon.map[x][y].tile < TILE_WALL && !isBlocked(e, x, y))
	{
		e->x = x;
		e->y = y;
	}
}



void drawEntities(void)
{
	Entity *e;
	int i;

	for (i = 0, e = entsToDraw[0] ; i < MAX_ENTS_TO_DRAW && e != NULL ; e = entsToDraw[++i])
	{
		drawEntity(e);
	}
}

Entity *getEntityAt(int x, int y)
{
	Entity *e, *rtn;

	rtn = NULL;

	for (e = dungeon.entityHead.next ; e != NULL ; e = e->next)
	{
		if (e->x == x && e->y == y)
		{
			if (e->solid)
			{
				return e;
			}

			rtn = e;
		}
	}

	return rtn;
}

static void drawEntity(Entity *e)
{
	int x, y;

	x = (e->x - dungeon.camera.x);
	y = (e->y - dungeon.camera.y);

	if (x >= 0 && y >= 0 && x < MAP_RENDER_WIDTH && y < MAP_RENDER_HEIGHT)
	{
		x *= MAP_TILE_SIZE;
		y *= MAP_TILE_SIZE;

		if (e == dungeon.attackingEntity)
		{
			x += dungeon.attackDir.x * (MAP_TILE_SIZE / 2);
			y += dungeon.attackDir.y * (MAP_TILE_SIZE / 2);
		}

		blitAtlasImage(e->texture, x + MAP_RENDER_X, y + MAP_RENDER_Y, 0, e->facing == FACING_RIGHT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}
}

static int isBlocked(Entity *e, int x, int y)
{
	Entity *other;

	for (other = dungeon.entityHead.next ; other != NULL ; other = other->next)
	{
		if (other->x == x && other->y == y)
		{
			switch (other->type)
			{
				case ET_PLAYER:
				case ET_MONSTER:
					doMeleeAttack(e, other);
					return 1;

				default:
					break;
			}
		}
	}

	return 0;
}

void addEntityToDungeon(Entity *e)
{
	int x, y, ok;

	do
	{
		x = 1 + rand() % (MAP_WIDTH - 2);
		y = 1 + rand() % (MAP_HEIGHT - 2);

		ok = dungeon.map[x][y].tile > TILE_HOLE && dungeon.map[x][y].tile < TILE_WALL && !isOccupied(x, y);
	}
	while (!ok);

	e->x = x;
	e->y = y;
}

static int isOccupied(int x, int y)
{
	Entity *e;

	for (e = dungeon.entityHead.next ; e != NULL ; e = e->next)
	{
		if (e->x == x && e->y == y)
		{
			return 1;
		}
	}

	return 0;
}

static int drawComparator(const void *a, const void *b)
{
	Entity *e1, *e2;

	e1 = *((Entity**) a);
	e2 = *((Entity**) b);

	if (e1 == dungeon.attackingEntity || e2 == dungeon.attackingEntity)
	{
		return e1 == dungeon.attackingEntity ? 1 : -1;
	}

	return e2->type - e1->type;
}
