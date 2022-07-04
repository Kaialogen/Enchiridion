#include "hud.h"

static void drawBloodSplat(void);
static void drawTopBar(void);

static AtlasImage *bloodSplatTexture;
static SDL_Point bloodSplat;
static double bloodSplatTimer;

void initHud(void)
{
	bloodSplatTexture = getAtlasImage("graphics/entities/blood.png", 1);

	bloodSplatTimer = 0;
}

void doHud(void)
{
	bloodSplatTimer = MAX(bloodSplatTimer - app.deltaTime, 0);

	dungeon.animationTimer = MAX(dungeon.animationTimer, bloodSplatTimer);
}

void setBloodSplat(int x, int y)
{
	bloodSplat.x = x;
	bloodSplat.y = y;

	bloodSplatTimer = FPS / 5;
}

void drawHud(void)
{
	drawBloodSplat();
	
	drawTopBar();
}

static void drawTopBar(void)
{
	char text[16];
	Monster *m;
	double healthPercent;

	drawRect(0, 0, SCREEN_WIDTH, 30, 0, 0, 0, 160);

	m = (Monster*) dungeon.player->data;

	healthPercent = (1.0 * m->hp) / m->maxHP;

	sprintf(text, "HP : %d / %d", m->hp, m->maxHP);

	if (healthPercent <= 0.2)
	{
		drawText(text, 10, 0, 255, 64, 64, TEXT_ALIGN_LEFT, 0);
	}
	else if (healthPercent <= 0.5)
	{
		drawText(text, 10, 0, 255, 255, 0, TEXT_ALIGN_LEFT, 0);
	}
	else
	{
		drawText(text, 10, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
	}

	sprintf(text, "Attack : %d - %d", m->minAttack, m->maxAttack);
	drawText(text, 300, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

	sprintf(text, "Defence : %d", m->defence);
	drawText(text, 600, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
}

static void drawBloodSplat(void)
{
	int x, y;

	if (bloodSplatTimer > 0)
	{
		x = (bloodSplat.x - dungeon.camera.x);
		y = (bloodSplat.y - dungeon.camera.y);

		blitAtlasImage(bloodSplatTexture, (x * MAP_TILE_SIZE) + MAP_RENDER_X, (y * MAP_TILE_SIZE) + MAP_RENDER_Y, 0, SDL_FLIP_NONE);
	}
}
