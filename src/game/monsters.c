#include "monsters.h"

static void think(Entity *e);
static void lookForPlayer(Entity *e, Monster *m);
static void moveToPlayer(Entity *e, Monster *m);
static void patrol(Entity *e, Monster *m);

Entity *createRandomMonster(void);
void nextMonster(void);

void doMonsters(void)
{
	int processing;

	processing = 1;

	do
	{
		think(dungeon.currentEntity);
		nextMonster();

		processing = dungeon.animationTimer == 0 && dungeon.currentEntity != dungeon.player;
	}
	while (processing);
}

void nextMonster(void)
{
	int found;
	Entity *e;

	e = dungeon.currentEntity;

	do
	{
		e = e->next;

		if (e == NULL)
		{
			e = dungeon.entityHead.next;
		}

		found = !e->dead && (e->type == ET_MONSTER || e->type == ET_PLAYER);
	}
	while (!found);

	dungeon.currentEntity = e;
}

static void think(Entity *e)
{
	Monster *m;

	m = (Monster*) e->data;

	if (!m->alert)
	{
		lookForPlayer(e, m);
	}
	else if (hasLOS(e, dungeon.player->x, dungeon.player->y))
	{
		moveToPlayer(e, m);
	}
	else
	{
		patrol(e, m);
	}
}

static void lookForPlayer(Entity *e, Monster *m)
{
	m->alert = getDistance(e->x, e->y, dungeon.player->x, dungeon.player->y) <= m->visRange && hasLOS(e, dungeon.player->x, dungeon.player->y);
}

static void moveToPlayer(Entity *e, Monster *m)
{
	int dx, dy;

	createAStarRoute(e, dungeon.player->x, dungeon.player->y, &dx, &dy);

	moveEntity(e, dx, dy);

	m->patrolDest.x = dungeon.player->x;

	m->patrolDest.y = dungeon.player->y;
}

static void patrol(Entity *e, Monster *m)
{
	int dx, dy;

	if (dungeon.map[m->patrolDest.x][m->patrolDest.y].tile >= TILE_GROUND && dungeon.map[m->patrolDest.x][m->patrolDest.y].tile < TILE_WALL)
	{
		createAStarRoute(e, m->patrolDest.x, m->patrolDest.y, &dx, &dy);

		moveEntity(e, dx, dy);

		if (e->x == m->patrolDest.x && e->y == m->patrolDest.y)
		{
			m->patrolDest.x = rand() % MAP_WIDTH;

			m->patrolDest.y = rand() % MAP_HEIGHT;
		}
	}
	else
	{
		m->patrolDest.x = rand() % MAP_WIDTH;

		m->patrolDest.y = rand() % MAP_HEIGHT;
	}
}

void addMonsters(void)
{
	int i;
	
	for (i = 0; i < 3; i++)
	{
	addEntityToDungeon(initEntity("Cultist"));
	}
}

static Monster *createMonster(Entity *e)
{
	Monster *m;

	m = malloc(sizeof(Monster));
	memset(m, 0, sizeof(Monster));

	e->type = ET_MONSTER;
	e->solid = 1;
	e->data = m;

	return m;
}

void initCultist(Entity *e)
{
	Monster *m;

	m = createMonster(e);
	m->hp = m->maxHP = 1 + rand() % 4;
	m->defence = 1;
	m->minAttack = 1;
	m->maxAttack = 3;
	m->visRange = 12;

	STRCPY(e->name, "Cultist");
	e->texture = getAtlasImage("graphics/entities/Cultist.png", 1);
}
