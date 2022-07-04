#include "dungeon.h"

static void logic(void);
static void draw(void);
static void createDungeon(void);
static void doCamera(void);

void initDungeon(void)
{
	memset(&dungeon, 0, sizeof(Dungeon));

	initMap();
	
	initHud();

	createDungeon();

	app.delegate.logic = logic;

	app.delegate.draw = draw;
}

static void createDungeon(void)
{
	initEntities();

	initEntity("Player");

	if (1)
	{
		generateMap();
	}
	else
	{
		generateEmptyMap();
	}

	addMonsters();

	updateFogOfWar();
	
	dungeon.currentEntity = dungeon.player;
}

static void logic(void)
{
	doEntities();

	doHud();

	dungeon.animationTimer = MAX(dungeon.animationTimer - app.deltaTime, 0);

	if (dungeon.animationTimer <= FPS / 5)
	{
		dungeon.attackingEntity = NULL;
	}

	if (dungeon.animationTimer == 0)
	{
		if (dungeon.currentEntity == dungeon.player)
		{
			doPlayer();
		}
		else
		{
			doMonsters();
		}
	}

	doCamera();
}

static void doCamera(void)
{
	dungeon.camera.x = dungeon.player->x - MAP_RENDER_WIDTH / 2;
	dungeon.camera.y = dungeon.player->y - MAP_RENDER_HEIGHT / 2;
}

static void draw(void)
{
	drawMap();

	drawEntities();
	
	drawHud();
}
